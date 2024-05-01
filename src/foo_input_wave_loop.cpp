// SPDX-License-Identifier: MIT
// Copyright (c) 2014-2024 Suwasaki Ryu
//----------------------------------------------------------------------------
// foo_input_wave_loop (foobar2000 component)
// foo_input_wave_loop.cpp
//
// References:
//   * input_raw.cpp (foobar2000 SDK sample)
//   * Multimedia Programming Interface and Data Specifications 1.0
//       http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/riffmci.pdf
//   * Microsoft Multimedia Standards Update, New Multimedia Data Types and Data Techniques, Revision: 3.0
//       http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/RIFFNEW.pdf
//
// Changes:
//   1.1 (1 May 2024) : Support x64 platform, based on foobar2000 SDK 2023-09-23
//   1.0 (2 May 2014) : First release, based on foobar2000 SDK 2011-03-11
//
//----------------------------------------------------------------------------

#ifdef __cplusplus
#include <helpers/foobar2000+atl.h>
#endif

#include "../SDK/foobar2000.h"
#include "../helpers/helpers.h"
#include "foo_input_wave_loop.h"

class input_wave_loop : public input_stubs
{
public:
	input_wave_loop()
	{
		 pFile                 = NULL;
		 fileStats.m_size      = 0;
		 fileStats.m_timestamp = 0;

		 waveFileInfo.clear();
	}

	~input_wave_loop()
	{
	}

	// Opens specified file for info read / decoding / info write. This is called only once, immediately after object creation,
	// before any other methods, and no other methods are called if open() fails.
	void open(service_ptr_t<file> p_filehint, const char* p_path, t_input_open_reason p_reason, abort_callback& p_abort)
	{
		FB2K_console_formatter() << "foo_input_wave_loop : file = " << p_path;

		if (p_reason == input_open_info_write)
		{
			throw exception_io_unsupported_format();
		}

		// p_filehint may be null, hence next line
		pFile = p_filehint;

		// if pFile is null, opens file with appropriate privileges for our operation
		// (read/write for writing tags, read-only otherwise).
		input_open_file_helper(pFile, p_path, p_reason, p_abort);

		fileStats = pFile->get_stats(p_abort);

		if (fileStats.m_size == filesize_invalid)
		{
			throw exception_io_unsupported_format();
		}

		if (!GetWaveFileInfo(pFile, fileStats.m_size, waveFileInfo, p_abort))
		{
			throw exception_io_unsupported_format();
		}

		FB2K_console_formatter() << "foo_input_wave_loop : samplingRate = "        << waveFileInfo.samplingRate;
		FB2K_console_formatter() << "foo_input_wave_loop : channels = "            << waveFileInfo.channels;
		FB2K_console_formatter() << "foo_input_wave_loop : quantizationBitRate = " << waveFileInfo.quantizationBitRate;
		FB2K_console_formatter() << "foo_input_wave_loop : bytesPerSample = "      << waveFileInfo.bytesPerSample;
		FB2K_console_formatter() << "foo_input_wave_loop : dataOffset = "          << waveFileInfo.dataOffset;
		FB2K_console_formatter() << "foo_input_wave_loop : dataSize = "            << waveFileInfo.dataSize;
		FB2K_console_formatter() << "foo_input_wave_loop : sampleNum = "           << waveFileInfo.sampleNum;
		FB2K_console_formatter() << "foo_input_wave_loop : loop = "                << waveFileInfo.loop;
		FB2K_console_formatter() << "foo_input_wave_loop : loopStar = "            << waveFileInfo.loopStart;
		FB2K_console_formatter() << "foo_input_wave_loop : loopEnd = "             << waveFileInfo.loopEnd;
		FB2K_console_formatter() << "foo_input_wave_loop : smplLoop = "            << waveFileInfo.smplLoop;
		FB2K_console_formatter() << "foo_input_wave_loop : smplLoopStart = "       << waveFileInfo.smplLoopStart;
		FB2K_console_formatter() << "foo_input_wave_loop : smplLoopEnd = "         << waveFileInfo.smplLoopEnd;
		FB2K_console_formatter() << "foo_input_wave_loop : id3Loop = "             << waveFileInfo.id3Loop;
		FB2K_console_formatter() << "foo_input_wave_loop : id3LoopStart = "        << waveFileInfo.id3LoopStart;
		FB2K_console_formatter() << "foo_input_wave_loop : id3LoopLength = "       << waveFileInfo.id3LoopLength;
	}

	// See: input_info_reader::get_info(). Valid after open() with any reason.
	void get_info(file_info& p_info, abort_callback& p_abort)
	{
		t_uint32 rate_kbps = (waveFileInfo.quantizationBitRate * waveFileInfo.channels * waveFileInfo.samplingRate + 500) / 1000;

		p_info.info_set_int("samplerate",    waveFileInfo.samplingRate);
		p_info.info_set_int("channels",      waveFileInfo.channels);
		p_info.info_set_int("bitspersample", waveFileInfo.quantizationBitRate);
		p_info.info_set_int("bitrate",       rate_kbps);

		p_info.info_set("codec",    "PCM");
		p_info.info_set("encoding", "lossless");

		t_uint32 len_sec = waveFileInfo.dataSize / (waveFileInfo.bytesPerSample * waveFileInfo.samplingRate);
		if (waveFileInfo.loop > 0)
		{
			len_sec = 24 * 60 * 60;
		}
		p_info.set_length(len_sec);
	}

	// See: input_info_reader_v2::get_stats2()
	t_filestats2 get_stats2(unsigned f, abort_callback& a)
	{
		return pFile->get_stats2_(f, a);
	}

	// See: input_info_reader::get_file_stats(). Valid after open() with any reason.
	t_filestats get_file_stats(abort_callback& p_abort)
	{
		return pFile->get_stats(p_abort);
	}

	// See: input_decoder::initialize(). Valid after open() with input_open_decode reason.
	void decode_initialize(unsigned p_flags, abort_callback& p_abort)
	{
		console::info("foo_input_wave_loop : play start");

		pFile->seek(waveFileInfo.dataOffset, p_abort);

		playPos = 0;

		playBuffer.set_size(deltaReadSize * waveFileInfo.bytesPerSample);
	}

	// See: input_decoder::run(). Valid after decode_initialize().
	bool decode_run(audio_chunk& p_chunk, abort_callback& p_abort)
	{
		t_uint32 samplePlayEnd;


		if (waveFileInfo.loop && (playPos <= waveFileInfo.loopEnd))
		{
			samplePlayEnd = waveFileInfo.loopEnd + 1;
		}
		else
		{
			samplePlayEnd = waveFileInfo.sampleNum;
		}


		t_size readSample = min(deltaReadSize, samplePlayEnd - playPos);
		t_size readSize   = readSample * waveFileInfo.bytesPerSample;

		if (readSize == 0)
		{
			// EOF
			console::info("foo_input_wave_loop : play stop (EOF)");
			return false;
		}


		t_size readSizeDone   = pFile->read(playBuffer.get_ptr(), readSize, p_abort);
		t_size readSampleDone = readSizeDone / waveFileInfo.bytesPerSample;

		if (readSizeDone == 0)
		{
			// read fail
			console::info("foo_input_wave_loop : play stop (read error)");
			return false;
		}

		playPos += (t_uint32)readSampleDone;

		p_chunk.set_data_fixedpoint(playBuffer.get_ptr(), readSizeDone, waveFileInfo.samplingRate,
		                            waveFileInfo.channels, waveFileInfo.quantizationBitRate,
		                            audio_chunk::g_guess_channel_config(waveFileInfo.channels));

		if (playPos >= samplePlayEnd)
		{
			if (waveFileInfo.loop && (playPos <= waveFileInfo.loopEnd + 1))
			{
				console::info("foo_input_wave_loop : sample loop!");

				pFile->seek(waveFileInfo.dataOffset + waveFileInfo.loopStart * waveFileInfo.bytesPerSample, p_abort);

				playPos = waveFileInfo.loopStart;
			}
		}

		// processed successfully, no EOF
		return true;
	}

	// See: input_decoder::seek(). Valid after decode_initialize().
	void decode_seek(double p_seconds, abort_callback& p_abort)
	{
		// throw exceptions if someone called decode_seek() despite of our input having reported itself as nonseekable.
		pFile->ensure_seekable();

		if (waveFileInfo.loop == 0)
		{
			// IMPORTANT: convert time to sample offset with proper rounding!
			//            audio_math::time_to_samples does this properly for you.
			t_uint32 targetPlayPos = (t_uint32)audio_math::time_to_samples(p_seconds, waveFileInfo.samplingRate);

			if (targetPlayPos >= (waveFileInfo.sampleNum - 1))
			{
				targetPlayPos = waveFileInfo.sampleNum - 1;
			}

			pFile->seek(waveFileInfo.dataOffset + targetPlayPos * waveFileInfo.bytesPerSample, p_abort);

			playPos = targetPlayPos;
		}
	}

	// See: input_decoder::can_seek(). Valid after decode_initialize().
	bool decode_can_seek()
	{
		return pFile->can_seek();
	}

	// See: input_decoder::get_dynamic_info(). Valid after decode_initialize().
	bool decode_get_dynamic_info(file_info& p_out, double& p_timestamp_delta)
	{
		// deals with dynamic information such as VBR bitrates
		return false;
	}

	// See: input_decoder::get_dynamic_info_track(). Valid after decode_initialize().
	bool decode_get_dynamic_info_track(file_info& p_out, double& p_timestamp_delta)
	{
		// deals with dynamic information such as track changes in live streams
		return false;
	}

	// See: input_decoder::on_idle(). Valid after decode_initialize().
	void decode_on_idle(abort_callback& p_abort)
	{
		pFile->on_idle(p_abort);
	}

	// See: input_info_writer::set_info(). Note that input_info_writer::commit() call isn't forwarded
	// because it's useless in case of non-multitrack-enabled inputs. Valid after open() with input_open_info_write reason.
	void retag(const file_info& p_info, abort_callback& p_abort)
	{
		throw exception_io_unsupported_format();
	}

	// See: input_info_writer_v2::remove_tags().
	void remove_tags(abort_callback&)
	{
		throw exception_tagging_unsupported();
	}

	// See: input_entry::is_our_content_type().
	static bool g_is_our_content_type(const char* p_content_type)
	{
		// match against supported mime types here
		return false;
	}

	// See: input_entry::is_our_path().
	static bool g_is_our_path(const char* p_path, const char* p_extension)
	{
		return stricmp_utf8(p_extension, "wavloop") == 0;
	}

	// See: input_entry_v2::get_name().
	static const char* g_get_name()
	{
		return "foo_input_wave_loop";
	}

	// See: input_entry_v2::get_guid().
	static const GUID g_get_guid()
	{
		static const GUID I_am_foo_sample_and_this_is_my_decoder_GUID = { 0xdd9720d5, 0x0db3, 0x4870,{ 0x89, 0x90, 0x7a, 0x6c, 0x92, 0x31, 0x65, 0x08 } };

		return I_am_foo_sample_and_this_is_my_decoder_GUID;
	}



private:
	enum
	{
		deltaReadSize = 1024,
	};


	service_ptr_t<file>   pFile;
	t_filestats           fileStats;
	WaveFileInfo          waveFileInfo;

	pfc::array_t<t_uint8> playBuffer;
	t_uint32              playPos;


	bool GetWaveFileInfo(service_ptr_t<file> file, t_filesize fileSize, WaveFileInfo& info, abort_callback& p_abort)
	{
		info.clear();

		// Read RIFF Header
		if (fileSize < sizeof(RiffListCkHeader))
		{
			return false;
		}

		RiffListCkHeader header;
		file->seek(0, p_abort);
		file->read(&header, sizeof(header), p_abort);

		if (!((header.ID[0] == 'R') && (header.ID[1] == 'I') && (header.ID[2] == 'F') && (header.ID[3] == 'F')))
		{
			console::info("foo_input_wave_loop : Illegal WAV file (RIFF header ID)");
			return false;
		}

		if (header.size != (fileSize - sizeof(RiffCkHeader)))
		{
			console::info("foo_input_wave_loop : Illegal WAV file (RIFF header size)");
			return false;
		}

		if (!((header.formType[0] == 'W') && (header.formType[1] == 'A') && (header.formType[2] == 'V') && (header.formType[3] == 'E')))
		{
			console::info("foo_input_wave_loop : Illegal WAV file (RIFF form type)");
			return false;
		}


		t_uint32 filePos       = sizeof(RiffListCkHeader);
		bool     fmtFound      = false;
		bool     dataFound     = false;
		bool     smplLoopFound = false;
		bool     id3LoopFound  = false;

		// read each chunk
		while(filePos < fileSize)
		{
			RiffCkHeader ckHeader;
			file->seek(filePos, p_abort);
			file->read(&ckHeader, sizeof(ckHeader), p_abort);

			if (   (!fmtFound)
				&& (ckHeader.ID[0] == 'f') && (ckHeader.ID[1] == 'm') && (ckHeader.ID[2] == 't') && (ckHeader.ID[3] == ' '))
			{
				// WAVE <fmt-ck> chunk ("fmt ")
				WaveFmtCkPcm fmtCk;
				file->seek(filePos, p_abort);
				file->read(&fmtCk, sizeof(fmtCk), p_abort);

				if (fmtCk.formatTag != 1) // must WAVE_FORMAT_PCM
				{
					console::info("foo_input_wave_loop : Illegal WAV file (not PCM format)");
					return false;
				}

				info.samplingRate        = fmtCk.samplesPerSec;
				info.channels            = fmtCk.channels;
				info.quantizationBitRate = fmtCk.bitsPerSample;
				info.bytesPerSample      = fmtCk.blockAlign;

				fmtFound = true;
			}
			else if (   (!dataFound)
			         && (ckHeader.ID[0] == 'd') && (ckHeader.ID[1] == 'a') && (ckHeader.ID[2] == 't') && (ckHeader.ID[3] == 'a'))
			{
				// WAVE <data-ck> chunk ("data")
				info.dataOffset = filePos + sizeof(RiffCkHeader);
				info.dataSize   = ckHeader.size;

				dataFound = true;
			}
			else if (   (!smplLoopFound)
			         && (ckHeader.ID[0] == 's') && (ckHeader.ID[1] == 'm') && (ckHeader.ID[2] == 'p') && (ckHeader.ID[3] == 'l'))
			{
				// WAVE <sample-ck> chunk ("smpl")
				WaveSampleCk smplCk;
				file->seek(filePos, p_abort);
				file->read(&smplCk, sizeof(smplCk), p_abort);

				if ((smplCk.sampleLoops > 0) && (smplCk.size >= (sizeof(WaveSampleCk) + sizeof(WaveSampleLoop) - sizeof(RiffCkHeader))))
				{
					WaveSampleLoop smplLoop;
					file->read(&smplLoop, sizeof(smplLoop), p_abort);

					info.smplLoop      = 1;
					info.smplLoopStart = smplLoop.start;
					info.smplLoopEnd   = smplLoop.end;

					smplLoopFound = true;
				}
			}
			else if(   (!id3LoopFound)
			        && (ckHeader.ID[0] == 'i') && (ckHeader.ID[1] == 'd') && (ckHeader.ID[2] == '3') && (ckHeader.ID[3] == ' '))
			{
				// MP3 <id3-ck> chunk ("id3 ")
				pfc::array_t<t_uint8> id3Buffer;
				id3Buffer.set_size(ckHeader.size);
				file->read(id3Buffer.get_ptr(), ckHeader.size, p_abort);

				if (GetWaveFileInfoFromID3(id3Buffer.get_ptr(), ckHeader.size, info))
				{
					id3LoopFound = true;
				}
			}

			filePos += sizeof(RiffCkHeader) + ckHeader.size;
		}

		if (!(fmtFound && dataFound))
		{
			console::info("foo_input_wave_loop : Illegal WAV file (not data found)");
			return false;
		}

		if ((info.bytesPerSample > 0) && (info.dataSize > 0))
		{
			info.sampleNum = info.dataSize / info.bytesPerSample;
		}

		// <sample-loop> is prior to ID3v2 LOOPSTART/LOOPLENGTH
		if (info.smplLoop > 0)
		{
			info.loop      = info.smplLoop;
			info.loopStart = info.smplLoopStart;
			info.loopEnd   = info.smplLoopEnd;
		}
		else if ((info.id3Loop > 0) && (info.id3LoopLength > 0))
		{
			info.loop      = info.id3Loop;
			info.loopStart = info.id3LoopStart;
			info.loopEnd   = info.id3LoopStart + info.id3LoopLength - 1;
		}

		if (info.loop > 0)
		{
			if (info.loopStart >= info.sampleNum)
			{
				info.loopStart = 0;
			}

			if (info.loopEnd >= info.sampleNum)
			{
				info.loopEnd = info.sampleNum - 1;
			}
			else if(info.loopEnd < info.loopStart)
			{
				info.loopEnd = info.sampleNum - 1;
			}
		}

		return true;
	}

	bool GetWaveFileInfoFromID3(const void* pID3, t_uint32 size, WaveFileInfo& info)
	{
		const t_uint8* pData = (const t_uint8*)pID3;


		// ID3v2 header
		const ID3v2Header* pHeader = (const ID3v2Header*)pData;

		if (!((pHeader->ID[0] == 'I') && (pHeader->ID[1] == 'D') && (pHeader->ID[2] == '3')))
		{
			console::info("foo_input_wave_loop : Illegal ID3 Header ID");
			return false;
		}

		if (!(((pHeader->version[0] == 3) || (pHeader->version[0] == 4)) && (pHeader->version[1] == 0)))
		{
			console::info("foo_input_wave_loop : unsupported ID3 Header version");
			return false;
		}

		bool     extendedHeader = (pHeader->flags & 0x40) ? true : false;
		t_uint32 id3DataSize    =   ((pHeader->size[0] & 0x7F) << 21)
		                          + ((pHeader->size[1] & 0x7F) << 14)
		                          + ((pHeader->size[2] & 0x7F) << 7)
		                          +  (pHeader->size[3] & 0x7F);


		// ID3v2 extended header
		pData += sizeof(ID3v2Header);
		if (extendedHeader)
		{
			const ID3v2ExtendedHeader* pExHeader = (const ID3v2ExtendedHeader*)pData;

			t_uint32 extendedHeaderSize =   ((pExHeader->size[0] & 0x7F) << 21)
			                              + ((pExHeader->size[1] & 0x7F) << 14)
			                              + ((pExHeader->size[2] & 0x7F) << 7)
			                              +  (pExHeader->size[3] & 0x7F);

			pData       += extendedHeaderSize;
			id3DataSize -= extendedHeaderSize;
		}


		// ID3v2 frame
		bool loopStartFound  = false;
		bool loopLengthFound = false;

		while (id3DataSize > sizeof(ID3v2Frame))
		{
			const ID3v2Frame* pFrame = (const ID3v2Frame*)pData;

			if ((pFrame->ID[0] == 0x00) || (pFrame->ID[1] == 0x00) || (pFrame->ID[2] == 0x00) || (pFrame->ID[3] == 0x00))
			{
				break;
			}

			t_uint32 frameSize = (pFrame->size[0] << 24) + (pFrame->size[1] << 16) + (pFrame->size[2] << 8) + pFrame->size[3];

			if ((pFrame->ID[0] == 'T') || (pFrame->ID[1] == 'X') || (pFrame->ID[2] == 'X') || (pFrame->ID[3] == 'X'))
			{
				// #TXXX User defined text information frame
				const t_uint8* pTXXX   = (const t_uint8*)&pData[sizeof(ID3v2Frame)];
				bool           tagRead = false;

				pfc::array_t<char> tagName;
				tagName.set_size(frameSize);
				pfc::array_t<char> tagValue;
				tagValue.set_size(frameSize);

				t_uint8  textEnc = pTXXX[0];
				t_uint32 pos = 1, i;

				// Text encoding
				switch(textEnc)
				{
				case 3:
					// UTF-8 (encoded Unicode)

					// UTF-8 BOM check
					if ((pTXXX[pos] == 0xEF) && (pTXXX[pos + 1] == 0xBB) && (pTXXX[pos + 2] == 0xBF))
					{
						pos += 3;
					}
					// no break

				case 0:
					// ISO-8859-1
					for (i = 0; (i < frameSize) && (pos < frameSize); i++)
					{
						tagName[i] = pTXXX[pos];
						pos++;

						if (tagName[i] == '\0')
						{
							break;
						}
					}
					tagName[i] = '\0';

					for (i = 0; (i < frameSize) && (pos < frameSize); i++)
					{
						tagValue[i] = pTXXX[pos];
						pos++;

						if (tagValue[i] == '\0')
						{
							break;
						}
					}
					tagValue[i] = '\0';

					tagRead = true;
					break;

				case 1:
					// UTF-16 (encoded Unicode with BOM)

					// UTF-16 BOM check
					if (pos < frameSize - 1)
					{
						bool bigEndian = false;

						if ((pTXXX[pos] == 0xFF) && (pTXXX[pos + 1] == 0xFE))
						{
							// LE (little endian)
							pos += 2;
						}
						else if ((pTXXX[pos] == 0xFE) && (pTXXX[pos + 1] == 0xFF))
						{
							// BE (big endian)
							bigEndian = true;
							pos += 3;
						}

						for (i = 0; (i < frameSize) && (pos < frameSize); i++)
						{
							tagName[i] = pTXXX[pos];
							pos += 2;

							if (tagName[i] == '\0')
							{
								if (bigEndian)
								{
									pos--;
								}
								break;
							}
						}
						tagName[i] = '\0';
					}

					if (pos < frameSize - 1)
					{
						bool bigEndian = false;

						if ((pTXXX[pos] == 0xFF) && (pTXXX[pos + 1] == 0xFE))
						{
							// LE (little endian)
							pos += 2;
						}
						else if ((pTXXX[pos] == 0xFE) && (pTXXX[pos + 1] == 0xFF))
						{
							// BE (big endian)
							bigEndian = true;
							pos += 3;
						}

						for (i = 0; (i < frameSize) && (pos < frameSize); i++)
						{
							tagValue[i] = pTXXX[pos];
							pos += 2;

							if (tagValue[i] == '\0')
							{
								if (bigEndian)
								{
									pos--;
								}
								break;
							}
						}
						tagValue[i] = '\0';
					}

					tagRead = true;
					break;

				case 2:
					// UTF-16BE (encoded Unicode without BOM)
					pos += 1;

					for (i = 0; (i < frameSize) && (pos < frameSize); i++)
					{
						tagName[i] = pTXXX[pos];
						pos += 2;

						if (tagName[i] == '\0')
						{
							pos--;
							break;
						}
					}
					tagName[i] = '\0';

					for (i = 0; (i < frameSize) && (pos < frameSize); i++)
					{
						tagValue[i] = pTXXX[pos];
						pos += 2;

						if (tagValue[i] == '\0')
						{
							pos--;
							break;
						}
					}
					tagValue[i] = '\0';

					tagRead = true;
					break;

				default:
					break;
				}

				if (tagRead)
				{
					FB2K_console_formatter() << "foo_input_wave_loop : ID3 tag (" << &tagName[0] << ", " << &tagValue[0] << ")";

					if ((!loopStartFound) && (pfc::strcmp_ex(&tagName[0], 9, "LOOPSTART", 9) == 0))
					{
						info.id3LoopStart = (t_uint32)pfc::string_to_float(&tagValue[0]);
						loopStartFound    = true;
					}
					else if ((!loopLengthFound) && (pfc::strcmp_ex(&tagName[0], 10, "LOOPLENGTH", 10) == 0))
					{
						info.id3LoopLength = (t_uint32)pfc::string_to_float(&tagValue[0]);
						loopLengthFound    = true;
					}
				}
			}

			pData       += sizeof(ID3v2Frame) + frameSize;
			id3DataSize -= sizeof(ID3v2Frame) + frameSize;
		}

		if (loopStartFound && loopLengthFound)
		{
			info.id3Loop = 1;
			return true;
		}

		return false;
	}
};

static input_singletrack_factory_t<input_wave_loop> g_input_wave_loop_factory;



// Declaration of your component's version information
// Since foobar2000 v1.0 having at least one of these in your DLL is mandatory to let the troubleshooter tell different versions of your component apart.
// Note that it is possible to declare multiple components within one DLL, but it's strongly recommended to keep only one declaration per DLL.
// As for 1.1, the version numbers are used by the component update finder to find updates; for that to work, you must have ONLY ONE declaration per DLL. If there are multiple declarations, the component is assumed to be outdated and a version number of "0" is assumed, to overwrite the component with whatever is currently on the site assuming that it comes with proper version numbers.
DECLARE_COMPONENT_VERSION(
	"Wave Loop",
	"1.1",
	"foo_input_wave_loop (foobar2000 component)\n"
	"Support WAV file (*.wavloop) with loop point\n"
	"\n"
	"Copyright (c) 2014-2024 Suwasaki Ryu\n"
	"Distributed under MIT License\n"
	"https://github.com/suwasakix/foo_input_wave_loop"
);

DECLARE_FILE_TYPE("WAV files", "*.WAVLOOP");

// This will prevent users from renaming your component around (important for proper troubleshooter behaviors) or loading multiple instances of it.
VALIDATE_COMPONENT_FILENAME("foo_input_wave_loop.dll");

// Activate cfg_var downgrade functionality if enabled. Relevant only when cycling from newer FOOBAR2000_TARGET_VERSION to older.
FOOBAR2000_IMPLEMENT_CFG_VAR_DOWNGRADE;


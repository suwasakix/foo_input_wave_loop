// SPDX-License-Identifier: MIT
// Copyright (c) 2014-2025 Suwasaki Ryu
//----------------------------------------------------------------------------
// foo_input_wave_loop (foobar2000 component)
// foo_input_wave_loop.h
//
// References:
//   * input_raw.cpp (foobar2000 SDK sample)
//   * Multimedia Programming Interface and Data Specifications 1.0
//       https://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/riffmci.pdf
//   * Microsoft Multimedia Standards Update, New Multimedia Data Types and Data Techniques, Revision: 3.0
//       https://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/RIFFNEW.pdf
//   * The ID3v2 documents
//       https://id3.org/Developer%20Information
//
// Changes:
//   1.2 (28 Sep 2025) : Fixed ID3 tag reading function
//   1.1 ( 1 May 2024) : Support x64 platform, based on foobar2000 SDK 2023-09-23
//   1.0 ( 2 May 2014) : First release, based on foobar2000 SDK 2011-03-11
//
//----------------------------------------------------------------------------

#ifndef foo_input_wave_loop_h
#define foo_input_wave_loop_h

#include "../SDK/foobar2000.h"
#include "../helpers/helpers.h"

struct WaveFileInfo
{
	t_uint32 samplingRate;              // sampling rate (in samples per second)
	t_uint32 channels;                  // number of channels
	t_uint32 quantizationBitRate;       // number of bits of a channel data used to represent each sample
	t_uint32 bytesPerSample;            // number of bytes of data used to represent each sample
	t_uint32 dataOffset;                // file offset of wave chunk data
	t_uint32 dataSize;                  // size of wave chunk data
	t_uint32 sampleNum;                 // number of samples
	t_uint32 loop;                      // exist loop
	t_uint32 loopStart;                 // startpoint of the loop in samples
	t_uint32 loopEnd;                   // endpoint of the loop in samples (this sample will also be played)
	t_uint32 smplLoop;                  // [smpl] exist loop
	t_uint32 smplLoopStart;             // [smpl] startpoint of the loop in samples
	t_uint32 smplLoopEnd;               // [smpl] endpoint of the loop in samples (this sample will also be played)
	t_uint32 id3Loop;                   // [id3] exist loop
	t_uint32 id3LoopStart;              // [id3] startpoint of the loop in samples
	t_uint32 id3LoopLength;             // [id3] length of the loop in samples

	void clear()
	{
		samplingRate        = 0;
		channels            = 0;
		quantizationBitRate = 0;
		bytesPerSample      = 0;
		dataOffset          = 0;
		sampleNum           = 0;
		loop                = 0;
		loopStart           = 0;
		loopEnd             = 0;
		smplLoop            = 0;
		smplLoopStart       = 0;
		smplLoopEnd         = 0;
		id3Loop             = 0;
		id3LoopStart        = 0;
		id3LoopLength       = 0;
	}
};

// RIFF chunk header
struct RiffCkHeader
{
	t_uint8  ID[4];                     // Chunk type identifier
	t_uint32 size;                      // Chunk size field
};

// RIFF list chunk header
struct RiffListCkHeader
{
	t_uint8  ID[4];                     // Chunk type identifier ("RIFF" or "LIST")
	t_uint32 size;                      // Chunk size field
	t_uint8  formType[4];               // Form type
};

// WAVE <fmt-ck> chunk for PCM
struct WaveFmtCkPcm
{
	t_uint8  ID[4];                     // Chunk type identifier ("fmt ")
	t_uint32 size;                      // Chunk size field
	t_uint16 formatTag;                 // Format category (1 : PCM)
	t_uint16 channels;                  // number of channels
	t_uint32 samplesPerSec;             // sampling rate (in samples per second)
	t_uint32 avgBytesPerSec;            // average number of bytes per second at which the waveform data should be transferred
	t_uint16 blockAlign;                // block alignment (in bytes) of the waveform data
	t_uint16 bitsPerSample;             // number of bits of data used to represent each sample of each channel
};

// WAVE <data-ck> chunk
struct WaveDataCk
{
	t_uint8  ID[4];                     // Chunk type identifier ("data")
	t_uint32 size;                      // Chunk size field
};

// WAVE <sample-ck> chunk
struct WaveSampleCk
{
	t_uint8  ID[4];                     // Chunk type identifier ("smpl")
	t_uint32 size;                      // Chunk size field
	t_uint32 manufacturer;              // MMA Manufacturer code for the intended target device
	t_uint32 product;                   // Product code of the intended target device
	t_uint32 samplePeriod;              // period of one sample in nanoseconds (22675 : 44.kHz)
	t_uint32 MIDIUnityNote;             // MIDI note which will replay the sample at original pitch (60 : Middle C)
	t_uint32 MIDIPitchFraction;         // fraction of a semitone up from the specified dwMIDIUnityNote
	t_uint32 SMPTEFormat;               // SMPTE time format used in the dwSMPTEOffset field (0 : no SMPTE offset)
	t_uint32 SMPTEOffset;               // time offset for the sample
	t_uint32 sampleLoops;               // number of <sample-loop> records
	t_uint32 samplerData;               // size in bytes of the optional <sampler-specific-data>
};

// WAVE <sample-loop> structure
struct WaveSampleLoop
{
	t_uint32 identifier;                // Identifies the unique 'name' of the loop
	t_uint32 type;                      // loop type (0 : Loop forward)
	t_uint32 start;                     // startpoint of the loop in samples
	t_uint32 end;                       // endpoint of the loop in samples (this sample will also be played)
	t_uint32 fraction;                  // Allows fine-tuning for loop fractional areas between samples
	t_uint32 playCount;                 // Specifies the number of times to play the loop (0 : infinite)
};

// ID3v2 (ID3v2.3.0 / ID3v2.4.0) header
struct ID3v2Header
{
	t_uint8  ID[3];                     // ID3v2/file identifier ("ID3")
	t_uint8  version[2];                // ID3v2 version ($03 00 : ID3v2.3.0, $04 00 : ID3v2.4.0)
	t_uint8  flags;                     // ID3v2 flags (%abc00000 : ID3v2.3.0, %abcd0000 : ID3v2.4.0)
	t_uint8  size[4];                   // ID3v2 size (4 * %0xxxxxxx, not include footer size)
};

// ID3v2 (ID3v2.3.0 / ID3v2.4.0) extended header
struct ID3v2ExtendedHeader
{
	t_uint8  size[4];                   // Extended header size ($xx xx xx xx : ID3v2.3.0, 4 * %0xxxxxxx : ID3v2.4.0)
	t_uint8  flagsSize;                 // Number of flag bytes
	t_uint8  flags;                     // Extended Flags
};

// ID3v2 (ID3v2.3.0 / ID3v2.4.0) frame
struct ID3v2Frame
{
	t_uint8  ID[4];                     // Frame ID
	t_uint8  size[4];                   // Size ($xx xx xx xx : ID3v2.3.0, 4 * %0xxxxxxx : ID3v2.4.0)
	t_uint8  flags[2];                  // Flags
};

#endif // foo_input_wave_loop_h


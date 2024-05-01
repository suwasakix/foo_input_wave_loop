# foo_input_wave_loop

WAV �t�@�C���̖������[�v�Đ����s�� foobar2000 �R���|�[�l���g

foobar2000 component for infinite loop playback of WAV file

&nbsp;

## �ڎ� - Contents

 - [���̃\�t�g�E�F�A�ɂ���](#���̃\�t�g�E�F�A�ɂ���---about-this-software)
 - [�\�t�g�E�F�A�̃_�E�����[�h](#�\�t�g�E�F�A�̃_�E�����[�h---download-software)
 - [�����](#�����---operating-environment)
 - [�T�|�[�g����t�@�C���̎��](#�T�|�[�g����t�@�C���̎��---supported-file-types)
 - [WAV�t�@�C���Ƀ��[�v�|�C���g��t��������@](#wav�t�@�C���Ƀ��[�v�|�C���g��t��������@---how-to-append-the-loop-point-to-wav-file)
 - [CUE�V�[�g�̏���](#cue�V�[�g�̏���---playback-using-cue-sheet)
 - [�g�p��](#�g�p��---example-of-use)
 - [�{�\�t�g�E�F�A�̃��C�Z���X�ɂ���](#�{�\�t�g�E�F�A�̃��C�Z���X�ɂ���)
 - [���상��](#���상��)

&nbsp;

## ���̃\�t�g�E�F�A�ɂ��� - About this software

�{�\�t�g�E�F�A�́Afoobar2000 �Ń��[�v�|�C���g���������� WAV �t�@�C�������[�v�Đ����邽�߂̃R���|�[�l���g�ł��BWAV �t�@�C���̐����Ȏd�l�ł��郋�[�v�|�C���g���̂ق��AID3 �^�O��� "LOOPSTART"�C"LOOPLENGTH" �ɂ��Ή����܂��B

This software is foobar200 component to play WAV file that has loop point information. This component supports regular loop point and also ID3 tag ("LOOPSTART" and "LOOPLENGTH").

�y Caution ! �z

�@foobar2000 �{�̂� WAV �t�@�C���Đ��p�R���|�[�l���g�Ƃ̏Փ˂�����邽�߁A�{�R���|�[�l���g�͊g���q�� ".wavloop" �̃t�@�C���i".wav" �ł͂Ȃ��j�ɓK�p�����d�l�ɂ��Ă��܂��B���̂��߁A���[�v�Đ������� WAV �t�@�C��������΁A�g���q�� ".wavloop" �ɕύX������ł����p���������B

To avoid the conflict with foobar2000 standard input component, this component is applied to ".wavloop" file, not to ".wav" file. So you need to change the extension of WAV file to ".wavloop" for loop playback.

&nbsp;

## �\�t�g�E�F�A�̃_�E�����[�h - Download software

������̃y�[�W����g���q���u.fb2k-component�v�̃t�@�C�����_�E�����[�h���Ă��������B

&emsp; https://www.github.com/suwasakix/foo_input_wave_loop/releases

&nbsp;

## ����� - Operating environment

�{�\�t�g�E�F�A (v1.1) �́A�ȉ��̊��œ��삷�邱�Ƃ��m�F���Ă��܂��B

- foobar2000 v2.1.4 (x64) on Windows 11
- foobar2000 v2.1.4 (x86) on Windows 11
- foobar2000 v1.6.17 on Windows 11

&nbsp;

## �T�|�[�g����t�@�C���̎�� - Supported file types

- "smpl" �`�����N�Ƀ��[�v�|�C���g�������� WAV �t�@�C��
- ID3 �^�O�ɁARPG�c�N�[���`���̃��[�v�|�C���g��� (LOOPSTART �� LOOPLENGTH) ������ WAV �t�@�C��

  - ���[�v�|�C���g�����t�@�C���́A�Đ����Ԃ� 1d 0:00:00 �̃t�@�C���Ƃ��ĔF������܂��B
  - ���[�v�Đ����A�V�[�N�o�[�ōĐ�������ύX���邱�Ƃ͂ł��܂���B
  - �t�H�[�}�b�g�`���� PCM �̂݃T�|�[�g���܂��B
  - "smpl" �`�����N�ɕ����̃��[�v�|�C���g��񂪑��݂���ꍇ�ɂ́A�ŏ��̃��[�v�|�C���g���݂̂��g�p����܂��B
  - ID3v2.3 �� ID3v2.4 �ɑΉ����܂��B
  - �����̃��[�v�������ꍇ�ɂ́A"smpl" �`�����N�̏�񂪗D�悳��܂��B


- WAV file containing "smpl" chunk with loop points
- WAV file containing "LOOPSTART" and "LOOPLENGTH" (defined by RPG Maker) in ID3 tag

  - This component considers the duration of file with loop point as "1d 0:00:00" (1 day).
  - In case of loop playback, you cannot change play time by seekbar.
  - Support only PCM format.
  - When the "smpl" chunk has plural loop point information, only first loop point is referred.
  - Support ID3v2.3 and ID3v2.4.
  - If the file has both "smpl" chunk and ID3 tag, this component get only "smpl" chunk information.

&nbsp;

## WAV�t�@�C���Ƀ��[�v�|�C���g��t��������@ - How to append the loop point to WAV file

#### WAV�t�@�C���� "smpl" �`�����N��t������ꍇ - Case of appending "smpl" chunks to WAV file

�����ҏW�\�t�g Wavosaur �� "smpl" �`�����N�̃��[�v�|�C���g��ҏW���邱�Ƃ��\�ł��B  
Wavosaur ��[���̃T�C�g](https://www.wavosaur.com)����_�E�����[�h�ł��܂��B  

You can edit the loop points of "smpl" chunks by Wavosaur.  
Wavosaur can be downloaded from [this site](https://www.wavosaur.com).  

&nbsp;

#### WAV�t�@�C���� ID3 �^�O��t������ꍇ - Case of appending ID3 tags to WAV file

�����ҏW�\�t�g Audacity �� ID3 �^�O��ҏW���邱�Ƃ��\�ł��B  
Audacity ��[���̃T�C�g](https://www.audacityteam.org)����_�E�����[�h�ł��܂��B  
You can edit the ID3 tags by Audacity.  
Audacity can be downloaded from [this site](https://www.audacityteam.org).  

&nbsp;

##### ���[�v�|�C���g�̍쐬�菇 - How to append the loop point by Audacity

1. Audacity ���N����A���j���[�́u�ҏW(E)�v���u�ݒ�(F)...�v��I�����A�u�i���v�J�e�S���[�́u�������ϊ� - �f�B�U�����O(h)�v���u�����v�ɐݒ肵�܂��B  

   �� �f�B�U�����O�̐ݒ���u�����v�ɂ��Ȃ������ꍇ�AWAV �t�@�C����ǂݍ��񂾍ۂɃf�B�U�����O���������s����Ă��܂��A�����f�[�^�� WAV �t�@�C���̕ҏW�O��Ńo�C�i����v���Ȃ��Ȃ�܂��B

2. WAV �t�@�C�����J���܂��B  

3. ���j���[�́u�t�@�C��(F)�v���u�����o��(E)...�v��I�����A�t�@�C��������͂��āu�ۑ�(S)�v���N���b�N���܂��B  

4. �u���^�f�[�^��ҏW�v�E�B���h�E���\�������̂ŁA�^�O�̗��� "LOOPSTART" ����� "LOOPLENGTH" ��ǉ����A���ꂼ��̃��[�v�|�C���g�̒l����͂��āuOK(O)�v���N���b�N���܂��B  

    �� "LOOPSTART" �ɂ̓��[�v�J�n�ʒu���A"LOOPLENGTH" �ɂ̓��[�v����͈͂̒������T���v���P�ʂœ��͂��܂��B�Ⴆ�� 44.1kHz �� WAV �t�@�C���� "LOOPSTART" �̒l�� 441000�A"LOOPLENGTH" �̒l�� 882000 �ɐݒ肷��ƁA���[�v����͈͂� 00:10.000 �` 00:30.000 �ɂȂ�܂��B

5. �ۑ����� WAV �t�@�C���̊g���q�� ".wavloop" �ɕύX���āAfoobar2000 �̃��f�B�A���C�u�����Ŏw�肳�ꂽ�t�H���_�ɒu���܂��B

&nbsp;

1. Start Audacity, and Select menu "Edit(E)" -> "Preferences(F)...", and select "Quality " category, and set "High-quality Conversion - Dither" to "None". (for guaranteeing the binary consistency of audio data)  

2. Open WAV file.  

3. Select menu "File(F)" -> "Export(E)...". Input file name and click "Save(S)" button.  

4. Window "Edit Metadata" is shown. Then append tag "LOOPSTART" and "LOOPLENGTH". Input each value (loop point) and click "OK" button.  

5. Change the the extension of WAV file to ".wavloop" and put it to the media library folder of foobar2000.

&nbsp;

## CUE�V�[�g�̏��� - Playback using CUE sheet

CUE �V�[�g���g���čĐ�����ɂ́A���̂悤�ȏ����� CUE �V�[�g���쐬���Ă��������B

```
PERFORMER "Performer"
TITLE "Title"
FILE "test01.wavloop" WAVE
  TRACK 01 AUDIO
    TITLE "Test01"
    PERFORMER "Performer"
    INDEX 01 00:00:00
FILE "test02.wavloop" WAVE
  TRACK 02 AUDIO
    TITLE "Test02"
    PERFORMER "Performer"
    INDEX 01 00:00:00
FILE "test03.wavloop" WAVE
  TRACK 03 AUDIO
    TITLE "Test03"
    PERFORMER "Performer"
    INDEX 01 00:00:00
```

�� foobar2000 v2.x �ł́ATRACK �̔ԍ��͕K�� 01, 02, 03, ... �̏��ɋL�q���Ă��������B�ԍ��̕��т��A�ԂɂȂ��Ă��Ȃ� CUE �t�@�C���̓G���[�ɂȂ�܂��B

&nbsp;

## �g�p�� - Example of use

FF7 (FF7R) �̃~�b�h�K����24���Ԑ킢���������l�̂��߂̎g�p��ł��B<span style="font-size:70%;">����Ȑl���邩�ǂ����m��񂯂�</span>  

�� �����Ŏg�p���Ă���A�v���̉�ʂ͉p��ł̂��̂ł��B���{��ł��g�p������͊e���ŉ�ʂ̕�����ǂݑւ��Ă��������B  

1. FINAL FANTASY VII REMAKE Original Soundtrack �𔃂��Ă���B  

   <a href="./docs/images/soundtrack.jpg"><img src="./docs/images/soundtrack.jpg" width="320" height="240"></a>  

2. Exact Audio Copy �Ȃǂ̃\�t�g�ŁADisc1 �́u���j�~�b�V���� (Bombing Mission)�v�����b�s���O����B  

   ���b�s���O�Ɏg�p������w�f�B�X�N�h���C�u�́APureRead �𓋍ڂ��� PIONNER ���h���C�u�𐄏����܂��B  

   <a href="./docs/images/ripping.jpg"><img src="./docs/images/ripping.jpg" width="320" height="240"></a>  

   Exact Audio Copy �Ń��b�s���O����ꍇ�A�g���b�N���X�g�̉E�N���b�N���j���[����u�I�������g���b�N���R�s�[(C)�v���u�����k...�v��I������ WAV �`���ŕۑ����܂��B  

   <a href="./docs/images/track.gif"><img src="./docs/images/track.gif" width="640" height="67"></a>  

   �R�s�[���ĕۑ����ꂽ WAV �t�@�C���̃T�C�Y�� 36,352,556 �o�C�g�ɂȂ�܂����B�h���C�u�� CD ����꒼���ăR�s�[���Ď��s���Ă��S���������e�̃t�@�C�����쐬����܂����̂ŁAPureRead ���ڃh���C�u�� Exact Audio Copy �̑g�ݍ��킹�ɂ�郊�b�s���O�̒������͔��ɍ����Ǝv���܂��B�g���b�N�P�ʂŃR�s�[����ꍇ�ɂ́A���O�ɃM���b�v���o�����s����K�v�͂Ȃ������ł��B  

3. Audacity �� WAV �t�@�C���� "LOOPSTART" �� "LOOPLENGTH" �̃^�O��t������B  

   Audacity ���N��������A���j���[�́u�ҏW(E)�v���u�ݒ�(F)...�v��I�����A�u�i���v�J�e�S���[�́u�������ϊ� - �f�B�U�����O(h)�v���u�����v�ɐݒ肵�܂��B  

   <a href="./docs/images/audacity_preferences.gif"><img src="./docs/images/audacity_preferences.gif" width="320" height="223"></a>  

   ���b�s���O���� WAV �t�@�C�����I�[�v�����āA���y�̃��[�v�|�C���g�ɂȂ��Ă���ӏ���T���܂��BAudacity ���Q�N�����Ă��ꂼ��� WAV �t�@�C�����J���āA���[�v�̊J�n�E�I���ɂȂ肻���Ȉʒu���A�g�`������ׂȂ���T���ƍ�Ƃ��₷���Ǝv���܂��B  

   <a href="./docs/images/audacity_seek1.gif"><img src="./docs/images/audacity_seek1.gif" width="640" height="343"></a>  

   ���y�𕷂��Ċm�F���Ȃ��� (�w�b�h�z������) �g�`���g�債�Ă����A���[�v�|�C���g�̈ʒu��ǂ����݂܂��B�㑤�����[�v�J�n�ʒu�̔g�`�A���������[�v�I���ʒu�̔g�`�ł��B����������ׂ�ƁA���[�v�|�C���g�ȍ~�̔g�`�����Ă��邱�Ƃɂ����ڂ��������B  

   <a href="./docs/images/audacity_seek2.gif"><img src="./docs/images/audacity_seek2.gif" width="640" height="343"></a>  

   Bombing Mission �̃��[�v�J�n�ʒu�� 346,016 �Ԗڂ̃T���v���A���[�v�I���ʒu�� 8,167,653  �Ԗڂ̃T���v���ɂ��܂����B�I�������T���v���̔ԍ��́u���ԃc�[���o�[�v�Ŋm�F���邱�Ƃ��ł��܂� (�\���P�ʂ́u�T���v���v�ɐݒ肵�Ă�������)�B�g�`���[�����x���ɋ߂��ʒu�Ƀ��[�v�|�C���g��ݒ肷��̂��A�Đ����Ƀ��[�v�̌p���ڂ�ڗ����Ȃ�����R�c�ł��B  

   <a href="./docs/images/audacity_seek3.gif"><img src="./docs/images/audacity_seek3.gif" width="640" height="343"></a>  

   ���[�v�|�C���g�����߂���A���[�v�Đ��̃e�X�g�����܂��B�u�I���c�[���o�[�v�Ƀ��[�v�J�n�ʒu�E���[�v�I���ʒu�̃T���v���ԍ�����͂��āA���[�v��L����������ōĐ������s���܂��B  

   <a href="./docs/images/audacity_play.gif"><img src="./docs/images/audacity_play.gif" width="640" height="179"></a>  

   �e�X�g���Ė�肪�Ȃ���΁AWAV �t�@�C���̃^�O���Ƀ��[�v�J�n�ʒu�E���[�v��Ԃ̒�����ǉ����܂��B���j���[�́u�ҏW(E)�v���u���^�f�[�^�G�f�B�^(M)�v��I�����ă��^�f�[�^�^�O�̕ҏW��ʂ��J���A���[�v�J�n�ʒu�̃T���v���ԍ��� LOOPSTART ���A���[�v��Ԃ̒����� LOOPLENGTH �ɐݒ肵�܂��B����̗�ł́ALOOPSTART �̒l�� 346016�ALOOPLENGTH �̒l�� 7821637 (= 8167653 - 346016) �ƂȂ�܂��B���l�̕�����ɂɃJ���}���܂߂Ȃ��悤�����ӂ��������B

   <a href="./docs/images/audacity_metadata.gif"><img src="./docs/images/audacity_metadata.gif" width="320" height="289"></a>  

   �Ō�ɁA���j���[�́u�t�@�C��(F)�v���u�I�[�f�B�I���G�N�X�|�[�g(E)...�v��I�����ăG�N�X�|�[�g��ʂ��J���A�^�O����ǉ����� WAVE �t�@�C����ۑ����܂��B�G�N�X�|�[�g��ʂł̓t�@�C�������w�肵�ĕۑ����邾���Ŗ�肠��܂���B

   �ۑ����� WAV �t�@�C���͌��t�@�C���Ƀ^�O����ǉ����������Ȃ̂ŁA��ʓI�ȃA�v���P�[�V�����ł����t�@�C���Ɠ����悤�ɍĐ��ł��܂��B

4. foobar2000 �� foo_input_wave_loop ���C���X�g�[������B  

   foobar2000 ���N�����A���j���[�́uFile�v���uPrefernces�v��I�����Đݒ��ʂ��J���AComponents �^�u��ʂ��� foo_input_wave_loop (�g���q�� .fb2k-component �̃t�@�C��) ���C���X�g�[�����܂��B

   <a href="./docs/images/fb2k_install.gif"><img src="./docs/images/fb2k_install.gif" width="320" height="236"></a>  

   �C���X�g�[������������ɂ� foobar2000 �̍ċN�����K�v�ł��BOK �{�^���������ƍċN���𑣂����̂� foobar2000 ���ċN�����܂��B

   <a href="./docs/images/fb2k_installed.gif"><img src="./docs/images/fb2k_installed.gif" width="320" height="236"></a>  

   foobar2000 �̍ċN����ɐݒ��ʂ��J���ƁAfoo_input_wave_loop ���C���X�g�[���ς݂ł��邱�Ƃ��m�F�ł��܂��B

   <a href="./docs/images/fb2k_components.gif"><img src="./docs/images/fb2k_components.gif" width="320" height="236"></a>  

   foobar2000 �� CUE �ŉ^�p����ꍇ�AMedia Library �^�u��ʂ̐ݒ���s���Ă��������B��̓I�ɂ́A�uRestrict to�v�Ɂu*.cue�v��ǉ����APlaylist View �Ƀg���b�N���\������Ȃ��ꍇ�� Library viewer selection playlist �� Enabled �Ƀ`�F�b�N�����܂��B

   <a href="./docs/images/fb2k_library.gif"><img src="./docs/images/fb2k_library.gif" width="320" height="236"></a>  

5. CUE �V�[�g���쐬���āA�Đ��ɕK�v�ȃt�@�C���ꎮ�� foobar2000 �̃��f�B�A���C�u�����Ŏw�肳�ꂽ�t�H���_�ɒu���B  

   �ȉ��̂悤�ȃt�@�C�����쐬���܂��B�t�@�C����ۑ�����ۂɁA�����R�[�h (�G���R�[�h) �́uUTF-8�v�܂��́uUTF-8 (BOM �t��)�v��I�����Ă��������B

   ```plaintext
   PERFORMER "Nobuo Uematsu"
   TITLE "FINAL FANTACY VII REMAKE"
   FILE "BombingMission.wavloop" WAVE
     TRACK 01 AUDIO
       TITLE "���j�~�b�V����  Bombing Mission"
       PERFORMER "Nobuo Uematsu"
       INDEX 01 00:00:00
   ```

   CUE �V�[�g�̃t�@�C�����́uFINAL FANTACY VII REMAKE.cue�v�Ƃ��܂��B�ȉ��̃t�@�C���� foobar2000 �̃��f�B�A���C�u�����Ŏw�肳�ꂽ�t�H���_�ȉ��̏ꏊ�ɒu���܂��B�����̃t�@�C���͓���t�H���_�ɒu���K�v������܂��B

   ```
   FINAL FANTACY VII REMAKE.cue
   FINAL FANTACY VII REMAKE.jpg (�J�o�[�W���P�b�g�̉摜�t�@�C���A�K�{�ł͂Ȃ�)
   BombingMission.wavloop (3. �Ń^�O����ǉ����� WAV �t�@�C���A�g���q�� .wavloop �ɕύX)
   ```

   foorbar2000 ���N�����ăv���C���X�g���m�F����ƁA�Đ����ԁu1d 0:00:00�v�Ƃ����g���b�N���\�������͂��B

   <a href="./docs/images/fb2k_view.jpg"><img src="./docs/images/fb2k_view.jpg" width="640" height="480"></a>  

   �ł́A�S�䂭�܂Ń~�b�h�K�����C�t�����y���݂��������B<span style="font-size:70%;">�܂��A���ۂ̗p�r�Ƃ��Ă͓O���Ɨp�ł��傤�ȁc�c</span>

&nbsp;

## �{�\�t�g�E�F�A�̃��C�Z���X�ɂ���

�{�v���O�����̃��C�Z���X�� MIT ���C�Z���X�ł��B

- �{�v���O�����̒��쌠�͍�� (suwasakix) ���ێ����܂��B�{�v���O�����̔Еz�ɂ͒��쌠�\����K�v�Ƃ��܂��B
- �{�v���O�����͖����ł���A��҂̋��𓾂邱�ƂȂ��N�ł����R�ɖ������ŗ��p�\�ł��B���ς��邱�Ƃ���؎��R�ł��B
- �{�v���O�����͖��ۏ؂ł��B��҂́A�\�t�g�E�F�A�̗��p�ɂ���Đ��������ʂɉ��炻�̐ӔC�𕉂��܂���B

&nbsp;

## ���상��

foo_input_wave_loop �́AWAV �t�@�C���̃��[�v�|�C���g�ɑΉ������Đ��p�R���|�[�l���g�ł��B�P�g���b�N�����s�[�g�Đ�����̂ł͂Ȃ��A�Ȃ̓r���̕����������J��Ԃ��Đ����邱�Ƃ��ł��܂��B (�p�r�Ƃ��ẮA�T�E���h�g���b�N�� BGM ��؂�ڂȂ��E�G���h���X�ɍĐ����邱�Ƃ�z�肵�Ă��܂�) ���̓���ȗp�r�䂦�ɁA���̃v���O�C���𐻍삷��ɓ������ẮAfoobar2000 �̎d�l (�H) �ɋ������ꂽ�ӏ������������݂��܂��B

�P�́A�g���q�� ".wav" �̃t�@�C����{�R���|�[�l���g�őΉ��ł��Ȃ����Ƃł��Bfoobar2000 �ɂ́A������Ԃ� WAV �t�@�C���Đ��p�R���|�[�l���g (foo_input_std.dll) �����܂��B�{�̂̋@�\�ƏՓ˂��N������ɂ͂����܂���Bfoobar2000 �{�̂̃\�[�X�R�[�h�����J����Ă��Ȃ��̂ŃA�v���̓��삩��̐����ɂȂ�܂����A����g���q�̃t�@�C���ɑΉ������R���|�[�l���g���������݂���ꍇ�ɁA�ǂ̃R���|�[�l���g���Đ��Ɏg���邩�� foobar2000 �{�̋N�����Ƀ����_���Ō��܂�悤�ł��B�ǂ̊g���q�ɑ΂��� �ǂ̃R���|�[�l���g��K�p����̂� foobar2000 �{�̂���I���ł���΂悩�����̂ł����A�����ɂ� ���̂悤�Ȑݒ�͂���܂���ł����̂ŁA�{�R���|�[�l���g�őΉ�����t�@�C���� ".wav" �ȊO�ɂ�����𓾂܂���ł����B�Ƃ������ƂŁA�{�R���|�[�l���g�Ń��[�v�Đ������� WAV �t�@�C��������΁A�ʓ|�ł����t�@�C���̊g���q�� ".wavloop" �ɕύX���� foobar2000 �̃��f�B�A���C�u�����̃t�H���_�ɒu���Ă��������B

�����P�́A�R���|�[�l���g����͍Đ����Ԃ�V�[�N�o�[�̓����ς����Ȃ����Ƃł��B�l�I�ɂ́A���[�v�Đ�����ꍇ�ł����Ă��Đ����Ԃ̕\���͒ʏ�̎d�l�̂܂܂ɂ��āA���[�v�|�C���g�Ɉ����|�������Ƃ���ōĐ�������V�[�N�o�[�̕\�������[�v�擪�̏�Ԃɖ߂��� �c�c �Ƃ������Ƃ�����Ă݂��������̂ł����Afoobar2000 SDK �� API �ɂ͂����܂ł̋@�\�͂Ȃ��悤�ł��B���[�v����� WAV �t�@�C���̍Đ����Ԃ� "1d 0:00:00" �ƕ\�����Ă���̂́ACUE �V�[�g����t�@�C�����Đ������Ƃ��ɍĐ����������̃t�@�C���̍Đ����Ԃ𒴂��Ă��܂��ƁA���̃g���b�N�̍Đ��� foobar2000 �{�̂ɂ���ċ����I�ɑł��؂��Ă��܂����߂ł��B���̖���������邽�߂ɁA���[�v�|�C���g�������� WAV �t�@�C���̍Đ����Ԃ� 24 ���Ԃł���� foobar2000 �ɒʒm����悤�ɂ��Ă��܂��B�ۈ�����[�v�Đ������Ƃ���Ő؂ꂽ�獢��A�Ƃ����l�͗��΂ɒN�����Ȃ��ł��傤 (^-^;

�����A��� foobar2000 �̎d�l����������� ���̂悤�Ȃ��Ƃ��\�ƂȂ錩���݂���������A�Ή��������Ǝv���܂��B�����Ƃ��A����ȗv�]�䂦�� foobar2000 �{�̂��Ή����Ă����Ƃ͎v���܂��� (^^;

���āAWAV �t�@�C���̃��[�v�|�C���g�ł����A����� WAV �t�@�C���̎d�l�Ƃ��Ă͂��܂�ɂ��}�C�i�[�����邽�߂� �Ή����Ă���\�t�g�͂قǂ�ǂ���܂���BWavosaur �����[�v�|�C���g�̕ҏW�ɑΉ����Ă��邭�炢�ł��傤���B����������������܂��ƁA�����ȃ��[�v�|�C���g�̎d�l�����ɑΉ�����̂͂��܂�ɂ��s�e�؂ł��̂ŁA�{�R���|�[�l���g�ł� ID3 �^�O�ɂ�郋�[�v�|�C���g�ɂ��Ή�����悤�ɂ��܂����B������uRPG�c�N�[���`���v�A"LOOPSTART" �^�O�� "LOOPLENGTH" �^�O�ɂ�胋�[�v�|�C���g���w�肷����@�ł��B����Ȃ�AAudacity �Ƃ����L���ǂ���̃T�E���h�ҏW�\�t�g�Ń��[�v�|�C���g�̏���ҏW���邱�Ƃ��\�ł��B�������AAudacity �̏����ݒ�ł̓I�[�f�B�I�t�@�C����ǂݍ��񂾎��_�Ńf�[�^���f�B�U�����O��������Ă��܂����߁A�t�@�C���̕ҏW�O��Ńf�[�^�̃o�C�i������v���Ȃ��Ȃ邱�Ƃɂ͂����ӂ��������B�i�f�B�U�����O�����𖳌��ɂ���ɂ́Afoobar2000 �̐ݒ��ʂŁu�i���v�J�e�S���[�́u�������ϊ� - �f�B�U�����O(h)�v���u�����v�ɐݒ肵�܂��j

����ŁA��҂Ƃ��Ă̓��[�v�|�C���g�ҏW�p�̃\�t�g��ʂɍ���Ԃ��Ȃ���Ƃ������̂ł� (�P�[�P�G

(2014.5.2)

&nbsp;

���񃊃��[�X�ȗ������Ƃق����炩���ɂ��Ă��܂����� (������������� foobar2000 �R���|�[�l���g�̎��v���Ă���񂩂��ȁH) �AGitHub Pages �Ƀu���O��������̂��@��Ƀ\�t�g�̌��J�ꏊ�� GitHub �̃��|�W�g���Ɉڂ��āA�\�t�g���ŐV�� foobar2000 SDK �Ńr���h���������Ƃɂ��܂����B�����񂹂� 10�N�Ԃق����炩���ł����̂ōŏ��Ƀr���h�������Ƃ���ł܂����A�\�t�g���r���h����Ƃ���ł��܂����A�Ȃ�Ƃ��r���h���ʂ����Ǝv������ŐV�� foobar2000 �ł͎v�����悤�ɓ����Ȃ��c�c����ł��Ȃ�Ƃ��������Ƃ���܂ł͎����Ă��ꂽ�̂Ńo�[�W�����A�b�v�łƂ��Č��J���܂��B

foobar2000 �� 2023�N�� 2.x �Ƀo�[�W�����A�b�v���܂������A���ۂɐG���Ă���Ƃ��낢��ׂ����Ƃ���Ńo�O���c���Ă���悤�ł��B2.x �̓��삪���������܂ł́A1.x �n�̍ŏI�o�[�W�����ŗl�q����������悢��������܂���B

foo_input_wave_loop ���\�[�X�t�@�C������r���h����菇�ɂ��ẮA[������̃h�L�������g](DEVELOPMENT.md)�ɂ܂Ƃ߂Ă���܂��Bfoobar2000 �̃R���|�[�l���g���r���h���邽�߂ɕK�v�ȃ\�t�g�̐������珑���Ă���܂��̂ŁA������ foobar200 �R���|�[�l���g���쐬���������ɂƂ��Ă͎Q�l�ɂȂ�Ǝv���܂��B

(2024.5.1)


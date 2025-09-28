# foo_input_wav_loop (foobar2000 plugin) 開発メモ

このドキュメントは、foo_input_wav_loop v1.1 のビルド環境の構築方法と、ビルドする方法についてまとめたものです。

&nbsp;

## 開発環境

- foobar2000 SDK 2023-09-23

- Visual Studio Community 2022

- Windows Template Library (WTL) 10.0.10320

&nbsp;

## 開発環境のインストール

### foobar200 SDK

foobar2000 公式サイトから入手します。  
&emsp; https://www.foobar2000.org/SDK

今回使用したバージョンは 2023-09-23 です。  
&emsp; https://www.foobar2000.org/getfile/SDK-2023-09-23.7z

&nbsp;

### Visual Studio Community 2022

Microsoft のサイトから Visual Studio Community 2022 のインストーラを入手します。  
&emsp; https://visualstudio.microsoft.com/ja/downloads/

Visual Studio Community 2022 のインストーラを実行して以下のコンポーネントをインストールします。

- ワークロード
  - C++ によるデスクトップ開発 (オプションはデフォルトのままでOK)

&nbsp;

### Windows Template Library (WTL)

SourceForge から WTL を入手します。  
&emsp; https://sourceforge.net/projects/wtl/

今回使用したバージョンは 10.0.10320 です。  
&emsp; https://sourceforge.net/projects/wtl/files/WTL%2010/WTL%2010.0.10320%20Release/WTL10_10320_Release.zip/download

※ WTL のリリースパッケージは GitHub でも公開されています。(配布物は SourceForge のものと同一)

ダウンロードした zip ファイルを解凍して任意のフォルダにインストールします。  
(ここでは C:\Program Files\Windows Template Library 以下にコピーする前提で進めます)

&nbsp;

## foobar2000 プラグインのサンプルプロジェクトのビルド

まずは下調べとして、foorbar2000 SDK に付属しているサンプルプロジェクト (foo_sample) でビルドが通るかどうかの確認をします。

&nbsp;

### サンプルプロジェクトのフォルダ構成

foobar200 SDK に含まれているソリューション (.svn) とプロジェクト (.vcxproj) の構成は以下のようになっています。

```
SDK-2023-09-23
├── foobar2000
│   ├── foo_input_validator
│   ├── foo_sample
│   │   ├── foo_sample.sln
│   │   └── foo_sample.vcxproj
│   ├── foobar2000_component_client
│   │   └── foobar2000_component_client.vcxproj
│   ├── helpers
│   │   └── foobar2000_sdk_helpers.vcxproj
│   ├── helpers-mac
│   ├── SDK
│   │   └── foobar2000_SDK.vcxproj
│   └── shared
│        └── shared.vcxproj
├── libPPUI
│   └── libPPUI.vcxproj
└── pfc
     └── pfc.vcxproj
```

&nbsp;

### サンプルプロジェクトのビルド設定

■ Visual Studio でサンプルプロジェクトのソリューション (foo_sample.sln) を開きます

Visual Studio を起動し、「プロジェクトやソリューションを開く」で foo_sample.sln を選択します

ソリューション エクスプローラー画面に、以下のプロジェクトが表示されていることを確認します。

- foo_sample
- foobar2000_component_client
- foobar2000_SDK
- foobar2000_sdk_helpers
- libPPUI
- pfc

&nbsp;

■ ソリューションの構成マネージャーに x64 の設定を追加します

ソリューション エクスプローラーで、ソリューションの右クリックメニューから「構成マネージャー...」を選択すると設定画面が表示されます。

foo_sample のソリューション プラットフォームには x86 のみが登録されているので、x64 向けのプラットフォーム設定を新規作成して以下の通りにカスタマイズします。

- 構成 : Debug, プラットフォーム : x64

|プロジェクト               |構成          |プラットフォーム|ビルド|
|---------------------------|--------------|----------------|------|
|foo_sample                 |Debug         |x64             |✓    |
|foobar2000_component_client|Debug         |x64             |✓    |
|foobar2000_SDK             |Debug         |x64             |✓    |
|foobar2000_sdk_helpers     |Debug         |x64             |✓    |
|libPPUI                    |Debug         |x64             |✓    |
|pfc                        |**Debug FB2K**|x64             |✓    |

- 構成 : Release, プラットフォーム : x64

|プロジェクト               |構成            |プラットフォーム|ビルド|
|---------------------------|----------------|----------------|------|
|foo_sample                 |Release         |x64             |✓    |
|foobar2000_component_client|Release         |x64             |✓    |
|foobar2000_SDK             |Release         |x64             |✓    |
|foobar2000_sdk_helpers     |Release         |x64             |✓    |
|libPPUI                    |Release         |x64             |✓    |
|pfc                        |**Release FB2K**|x64             |✓    |

&nbsp;

■ 各プロジェクトのプロパティを変更します

ソリューション エクスプローラーで、プロジェクトの右クリックメニューから「プロパティ」を選択すると設定画面が表示されるので、以下の通りに設定を変更します。

- 構成 : すべての構成, プラットフォーム : Win32

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

- 構成 : すべての構成, プラットフォーム : x64

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

&nbsp;

■ ビルドを実行します

メニューの「ビルド」→「ソリューションのリビルド」を実行して、以下の構成とプラットフォームの組み合わせでビルドが通ることを確認します

- 構成 : Debug構成, プラットフォーム : Win32
- 構成 : Release構成, プラットフォーム : Win32
- 構成 : Debug, プラットフォーム : x64
- 構成 : Release, プラットフォーム : x64

&nbsp;

## foo_input_wave_loop のビルド環境構築

foo_input_wave_loop のためのプロジェクトを新規作成してビルドを通すための設定を記します。

&nbsp;

### foo_input_wave_loop のフォルダ構成

foorbar2000 SDK のサンプルプロジェクト (foo_sample) に倣って以下のフォルダ構成とします。

```
SDK-2023-09-23
├── foobar2000
│   ├── foo_input_validator
│   ├── foo_input_wave_loop
│   │   ├── foo_input_wave_loop.sln
│   │   └── foo_input_wave_loop.vcxproj
│   ├── foobar2000_component_client
│   │   └── foobar2000_component_client.vcxproj
│   ├── helpers
│   │   └── foobar2000_sdk_helpers.vcxproj
│   ├── helpers-mac
│   ├── SDK
│   │   └── foobar2000_SDK.vcxproj
│   └── shared
│        └── shared.vcxproj
├── libPPUI
│   └── libPPUI.vcxproj
└── pfc
     └── pfc.vcxproj
```

&nbsp;

### foo_input_wave_loop のプロジェクト作成

事前に foorbar2000 SDK を解凍したものを用意しておきます。

■ Visual Studio でプロジェクトを新規作成します

Visual Studio を起動し、「新しいプロジェクトの作成」を選択します。

プロジェクト テンプレートは「空のプロジェクト (C++ Windows コンソール)」を選択します。

プロジェクトの設定は以下の通りとします。

- プロジェクト名 : foo_input_wave_loop
- 場所 : SDK-2023-09-23\foobar2000\
- ソリューションとプロジェクトを同じディレクトリに配置する : Yes

※ foobar200 プラグインのプロジェクト名は、必ず "foo_" から始まる名前でなければなりません

&nbsp;

■ ソリューションにソースファイルを追加登録します

SDK-2023-09-23\foobar2000\foo_input_wave_loop のフォルダに以下のファイルをコピーします。

- foo_input_wave_loop.cpp
- foo_input_wave_loop.h

ソリューション エクスプローラーで、foo_input_wave_loop プロジェクトのの右クリックメニューから「追加」→「既存の項目...」を選択し、foo_input_wave_loop のフォルダにコピーした上記のファイルを追加します。

&nbsp;

■ ソリューションに foobar2000 プラグインのビルドに必要なプロジェクトを追加します

ソリューション エクスプローラーで、ソリューションの右クリックメニューから「追加」→「既存のプロジェクト...」を選択し、foorbar2000 SDK に含まれる以下のプロジェクトを追加します。

- foobar2000\foobar2000_component_client\foobar2000_component_client.vcxproj
- foobar2000\SDK\foobar2000_SDK.vcxproj
- foobar2000\helpers\foobar2000_sdk_helpers.vcxproj
- libPPUI\libPPUI.vcxproj
- pfc\pfc.vcxproj

&nbsp;

■ プロジェクトの依存関係を設定します

ソリューション エクスプローラーで、ソリューションの右クリックメニューから「プロジェクトの依存関係...」を選択し、依存関係を以下の通り設定します。

|プロジェクト               |依存先                                                                           |
|---------------------------|---------------------------------------------------------------------------------|
|foo_input_wave_loop        |foobar2000_component_client, foobar2000_SDK, foobar2000_sdk_helpers, libPPUI, pfc|
|foobar2000_component_client|(なし)                                                                           |
|foobar2000_SDK             |(なし)                                                                           |
|foobar2000_sdk_helpers     |(なし)                                                                           |
|libPPUI                    |(なし)                                                                           |
|pfc                        |(なし)                                                                           |

ソリューション エクスプローラーで、foo_input_wave_loop プロジェクトの右クリックメニューから「追加」→「参照...」を選択し、以下のプロジェクトを参照先に追加します。

- foobar2000_component_client
- foobar2000_SDK
- foobar2000_sdk_helpers
- libPPUI
- pfc

&nbsp;

■ ソリューションの構成マネージャーを変更します

ソリューション エクスプローラーで、ソリューションの右クリックメニューから「構成マネージャー...」を選択すると設定画面が表示されるので、以下の通りにカスタマイズします。

- 構成 : Debug, プラットフォーム : x86

|プロジェクト               |構成          |プラットフォーム|ビルド|
|---------------------------|--------------|----------------|------|
|foo_input_wave_loop        |Debug         |Win32           |✓    |
|foobar2000_component_client|Debug         |Win32           |✓    |
|foobar2000_SDK             |Debug         |Win32           |✓    |
|foobar2000_sdk_helpers     |Debug         |Win32           |✓    |
|libPPUI                    |Debug         |Win32           |✓    |
|pfc                        |**Debug FB2K**|Win32           |✓    |

- 構成 : Release, プラットフォーム : x86

|プロジェクト               |構成            |プラットフォーム|ビルド|
|---------------------------|----------------|----------------|------|
|foo_input_wave_loop        |Release         |Win32           |✓    |
|foobar2000_component_client|Release         |Win32           |✓    |
|foobar2000_SDK             |Release         |Win32           |✓    |
|foobar2000_sdk_helpers     |Release         |Win32           |✓    |
|libPPUI                    |Release         |Win32           |✓    |
|pfc                        |**Release FB2K**|Win32           |✓    |

- 構成 : Debug, プラットフォーム : x64

|プロジェクト               |構成          |プラットフォーム|ビルド|
|---------------------------|--------------|----------------|------|
|foo_input_wave_loop        |Debug         |x64             |✓    |
|foobar2000_component_client|Debug         |x64             |✓    |
|foobar2000_SDK             |Debug         |x64             |✓    |
|foobar2000_sdk_helpers     |Debug         |x64             |✓    |
|libPPUI                    |Debug         |x64             |✓    |
|pfc                        |**Debug FB2K**|x64             |✓    |

- 構成 : Release, プラットフォーム : x64

|プロジェクト               |構成            |プラットフォーム|ビルド|
|---------------------------|----------------|----------------|------|
|foo_input_wave_loop        |Release         |x64             |✓    |
|foobar2000_component_client|Release         |x64             |✓    |
|foobar2000_SDK             |Release         |x64             |✓    |
|foobar2000_sdk_helpers     |Release         |x64             |✓    |
|libPPUI                    |Release         |x64             |✓    |
|pfc                        |**Release FB2K**|x64             |✓    |

&nbsp;

■ foo_input_wave_loop プロジェクトのプロパティを変更します

ソリューション エクスプローラーで、foo_input_wave_loop プロジェクトの右クリックメニューから「プロパティ」を選択すると設定画面が表示されるので、以下の通りに設定を変更します。

- 構成 : すべての構成, プラットフォーム : Win32

  - 構成プロパティ － 全般 － 構成の種類  
    &ensp; ダイナミック ライブラリ (.dll)

  - 構成プロパティ － 全般 － C++言語標準  
    &ensp; ISO C++17 標準 (/std:c++17)

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

  - 構成プロパティ － C/C++ － 全般 － 追加のインクルード ディレクトリ  
    &ensp; ..;../..

  - 構成プロパティ －リンカー － 入力 － 追加の依存ファイル  
    &ensp; ../shared/shared-$(Platform).lib

  - 構成プロパティ －リンカー － システム － サブシステム  
    &ensp; Windows (/SUBSYSTEM:WINDOWS)

- 構成 : すべての構成, プラットフォーム : x64

  - 構成プロパティ － 全般 － 構成の種類  
    &ensp; ダイナミック ライブラリ (.dll)

  - 構成プロパティ － 全般 － C++言語標準  
    &ensp; ISO C++17 標準 (/std:c++17)

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

  - 構成プロパティ － C/C++ － 全般 － 追加のインクルード ディレクトリ  
    &ensp; ..;../..

  - 構成プロパティ －リンカー － 入力 － 追加の依存ファイル  
    &ensp; ../shared/shared-$(Platform).lib

  - 構成プロパティ －リンカー － システム － サブシステム  
    &ensp; Windows (/SUBSYSTEM:WINDOWS)

&nbsp;

■ foo_input_wave_loop 以外のプロジェクトのプロパティを変更します

ソリューション エクスプローラーで、foo_input_wave_loop 以外の各プロジェクトの右クリックメニューから「プロパティ」を選択すると設定画面が表示されるので、以下の通りに設定を変更します。

- 構成 : すべての構成, プラットフォーム : Win32

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

- 構成 : すべての構成, プラットフォーム : x64

  - 構成プロパティ － VC++ ディレクトリ － インクルード ディレクトリ  
    &ensp; C:\Program Files\Windows Template Library\WTL10_10320_Release\Include;$(IncludePath)

&nbsp;

■ ビルドを実行します

メニューの「ビルド」→「ソリューションのリビルド」を実行して、以下の構成とプラットフォームの組み合わせで foo_input_wave_loop.dll をビルドします。

- 構成 : Debug構成, プラットフォーム : Win32
- 構成 : Release構成, プラットフォーム : Win32
- 構成 : Debug, プラットフォーム : x64
- 構成 : Release, プラットフォーム : x64

&nbsp;

■ コンポーネントファイルの構成

配布用のコンポーネントファイル (foo_input_wave_loop.fb2k-component) の実体は zip ファイルで、その内部構成は以下の通りです。

```
foo_input_wave_loop.fb2k-component
├── foo_input_wave_loop.dll (foo_input_wave_loop\Release\foo_input_wave_loop.dll)
└── x64
     └──  foo_input_wave_loop.dll (foo_input_wave_loop\x64\Release\foo_input_wave_loop.dll)
```


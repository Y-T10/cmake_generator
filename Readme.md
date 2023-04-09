# CMakeScriptWizard

## 概要
CMakeScriptWizard (CSWiz) は、CMakeが実行するスクリプトを自動生成するツールです．
生成には雛形となるコードを用いるため、ユーザ独自の雛形を用いてコードを生成することができます．

## 使い方
`sample`にある`SayHello`プログラムのディレクトリを例にツールの使い方を説明します．
移行のコマンド操作は`AppHello`ディレクトリにて行っていると考えてください．

```
AppHello/
└─src
    ├── main.cpp
    ├── say-hello.cpp
    └── say-hello.hpp
```

### テンプレートファイルの追加
`csw`は作業ディレクトリの`templates`からテンプレートファイルを読み込むため、`AppHello`に`templates`ディレクトリを追加し、そこにテンプレートファイルを追加します．

`templates`追加後の`AppHello`．

```
AppHello/
├─src
│  ├── main.cpp
│  ├── say-hello.cpp
│  └── say-hello.hpp
└── templates
    ├── addSubDirectories.jinja
    ├── binary.jinja
    ├── library.jinja
    └── project.jinja
```

### プログラムのビルドスクリプトの生成
プログラムのビルドスクリプトは下記の通りに実行することで生成できます．

```bash
path/to/csw -n SayHello -t binary ./src/
```

生成されるコードの例．

```CMake
# define library
add_executable(SayHello)

# Build properties

# Target sources
target_sources(SayHello PRIVATE
main.cpp
say-hello.cpp
)

# Target include directories
target_include_directories(SayHello PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)
```

### プロジェクトファイルの生成
プロジェクト用スクリプトは下記の通りに実行することで生成できます．

```bash
path/to/csw -t project ./
```

生成されるコードの例．

```CMake
cmake_minimum_required(VERSION 3.22.1)

project(AppHello VERSION 0.0.0 LANGUAGES CXX)

cmake_policy(SET CMP0076 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0076 NEW)
cmake_policy(SET CMP0128 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0128 NEW)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_BUILD_TYPE Release)
# sub directories
add_subdirectory(src)
```

## TODO
* [ ] スクリプトの種類の指定方法を変更．
  - [ ] 複数選択できるようにする．
  - [ ] オプションを使用しない．

## ライセンス
### fmt
Copyright (c) 2012 - present, Victor Zverovich and {fmt} contributors

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## inja
MIT License

Copyright (c) 2018-2021 Berscheid

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## cxxopt
Copyright (c) 2014 Jarryd Beck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

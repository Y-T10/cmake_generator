# CMakeTGen

CMakeTGen は、CMake で利用するファイルを雛形から生成するツールです．
プログラムは[draft](https://github.com/Y-T10/cmake_generator/tree/draft)ブランチにて開発しています。

## プロジェクトの状態

現在このプロジェクトはツールの設計段階にあります．

## 使用例
プロジェクト`newProject`のCMakeファイルを生成する．
```bash
tcm project -n "newProject" -v "0.0.0" -l "CXX" -b "Release"
```

Threadライブライに依存するライブラリ`newLibrary`のCMakeファイルを生成する．
```bash
tcm library -n "newLibrary" -d ./src -l "Thread"
```

## ツールでできるようにしたいこと
* template内の雛形ファイルからコードを自動生成する。
  - 雛形ファイルはCMakeの記法とテンプレートエンジンJinjaのテンプレート記法を混ぜたもの。
* ユーザが指定した設定より雛形ファイルからCMakeListst.txtを生成する．
* ユーザの開発環境を調べてCMakeListst.txtを更新する．

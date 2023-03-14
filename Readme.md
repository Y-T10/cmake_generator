# CMakeTGen

CMakeTGen は、CMake で利用するファイルを雛形から生成するツールです．
プログラムは[draft](https://github.com/Y-T10/cmake_generator/tree/draft)ブランチにて開発しています。

## プロジェクトの状態

現在このプロジェクトはツールの設計段階にあります．

## ツールでできるようにしたいこと
* template内の雛形ファイルからコードを自動生成する。
  - 雛形ファイルはCMakeの記法とテンプレートエンジンJinjaのテンプレート記法を混ぜたもの。
* ユーザが指定した設定より雛形ファイルからCMakeListst.txt を生成する．
* ユーザの開発環境を調べてCMakeListst.txt を更新する．

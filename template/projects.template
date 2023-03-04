# プロジェクト設定

# project.cmakeVersionMin: cmakeの最低バージョン
# project.names: プロジェクト名．
# project.version: プロジェクトのバージョン．
# project.language: プロジェクトのソースコードの言語．
# project.defBuildType: デフォルトのビルドタイプ．
#   "Debug", "Release"等が入る
# project.policies: CMakeのポリオシー設定の一覧．
#   要素: {number = "XXXX", value = "NEW|OLD", isGlobal = true|false} (Xは[0,9]の番号)
# project.includes: CMakeが扱うモジュールのパスの一覧
# project.packages: プロジェクトが扱うパッケージの一覧．
#   要素: {name = "package name"}
# project.subdirecotries: CMakeが辿るプロジェクトのサブディレクトリ

cmake_minimum_required(VERSION {{project.cmakeVersionMin}})

# CMake Project
project({{project.name}} VERSION {{project.version}} LANGUAGES {{project.language}})

# CMake Policy
{% for policy in project.policies %}
cmake_policy(SET CMP{{policy.number}} {{policy.value}})
{% if policy.isGlobal %}
set(CMAKE_POLICY_DEFAULT_CMP{{policy.number}} {{policy.value}})
{% endif %}
{% endfor %}

# Default Build Type
set(CMAKE_BUILD_TYPE {{project.defBuildType}})

# Include files
{% for inc in project.includes %}
include({{inc}})
{% endfor %}

# Packages
{% for pkg in project.packages %}
find_package({{pkg.name}} REQUIRED)
{% endfor %}

# Sub directory
{% for dir in project.subdirecotries %}
add_subdirectory({{dir}})
{% endfor %}
# target.isProgram: ターゲットがプログラムか．
# target.name: プログラム名
# target.properties: プログラムビルド時のプロパティ
# target.sources: プログラムのソースコード
# target.includeDirs: プログラムのインクルードディレクトリ
# target.libraries: プログラムのライブラリ

{% if target.isProgram %}
add_executable({{target.name}})
{% else %}
add_library({{target.name}})
{% endif %}

# Build properties
{% for property in target.properties %}
set_target_properties({{target.name}} PROPERTIES {{property.name}} {{property.value}})
{% endfor %}

# Target sources
target_sources({{target.name}} PRIVATE
{% for src in target.sources %}
{{src}}
{% endfor %}
)

# Target include directories
target_include_directories({{target.name}} PUBLIC
{% for dir in target.includeDirs %}
{{dir}}
{% endfor %}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries({{target.name}} PRIVATE
{% for lib in target.libraries %}
{{lib}}
{% endfor %}
)
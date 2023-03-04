# ターゲットのビルド設定

# target.isProgram: ターゲットがプログラムか．
# target.name: ターゲット名
# target.properties: ターゲットビルド時のプロパティ
#   要素: {name = "property name", value = "property value"}
# target.sources: ターゲットのソースコード
# target.includeDirs: ターゲットのインクルードディレクトリ
# target.libraries: ターゲットのライブラリ

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
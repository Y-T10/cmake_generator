# define library
add_library({{target.name}})

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
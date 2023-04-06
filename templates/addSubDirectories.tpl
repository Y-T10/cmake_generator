# sub directories
{% for dir in subDirs %}
add_subdirectory({{dir}})
{% endfor %}
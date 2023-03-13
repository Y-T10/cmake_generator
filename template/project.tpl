cmake_minimum_required(VERSION {{cmakeVersionMin}})

project({{project.name}} VERSION {{project.version}} LANGUAGES {{project.lang}})

{% for policy in project.policies %}
cmake_policy(SET CMP{{policy.number}} {{policy.value}})
{% if policy.isGlobal %}
set(CMAKE_POLICY_DEFAULT_CMP{{policy.number}} {{policy.value}})
{% endif %}
{% endfor %}

set(CMAKE_BUILD_TYPE {{project.buildType}})
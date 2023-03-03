cmake_minimum_required(VERSION {{project.cmakeVersion}})

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
find_package({{pkg.name}} REQUIRED CONFIG REQUIRED)
{% endfor %}

# Sub directory
{% for dir in project.subdirecotries %}
add_subdirectory({{dir}} REQUIRED CONFIG REQUIRED)
{% endfor %}
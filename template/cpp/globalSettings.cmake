# C++用のグローバル設定

# 入力例
# global.compilerOption = "-Wall" (デフォルト値)
# global.properties = [{"CXX_STANDARD", 20}, {"CXX_EXTENSIONS", true}] (trueは"ON"に変換される)
# 出力例
# add_compile_options(-Wall .... $<$<CONFIG:Debug>:-g3>)
# set_property(GLOBAL PROPERTY CXX_STANDARD 20)
# set_property(GLOBAL PROPERTY CXX_EXTENSIONS ON)

add_compile_options({{global.compilerOption}} $<$<CONFIG:Debug>:-g3>)
{% for property in global.properties %}
set_property(GLOBAL PROPERTY {{property.name}} {{property.value}})
{% endfor %}
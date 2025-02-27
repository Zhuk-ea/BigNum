# CMakeList.txt: проект CMake для BigNums; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BigNums")

# Добавьте источник в исполняемый файл этого проекта.
add_library (BigNums SHARED src/BigNum.cpp include/BigNum.h src/Func.h src/Info.h)


target_include_directories(BigNums PRIVATE
    include
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_executable(test
    src/main.cpp
)

target_link_libraries(test PRIVATE
    BigNums
)


target_include_directories(test PRIVATE
    include
)

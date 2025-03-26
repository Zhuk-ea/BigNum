cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BigNums")

add_library (BigNums SHARED src/BigNum.cpp include/BigNum.h include/Func.h include/Info.h)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tutor_tests tests/test.cpp)
target_link_libraries(tutor_tests PRIVATE BigNums Catch2::Catch2WithMain)
add_custom_target(tutor_test ./tutor_tests DEPENDS tutor_tests)


target_include_directories(BigNums PRIVATE
    include
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_executable(tests
    src/Tests.cpp
    src/main.cpp
)

target_link_libraries(tests PRIVATE
    BigNums
)


target_include_directories(tests PRIVATE
    include
)

add_custom_target(test ./tests DEPENDS tests)

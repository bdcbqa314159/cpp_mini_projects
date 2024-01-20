set(EXE_SOURCE_1
    code.cpp)

set (EXE_TESTS
    application.cpp)

add_executable(${PROJECT_1} ${EXE_SOURCE_1})
add_executable(tests ${EXE_TESTS})
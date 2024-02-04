set(EXE_SOURCE_1
    code.cpp)

set (EXE_TESTS
    application.cpp DataMenu.hpp Datamenu.cpp)

set (EXE_MENU
    menu.cpp)

add_executable(${PROJECT_1} ${EXE_SOURCE_1})
add_executable(tests ${EXE_TESTS})
add_executable(menu ${EXE_MENU})
set(EXE_SOURCE_1
    code.cpp)

set (EXE_TESTS application.cpp 
                Menu.cpp 
                Menu.hpp 
                io_utility.hpp 
                io_utility.cpp 
                DataMenu.hpp 
                Datamenu.cpp 
                Checker.hpp 
                Person.hpp 
                Person.cpp 
                ABO.hpp 
                ABO.cpp 
                Donor.hpp 
                Donor.cpp 
                Donors.hpp 
                Donors.cpp
                Hospital.hpp
                Hospital.cpp
                Hospitals.hpp
                Hospitals.cpp
                BloodStock.hpp
                BloodStock.cpp)

add_executable(${PROJECT_1} ${EXE_SOURCE_1})
add_executable(tests ${EXE_TESTS})
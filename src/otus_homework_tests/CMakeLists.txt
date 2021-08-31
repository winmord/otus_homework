cmake_minimum_required(VERSION 3.0.0)
project(otus_homework_tests C CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS /wd4251 /wd4275 /wd4003 /wd4005 /wd4503 /wd4290 )
endif()

find_package(Threads REQUIRED)

include_directories(${CONAN_INCLUDE_DIRS})
include_directories(${otus_homework_SOURCE_DIR}/include)
include_directories(${otus_homework_tests_SOURCE_DIR}/include)

set(SOURCE_FILES
	src/include/common_test_functions.hpp

	src/common_test_functions.cpp
	src/main.cpp
	src/month1_lesson3_homework_tests.cpp
	src/month1_lesson4_homework_tests.cpp
	src/month3_lesson12_homework_tests.cpp
	src/month3_lesson14_homework_tests.cpp
	src/month3_lesson15_homework_tests.cpp
	src/month3_lesson23_homework_tests.cpp
   )
	
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})
	
add_executable(otus_homework_tests ${SOURCE_FILES})
target_link_libraries(otus_homework_tests otus_homework ${CONAN_LIBS} Threads::Threads)
add_test(NAME "otus_homework_tests" COMMAND otus_homework_tests)

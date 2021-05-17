cmake_minimum_required(VERSION 3.0.0)
project(otus_homework_tests C CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS /wd4251 /wd4275 /wd4003 /wd4005 /wd4503 /wd4290 )
endif()

include_directories(${CONAN_INCLUDE_DIRS})
include_directories(${otus_homework_SOURCE_DIR}/include)

set(SOURCE_FILES
	src/main.cpp
	)
	
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})
	
add_executable(otus_homework_tests ${SOURCE_FILES})
target_link_libraries(otus_homework_tests otus_homework ${CONAN_LIBS})
add_test(NAME "otus_homework_tests" COMMAND otus_homework_tests)

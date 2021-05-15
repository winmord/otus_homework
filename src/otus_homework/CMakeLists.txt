cmake_minimum_required(VERSION 3.0.0)
project(otus_homework C CXX)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
endif()

add_definitions(-DOTUS_HOMEWORK_DLL_EXPORTS)
if (${BUILD_SHARED_LIBS})
    add_definitions(-DOTUS_HOMEWORK_DLL)
endif ()

if(MSVC)
    add_definitions(/wd4251 /wd4275 /wd4003 /wd4005 /wd4503 /wd4290 -D_SCL_SECURE_NO_WARNINGS)
else ()
    message("not ready for non-msvc compilation")
endif ()

include_directories(${otus_homework_SOURCE_DIR}/include)

set(SOURCE_FILES
	include/otus_homework/adapters/movable_adapter.hpp
	include/otus_homework/commands/move_command.hpp
	include/otus_homework/interfaces/i_command.hpp
	include/otus_homework/interfaces/i_movable.hpp
	include/otus_homework/interfaces/i_uobject.hpp
	include/otus_homework/movement_vector.hpp
	include/otus_homework/otus_homework_api.hpp
	src/adapters/movable_adapter.cpp
	src/commands/move_command.cpp
	src/movement_vector.cpp
	)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})
	
add_library(otus_homework ${SOURCE_FILES})
target_link_libraries(otus_homework ${CONAN_LIBS})
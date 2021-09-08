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
	include/otus_homework/commands/burn_fuel_command.hpp
	include/otus_homework/commands/change_velocity_command.hpp
	include/otus_homework/commands/check_fuel_command.hpp
	include/otus_homework/commands/hard_stop_command.hpp
	include/otus_homework/commands/initialize_tank_command.hpp
	include/otus_homework/commands/ioc_checkout_scope_command.hpp
	include/otus_homework/commands/ioc_new_scope_command.hpp
	include/otus_homework/commands/ioc_register_command.hpp
	include/otus_homework/commands/ioc_unregister_command.hpp
	include/otus_homework/commands/macro_command.hpp
	include/otus_homework/commands/move_command.hpp
	include/otus_homework/commands/move_to_command.hpp
	include/otus_homework/commands/rotate_command.hpp
	include/otus_homework/commands/run_command.hpp
	include/otus_homework/commands/setup_tank_direction_command.hpp
	include/otus_homework/commands/setup_tank_owner_command.hpp
	include/otus_homework/commands/setup_tank_position_command.hpp
	include/otus_homework/commands/soft_stop_command.hpp

	include/otus_homework/interfaces/i_command.hpp
	include/otus_homework/interfaces/i_fuel_burnable.hpp
	include/otus_homework/interfaces/i_fuel_checkable.hpp
	include/otus_homework/interfaces/i_movable.hpp
	include/otus_homework/interfaces/i_rotatable.hpp
	include/otus_homework/interfaces/i_state.hpp
	include/otus_homework/interfaces/i_uobject.hpp
	include/otus_homework/interfaces/i_velocity_changable.hpp

	include/otus_homework/states/move_to_state.hpp
	include/otus_homework/states/soft_stop_state.hpp
	include/otus_homework/states/usual_state.hpp

	include/otus_homework/utils/ioc_container.hpp
	include/otus_homework/utils/ioc_storage.hpp

	include/otus_homework/blocking_queue.hpp
	include/otus_homework/command_executor.hpp
	include/otus_homework/globals.hpp
	include/otus_homework/movement_vector.hpp
	include/otus_homework/otus_homework_api.hpp

	src/commands/burn_fuel_command.cpp
	src/commands/change_velocity_command.cpp
	src/commands/check_fuel_command.cpp
	src/commands/hard_stop_command.cpp
	src/commands/initialize_tank_command.cpp
	src/commands/ioc_checkout_scope_command.cpp
	src/commands/ioc_new_scope_command.cpp
	src/commands/ioc_register_command.cpp
	src/commands/ioc_unregister_command.cpp
	src/commands/macro_command.cpp
	src/commands/move_command.cpp
	src/commands/move_to_command.cpp
	src/commands/rotate_command.cpp
	src/commands/run_command.cpp
	src/commands/setup_tank_direction_command.cpp
	src/commands/setup_tank_owner_command.cpp
	src/commands/setup_tank_position_command.cpp
	src/commands/soft_stop_command.cpp
	
	src/states/move_to_state.cpp
	src/states/soft_stop_state.cpp
	src/states/usual_state.cpp

	src/utils/ioc_container.cpp
	src/utils/ioc_storage.cpp

	src/command_executor.cpp
	src/globals.cpp
	src/movement_vector.cpp
	)

foreach(SOURCE_FILE IN LISTS SOURCE_FILES)
	execute_process(
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../utils/adapters_generator.exe ${CMAKE_CURRENT_SOURCE_DIR}
												   ${SOURCE_FILE}
												   "include/otus_homework/adapters/generated"
	)
endforeach()

set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/otus_homework/adapters/generated)
add_custom_target(clean-all
	rm -rf "${CMAKE_CURRENT_SOURCE_DIR}/include/otus_homework/adapters/generated/*"
	COMMAND cmake --build ${CMAKE_BINARY_DIR} --target clean
)

file(GLOB generated_headers CONFIGURE_DEPENDS "include/otus_homework/adapters/generated/*.hpp")

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES} ${generated_headers})
	
add_library(otus_homework ${SOURCE_FILES} ${generated_headers})
target_link_libraries(otus_homework ${CONAN_LIBS})
#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <otus_homework/command_executor.hpp>
#include <otus_homework/commands/hard_stop_command.hpp>
#include <otus_homework/states/usual_state.hpp>
#include <otus_homework/commands/move_to_command.hpp>
#include <otus_homework/commands/run_command.hpp>

#include "include/common_test_functions.hpp"

using namespace fakeit;
using namespace tank_battle_server;

class test_command : public i_command
{
public:
	test_command(std::shared_ptr<bool> is_executed)
		: is_executed_(std::move(is_executed))
	{
	}

	void execute() override
	{
		*this->is_executed_ = true;
	}

private:
	std::shared_ptr<bool> is_executed_;
};

TEST_CASE("move to state test")
{
	auto is_executed = std::make_shared<bool>(false);
	auto execution_condition = std::make_shared<std::condition_variable>();

	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	auto state = std::make_shared<usual_state>(command_queue);
	auto pointer_to_state = std::make_shared<std::shared_ptr<i_state>>(state);

	const command_executor cmd_executor(pointer_to_state, command_queue);

	auto new_command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();
	const auto move_to = std::make_shared<move_to_command>(pointer_to_state, command_queue, new_command_queue);
	command_queue->push(move_to);

	const auto test_cmd = std::make_shared<test_command>(is_executed);
	command_queue->push(test_cmd);

	const auto hard_stop = std::make_shared<hard_stop_command>(pointer_to_state);
	command_queue->push(hard_stop);

	check_command_executor_finish(cmd_executor);

	REQUIRE_FALSE(*is_executed);
	REQUIRE_FALSE(new_command_queue->empty());
	new_command_queue->pop();
	REQUIRE(new_command_queue->empty());
}

TEST_CASE("run state test")
{
	auto is_executed = std::make_shared<bool>(false);

	auto command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();

	auto state = std::make_shared<usual_state>(command_queue);
	auto pointer_to_state = std::make_shared<std::shared_ptr<i_state>>(state);

	command_executor cmd_executor(pointer_to_state, command_queue);

	auto new_command_queue = std::make_shared<blocking_queue<std::shared_ptr<i_command>>>();
	const auto move_to = std::make_shared<move_to_command>(pointer_to_state, command_queue, new_command_queue);
	command_queue->push(move_to);

	auto test_cmd = std::make_shared<test_command>(is_executed);
	command_queue->push(test_cmd);

	REQUIRE_FALSE(*is_executed);

	const auto run = std::make_shared<run_command>(pointer_to_state, command_queue);
	command_queue->push(run);

	command_queue->push(test_cmd);
	
	const auto hard_stop = std::make_shared<hard_stop_command>(pointer_to_state);
	command_queue->push(hard_stop);

	check_command_executor_finish(cmd_executor);

	REQUIRE(*is_executed);
	REQUIRE_FALSE(new_command_queue->empty());
	REQUIRE(command_queue->empty());
}

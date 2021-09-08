#include <map>
#include <catch2/catch.hpp>
#include <fakeit.hpp>

#include <otus_homework/commands/initialize_tank_command.hpp>
#include <otus_homework/interfaces/i_uobject.hpp>
#include <otus_homework/movement_vector.hpp>

#include "otus_homework/globals.hpp"

using namespace fakeit;
using namespace tank_battle_server;

class tank_object : public i_uobject
{
public:
	std::any get_value(std::string const& key) override
	{
		return this->values_.at(key);
	}

	void set_value(std::string const& key, std::any const& value) override
	{
		values_.emplace(std::pair<std::string, std::any>(key, value));
	}

private:
	std::map<std::string, std::any> values_;
};

TEST_CASE("set tank direction command test")
{
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.new"), std::string("set tank direction command test"))->execute();
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.current"), std::string("set tank direction command test"))->execute();

	auto direction{0};

	Mock<i_uobject> i_uobject_mock;
	When(Method(i_uobject_mock, get_value)).AlwaysDo(
		[&](std::string const& key) { return direction; }
	);
	When(Method(i_uobject_mock, set_value)).AlwaysDo([&](std::string const& key, std::any const& value)
	{
		direction = std::any_cast<int>(value);
	});

	auto obj = ioc_provider::IoC.resolve<i_uobject>("object");

	obj = std::shared_ptr<i_uobject>(&i_uobject_mock(), [](...)
	{
	});

	const auto command_names = std::list<std::string>{std::string("set tank direction")};

	auto cmd = initialize_tank_command(obj, command_names);
	cmd.execute();

	REQUIRE(direction == 1);
}

TEST_CASE("set tank position command test")
{
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.new"), std::string("set tank position command test"))->execute();
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.current"), std::string("set tank position command test"))->execute();

	std::vector<movement_vector> positions;

	for (auto i = 0; i < 4; i++)
	{
		auto obj = ioc_provider::IoC.resolve<i_uobject>("object");

		obj = std::make_shared<tank_object>();

		const auto command_names = std::list<std::string>{std::string("set tank owner"), std::string("set tank position")};

		auto cmd = initialize_tank_command(obj, command_names);
		cmd.execute();

		positions.push_back(std::any_cast<movement_vector>(obj->get_value("position")));
	}

	REQUIRE(positions[0] == movement_vector({ 0, 0 }));
	REQUIRE(positions[1] == movement_vector({ 1, 0 }));
	REQUIRE(positions[2] == movement_vector({ 2, 0 }));
	REQUIRE(positions[3] == movement_vector({ 0, 5 }));
}

TEST_CASE("set tank owner command test")
{
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.new"), std::string("set tank owner command test"))->execute();
	ioc_provider::IoC.resolve<i_command>(std::string("scopes.current"), std::string("set tank owner command test"))->execute();

	auto owner{0};

	Mock<i_uobject> i_uobject_mock;
	When(Method(i_uobject_mock, get_value)).AlwaysDo(
		[&](std::string const& key) { return owner; }
	);
	When(Method(i_uobject_mock, set_value)).AlwaysDo([&](std::string const& key, std::any const& value)
	{
		owner = std::any_cast<int>(value);
	});

	for (auto i = 0; i < 3; i++)
	{
		auto obj = ioc_provider::IoC.resolve<i_uobject>("object");

		obj = std::shared_ptr<i_uobject>(&i_uobject_mock(), [](...)
		{
		});

		const auto command_names = std::list<std::string>{std::string("set tank owner")};

		auto cmd = initialize_tank_command(obj, command_names);
		cmd.execute();

		REQUIRE(owner == 0);
	}

	const auto pointer_to_uobject = std::shared_ptr<i_uobject>(&i_uobject_mock(), [](...)
	{
	});

	const auto command_names = std::list<std::string>{std::string("set tank owner")};

	auto cmd = initialize_tank_command(pointer_to_uobject, command_names);
	cmd.execute();

	REQUIRE(owner == 1);
}

#include "otus_homework/utils/ioc_container.hpp"

namespace tank_battle_server
{
	thread_local std::shared_ptr<ioc_storage> ioc_container::container_ = std::make_shared<ioc_storage>();
}

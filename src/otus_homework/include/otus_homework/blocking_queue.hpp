#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>

namespace tank_battle_server
{
	template <typename T>
	class blocking_queue
	{
	public:
		void push(T const& value)
		{
			std::lock_guard<std::mutex> lg(this->queue_mutex_);
			this->queue_.push(value);
			this->queue_lock_condition_.notify_one();
		}

		T pop()
		{
			std::unique_lock<std::mutex> locker(this->queue_mutex_);
			this->queue_lock_condition_.wait(locker, [this]() { return !this->queue_.empty(); });

			T res(std::move(this->queue_.front()));
			this->queue_.pop();

			return res;
		}

		bool empty()
		{
			std::lock_guard<std::mutex> lg(this->queue_mutex_);

			return queue_.empty();
		}

	private:
		std::mutex queue_mutex_;
		std::condition_variable queue_lock_condition_;
		std::queue<T> queue_;
	};
}

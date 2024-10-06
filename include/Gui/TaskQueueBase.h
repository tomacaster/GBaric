#pragma once

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <iostream>

namespace Gui::Thread
{
    using Task = std::function<void()>;

    class TaskQueueBase
    {
        public:
            TaskQueueBase();
            virtual ~TaskQueueBase() = default;
        protected:
            std::atomic<bool> _done;
            std::queue<Task> _taskQueue;
            std::mutex _mutex;
            std::condition_variable _cv;
            bool FetchTask(Task& task);
    };
}

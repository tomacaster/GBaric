#include "TaskQueueBase.h"

namespace Gui::Thread
{
    Gui::Thread::TaskQueueBase::TaskQueueBase() : _done(false)
    {
        
    }
    bool TaskQueueBase::FetchTask(Task &task)
    {
        return false;
    }
}

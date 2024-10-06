#include "Gui/GuiThread.h"
#include <thread>

namespace Gui::Thread
{
    shared_mutex GuiThread::_queueMutex;
    vector<std::function<void()>> GuiThread::_mainQueue;

    GuiThread::GuiThread(RefPtr<Glib::Dispatcher> emiter) : _emiter(emiter)
    {
        
    }

    void GuiThread::QueueTherad(shared_ptr<void> param)
    {
        for(;;)
        {
            
        }
    }

    bool GuiThread::InitThread()
    {
        

        return true;
    }

    void GuiThread::AddReceiver(std::function<void()> handler)
    {
        lock_guard<shared_mutex> lock(_queueMutex);
        _mainQueue.push_back(std::move(handler));
    }
}


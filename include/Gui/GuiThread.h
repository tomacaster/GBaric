#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include <memory>
#include <functional>
#include <shared_mutex>

using namespace std;
using namespace Glib;

namespace Gui::Thread
{
    class GuiThread
    {
        public:
            bool InitThread();
            void AddReceiver(std::function<void()> handler);

        private:
            GuiThread(RefPtr<Glib::Dispatcher> emiter);
            Glib::RefPtr<Glib::Dispatcher> _emiter;
            static shared_mutex _queueMutex;
            static vector<function<void()>> _mainQueue;
            vector<function<void()>> _queue;
            static void QueueTherad(shared_ptr<void> param);
    };
}

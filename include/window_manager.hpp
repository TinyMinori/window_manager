
#ifndef WINDOW_MANAGER_HPP_
#define WINDOW_MANAGER_HPP_

    extern "C" {
        #include <X11/Xlib.h>
    }

    class Events;

    #include "events.hpp"
    #include "renderer.hpp"

    #include <unordered_map>
    #include <memory>

    class WindowManager {
        public:
            static  std::unique_ptr<WindowManager> create();
            ~WindowManager();
            void    run();

            static int  onXError(Display *display, XErrorEvent *e);
            static int  onWMDetected(Display *display, XErrorEvent *e);
            static bool wm_detected;

            Display *getDisplay();
            const Window    &getRoot();
            std::unordered_map<Window, Window>  &getClients();

        private:
            WindowManager(Display *display);

            Display         *_display;
            const Window    _root;
            std::unordered_map<Window, Window>  _clients;
    };

         

  
#endif
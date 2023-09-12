/*
 * include/application.hpp
 * 
 * Created 25 June 2020, 10:34 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_
    extern "C" {
        #include <X11/Xlib.h>
    }

    #include <unordered_map>
    #include <memory>

    #include <algorithm>
    #include <exception>
    #include <iostream>

    class Application {
        public:
            Application();
            ~Application();

            static int  onXError(Display *display, XErrorEvent *e);
            static int  onWMDetected(Display *display, XErrorEvent *e);

            Display                             *getDisplay();
            const Window                        &getRoot();
            std::unordered_map<Window, Window>  &getClients();

            static bool                         wm_detected;

        private:
            Application(const Application &) =  delete;

            Display                             *_display;
            Window                              _root;
            std::unordered_map<Window, Window>  _clients;
            
    };
#endif
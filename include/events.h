/*
 * include/events.hpp
 * 
 * Created 27 June 2020, 05:09 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

    #include <algorithm>
    #include "application.h"

    class Events {
        public:
            Events(Application &wm);
            ~Events();                 

            void    run();

        private:
            void    onCreateNotify(const XCreateWindowEvent &e);
            void    onDestroyNotify(const XDestroyWindowEvent &e);
            void    onReparentNotify(const XReparentEvent &e);
            void    onConfigureRequest(const XConfigureRequestEvent &e);
            void    onMapRequest(const XMapRequestEvent &e);
            void    onMapNotify(const XMapEvent &e);
            void    onConfigureNotify(const XConfigureEvent &e);
            void    onUnmapNotify(const XUnmapEvent &e);
            void    onButtonPressed(const XButtonPressedEvent &e);
            void    onButtonReleased(const XButtonReleasedEvent &e);
            void    onMotionNotify(const XMotionEvent &e);
            void    onKeyPressed(const XKeyPressedEvent &e);
            void    onKeyReleased(const XKeyReleasedEvent &e);

            Application     &_app;
    };

#endif
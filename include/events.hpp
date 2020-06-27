#ifndef EVENTS_HPP_
#define EVENTS_HPP_

    #include "window_manager.hpp"
    #include "renderer.hpp"

    class WindowManager;

    class Events {
        public:
            static void    loop(WindowManager &wm);

        private:
            Events();
            
            static void    onCreateNotify(WindowManager &wm, const XCreateWindowEvent &e);
            static void    onDestroyNotify(WindowManager &wm, const XDestroyWindowEvent &e);
            static void    onReparentNotify(WindowManager &wm, const XReparentEvent &e);
            static void    onConfigureRequest(WindowManager &wm, const XConfigureRequestEvent &e);
            static void    onMapRequest(WindowManager &wm, const XMapRequestEvent &e);
            static void    onMapNotify(WindowManager &wm, const XMapEvent &e);
            static void    onConfigureNotify(WindowManager &wm, const XConfigureEvent &e);
            static void    onUnmapNotify(WindowManager &wm, const XUnmapEvent &e);
            static void    onButtonPressed(WindowManager &wm, const XButtonPressedEvent &e);
            static void    onButtonReleased(WindowManager &wm, const XButtonReleasedEvent &e);
            static void    onMotionNotify(WindowManager &wm, const XMotionEvent &e);
            static void    onKeyPressed(WindowManager &wm, const XKeyPressedEvent &e);
            static void    onKeyReleased(WindowManager &wm, const XKeyReleasedEvent &e);
    };

#endif
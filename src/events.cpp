/*
 * src/events.cpp
 * 
 * Created 27 June 2020, 05:16 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#include "events.h"
#include "renderer.h"

Events::Events(Application &wm)
    :   _app(wm) {}

Events::~Events() {}

void    Events::run() {
    XEvent e;
    while (1) {
        XNextEvent(_app.getDisplay(), &e);
        //LOG(INFO) << "Received event: " << ToString(e);

        switch (e.type) {
        case CreateNotify:
            onCreateNotify(e.xcreatewindow);
            break;
        case DestroyNotify:
            onDestroyNotify(e.xdestroywindow);
            break;
        case ReparentNotify:
            onReparentNotify(e.xreparent);
            break;
        case MapNotify:
            onMapNotify(e.xmap);
            break;
        case UnmapNotify:
            onUnmapNotify(e.xunmap);
            break;
        case ConfigureNotify:
            onConfigureNotify(e.xconfigure);
            break;
        case MapRequest:
            onMapRequest(e.xmaprequest);
            break;
        case ConfigureRequest:
            onConfigureRequest(e.xconfigurerequest);
            break;
        case ButtonPress:
            onButtonPressed(e.xbutton);
            break;
        case ButtonRelease:
            onButtonReleased(e.xbutton);
            break;
        case MotionNotify:
            while (
                XCheckTypedWindowEvent(
                    _app.getDisplay(), e.xmotion.window, MotionNotify, &e));
            onMotionNotify(e.xmotion);
            break;
        case KeyPress:
            onKeyPressed(e.xkey);
            break;
        case KeyRelease:
            onKeyReleased(e.xkey);
            break;
        default:
            std::cerr << "Ignored event";
        }
    }
}

void    Events::onCreateNotify(const XCreateWindowEvent &e) {}

void    Events::onConfigureRequest(const XConfigureRequestEvent &e) {
    XWindowChanges  changes;

    changes.x = e.x;
    changes.y = e.y;
    changes.width = e.width;
    changes.height = e.height;
    changes.border_width = e.border_width;
    changes.sibling = e.above;
    changes.stack_mode = e.detail;

    if (this->_app.getClients().count(e.window)) {
        const Window frame = this->_app.getClients()[e.window];
        XConfigureWindow(this->_app.getDisplay(), frame, e.value_mask, &changes);
    }

    XConfigureWindow(this->_app.getDisplay(), e.window, e.value_mask, &changes);
    //LOG(INFO) << "Resize " << e.window << " to " < Size<int>(e.width, e.height);
}

void    Events::onDestroyNotify(const XDestroyWindowEvent &e) {}

void    Events::onReparentNotify(const XReparentEvent &e) {}

void    Events::onMapRequest(const XMapRequestEvent &e) {
    
    Renderer::getInstance().frame(this->_app, e.window, false);

    XMapWindow(this->_app.getDisplay(), e.window);
}

void    Events::onMapNotify(const XMapEvent &e) {}

void    Events::onConfigureNotify(const XConfigureEvent &e) {}

void    Events::onUnmapNotify(const XUnmapEvent &e) {
    if (!this->_app.getClients().count(e.window)) {
        std::cout << "Ignore UnmapNotify for non-client window " << e.window;
        return;
    }

    if (e.event == this->_app.getRoot()) {
        std::cout << "Ignore UnmapNotiy for reparented pre-existing window " << e.window;
        return ; 
    }

    Renderer::getInstance().unframe(this->_app, e.window);
}

void    Events::onButtonPressed(const XButtonPressedEvent &e) {}

void    Events::onButtonReleased(const XButtonReleasedEvent &e) {}

void    Events::onMotionNotify(const XMotionEvent &e) {}

void    Events::onKeyPressed(const XKeyPressedEvent &e) {}

void    Events::onKeyReleased(const XKeyReleasedEvent &e) {}
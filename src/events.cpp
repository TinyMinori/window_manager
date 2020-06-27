#include "events.hpp"
#include <glog/logging.h>
#include <algorithm>

Events::Events() {}

void    Events::loop(WindowManager &wm) {
  for (;;) {
    XEvent e;
    XNextEvent(wm.getDisplay(), &e);
    //LOG(INFO) << "Received event: " << ToString(e);

    switch (e.type) {
      case CreateNotify:
        onCreateNotify(wm, e.xcreatewindow);
        break;
      case DestroyNotify:
        onDestroyNotify(wm, e.xdestroywindow);
        break;
      case ReparentNotify:
        onReparentNotify(wm, e.xreparent);
        break;
      case MapNotify:
        onMapNotify(wm, e.xmap);
        break;
      case UnmapNotify:
        onUnmapNotify(wm, e.xunmap);
        break;
      case ConfigureNotify:
        onConfigureNotify(wm, e.xconfigure);
        break;
      case MapRequest:
        onMapRequest(wm, e.xmaprequest);
        break;
      case ConfigureRequest:
        onConfigureRequest(wm, e.xconfigurerequest);
        break;
      case ButtonPress:
        onButtonPressed(wm, e.xbutton);
        break;
      case ButtonRelease:
        onButtonReleased(wm, e.xbutton);
        break;
      case MotionNotify:
        while (XCheckTypedWindowEvent(
            wm.getDisplay(), e.xmotion.window, MotionNotify, &e)) {}
        onMotionNotify(wm, e.xmotion);
        break;
      case KeyPress:
        onKeyPressed(wm, e.xkey);
        break;
      case KeyRelease:
        onKeyReleased(wm, e.xkey);
        break;
      default:
        LOG(WARNING) << "Ignored event";
    }
  }
}

void    Events::onCreateNotify(WindowManager &wm, const XCreateWindowEvent &e) {}

void    Events::onConfigureRequest(WindowManager &wm, const XConfigureRequestEvent &e) {
    XWindowChanges  changes;

    changes.x = e.x;
    changes.y = e.y;
    changes.width = e.width;
    changes.height = e.height;
    changes.border_width = e.border_width;
    changes.sibling = e.above;
    changes.stack_mode = e.detail;

    if (wm.getClients().count(e.window)) {
        const Window frame = wm.getClients()[e.window];
        XConfigureWindow(wm.getDisplay(), frame, e.value_mask, &changes);
    }

    XConfigureWindow(wm.getDisplay(), e.window, e.value_mask, &changes);
    //LOG(INFO) << "Resize " << e.window << " to " < Size<int>(e.width, e.height);
}

void    Events::onDestroyNotify(WindowManager &wm, const XDestroyWindowEvent &e) {}

void    Events::onReparentNotify(WindowManager &wm, const XReparentEvent &e) {}

void    Events::onMapRequest(WindowManager &wm, const XMapRequestEvent &e) {
    
    Renderer::frame(wm, e.window, false);

    XMapWindow(wm.getDisplay(), e.window);
}

void    Events::onMapNotify(WindowManager &wm, const XMapEvent &e) {}

void    Events::onConfigureNotify(WindowManager &wm, const XConfigureEvent &e) {}

void    Events::onUnmapNotify(WindowManager &wm, const XUnmapEvent &e) {
    if (!wm.getClients().count(e.window)) {
        LOG(INFO) << "Ignore UnmapNotify for non-client window " << e.window;
        return;
    }

    if (e.event == wm.getRoot()) {
        LOG(INFO) << "Ignore UnmapNotiy for reparented pre-existing window " << e.window;
        return ; 
    }

    Renderer::unframe(wm, e.window);
}

void    Events::onButtonPressed(WindowManager &wm, const XButtonPressedEvent &e) {}

void    Events::onButtonReleased(WindowManager &wm, const XButtonReleasedEvent &e) {}

void    Events::onMotionNotify(WindowManager &wm, const XMotionEvent &e) {}

void    Events::onKeyPressed(WindowManager &wm, const XKeyPressedEvent &e) {}

void    Events::onKeyReleased(WindowManager &wm, const XKeyReleasedEvent &e) {}
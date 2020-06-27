extern "C" {
    #include <X11/Xutil.h>
}

#include "window_manager.hpp"
#include "renderer.hpp"
#include <glog/logging.h>
#include <algorithm>

using std::unique_ptr;

bool    WindowManager::wm_detected;

unique_ptr<WindowManager>   WindowManager::create() {
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        LOG(ERROR) << "Failed to open X display " << XDisplayName(nullptr);
        return nullptr;
    }

    return unique_ptr<WindowManager>(new WindowManager(display));
}

WindowManager::WindowManager(Display *display)
    : _display(CHECK_NOTNULL(display)),
    _root(DefaultRootWindow(_display))
{}

WindowManager::~WindowManager() {
    XCloseDisplay(_display);
}

void    WindowManager::run() {
    wm_detected = false;

    XSetErrorHandler(&WindowManager::onWMDetected);
    
    XSelectInput(
        _display,
        _root,
        SubstructureRedirectMask | SubstructureNotifyMask);
    
    XSync(_display, false);
    
    if (wm_detected) {
        LOG(ERROR) << "Detected another window manager on display " << XDisplayString(_display);
        return; 
    }

    XSetErrorHandler(&WindowManager::onXError);

    XGrabServer(_display);

    Window  root, parent;
    Window  *top_level_windows;
    unsigned int num_top_level_windows;
    CHECK(XQueryTree(
        _display,
        _root,
        &root,
        &parent,
        &top_level_windows,
        &num_top_level_windows));

    for (unsigned int i = 0; i < num_top_level_windows; i++) {
        Renderer::frame(*this, top_level_windows[i], true);
    }

    XFree(top_level_windows);

    XUngrabServer(_display);

    Events::loop(*this);
}

Display *WindowManager::getDisplay() {
    return _display;
}

const Window  &WindowManager::getRoot() {
    return _root;
}

std::unordered_map<Window, Window>  &WindowManager::getClients() {
    return _clients;
}

int WindowManager::onWMDetected(Display *display, XErrorEvent *e) {
    CHECK_EQ(static_cast<int>(e->error_code), BadAccess);

    wm_detected = true;

    return 0;
}

int WindowManager::onXError(Display *display, XErrorEvent *e) {
    return 0;
}
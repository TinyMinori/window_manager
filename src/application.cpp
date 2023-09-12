/*
 * src/application.cpp
 * 
 * Created 25 June 2020, 10:34 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#include "application.h"
#include "renderer.h"

extern "C" {
    #include <X11/Xutil.h>
}

bool    Application::wm_detected = false;

Application::Application()
    : _display(nullptr) {

    this->_display = XOpenDisplay(nullptr);
    if (this->_display == nullptr) {
        std::cerr << "Failed to open X display " << XDisplayName(nullptr) << std::endl;
        throw std::logic_error("Ooops");
    }

    this->_root = DefaultRootWindow(this->_display);

    wm_detected = false;

    XSetErrorHandler(&onWMDetected);
    
    XSelectInput(
        this->_display,
        this->_root,
        SubstructureRedirectMask | SubstructureNotifyMask);
    
    XSync(this->_display, false);
    
    if (wm_detected) {
        std::cerr << "Detected another window manager on display " << XDisplayString(_display) << std::endl;
        return; 
    }

    XSetErrorHandler(&onXError);

    XGrabServer(this->_display);

    Window  root, parent;
    Window  *top_level_windows;
    unsigned int num_top_level_windows;

    int result = XQueryTree(
        this->_display,
        this->_root,
        &root,
        &parent,
        &top_level_windows,
        &num_top_level_windows);

    if (!result) {
        std::cerr << "Failed to query X tree informations" << std::endl;
        throw std::logic_error("Ooops");
    }

    for (unsigned int i = 0; i < num_top_level_windows; i++) {
        Renderer::getInstance().frame(*this, top_level_windows[i], true);
    }

    XFree(top_level_windows);

    XUngrabServer(this->_display);
}

Application::~Application() {
    XCloseDisplay(this->_display);
}

Display *Application::getDisplay() {
    return this->_display;
}

const Window  &Application::getRoot() {
    return this->_root;
}

std::unordered_map<Window, Window>  &Application::getClients() {
    return this->_clients;
}

int Application::onWMDetected(Display *display, XErrorEvent *e) {
    if (static_cast<int>(e->error_code) == BadAccess)
        throw std::logic_error("Error on WmDetected");

    wm_detected = true;

    return 0;
}

int Application::onXError(Display *display, XErrorEvent *e) {
    return 0;
}
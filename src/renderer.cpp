/*
 * src/renderer.cpp
 * 
 * Created 27 June 2020, 05:23 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#include "renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

Renderer    &Renderer::getInstance() {
    static Renderer instance;

    return instance;
}

void    Renderer::frame(Application &wm, Window w, bool created_before_wm) {
    const unsigned int BORDER_WIDTH = 3;
    const unsigned long BORDER_COLOR = 0xff0000;
    const unsigned long BG_COLOR = 0x0000ff;

    XWindowAttributes x_window_attrs;
    if(!XGetWindowAttributes(wm.getDisplay(), w, &x_window_attrs)) {
        throw std::logic_error("Oops Frame");
    }

    if (created_before_wm) {
        if (x_window_attrs.override_redirect || x_window_attrs.map_state != IsViewable) {
            return ;
        }
    }

    const Window frame = XCreateSimpleWindow(
        wm.getDisplay(),
        wm.getRoot(),
        x_window_attrs.x,
        x_window_attrs.y,
        x_window_attrs.width,
        x_window_attrs.height,
        BORDER_WIDTH,
        BORDER_COLOR,
        BG_COLOR);

    XSelectInput(
        wm.getDisplay(),
        frame,
        SubstructureRedirectMask | SubstructureNotifyMask);

    XAddToSaveSet(wm.getDisplay(), w);

    XReparentWindow(
        wm.getDisplay(),
        w,
        frame,
        0, 0);

    XMapWindow(wm.getDisplay(), frame);

    wm.getClients()[w] = frame;

    std::cout << "Framed window " << w << " [" << frame << "]" << std::endl;
}

void    Renderer::unframe(Application &wm, Window w) {
    const Window frame = wm.getClients()[w];

    XUnmapWindow(wm.getDisplay(), frame);
    XReparentWindow(
        wm.getDisplay(),
        w,
        wm.getRoot(),
        0, 0);

    XRemoveFromSaveSet(wm.getDisplay(), w);

    XDestroyWindow(wm.getDisplay(), frame);

    wm.getClients().erase(w);

    std::cout << "Unframed window " << w << " [" << frame << "]" << std::endl;
}
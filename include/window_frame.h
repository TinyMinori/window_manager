/*
 * include/window_frame.hpp
 * 
 * Created the 08 March 2021, 10:27 pm by TinyMinori
 * Description :
 * 
 * Project repository: https://github.com/TinyMinori
 * Copyright 2023 TinyMinori
 */

#ifndef WINDOW_FRAME_HPP_
#define WINDOW_FRAME_HPP_

extern "C" {
    #include <X11/Xlib.h>
}
#include <memory>

class WindowFrame {
    std::unique_ptr<Window> container;
};

#endif
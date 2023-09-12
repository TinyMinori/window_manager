/*
 * src/main.cpp
 * 
 * Created 25 June 2020, 10:34 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#include <cstdlib>
#include <iostream>
#include "application.h"
#include "events.h"
#include "renderer.h"

int main(int argc, char **argv) {
    try {
        Renderer::getInstance();
        Application     application = Application();
        Events          events = Events(application);

        events.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Failed to initialize window manager." << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
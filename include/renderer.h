/*
 * include/renderer.hpp
 * 
 * Created 27 June 2020, 05:09 by mynori
 * Description :
 * 
 * Project repo https://github.com/mynori
 * Copyright 2023 TinyMinori
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_
    
    #include "application.h"

    class Renderer {
        public:
            ~Renderer();
            Renderer(Renderer const &) = delete;
            void    operator=(Renderer const&) = delete;

            static Renderer &getInstance();
            void            frame(Application &wm, Window w, bool created_before_wm);
            void            unframe(Application &wm, Window w);
        private:
            Renderer();
    };

#endif
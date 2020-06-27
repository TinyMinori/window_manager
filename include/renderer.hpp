#ifndef RENDERER_HPP_
#define RENDERER_HPP_
    
    #include "window_manager.hpp"

    class WindowManager;
    
    class Renderer {
        public:
            static void    frame(WindowManager &wm, Window w, bool created_before_wm);
            static void    unframe(WindowManager &wm, Window w);
        
        private:
            Renderer();
    };

#endif
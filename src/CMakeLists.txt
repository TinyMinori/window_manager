
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/renderer.h"
                "${PROJECT_SOURCE_DIR}/include/application.h"
                "${PROJECT_SOURCE_DIR}/include/events.h"
                "${PROJECT_SOURCE_DIR}/include/window_frame.h"
)

add_library(src
                renderer.cpp
                events.cpp
                application.cpp
                ${HEADER_LIST}
)

target_include_directories(src PUBLIC ../include)
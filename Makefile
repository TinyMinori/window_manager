XEPHYR		= `which Xephyr`

RM			= rm -rf

CXXFLAGS	?= -Wall -g

CXXFLAGS	+= -std=c++1y -Iinclude/

CXXFLAGS	+= `pkg-config --cflags x11 libglog`

LDFLAGS		+= `pkg-config --libs x11 libglog`

SRC			= src/renderer.cpp			\
			  src/events.cpp			\
			  src/window_manager.cpp	\
			  src/main.cpp

OBJ			= $(SRC:.cpp=.o)

NAME		= window_manager

$(NAME)		= all

all:	$(HEADERS) $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean	all

test:
	xinit ./xinitrc -- \
			$(XEPHYR) \
        	:100 \
        	-ac \
        	-screen 800x600 \
        	-host-cursor

.PHONY: $(NAME) all clean fclean re

# WindowManager/Makefile
# 
# Created 25 June 2020, 10:33 by mynori
# Description :
# 
# Project repo https://github.com/mynori
# Copyright 2020 mynori

# Commands
XEPHYR		= `which Xephyr`
ECHO		= echo -e

# Vars
C_RESET		= \e[0m
C_ERROR		= \e[31m
C_SUCCESS	= \e[32m
C_INFO		= \e[94m
C_WARN		= \e[38;5;202m

S_BOLD		= \e[1m

CXXFLAGS	?= -Wall -Werror -g

CXXFLAGS	+= -std=c++11 -Iinclude/

CXXFLAGS	+= -lX11 -lglog # `pkg-config --cflags x11 libglog`

LDFLAGS		+= -lX11 -lglog #`pkg-config --libs x11 libglog`
LDFLAGS		+= -Iinclude/

SRC 		=	src/events.cpp		\
				src/application.cpp	\
				src/main.cpp		\
				src/renderer.cpp

HEADERS		=	include/events.hpp		\
				include/application.hpp	\
				include/renderer.hpp

OBJ			= $(SRC:.cpp=.o)

B_NAME		= window_manager

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
	$(ECHO) "[$(C_SUCCESS)$^$(C_RESET)] Compilation succeed" || \
	($(ECHO) "[$(C_ERROR)$^$(C_RESET)] Compilation failed"; exit 1)


$(NAME): all

all:	$(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) && \
	$(ECHO) "[$(C_SUCCESS)$(B_NAME)$(C_RESET)] Compilation succeed" || \
	($(ECHO) "[$(C_ERROR)$(B_NAME)$(C_RESET)] Compilation failed"; exit 1)

clean:
	@$(RM) $(OBJ) && \
	$(ECHO) "$(C_INFO)Object files removed$(C_RESET)" || \
	$(ECHO) "$(C_WARN)Can't remove object files$(C_RESET)"

fclean:	clean
	@$(RM) $(B_NAME) && \
	$(ECHO) "$(C_INFO)$(B_NAME) removed$(C_RESET)" || \
	$(ECHO) "$(C_WARN)Can't remove $(B_NAME)$(C_RESET)"

re:	fclean	all

test:
	xinit ./xinitrc -- \
			$(XEPHYR) \
        	:100 \
        	-ac \
        	-screen 800x600 \
        	-host-cursor

.PHONY: $(NAME) all clean fclean re

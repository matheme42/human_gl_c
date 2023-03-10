# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matheme <matheme@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 11:06:26 by yalabidi          #+#    #+#              #
#    Updated: 2023/01/26 19:10:34 by matheme          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_RED = \033[0;38;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m

# nom de l'executable
NAME = human_gl

# paths
SRC_PATH= srcs
OBJ_PATH= .objs
INC_PATH= includes



#framework
FRAMEWORK= -lglfw -l dl -lfreetype
FRAMEWORK_INC = libraries/includes

INC= $(INC_PATH)/*

NAME_SRC= main.cpp application.cpp shader.cpp mat4.cpp control.cpp skeleton.cpp object.cpp cubemap.cpp menu.cpp textdisplay.cpp animation.cpp
			

NAME_SRC_C= glad.c \

NAME_SRC_LEN	= $(shell echo -n $(NAME_SRC) | wc -w)
I				= 

OBJ_NAME		= $(NAME_SRC:.cpp=.o)

OBJ_NAME_C		= $(NAME_SRC_C:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME)) $(addprefix $(OBJ_PATH)/,$(OBJ_NAME_C))

DEBUG_FLAG = #-Wall -Wextra #-fsanitize=address

OPTIMISATION_FLAG = -ofast -fsanitize=address#-o3 #-ofast  pas d'interet pour l'instant

CC			= gcc $(OPTIMISATION_FLAG)
GPP			= g++ -std=c++11 $(OPTIMISATION_FLAG) $(DEBUG_FLAG)



all: $(NAME)

$(NAME) : $(OBJS)
	@$(GPP) $^ -o $@ $(FRAMEWORK)
	@echo "	\033[2K\r$(DARK_BLUE)$(NAME):\t\t$(GREEN)loaded\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC) Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(GPP) -I $(INC_PATH) -I $(FRAMEWORK_INC) -c $< -o $@
	@$(eval I=$(shell echo $$(($(I)+1))))
	@printf "\033[2K\r${G}$(DARK_BLUE)>>\t\t\t\t$(I)/$(shell echo $(NAME_SRC_LEN)) ${N}$(BLUE)$<\033[36m \033[0m"

$(OBJ_PATH)/%.o: libraries/lib/%.c $(INC) Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true 
	@$(CC) -I $(FRAMEWORK_INC) -c $< -o $@


clean:
ifeq ("$(wildcard $(OBJ_PATH))", "")
else
	@rm -f $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[2K\r$(DARK_BLUE)$(NAME) objects:\t$(LIGHT_PINK)removing\033[36m \033[0m\n"
endif


fclean: clean
ifeq ("$(wildcard $(NAME))", "")
else
	@rm -f $(NAME)
	@printf "\033[2K\r$(DARK_BLUE)$(NAME):\t\t$(PINK)removing\033[36m \033[0m\n"
endif

re: fclean all

.PHONY: all re clean fclean lib silent

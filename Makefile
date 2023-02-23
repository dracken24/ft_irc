# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 13:22:35 by nadesjar          #+#    #+#              #
#    Updated: 2023/02/22 16:22:02 by dracken24        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS_C 		= ./objs_c/
P_OBJS_S 		= ./objs_s/

P_SRCS_C		= ./srcs_c/
P_SRCS_S		= ./srcs_s/

INCLUDE_PATH	= ./includes/

FILES_C			= $(P_SRCS_C)client.cpp
FILES_S			= $(P_SRCS_S)server.cpp


OBJS_S			= $(patsubst $(P_SRCS_S)%.cpp, $(P_OBJS_S)%.o, $(FILES_S))
OBJS_C			= $(patsubst $(P_SRCS_C)%.cpp, $(P_OBJS_C)%.o, $(FILES_C))

CC				= c++

CFLAGS			= -Wall -Werror -Wextra -std=c++98

NAME_S			= server
NAME_C			= client

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME_S) $(NAME_C) msg_out

$(NAME_S): $(OBJS_S)
	@$(CC) $(OBJS_S) $(CFLAGS) -o $(NAME_S)

$(NAME_C): $(OBJS_C)
	@$(CC) $(OBJS_C) $(CFLAGS) -o $(NAME_C)

# --------------------------- Recompilation Headers --------------------------- #

$(P_OBJS_S)server.o: $(P_SRCS_S)server.cpp
	@mkdir -p $(P_OBJS_S)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_C)client.o: $(P_SRCS_C)client.cpp
	@mkdir -p $(P_OBJS_C)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

# $(P_OBJS)mapTest.o: $(P_SRCS)mapTest.cpp $(INCLUDE_PATH)container.hpp
# 	@$(CC) -I $(CFLAGS) -c $< -o $@
# 	@printf "$G■"

# ----------------------------------- Git ------------------------------------ #

COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

# --------------------------------- Messages --------------------------------- #

msg_in:
	@echo $L"COMPILATION DE ft_irc EN COURS..."$W

msg_out:
	@echo $L"\nft_irc READY !!!\n"$W

signat:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--* $LPROJET:  ft_irc       PAR: NADESJAR$G *--*             |"
	@echo " |             ---------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"
	
# ---------------------------------- Colors ---------------------------------- #

L	= $(shell tput -Txterm setaf 5)
R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

# ---------------------------------- Clean ----------------------------------- #

clean:	
	@rm -fr $(P_OBJS_S) $(P_OBJS_C)

fclean: clean
	@echo $G"                                    BYE BYE !!!"$W
	@rm -f $(NAME_C) $(NAME_S)

re: fclean all


.PHONY: all msg_in msg_out clean fclean re signat

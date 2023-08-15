# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 13:22:35 by nadesjar          #+#    #+#              #
#    Updated: 2023/08/10 15:27:28 by smayrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS_S 		= ./objs/objs/
P_OBJS_C		= ./objs/commands/
P_OBJS_O 		= ./objs/others/

P_SRCS_S		= ./srcs/srcs/
P_SRCS_C		= ./srcs/commands/
P_SRCS_O		= ./srcs/others/

FILES_S			= $(P_SRCS_S)server.cpp $(P_SRCS_S)utils.cpp \
				$(P_SRCS_S)IrcCore.cpp $(P_SRCS_S)init.cpp \
				$(P_SRCS_S)mainLoop.cpp \

FILES_C			= $(P_SRCS_C)join.cpp $(P_SRCS_C)privateMessages.cpp  \
				$(P_SRCS_C)part.cpp $(P_SRCS_C)quitServer.cpp \
				$(P_SRCS_C)kick.cpp $(P_SRCS_C)invite.cpp \
				$(P_SRCS_C)mode.cpp $(P_SRCS_C)admin.cpp \
				$(P_SRCS_C)topic.cpp \

FILES_O			= $(P_SRCS_O)IrcMemory.cpp $(P_SRCS_O)Logger.cpp \
				$(P_SRCS_O)ChannelGestion.cpp $(P_SRCS_O)Splinter.cpp \

OBJS_S			= $(patsubst $(P_SRCS_S)%.cpp, $(P_OBJS_S)%.o, $(FILES_S))
OBJS_S			+= $(patsubst $(P_SRCS_O)%.cpp, $(P_OBJS_O)%.o, $(FILES_O))
OBJS_S 			+= $(patsubst $(P_SRCS_C)%.cpp, $(P_OBJS_C)%.o, $(FILES_C))

CC				= c++

CFLAGS			= -Wall -Wextra -Werror -std=c++98 -Wno-unused-parameter -Wno-unused-variable

NAME_S			= ircserv

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME_S) msg_out

$(NAME_S): $(OBJS_S) $(OBJS_O) $(OBJS_C)
	@$(CC) $(OBJS_S) $(OBJS_O) $(OBJS_C) $(CFLAGS) -o $(NAME_S)

# --------------------------- Recompilation Headers --------------------------- #

INCLUDE_PATH	= ./srcs/

INC_IRC			= $(P_SRCS_S)IrcCore.hpp $(INCLUDE_PATH)/includes/defines.hpp \
				$(INCLUDE_PATH)/others/IrcMemory.hpp $(INCLUDE_PATH)/others/Logger.hpp \
				$(INCLUDE_PATH)/others/ChannelGestion.hpp $(INCLUDE_PATH)/others/Splinter.hpp \

# ------------------------------------------------

$(P_OBJS_S)server.o: $(P_SRCS_S)server.cpp $(INC_IRC)
	@mkdir -p $(P_OBJS_S)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_S)utils.o: $(P_SRCS_S)utils.cpp $(INCLUDE_PATH)/includes/defines.hpp
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_S)IrcCore.o: $(P_SRCS_S)IrcCore.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_S)init.o: $(P_SRCS_S)init.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_S)mainLoop.o: $(P_SRCS_S)mainLoop.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

# ------------------------------------------------

$(P_OBJS_C)join.o: $(P_SRCS_C)join.cpp $(INC_IRC)
	@mkdir -p $(P_OBJS_C)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)privateMessages.o: $(P_SRCS_C)privateMessages.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)part.o: $(P_SRCS_C)part.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"
	
$(P_OBJS_C)kick.o: $(P_SRCS_C)kick.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"
	
$(P_OBJS_C)invite.o: $(P_SRCS_C)invite.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)quitServer.o: $(P_SRCS_C)quitServer.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)admin.o: $(P_SRCS_C)admin.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)mode.o: $(P_SRCS_C)mode.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

$(P_OBJS_C)topic.o: $(P_SRCS_C)topic.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$C■"

# ------------------------------------------------

$(P_OBJS_O)IrcMemory.o: $(P_SRCS_O)IrcMemory.cpp $(INCLUDE_PATH)/includes/defines.hpp $(INCLUDE_PATH)/others/Logger.hpp $(INCLUDE_PATH)/others/IrcMemory.hpp
	@mkdir -p $(P_OBJS_O)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

$(P_OBJS_O)Logger.o: $(P_SRCS_O)Logger.cpp $(INCLUDE_PATH)/includes/defines.hpp $(INCLUDE_PATH)/others/Logger.hpp $(INCLUDE_PATH)/others/IrcMemory.hpp
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

$(P_OBJS_O)ChannelGestion.o: $(P_SRCS_O)ChannelGestion.cpp $(INCLUDE_PATH)/includes/defines.hpp
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

$(P_OBJS_O)Splinter.o: $(P_SRCS_O)Splinter.cpp $(INC_IRC)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

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

R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
Y   = $(shell tput -Txterm setaf 3)
L	= $(shell tput -Txterm setaf 5)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

# ---------------------------------- Clean ----------------------------------- #

clean:	
	@rm -fr $(P_OBJS_S)

fclean: clean
	@echo $G"                                    BYE BYE !!!"$W
	@rm -f $(NAME_S)
	@rm -fr objs

re: fclean all


.PHONY: all msg_in msg_out clean fclean re signat


# client install

# git clone https://github.com/irssi/irssi
# cd irssi
# meson Build
# ninja -C Build && sudo ninja -C Build install

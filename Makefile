##
## EPITECH PROJECT, 2025
## 400
## File description:
## Makefile
## Author: nathan.jeannot@epitech.eu
##

NAME = myftp

# =============== SRC ===============

# -- CPP --
SRC  = src/main.cpp
SRC += src/core/Core.cpp
SRC += src/manager/CommandManager.cpp
SRC += src/server/Server.cpp
SRC += src/client/Client.cpp
SRC += src/client/DataSocket.cpp
SRC += src/socket/Socket.cpp
SRC += src/file/File.cpp
SRC += src/commands/abstract/ACommand.cpp
SRC += src/commands/argument/CommandArgument.cpp
SRC += src/commands/QuitCommand.cpp
SRC += src/commands/UserCommand.cpp
SRC += src/commands/PassCommand.cpp
SRC += src/commands/NoopCommand.cpp
SRC += src/commands/HelpCommand.cpp
SRC += src/commands/CwdCommand.cpp
SRC += src/commands/CdupCommand.cpp
SRC += src/commands/PwdCommand.cpp
SRC += src/commands/DeleCommand.cpp
SRC += src/commands/PasvCommand.cpp
SRC += src/commands/ListCommand.cpp
SRC += src/commands/TypeCommand.cpp
SRC += src/commands/StorCommand.cpp
SRC += src/commands/RetrCommand.cpp
SRC += src/commands/PortCommand.cpp

OBJ = $(SRC:%.cpp=%.o)

# =============== OTHER ===============

OK = \033[0;32m
KO = \033[0;31m
RESET = \033[0m

INCLUDES = -Isrc

CXXFLAGS = -Wall -Wextra $(INCLUDES)

CXXFLAGS = -iquote src -Wall -Wextra -Werror -g

GARBAGE  = $(OBJ)
GARBAGE += vgcore.*

# =====================================
all: $(NAME)

$(NAME): $(OBJ)
	@ g++ $(CXXFLAGS) -o $(NAME) $(OBJ)						\
	&& echo -e "$(OK)[RULE] $(NAME)$(RESET)" 				\
	|| echo -e "$(KO)[RULE] $(NAME)$(RESET)"

%.o: %.cpp
	@ g++ $(CXXFLAGS) -c $< -o $@ 							\
	&& echo -e "$(OK)[OK] $<$(RESET)"						\
	|| echo -e "$(KO)[KO] $<$(RESET)"

clean:
	@ $(RM) -r $(GARBAGE)									\
	&& echo -e "$(OK)[RULE] CLEAN"							\
	|| echo -e "$(KO)[RULE] CLEAN"

fclean: clean
	@ $(RM) $(NAME)											\
	&& echo -e "$(OK)[RULE] FCLEAN"							\
	|| echo -e "$(KO)[RULE] FCLEAN"

re: fclean all

.PHONY: all clean fclean re

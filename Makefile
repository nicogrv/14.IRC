NAME := ircserv

SRCDIR := srcs
INCDIR := inc
OBJDIR := objs

SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

CXX := c++
CXXFLAGS := -g -std=c++98 -Wall -Wextra -Werror -I$(INCDIR) -MMD

# ********************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $^ $(LIBS) -I $(INCDIR)
	@echo "\033[0;32m[✔️] $(NAME) successfully built.\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $(shell echo "$<" | sed 's/$(SRCDIR)\///')
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

# ********************************************************************** #

docker:
	clear
	docker kill ircserv || true
	mkdir -p srcs/
	mkdir -p inc/
	mkdir -p objs/
	sudo docker-compose build
	sudo docker-compose up -d
	sudo docker exec -it ircserv sh

clean:
	rm -rf objs
	rm -rf deps

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re

# SOURCES FILES ******************************************************** #

# ./utils/safeStrtoi.cpp
# ./utils/trim.cpp
# ./utils/checkStrValidity.cpp
# ./utils/endsWith.cpp
# ./utils/formatIrcMessage.cpp
# ./utils/printError.cpp
# ./utils/split.cpp
# ./utils/getMyHostname.cpp
# ./utils/formatTime.cpp
# ./classes/Client.cpp
# ./classes/Server.cpp
# ./classes/Channel.cpp
# ./connections/handleNewConnection.cpp
# ./connections/printConnectionStatus.cpp
# ./commands/INVITE.cpp
# ./commands/KICK.cpp
# ./commands/PRIVMSG.cpp
# ./commands/USER.cpp
# ./commands/callCorrespondingCommand.cpp
# ./commands/JOIN.cpp
# ./commands/CAP.cpp
# ./commands/PASS.cpp
# ./commands/PING.cpp
# ./commands/MODE.cpp
# ./commands/PART.cpp
# ./commands/NICK.cpp
# ./commands/TOPIC.cpp
# ./core/signals.cpp
# ./core/routine.cpp
# ./core/main.cpp

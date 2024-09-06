CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

UTILS_FILE = ./minitalk/minitalk.c ./minitalk/utils.c
UTILS_OBJS = $(UTILS_FILE:.c=.o)

SERVER_FILE = ./mandatory/server.c
SERVER_OBJS = $(SERVER_FILE:.c=.o)
CLIENT_FILE = ./mandatory/client.c
CLIENT_OBJS = $(CLIENT_FILE:.c=.o)

SERVER_BONUS_FILE = ./bonus/server_bonus.c
SERVER_BONUS_OBJS = $(SERVER_BONUS_FILE:.c=.o)
CLIENT_BONUS_FILE = ./bonus/client_bonus.c
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_FILE:.c=.o)

SERVER = server
CLIENT = client

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(UTILS_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(UTILS_OBJS) -o $(SERVER)
$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(UTILS_OBJS) -o $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJS) $(UTILS_OBJS)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) $(UTILS_OBJS) -o $(SERVER_BONUS)
$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) $(UTILS_OBJS) -o $(CLIENT_BONUS)


clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJS)
	$(RM) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS) $(UTILS_OBJS)
fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(RM) $(SERVER_BONUS) $(CLIENT_BONUS)
re: fclean all

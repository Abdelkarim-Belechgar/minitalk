SERVER_FILE = ./mandatory/server.c ./mandatory/minitalk.c ./mandatory/utils.c
CLIENT_FILE = ./mandatory/client.c ./mandatory/minitalk.c ./mandatory/utils.c
SERVER_FILE_BONUS = ./bonus/server_bonus.c ./bonus/minitalk_bonus.c ./bonus/utils_bonus.c
CLIENT_FILE_BONUS = ./bonus/client_bonus.c ./bonus/minitalk_bonus.c ./bonus/utils_bonus.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SERVER = server
CLIENT = client

SERVER_OBJS = $(SERVER_FILE:.c=.o)
CLIENT_OBJS = $(CLIENT_FILE:.c=.o)

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SERVER_BONUS_OBJS = $(SERVER_FILE_BONUS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_FILE_BONUS:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o server
$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o client

$(SERVER_BONUS): $(SERVER_BONUS_OBJS)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) $(LIBFT) -o server_bonus
$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) $(LIBFT) -o client_bonus

clean:
	$(MAKE) clean -C ./mandatory/
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	$(MAKE) clean -C ./bonus/
	$(RM) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS) 
fclean: clean
	$(MAKE) fclean -C ./
	$(RM) $(SERVER) $(CLIENT)
	$(RM) $(SERVER_BONUS) $(CLIENT_BONUS)
re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

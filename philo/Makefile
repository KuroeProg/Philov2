NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS = main.c \
		init.c \
		routine.c \
		monitoring.c \
		utils.c \
		fork.c \
		parsing.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
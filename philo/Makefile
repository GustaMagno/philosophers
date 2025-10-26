NAME	= philo
CC		= cc
CFLAGS	= -Iinclude -Wall -Wextra -Werror -g -fsanitize=thread

SRCS	= src/philosophers.c \
		src/parsing.c \
		src/routine.c \
		src/utils.c \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
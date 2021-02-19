SRCS= main.c \
		philosophers.c \
		print.c \
		utils.c \
		args.c \
		monitor.c

OBJS=$(SRCS:.c=.o)

CC=clang
FLAGS=-Wall -Wextra -Werror

NAME=philo_three
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
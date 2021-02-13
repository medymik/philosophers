CC=gcc
FLAGS=-Wall -Wextra -Werror
SRCS= args.c \
		eat.c \
		fork.c \
		life.c \
		main.c \
		mutexes.c \
		philosophers.c \
		print.c \
		sleep.c \
		time.c \
		utils.c
OBJS= $(SRCS:.c=.o)
NAME=philo_one
INCLUDES=philosophers.h

$(NAME): all

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

%.o: %.c $(INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@

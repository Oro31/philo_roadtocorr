CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

CC = clang

NAME = philo

SRC = ft_atoi.c	\
	  ft_init.c	\
	  ft_is_int.c	\
	  ft_monitoring.c	\
	  ft_mutex.c	\
	  ft_satiated.c	\
	  ft_status.c	\
	  ft_thread.c	\
	  ft_time.c	\
	  main.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

flemme: re
	make clean

.PHONY: clean fclean all re

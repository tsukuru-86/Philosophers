NAME := philo_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
SRCS := main_bonus.c parse_bonus.c init_bonus.c child_bonus.c \
	monitor_bonus.c parent_bonus.c output_bonus.c time_bonus.c cleanup_bonus.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

bonus: all

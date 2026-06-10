NAME = push_swap
NAME_BONUS = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror
CINCLUDES = -Iincludes

SRC_DIR     = .
ALGO_DIR    = algorithms
ACT_DIR     = actions
PRINTF_DIR	= ft_printf

BON_DIR		= bonus

SRC         = $(wildcard $(SRC_DIR)/*.c) \
              $(wildcard $(ACT_DIR)/*.c) \
              $(wildcard $(ALGO_DIR)/*.c) \
              $(wildcard $(PRINTF_DIR)/*.c)
# 			  actions/pa.c \
			  actions/pb.c \
			  actions/push.c \
			  actions/ra.c \
			  actions/rb.c \
			  actions/rev_rotate.c \
			  actions/rotate.c \
			  actions/rr.c \
			  actions/rra.c \
			  actions/rrb.c \
			  actions/rrr.c \
			  actions/sa.c \
			  actions/sb.c \
			  actions/ss.c \
			  actions/swap.c \
			  algorithms/radix.c \
			  algorithms/simple.c

SRC_BONUS = $(wildcard $(BON_DIR)/*.c) \
			$(wildcard $(BON_DIR)/gnl/*.c) \
			$(wildcard $(BON_DIR)/actions/*.c)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^
# $(NAME):
# 	$(CC) $(CFLAGS) -c $(SRC)
# 	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

# bonus: fclean
# 	$(CC) $(CFLAGS) -c $(SRC_BONUS)
# 	ar rcs $(NAME) $(OBJ_BONUS)

# USAGE: make test ARG="--bench 1 3 2 5 4"
test: all main.c
	$(CC) $(CFLAGS) $(CINCLUDES) main.c $(NAME) -o test_push_swap
	$(MAKE) clean
	@if [ -n "$(ARG)" ]; then \
		./test_push_swap $(ARG); \
	else \
		./test_push_swap 1 3 2 5 4; \
	fi
# 	./test_push_swap 1 2 3 4 5

# test: all main.c
# 	$(CC) $(CFLAGS) main.c $(NAME) -o test_push_swap
# 	$(MAKE) clean
# 	./test_push_swap 1 2 3 4 5

$(NAME_BONUS): $(OBJ_BONUS)
	ar rcs $@ $^

bonus: $(NAME_BONUS)

test_bonus: bonus
	$(CC) $(CFLAGS) $(CINCLUDES) $(NAME_BONUS) -o test_checker
	$(MAKE) clean
	@if [ -n "$(ARG)" ]; then \
		./test_push_swap $(ARG) | ./test_checker $(ARG); \
	else \
		./test_push_swap 1 3 2 5 4 | ./test_checker 1 3 2 5 4; \
	fi

memtest: all main.c
	$(CC) $(CFLAGS) $(CINCLUDES) main.c $(NAME) -o test_push_swap
	$(MAKE) clean
	valgrind --leak-check=full --track-origins=yes --error-limit=no --show-leak-kinds=all -s ./test_push_swap 1 3 2 5 4

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test bonus test_bonus

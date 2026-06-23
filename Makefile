# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/18 23:07:45 by jmielcar          #+#    #+#              #
#    Updated: 2026/06/18 23:07:47 by jmielcar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = push_swap
NAME_BONUS      = checker
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g
RM              = rm -rf
MKDIR           = mkdir -p

# Directorios separados para los objetos
OBJ_DIR         = obj
OBJ_BONUS_DIR   = obj_bonus

CINCLUDES       = -I. -Ibonus -Ibonus/gnl

SRCS            = actions/pa.c \
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
                  algorithms/radix_sort.c \
                  algorithms/insert_sort.c \
                  algorithms/insert_sort.utils.c \
                  algorithms/algo_utils.c \
                  algorithms/chunk_sort.c \
				  algorithms/simple.c \
                  ft_printf/ft_print_utils.c \
                  ft_printf/ft_printf.c \
                  bench.c \
                  compute_disorder.c \
                  flags_utils.c \
                  ft_split.c \
                  list_utils.c \
                  main.c \
                  print_utils.c \
                  utils.c

SRC_BONUS       = bonus/gnl/get_next_line.c \
                  bonus/gnl/get_next_line_utils.c \
                  bonus/apply_move_bonus.c \
                  bonus/checker_bonus.c \
                  bonus/checker_utils_bonus.c \
                  bonus/ft_split_bonus.c \
                  bonus/lst_utils_bonus.c

# Aquí mapeamos cada .c a su respectiva carpeta de objetos separada
OBJS            = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJ_BONUS       = $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS:.c=.o))

all: $(NAME)
	$(MAKE) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(OBJS) -o $(NAME)

bonus: $(NAME_BONUS)
	$(MAKE) clean


$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(OBJ_BONUS) -o $(NAME_BONUS)

# Regla de compilación para el programa obligatorio (va a OBJ_DIR)
$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

# Regla de compilación para el bonus (va a OBJ_BONUS_DIR)
$(OBJ_BONUS_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_BONUS_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus

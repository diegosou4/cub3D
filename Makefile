NAME = cub3D

BOLD = \033[1m
RESET = \033[0m
BLUE = \033[34m
RED = \033[31m


PARSER = init_parse.c join_map.c check_directions.c filled_map.c
GNL = get_next_line.c get_next_line_utils.c
LIBFT = ft_bzero.c ft_calloc.c ft_strdup.c ft_is_space.c ft_split.c \
		ft_len_darray.c ft_whitespaces.c ft_atoi.c ft_freedarray.c


SRC_PARSER = $(addprefix ./src/parse_map/, $(PARSER))
SRC_GNL = $(addprefix ./src/gnl/, $(GNL))
SRC_LIBFT = $(addprefix ./src/libft/, $(LIBFT))

SRC = $(SRC_GNL) $(SRC_PARSER) $(SRC_LIBFT)

CFLAGS = -g -I./ #-Wall -Wextra -Werror
CC = cc
LIB = minilibx-linux/libmlx_Linux.a


SRCOBJ = obj/
OBJ = $(addprefix $(SRCOBJ), $(SRC:./src/%.c=%.o))

all: $(NAME)
$(NAME): $(OBJ)
	@echo "$(BOLD)$(BLUE)cub3D huas been compiled successfully!$(RESET)"
	@${CC} ${CFLAGS} ${LIB} main.c ${OBJ} -o $(NAME)

$(SRCOBJ)%.o: src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)Cleaning objects!$(RESET)"
	@rm -rf $(SRCOBJ)
fclean: clean
	@echo "$(BOLD)$(RED)Deleting $(NAME)!$(RESET)"
	@rm -rf $(NAME)

re: fclean all

.PHONY	: re fclean clean all
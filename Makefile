NAME = cub3D

BOLD = \033[1m
RESET = \033[0m
BLUE = \033[34m
RED = \033[31m


PARSER = init_parse.c
GNL = get_next_line.c get_next_line_utils.c



SRC_PARSER = $(addprefix ./src/parse_map/, $(PARSER))
SRC_GNL = $(addprefix ./src/gnl/, $(GNL))

SRC = $(SRC_GNL) $(SRC_PARSER) 

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
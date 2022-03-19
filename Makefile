SRC_FILES= main.c cmd_split.c list.c parse_conditionals.c exec_command.c \
			get_path.c exit.c open.c signal.c error.c echo.c free.c env.c \
			pwd.c export.c unset.c cd.c parse.c
SRC_B_FILES=
SRC=$(addprefix src/, $(SRC_FILES))
SRC_B=$(addprefix src_bonus/, $(SRC_B_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
OBJ_B=$(addprefix obj_bonus/, $(SRC_B_FILES:.c=.o))
OBJ_B_DIR=obj_bonus
LIBFT=libft/libft.a
LIBFT_DIR=libft
NAME=minishell

all: $(NAME)

bonus: $(NAME_B)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(NAME_B): $(LIBFT) $(OBJ_B_DIR) $(OBJ_B)
	gcc -Wall -Werror -Wextra $(OBJ_B) $(LIBFT) -o $(NAME_B)

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

obj_bonus/%.o: src_bonus/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full ./minishell

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_B_DIR):
	mkdir $(OBJ_B_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

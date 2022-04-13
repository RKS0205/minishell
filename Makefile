SRC_FILES= main.c cmd_split.c list.c parse_conditionals.c exec_command.c \
			get_path.c exit.c open.c signal.c error.c echo.c free.c env.c \
			pwd.c export.c unset.c cd.c parse.c
SRC=$(addprefix src/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
LIBFT=libft/libft.a
LIBFT_DIR=libft
NAME=minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) $(LIBFT) -o $(NAME) -lreadline

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

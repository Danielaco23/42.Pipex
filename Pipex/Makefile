GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = pipex
B_NAME = pipex_bonus

SRC		=	main.c \
			forker.c \
			executioner.c \

B_SRC	=	main_bonus.c \
			forker.c \
			executioner.c \

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "$(GREEN)--------------------------------------------$(NC)"
	@echo "$(GREEN)-------------- Pipex Is Ready --------------$(NC)"
	@echo "$(GREEN)--------------------------------------------$(NC)"

$(NAME): $(OBJ) $(LIBFT) pipex.h
	@echo "$(YELLOW)------------- Compiling Pipex --------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)--------- Pipex Finished Compiling ---------$(NC)\n"

bonus: $(B_NAME)
	@echo "$(GREEN)--------------------------------------------$(NC)"
	@echo "$(GREEN)----------- Pipex Bonus Is Ready -----------$(NC)"
	@echo "$(GREEN)--------------------------------------------$(NC)"

$(B_NAME): $(B_OBJ) $(LIBFT)
	@echo "$(YELLOW)---------- Compiling Pipex Bonus -----------$(NC)"
	@$(CC) $(CFLAGS) $(B_OBJ) $(LIBFT) -o $(B_NAME)
	@echo "$(GREEN)------ Pipex Bonus Finished Compiling ------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft bonus

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -sC ./Libft fclean
	@rm -f $(OBJ) $(B_OBJ)
	@echo "$(RED)------------- Objects Cleaned --------------$(NC)"

fclean: clean
	@rm -f $(NAME) $(B_NAME)
	@echo "$(RED)-------------- Pipex Cleaned ---------------$(NC)"

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean re reb bonus

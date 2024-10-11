G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

PIPEX_NAME		=	pipex

PIPEX_B_NAME	=	pipex_bonus

PIPEX_SRC		=	main.c \
					forker.c \
					executioner.c \

PIPEX_B_SRC		=	main_bonus.c \
					forker.c \
					executioner.c \

PIPEX_OBJ_DIR	=	objects

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g3

LIBFT			=	./Libft/libft.a

PIPEX_OBJ		=	$(patsubst %.c, $(PIPEX_OBJ_DIR)/%.o, $(PIPEX_SRC))

all: $(PIPEX_NAME)
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)------------------------------------------ Pipex Is Ready ------------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"

$(PIPEX_NAME): $(LIBFT) $(PIPEX_OBJ) pipex.h
	@echo "$(Y)\n--------------------------------------- Compiling Just Pipex ---------------------------------------$(NC)"
	@$(CC) $(CFLAGS) $(PIPEX_OBJ) $(LIBFT) -o $(PIPEX_NAME)
	@echo "$(G)------------------------------------- Pipex Finished Compiling -------------------------------------$(NC)\n"

$(PIPEX_OBJ_DIR):
	@mkdir -p $(PIPEX_OBJ_DIR)

bonus:
	@make -s PIPEX_NAME="$(PIPEX_B_NAME)" PIPEX_SRC="$(PIPEX_B_SRC)" 

$(LIBFT):
	@make -sC ./Libft bonus

$(PIPEX_OBJ_DIR)/%.o: %.c | $(PIPEX_OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -sC ./Libft fclean
	@rm -rf $(PIPEX_OBJ_DIR)
	@echo "$(R)-------------------------------------- Pipex Has Been Cleaned --------------------------------------$(NC)"

fclean: clean
	@rm -f $(PIPEX_NAME) $(PIPEX_B_NAME)

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean re reb bonus

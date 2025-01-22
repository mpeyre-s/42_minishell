# Color
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

# Ajouter des smileys
SMILEY = 😊
THUMBS_UP = 👍
CHECK_MARK = ✅
TRASH = 🗑️
COMPUTER = 💻
ROCKET = 🚀

# Nom de l'exécutable
MINISHELL = minishell

# Répertoires
LIBFT_DIR = libft
OBJ_DIR = objects

# Fichiers sources
SRC_FILES = init_av/count_args.c init_av/init_av.c init_av/parse_args.c \
			exp/init_exp.c \
			errors/error_quote.c errors/errors.c \
			execution/execution.c execution/file.c \
			execution/builtin/echo.c \
			tests/tests.c \
			main.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I$(LIBFT_DIR)

# Bibliothèques et headers
LIBFT = $(LIBFT_DIR)/libft.a
INC = minishell.h $(LIBFT_DIR)/libft.h

# Règle par défaut : compiler les exécutables
all: $(OBJ_DIR) $(LIBFT) $(MINISHELL)
	@echo "$(GREEN)Compilation successful! $(ROCKET)$(RESET)"

# Créer le répertoire pour les objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Creating object directory $(OBJ_DIR)... $(COMPUTER)$(RESET)"

# Créer la bibliothèque libft
$(LIBFT): $(LIBFT_DIR)/Makefile
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft library built! $(CHECK_MARK)$(RESET)"

# Créer l'exécutable
$(MINISHELL): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@echo "$(YELLOW)Compiling $(MINISHELL)... $(COMPUTER)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(MINISHELL) $(LIBFT) -lreadline -lncurses
	@echo "$(GREEN)$(MINISHELL) successfully created! $(THUMBS_UP)$(RESET)"

# Règle pour générer les fichiers objets
$(OBJ_DIR)/%.o: %.c $(INC)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)Objects cleaned! $(TRASH)$(RESET)"

# Nettoyage complet (objets + exécutables)
fclean: clean
	@rm -f $(MINISHELL)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable $(MINISHELL) removed! $(TRASH)$(RESET)"

# Recompilation complète
re: fclean all

# Marque que les règles ne sont pas des fichiers
.PHONY: all clean fclean re

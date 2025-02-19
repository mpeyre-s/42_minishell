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
SRC_FILES = init_av/count_args.c init_av/init_av.c init_av/parse_args.c init_av/env.c \
			exp/init_exp.c exp/parsing_exp.c exp/replace_exp.c exp/check_and_build.c exp/new_env.c exp/add_or_del_env.c \
			errors/error_quote.c errors/errors.c \
			execution/execution.c execution/file.c execution/pipe.c execution/stdin.c\
			execution/utils/env_manager.c execution/utils/export_utils.c execution/utils/pipe_utils.c execution/utils/bin_utils.c\
			execution/builtin/echo.c execution/builtin/pwd.c  execution/builtin/env.c execution/builtin/export.c execution/builtin/unset.c execution/builtin/cd.c\
			delete_quote/quote.c \
			metachar/init_metachar.c \
			before_exec/command.c before_exec/free.c \
			signals.c \
			main.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compilateur et options
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I$(LIBFT_DIR)

# Bibliothèques et headers
LIBFT = $(LIBFT_DIR)/libft.a
INC = minishell.h $(LIBFT_DIR)/libft.h

# Lire la librairie Readline
READLINE_PATH = /opt/homebrew/opt/readline
ifneq ($(READLINE_PATH),)
INCLUDES += -I$(READLINE_PATH)/include
LDFLAGS += -L$(READLINE_PATH)/lib
endif
LDLIBS += -lreadline -lncurses

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
	@$(CC) $(CFLAGS) $(OBJ) -o $(MINISHELL) $(LIBFT) $(LDFLAGS) $(LDLIBS)
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

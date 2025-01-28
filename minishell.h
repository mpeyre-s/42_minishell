/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:34:03 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/28 09:26:34 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"


// Color codes
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

// Emojis
#define ROCKET  "🚀"
#define THUMBS_UP "👍"
#define CHECK_MARK "✅"
#define TRASH "🗑️"
#define COMPUTER "💻"


#define RESET_COLOR "\033[0m"

// Définition d'une fonction qui génère un code de couleur basé sur un indice
#define COLOR(i) "\033[38;5;" #i "m"  // Utilisation des couleurs 256 disponibles en ANSI

#define MINISHELL_TEST  \
  COLOR(33) "            _         _       _            _  _\n" \
  COLOR(39) "           (_)       (_)     | |          | || |\n" \
  COLOR(45) " _ __ ___   _  _ __   _  ___ | |__    ___ | || |\n" \
  COLOR(51) "| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n" \
  COLOR(57) "| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n" \
  COLOR(63) "|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|" RESET_COLOR




typedef struct s_args
{
	int		ac;
	char	**av;
	int		*was_quoted; // tableau d'int de taille index qui represente pour chaque index l'argument : 1 si meta 0 sinon
	int		*metachar;
	int		*pipe; // |
	int		*redirect_output; // >
	int		*append_redirect; // >>
	int		*redirect_input; // <
	int		*heredoc; // <<
}				t_args;

/* Gere les expansions c'est a dire les $ */
typedef struct s_exp
{
	int		ac;
	char	**av; // ici on a les arguments "bruts" rentre en ligne de commande
	char	**translate; // ici on a la traduction de ceux-ci
}				t_exp;


// CE QUE TU VAS RECUPERER
typedef struct s_command
{
	char	**args;          // Les arguments spécifiques à cette commande
	char	*input_file;     // Fichier d'entrée si '<'
	char	*heredoc_delim;  // Délimiteur pour le heredoc si '<<'
	char	*output_file;    // Fichier de sortie si '>' ou '>>'
	int		append;          // 2 si '>>', 1 si '>'
	int		pipe_out;        // 1 si cette commande envoie sa sortie dans un pipe
	struct s_command *next;  // Pointeur vers la commande suivante (liste chaînée)
}				t_command;


// --------INIT_AV-----------
char	**init_av(char *str, int *index, int i);
int		count_args(char *s);
int		parse_args(char *s, int *i, int *start);
int		is_metachar(int c);

// --------INIT_EXP-----------
void	init_exp(t_exp *exp);
int		parse_exp(t_args *args, t_exp *exp);
int		replace_av(char *substr, char **av, int start, t_exp *exp);
char	*build_new_av(char *before, char *exp, char *after);
int		check_expansion(char *s, t_exp *exp);
int		inside_single_quote(char *av, int limit);
int		init_all(t_args *args);

// -------- QUOTE -----------
int	deal_with_quote(t_args *args);

// --------ERRORS-----------
int		free_main(char *s, t_args *args, t_exp *exp, char *rl);
int		free_split(char **str, int index);
int		free_metachar(t_args *args);

// --------ERRORS QUOTE-----------
int		print_quote(char **result, int index);
int		check_error_quote(char **str, int index);
int		quote(char *s);




void	print_split_result(char **lines);
void	print_test_quote(t_args *args);
void	print_all(t_args *args);


#endif

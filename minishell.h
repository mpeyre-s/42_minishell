/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:34:03 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/14 22:47:23 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <signal.h>

// Color codes
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[1;33m"
# define RESET   "\033[0m"

// Emojis
# define ROCKET  "🚀"
# define THUMBS_UP "👍"
# define CHECK_MARK "✅"
# define TRASH "🗑️"
# define COMPUTER "💻"
# define BYE "👋😊"

# define RESET_COLOR "\033[0m"

# define COLOR(i) "\033[38;5;" #i "m"

# define MINISHELL_TEST  \
  COLOR(51) "            _         _       _            _  _\n" \
  COLOR(45) "           (_)       (_)     | |          | || |\n" \
  COLOR(39) " _ __ ___   _  _ __   _  ___ | |__    ___ | || |\n" \
  COLOR(33) "| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n" \
  COLOR(63) "| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n" \
  COLOR(57) "|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|" RESET_COLOR

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

char		**init_av(char *str, int *index, int i);
int			count_args(char *s);
int			parse_args(char *s, int *i, int *start);
int			is_metachar(int c);

// --------INIT_EXP-----------

int			init_exp(t_exp *exp, char **env);
int			parse_exp(t_args *args, t_exp *exp);
int			replace_av(char *substr, char **av, int start, t_exp *exp);
char		*build_new_av(char *before, char *exp, char *after);
int			check_expansion(char *s, t_exp *exp);
int			inside_single_quote(char *av, int limit);
int			init_all(t_args *args);
int			is_new_env(char **av, t_args *args, t_exp *exp);
void		modify_exp(char *s1, char *s2, t_exp *exp, int flag);

void		delete_one_exp(t_exp *exp, int n);
void		add_new_exp(t_exp *exp, char *s1, char *s2);

// --------FINAL_INIT-----------
t_command	*create_command(t_args *args, int start);
void		free_str(char **str);
void		free_command_list(t_command *cmd);
void		free_command(t_command *cmd);


// -------- QUOTE -----------
int			deal_with_quote(t_args *args);

// --------ERRORS-----------

int			free_main(char *s, t_args *args, char *rl);
int			free_split(char **str, int index);
int			free_metachar(t_args *args);
int			stop_main(char *s, t_args *args, t_exp *exp, char *rl);

// --------ERRORS QUOTE-----------

int			print_quote(char **result, int index);
int			check_error_quote(char **str, int index);
int			quote(char *s);

// --------EXECUTION-----------

int			start_exec(t_command *cmd, char ***env, int flag);
int			exec_cmd(t_command *cmd, char ***env);
int			execute_pipe(t_command *cmd, char ***env);
int			modify_stdout_and_exec(t_command *cmd, char ***env);
int			modify_stdin_and_exec(t_command *cmd, char ***env, int *flag);
int			stdin_heredoc(t_command *cmd, char *delim, char ***env, int *flag);

int			ft_echo(t_command *cmd);
int			ft_exit(t_command *cmd);
int			ft_pwd(t_command *cmd);
int			ft_env(char **env);
int			ft_export(t_command *cmd, char ***env);
int			ft_unset(t_command *cmd, char ***env);
int			ft_cd(t_command *cmd, char ***env);

// --------EXECUTION UTILS-----------
char		***ft_strdup_env(char **env);
char		*get_env_var(char **env, char *var);
int			ft_arraylen(char **array);
int			free_new_env(char **new_env, size_t i);
char		**create_new_env(char **env, size_t *size);
int			copy_old_env(char ***env, char **new_env, size_t *i);
char		*create_full_var(char *var_name, char *var_value);
int			env_var_exist(t_command *cmd, char **env);

// --------PIPE & Co-----------
void		handle_error(const char *msg, pid_t *pids, int (*pipe_fds)[2]);
int			count_pipes(t_command *cmd);
pid_t		*allocate_pids(int count);
int			(*allocate_pipe_fds(int count))[2];
void		create_pipes(int (*pipe_fds)[2], int count, pid_t *pids);
void		setup_fds(int i, int count, int (*pipe_fds)[2], t_command *cur);
void		close_pipes(int (*pipe_fds)[2], int count);
int			execute_command(t_command *cmd, char ***env, int (*pipe_fds)[2],
				int count, pid_t *pids);
void		wait_for_children(pid_t *pids, int count);

//------------UTILS---------------

void		handle_sigint(int sig);

#endif

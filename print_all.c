/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:08:49 by spike             #+#    #+#             */
/*   Updated: 2025/02/04 16:30:39 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction de test pour voir si les av sont bien tries (il faudra delete) */
void	print_split_result(char **lines)
{
	printf("PRINT SPLIT RESULT :\n\n");
	int i = 0;

	if (!lines)
	{
		printf("Lines is NULL.\n");
		return;
	}

	printf("Split result:\n");
	while (lines[i])
	{
		printf("lines[%d]: %s\n", i, lines[i]);
		i++;
	}
	printf("Total arguments: %d\n", i);
}

void print_all(t_args *args)
{
    int i = 0;

    while (i < args->ac)
    {
        printf("Argument [%d]:\n", i);
        printf("  av = %s\n", args->av[i]);
        printf("  was_in_quote = %d\n", args->was_quoted[i]);
        printf("  pipe = %d\n", args->pipe[i]);
        printf("  redirect_output = %d\n", args->redirect_output[i]);
        printf("  append_redirect = %d\n", args->append_redirect[i]);
        printf("  redirect_input = %d\n", args->redirect_input[i]);
        printf("  heredoc = %d\n", args->heredoc[i]);
		printf("  Is a metachar = %d", args->metachar[i]);
		printf("\n\n");
        i++;
    }
    printf("\n");
}

void print_test_quote(t_args *args)
{
    int i = 0;

    while (i < args->ac)
    {
        printf("Argument [%d]:\n", i);
        printf("  av = %s\n", args->av[i]);
        printf("  was_in_quote = %d\n", args->was_quoted[i]);
		i++;
	}
	printf("\n\n");
}

void	print_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return;

	printf("Command:\n");

	// Affiche les arguments
	printf("  Arguments:\n");
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("    - [%s]\n", cmd->args[i]);
			i++;
		}
	}
	else
		printf("    (no arguments)\n");

	// Affiche les fichiers redirigés et heredoc
	printf("  Input file: %s\n", cmd->input_file ? cmd->input_file : "(none)");
	printf("  Heredoc delimiter: %s\n", cmd->heredoc_delim ? cmd->heredoc_delim : "(none)");
	printf("  Output file: %s\n", cmd->output_file ? cmd->output_file : "(none)");
	printf("  Append mode: %d\n", cmd->append);

	// Pipe
	printf("  Pipe out: %d\n", cmd->pipe_out);

	// Ligne suivante
	printf("\n");
}

void	print_command_list(t_command *cmd_list)
{
	int cmd_num = 1;

	while (cmd_list)
	{
		printf("=== Command %d ===\n", cmd_num);
		print_command(cmd_list);
		cmd_list = cmd_list->next;
		cmd_num++;
	}
}
void	print_exp(t_exp *exp)
{
	int i = 0;
	while (i < exp->ac)
	{
		printf("%s = %s\n", exp->av[i], exp->translate[i]);
		i++;
	}
}

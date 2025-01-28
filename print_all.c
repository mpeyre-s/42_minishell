/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:08:49 by spike             #+#    #+#             */
/*   Updated: 2025/01/27 18:02:08 by spike            ###   ########.fr       */
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

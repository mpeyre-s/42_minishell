/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:08:49 by spike             #+#    #+#             */
/*   Updated: 2025/01/21 12:56:06 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction de test pour voir si les av sont bien tries (il faudra delete) */
void	print_split_result(char **lines)
{
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

// void print_all(t_args *args)
// {
//     int i = 0;

//     while (i < args->ac)
//     {
//         printf("Argument [%d]:\n", i);
//         printf("  av = %s\n", args->av[i]);
//         printf("  was_in_quote = %d\n", args->was_in_quote[i]);
//         printf("  pipe = %d\n", args->pipe[i]);
//         printf("  redirect_output = %d\n", args->redirect_output[i]);
//         printf("  append_redirect = %d\n", args->append_redirect[i]);
//         printf("  redirect_input = %d\n", args->redirect_input[i]);
//         printf("  heredoc = %d\n", args->heredoc[i]);
// 		printf("\n\n");
//         i++;
//     }
//     printf("\n");
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:55:27 by spike             #+#    #+#             */
/*   Updated: 2025/02/03 13:02:27 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* verifie si les quotes se ferment correctement */
int	quote(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (double_quote % 2 == 0)
				single_quote++;
		}
		else if (s[i] == '"')
		{
			if (single_quote % 2 == 0)
				double_quote++;
		}
		i++;
	}
	return (single_quote % 2 != 0 || double_quote % 2 != 0);
}

int	check_error_quote(char **str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (quote(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	print_quote(char **result, int index)
{
	char	*qline;
	char	*temp;

	while (check_error_quote(result, index))
	{
		qline = readline("quote> ");
		if (!qline)
		{
			ft_putstr_fd("problem with readline fct\n", 2);
			return (-1);
		}
		temp = ft_strjoin(result[index - 1], qline);
		free(result[index - 1]);
		free(qline);
		if (!temp)
		{
			ft_putstr_fd("Memory alloc error while concatenating strings", 2);
			return (-1);
		}
		result[index - 1] = temp;
	}
	return (0);
}

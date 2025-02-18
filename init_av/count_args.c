/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:47:39 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/18 18:56:08 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_metachar(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == '=');
}

static int	handle_quotes(char *s, int *i, char *quote)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		*quote = s[*i];
		(*i)++;
		while (s[*i] != *quote && s[*i] != '\0')
			(*i)++;
		if (s[*i] == '\0')
			return (-2);
		(*i)++;
		*quote = '\0';
	}
	return (0);
}

int	handle_metachar(char *s, int *i)
{
	if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
	{
		if (s[*i + 2] == s[*i])
			return (-1);
		(*i) += 2;
	}
	else
		(*i)++;
	return (0);
}

int	logic_count_args(char *s, int *i, char *quote)
{
	int	ret;

	ret = handle_quotes(s, i, quote);
	if (ret != 0)
		return (ret);
	else if (is_metachar(s[*i]))
		return (handle_metachar(s, i));
	else
	{
		while (s[*i] != ' ' && s[*i] != '\0'
			&& !is_metachar(s[*i]) && s[*i] != '\'' && s[*i] != '"')
			(*i)++;
	}
	return (0);
}

int	count_args(char *s)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	quote = '\0';
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			count++;
			if (logic_count_args(s, &i, &quote) == -1)
				return (-1);
		}
	}
	return (count);
}

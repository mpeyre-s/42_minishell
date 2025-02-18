/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:28:05 by hduflos           #+#    #+#             */
/*   Updated: 2025/02/18 18:54:12 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	forward_metachar(char *s, int *i)
{
	if (is_metachar(s[*i]))
	{
		if ((s[*i] == '>' || s[*i] == '<') && s[*i + 1] == s[*i])
			(*i) += 2;
		else
			(*i)++;
		return (1);
	}
	return (0);
}

int	handle_quotes(char *s, int *i, char *quote)
{
	if ((s[*i] == '\'' || s[*i] == '"') && *quote == '\0')
	{
		*quote = s[*i];
		(*i)++;
		return (1);
	}
	else if (s[*i] == *quote)
	{
		*quote = '\0';
		(*i)++;
		return (1);
	}
	return (0);
}

int	parse_args(char *s, int *i, int *start)
{
	char	quote;

	quote = '\0';
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0')
		return (0);
	if (is_metachar(s[*i]))
	{
		*start = *i;
		forward_metachar(s, i);
		return (1);
	}
	*start = *i;
	while (s[*i] != '\0')
	{
		if (handle_quotes(s, i, &quote))
			continue ;
		if (quote == '\0' && is_metachar(s[*i]))
			break ;
		if (quote == '\0' && s[*i] == ' ')
			break ;
		(*i)++;
	}
	return (1);
}

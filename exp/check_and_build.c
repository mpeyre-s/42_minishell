/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:25:43 by spike             #+#    #+#             */
/*   Updated: 2025/01/23 20:33:54 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expansion(char *s, t_exp *exp)
{
	int	i;

	i = 0;
	printf("exp->ac = %d\n", exp->ac);
	while (i < exp->ac)
	{
		printf("%s VS %s\n", s, exp->av[i]);
		if (ft_strncmp(s + 1, exp->av[i], ft_strlen(s)) == 0) // je fais s +1 sinon je vais comparer avec le dollar
			return (i);
		i++;
	}
	return (-1);
}
char *ft_strcat(char *dest, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (s[j])
	{
		dest[i + j] = s[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*build_new_av(char *before, char *exp, char *after)
{
	char *result;
	int total_size;

	total_size = ft_strlen(before) + ft_strlen(exp) + ft_strlen(after);
	result = malloc(total_size + 1);
	if (!result)
		return (NULL);

	ft_strlcpy(result, before, total_size);
	result = ft_strcat(result, exp);
	result = ft_strcat(result, after);

	return (result);
}


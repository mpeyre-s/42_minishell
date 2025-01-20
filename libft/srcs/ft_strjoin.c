/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:34:44 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 10:18:31 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strcat(char *res, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = 0;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(total_size + 1);
	if (!res)
		return (NULL);
	return (ft_strcat(res, s1, s2));
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Cas de test 1 : Chaînes normales
    const char *s1 = "Hello, ";
    const char *s2 = "World!";
    char *result1 = ft_strjoin(s1, s2);
    if (result1)
    {
        printf("Test 1: \"%s\" + \"%s\" = \"%s\"\n", s1, s2, result1);
        free(result1);
    }
    else
    {
        printf("Test 1: Erreur lors de l'allocation mémoire.\n");
    }

    // Cas de test 2 : Chaîne s1 vide
    s1 = "";
    s2 = "World!";
    char *result2 = ft_strjoin(s1, s2);
    if (result2)
    {
        printf("Test 2: \"%s\" + \"%s\" = \"%s\"\n", s1, s2, result2);
        free(result2);
    }
    else
    {
        printf("Test 2: Erreur lors de l'allocation mémoire.\n");
    }

    return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:48:19 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 10:23:44 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	res = (char *)malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = 0;
	return (res);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Cas de test 1 : Chaîne avec des espaces à couper au début et à la fin
    const char *s1 = "   Hello, World!   ";
    const char *set1 = " ";
    char *result1 = ft_strtrim(s1, set1);
    if (result1)
    {
        printf("Test 1: Trim \"%s\" de \"%s\" = \"%s\"\n", s1, set1, result1);
        free(result1);
    }
    else
    {
        printf("Test 1: Erreur lors de l'allocation mémoire.\n");
    }
    return (0);
}
*/

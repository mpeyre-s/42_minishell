/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:46:00 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:31:39 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int		i;
	char	c;

	i = 0;
	c = (char)ch;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	if (c == 0)
		return ((char *)(str + i));
	return (NULL);
}

/*
#include <stdio.h>

int main() 
{
    const char *str1 = "Hello, World!";
    char ch1 = 'o';

    printf("Test 1: Recherche du caractère '%c' dans \"%s\"\n", ch1, str1);
    char *result1 = ft_strchr(str1, ch1);
    if (result1) 
    {
        printf("Caractère trouvé à la position : %ld\n", result1 - str1);
        printf("Sous-chaîne à partir de la position : \"%s\"\n", result1);
    } 
    else 
    {
        printf("Caractère non trouvé.\n");
    }
    return (0);
}
*/

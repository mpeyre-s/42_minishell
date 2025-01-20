/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:18:33 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:49:33 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		str_len;
	char	c;

	c = (char)ch;
	str_len = ft_strlen(str);
	if (c == 0)
		return ((char *)(str + str_len));
	while (str_len > 0)
	{
		str_len--;
		if (str[str_len] == c)
			return ((char *)(str + str_len));
	}
	return (NULL);
}

/*
#include <stdio.h>

int main() 
{
    const char *str1 = "Hello, World!";
    char ch1 = 'o';

    printf("Test 1 last occurrence du caractère '%c' dans \"%s\"\n", ch1, str1);
    char *result1 = ft_strrchr(str1, ch1);
    if (result1) 
    {
        printf("last occurrence trouvée à la position : %ld\n", result1 - str1);
        printf("Sous-chaîne à partir de la position : \"%s\"\n", result1);
    } 
    else 
    {
        printf("Caractère non trouvé.\n");
    }
    return (0);
}
*/

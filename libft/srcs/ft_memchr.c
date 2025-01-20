/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:13:17 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:50:07 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int j, size_t size)
{
	const char	*temp;
	char		c;
	size_t		i;

	temp = (const char *)str;
	c = (char)j;
	i = 0;
	while (i < size)
	{
		if (temp[i] == c)
			return ((void *)(temp + i));
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main() 
{
    const char str1[] = "Hello, World!";
    char ch1 = 'o';
    size_t size1 = 13;

    printf("Test 1: Recherche du caractère '%c' dans \"%s\"\n", ch1, str1);
    void *result1 = ft_memchr(str1, ch1, size1);
    if (result1) 
    {
        printf("Caractère trouvé à la position : %ld\n", (char *)result1 - str1);
        printf("Sous-chaîne depuis la position : \"%s\"\n", (char *)result1);
    } 
    else 
    {
        printf("Caractère non trouvé.\n");
    }
    return (0);
}
*/

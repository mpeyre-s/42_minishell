/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:53:46 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:24:17 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src && len == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	return (dst);
}

/*
#include <stdio.h>

int main() 
{
    char str1[20] = "Hello, World!";
    char str2[20];  
    printf("Avant ft_memmove (cas simple):\n");
    printf("src: %s\n", str1);
    printf("dst: %s\n", str2);

    ft_memmove(str2, str1, 13);

    printf("\nAprès ft_memmove (cas simple):\n");
    printf("src: %s\n", str1);      
    printf("dst: %s\n", str2); 

    char str3[20] = "1234567890";
    printf("\nAvant ft_memmove (cas avec chevauchement):\n");
    printf("str3: %s\n", str3);

    ft_memmove(str3 + 4, str3, 6);

    printf("\nAprès ft_memmove (cas avec chevauchement):\n");
    printf("str3: %s\n", str3);  

    return 0;
}
*/

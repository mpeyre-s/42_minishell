/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:34:47 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:17:13 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!dst && !src))
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/*
#include <stdio.h>

void *ft_memcpy(void *dst, const void *src, size_t n);

int main() {
    char src[] = "Hello, World!";      
    char dst[20];                  

    printf("Avant memcpy:\n");
    printf("src: %s\n", src);
    printf("dst: %s\n", dst);  
    ft_memcpy(dst, src, 13);

    printf("\nAprès memcpy:\n");
    printf("src: %s\n", src);
    printf("dst: %s\n", dst);  
    return 0;
}
*/

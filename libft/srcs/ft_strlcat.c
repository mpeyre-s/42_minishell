/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:21:50 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:29:10 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	int		i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && i + dst_len < (size - 1))
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = 0;
	return (dst_len + src_len);
}

/*
#include <stdio.h>
#include <string.h> 

int main() 
{
    // Cas 1 : dst a de la place pour concaténer src
    char dst1[20] = "Hello, ";  
    const char *src1 = "World!";
    size_t size1 = 20;

    printf("Avant ft_strlcat (cas 1):\n");
    printf("dst1: %s\n", dst1);
    printf("src1: %s\n", src1);

    ft_strlcat(dst1, src1, size1);

    printf("Après ft_strlcat (cas 1):\n");
    printf("dst1: %s\n", dst1);  
    printf("Retour : %zu\n\n", ft_strlen(dst1));

    // Cas 2 : dst est trop petit pour contenir toute la concaténation
    char dst2[10] = "Hi "; 
    const char *src2 = "there!";
    size_t size2 = 10;

    printf("Avant ft_strlcat (cas 2):\n");
    printf("dst2: %s\n", dst2);
    printf("src2: %s\n", src2);

    ft_strlcat(dst2, src2, size2);

    printf("Après ft_strlcat (cas 2):\n");
    printf("dst2: %s\n", dst2);  
    printf("Retour : %zu\n\n", ft_strlen(dst2));

    return (0);
}
*/

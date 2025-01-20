/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:46:20 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 10:02:53 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	result = (char *)haystack;
	if (*needle == 0)
		return (result);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j] && i + j < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)(result + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

char    *ft_strnstr(const char *haystack, const char *needle, size_t len);

int main()
{
    const char *haystack = "Hello, World!";
    const char *needle1 = "World";
    const char *needle2 = "Hello";
    size_t len1 = 13;
    size_t len2 = 5;

    // Test 1 : needle trouvé dans haystack (dans les limites de len)
    char *result1 = ft_strnstr(haystack, needle1, len1);
    if (result1)
    {
        printf("Test 1: Trouvé \"%s\" dans"); 
	printf("\"%s\" position : %ld\n", needle1, haystack, result1 - haystack);
    }
    else
        printf("Test 1: \"%s\" non trouvé dans \"%s\".\n", needle1, haystack);

    // Test 2 : needle trouvé au début de haystack
    char *result2 = ft_strnstr(haystack, needle2, len2);
    if (result2)
    {
	    printf("Test 2: Trouvé \"%s\"");
	    printf("dans \"%s\" pos : %ld\n", needle2, haystack, result2 - haystack);
    }
    else
        printf("Test 2: \"%s\" non trouvé dans \"%s\".\n", needle2, haystack);

    return (0);
}
*/

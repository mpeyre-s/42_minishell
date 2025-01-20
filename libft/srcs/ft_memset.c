/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:42:34 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 09:18:33 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)ptr;
	i = 0;
	while (i < count)
	{
		temp[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}

/*
#include <stdio.h>
int main() 
{
    char str[20] = "Hello, World!";  
    printf("Avant memset: %s\n", str);

    ft_memset(str, 'X', 5);

    printf("Après memset: %s\n", str);

    return 0;
}
*/

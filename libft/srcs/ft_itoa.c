/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:08:32 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 12:05:16 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*fill_result(char *nb, int n, int size, int is_neg)
{
	nb[size] = '\0';
	size--;
	if (n == 0)
	{
		nb[size] = '0';
		return (nb);
	}
	if (n == -2147483648)
	{
		nb[size] = '8';
		size--;
		n = 214748364;
	}
	while (n)
	{
		nb[size] = (n % 10) + '0';
		n /= 10;
		size--;
	}
	if (is_neg)
		nb[0] = '-';
	return (nb);
}

static int	get_size(int n, int is_neg)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (is_neg)
	{
		size++;
		n = -n;
	}
	if (n == -2147483648)
		return (11);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*nb;
	int		is_neg;
	int		size;

	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		if (n != -2147483648)
			n = -n;
	}
	size = get_size(n, is_neg);
	nb = (char *)malloc(size + 1);
	if (!nb)
		return (NULL);
	return (fill_result(nb, n, size, is_neg));
}

/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Cas de test 1 : Entier positif
    int num1 = 12345;
    char *result1 = ft_itoa(num1);
    if (result1)
    {
        printf("Test 1: itoa(%d) = \"%s\"\n", num1, result1);
        free(result1);
    }
    else
    {
        printf("Test 1: Erreur lors de l'allocation mémoire.\n");
    }

    // Cas de test 2 : Entier négatif
    int num2 = -2147483648;
    char *result2 = ft_itoa(num2);
    if (result2)
    {
        printf("Test 2: itoa(%d) = \"%s\"\n", num2, result2);
        free(result2);
    }
    else
    {
        printf("Test 2: Erreur lors de l'allocation mémoire.\n");
    }
    return (0);
}
*/

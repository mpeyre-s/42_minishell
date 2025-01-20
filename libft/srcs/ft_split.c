/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:31:27 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 10:28:13 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*ft_malloc(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (ft_substr(str, 0, i));
}

static void	free_words(char **result, int j)
{
	while (j--)
		free(result[j]);
	free(result);
}

static char	**fill_result(char **resultat, char *str, char c)
{
	int	j;

	j = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			resultat[j] = ft_malloc(str, c);
			if (!resultat[j])
			{
				free_words(resultat, j);
				return (NULL);
			}
			j++;
			while (*str && *str != c)
				str++;
		}
	}
	resultat[j] = NULL;
	return (resultat);
}

char	**ft_split(char const *s, char c)
{
	char	**resultat;
	int		count;

	if (!s)
		return (NULL);
	count = count_words((char *)s, c);
	resultat = malloc((count + 1) * sizeof(char *));
	if (!resultat)
		return (NULL);
	return (fill_result(resultat, (char *)s, c));
}

/*
#include <stdio.h>
#include <stdlib.h>

char    **ft_split(char const *s, char c);

void print_split_result(char **result)
{
    int i = 0;
    if (result)
    {
        while (result[i])
        {
            printf("Segment %d: \"%s\"\n", i, result[i]);
            free(result[i]); 
            i++;
        }
        free(result); 
    }
    else
    {
        printf("Erreur : résultat de ft_split est NULL.\n");
    }
}

int main()
{
    // Cas de test 1 : Chaîne avec des délimiteurs au milieu
    const char *s1 = "Hello, World, OpenAI";
    char delim1 = ',';
    printf("Test 1: Splitting \"%s\" with delimiter '%c'\n", s1, delim1);
    char **result1 = ft_split(s1, delim1);
    print_split_result(result1);

    // Cas de test 2 : Chaîne avec des délimiteurs consécutifs
    const char *s2 = "Hello,,World,,OpenAI";
    char delim2 = ',';
    printf("\nTest 2: Splitting \"%s\" with delimiter '%c'\n", s2, delim2);
    char **result2 = ft_split(s2, delim2);
    print_split_result(result2);

    return (0);
}
*/

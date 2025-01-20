/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:24:16 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/14 12:16:11 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && (count > ((size_t)-1) / size))
		return (NULL);
	result = (void *)malloc(size * count);
	if (!result)
		return (NULL);
	if (result)
		ft_bzero(result, size * count);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 02:20:33 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/07 02:46:32 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next_cur;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next_cur = current->next;
		ft_lstdelone(current, del);
		current = next_cur;
	}
	*lst = NULL;
}

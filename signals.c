/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:25:32 by spike             #+#    #+#             */
/*   Updated: 2025/01/31 18:44:06 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");  // Saut de ligne propre
	rl_on_new_line();  // Remet readline proprement
	rl_replace_line("", 0);  // Efface la ligne actuelle
	rl_redisplay();  // Réaffiche le prompt
}

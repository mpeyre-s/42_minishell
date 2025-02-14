/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:14:25 by spike             #+#    #+#             */
/*   Updated: 2025/02/14 12:07:04 by spike            ###   ########.fr       */
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

int	fork_signal(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (1);
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}

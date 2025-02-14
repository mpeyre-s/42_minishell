/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:46 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 15:43:36 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_pipe(t_command *cmd, char ***env)
{
    t_command *cur;
    int count = 0;
    pid_t *pids;  // Tableau pour stocker les PIDs
    int i;

    // Compter le nombre de pipes
    cur = cmd;
    while (cur->next)
    {
        if (cur->pipe_out == 1)
            count++;
        cur = cur->next;
    }

    // Allouer le tableau des PIDs
    pids = malloc(sizeof(pid_t) * (count + 1));
    if (!pids)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Créer un tableau de pipes
    int pipe_fds[count][2];

    // Créer tous les pipes
    for (i = 0; i < count; i++)
    {
        if (pipe(pipe_fds[i]) == -1)
        {
            perror("pipe");
            free(pids);
            exit(EXIT_FAILURE);
        }
    }

    // Exécuter les commandes
    cur = cmd;
    for (i = 0; i <= count; i++)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            free(pids);
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {
            // Configuration des pipes pour le processus enfant
            if (i == 0 && cur->pipe_out)
            {
                dup2(pipe_fds[0][1], STDOUT_FILENO);
            }
            else if (i == count)
            {
                dup2(pipe_fds[i-1][0], STDIN_FILENO);
            }
            else
            {
                dup2(pipe_fds[i-1][0], STDIN_FILENO);
                dup2(pipe_fds[i][1], STDOUT_FILENO);
            }

            // Fermer tous les descripteurs de fichiers dans l'enfant
            for (int j = 0; j < count; j++)
            {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
            }

            exec_cmd(cur, env);
            exit(EXIT_FAILURE);
        }
        cur = cur->next;
    }

    // Parent : fermer tous les pipes
    for (i = 0; i < count; i++)
    {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
    }

    // Attendre tous les processus enfants dans l'ordre
    int status;
    for (i = 0; i <= count; i++)
    {
        waitpid(pids[i], &status, 0);
    }

    free(pids);
}

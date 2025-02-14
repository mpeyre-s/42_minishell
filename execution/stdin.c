/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:00:11 by spike             #+#    #+#             */
/*   Updated: 2025/02/14 23:27:34 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	modify_stdin_heredoc(t_command *cmd, char ***env, int *flag)
{
	int	original_stdin;
	int	file_fd;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin < 0)
		return (-1);
	file_fd = open("heredoc.txt", O_RDONLY);
	if (file_fd < 0)
		return (-1);
	if (dup2(file_fd, STDIN_FILENO) < 0)
	{
		close(file_fd);
		return (-1);
	}
	start_exec(cmd, env, *flag);
	if (dup2(original_stdin, STDIN_FILENO) < 0)
	{
		close(file_fd);
		close(original_stdin);
		return (-1);
	}
	close(file_fd);
	close(original_stdin);
	unlink("heredoc.txt");
	return (0);
}

char	*append_heredoc_line(char *temp, char *delim)
{
	char	*txt;
	char	*new_temp;

	txt = readline("> ");
	if (!txt)
	{
		ft_putstr_fd("problem with readline fct\n", 2);
		free(temp);
		return (NULL);
	}
	if (strncmp(txt, delim, strlen(delim)) == 0
		&& txt[strlen(delim)] == '\0')
	{
		free(txt);
		return (temp);
	}
	new_temp = ft_strjoin(temp, txt);
	free(txt);
	if (!new_temp)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (new_temp);
}

char	*read_heredoc_input(char *delim)
{
	char	*temp;
	char	*new_temp;

	temp = ft_strdup("");
	if (!temp)
		return (NULL);
	while (1)
	{
		new_temp = append_heredoc_line(temp, delim);
		if (!new_temp)
			return (NULL);
		if (new_temp == temp)
			break ;
		temp = new_temp;
	}
	return (temp);
}

int	write_heredoc_to_file(char *content)
{
	int	fd;

	fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	write(fd, content, strlen(content));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

int	stdin_heredoc(t_command *cmd, char *delim, char ***env, int *flag)
{
	char	*temp;

	*flag = 1;
	temp = read_heredoc_input(delim);
	if (!temp)
		return (-1);
	if (write_heredoc_to_file(temp) < 0)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	if (modify_stdin_heredoc(cmd, env, flag) == -1)
		return (-1);
	return (0);
}

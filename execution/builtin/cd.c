/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:06:46 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/02/14 22:58:44 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcpy(str + len1, s2, len2 + 1);
	free(s1);
	return (str);
}

static int	add_env_var(char ***env, char *new_var, int i)
{
	char	**new_env;

	new_env = realloc(*env, sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}
	*env = new_env;
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
	return (0);
}

static int	update_env(char ***env, const char *var_name, const char *new_value)
{
	char	*new_var;
	int		i;
	size_t	var_len;

	new_var = ft_strjoin(var_name, "=");
	if (!new_var)
		return (1);
	new_var = ft_strjoin_free(new_var, new_value);
	if (!new_var)
		return (1);
	i = 0;
	var_len = ft_strlen(var_name);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var_name, var_len) == 0
			&& (*env)[i][var_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (0);
		}
		i++;
	}
	return (add_env_var(env, new_var, i));
}

static int	change_directory(const char *path, char ***env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_putstr_fd("cd: getcwd error\n", STDERR_FILENO), 1);
	if (chdir(path) != 0)
	{
		free(old_pwd);
		return (ft_putstr_fd("cd: no such file or directory\n", 2), 1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		return (ft_putstr_fd("cd: getcwd error\n", STDERR_FILENO), 1);
	}
	if (update_env(env, "OLDPWD", old_pwd) || update_env(env, "PWD", new_pwd))
		ft_putstr_fd("cd: failed to update environment\n", STDERR_FILENO);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(t_command *cmd, char ***env)
{
	char	*path;
	char	*temp;

	path = NULL;
	if (ft_arraylen(cmd->args) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO), 2);
	else if (!cmd->args[1])
		path = ft_strdup(get_env_var(*env, "HOME"));
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		path = ft_strdup(get_env_var(*env, "OLDPWD"));
		if (path)
			ft_putendl_fd(path, STDOUT_FILENO);
	}
	else if (cmd->args[1][0] != '/')
	{
		temp = ft_strjoin(get_env_var(*env, "PWD"), "/");
		path = ft_strjoin(temp, cmd->args[1]);
		free(temp);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		return (ft_putstr_fd("cd: path not found\n", STDERR_FILENO), 1);
	return (change_directory(path, env), free(path), 0);
}

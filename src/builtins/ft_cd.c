/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:33:55 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/12 00:04:58 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_shell	*return_home_utils(t_shell *shell, char *pwd)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * (3));
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", pwd);
	tmp[2] = NULL;
	free_tab(shell->cmd);
	shell->cmd = tmp;
	shell = ft_export(shell);
	getcwd(pwd, 5000);
	shell->env = edit_env_value(shell, "PWD", pwd);
	shell->exit_code = 0;
	return (shell);
}

// handle "cd" or "cd --" case wich return the cd to /home/USER_VALUE
static t_shell	*return_home(t_shell *shell, char *pwd)
{
	char	*home;

	home = get_env(shell, "HOME");
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		shell->exit_code = 1;
		return (shell);
	}
	if ((access(home, X_OK)) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_code = 1;
		free(home);
		return (shell);
	}
	chdir(home);
	free(home);
	return (return_home_utils(shell, pwd));
}

// change the cd to the new one .
static t_shell	*change_directory(t_shell *shell, char *pwd)
{
	char	**tmp;

	if ((access(shell->cmd[1], X_OK)) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(shell->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_code = 1;
		return (shell);
	}
	chdir(shell->cmd[1]);
	tmp = malloc(sizeof(char *) * (3));
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", pwd);
	tmp[2] = NULL;
	free_tab(shell->cmd);
	shell->cmd = tmp;
	shell = ft_export(shell);
	getcwd(pwd, 5000);
	shell->env = edit_env_value(shell, "PWD", pwd);
	shell->exit_code = 0;
	return (shell);
}

// handle "cd -" case wich change directory to OLDPWD
static t_shell	*go_to_old_pwd(t_shell *shell, char *pwd)
{
	char	*old_pwd;
	char	**tmp;

	old_pwd = get_env(shell, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		shell->exit_code = 1;
		return (shell);
	}
	chdir(old_pwd);
	ft_printf("%s\n", old_pwd);
	tmp = malloc(sizeof(char *) * (3));
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin("OLDPWD=", pwd);
	tmp[2] = NULL;
	free_tab(shell->cmd);
	shell->cmd = tmp;
	shell = ft_export(shell);
	getcwd(pwd, 5000);
	shell->env = edit_env_value(shell, "PWD", pwd);
	shell->exit_code = 0;
	free(old_pwd);
	return (shell);
}

// cd function main
t_shell	*ft_cd(t_shell *shell)
{
	char	pwd[5000];

	if (tab_size(shell->cmd) > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments.\n", 2);
		shell->exit_code = 1;
		return (shell);
	}
	getcwd(pwd, 5000);
	if (!shell->cmd[1] || !ft_strcmp(shell->cmd[1], "--"))
		return (return_home(shell, pwd));
	else if (!ft_strcmp(shell->cmd[1], "-"))
		return (go_to_old_pwd(shell, pwd));
	else
		return (change_directory(shell, pwd));
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(shell->cmd[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	shell->exit_code = 1;
	return (shell);
}

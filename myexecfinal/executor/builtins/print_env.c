/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:58 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 10:25:57 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int    ft_print_env_err(t_shell *shell, char *path)
{
    write(STDERR_FILENO, "env: ", 5);
    write(STDERR_FILENO, path, ft_strlen(path));
    write(STDERR_FILENO, ": No such file or directory\n", 29);
    shell->g_status = 127;
    return (1);
}

int ft_check_path(t_shell *shell, char **paths)
{
    int i;
    int j;
    int flag;

    i = 0;
    while (paths[i] != NULL)
    {
        j = 0;
        flag = 1;
        while (paths[i][j])
        {
            if (paths[i][j] == '=')
                flag = 0;
            j++;
            if (flag == 1 && paths[i][j] == '\0')
                return (ft_print_env_err(shell, paths[i]));
        }
        i++;
    }
    return (0);
}

void ft_print_env(t_shell *shell, char **paths)
{
    int i;

    i = 0;
    
    if (ft_check_path(shell, paths) == 0)
    {
        while (shell->env[i])
        {
            write(shell->fdout, shell->env[i], ft_strlen(shell->env[i]));
            write(shell->fdout, "\n", 1);
            i++;
        }
        while (paths[i])
        {
            write(shell->fdout, paths[i], ft_strlen(paths[i]));
            write(shell->fdout, "\n", 1);
            i++;
        }
    }
}
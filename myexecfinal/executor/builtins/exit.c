/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:15:57 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 12:51:00 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Función para salir de minishell */
void ft_exit(char **command, t_shell *shell)
{
    shell->exit = 1;
    write(shell->fdout, "exit\n", 5);
    if (command[0] && command[1])
        write_exit_toomany_err(shell);
    else if (command[0] && ft_isdigit_str(command[0]) == 0)
        write_numeric_err(shell, command);
    else if (command[0])
        shell->g_status = ft_atoi(command[0]);
    else
        shell->g_status = 0;
}

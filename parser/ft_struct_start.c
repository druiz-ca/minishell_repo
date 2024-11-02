/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:15:48 by sternero          #+#    #+#             */
/*   Updated: 2024/11/02 11:23:47 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_pipe_direction(t_pipe_red *direction, int i)
{
    printf("ft_pipe_direction\n");
    if (i == 1)
    {
        direction->pipe = 1;
        direction->redir = 0;
    }
    else if (i == 2)
    {
        direction->pipe = 0;
        direction->redir = 1;
    }
    else if (i == 3)
    {
        direction->pipe = 1;
        direction->redir = 1;
    }
    else
    {
        direction->pipe = 0;
        direction->redir = 0;
    }        
}

void    ft_struct_start(t_pipe_red *pipe_red)
{
    printf("ft_struct_start\n");
    pipe_red->pipe = 0;
    pipe_red->redir = 0;
}

/* The ft_pipe_direction() function initializes the pipe and redirection flags.
    It is necessary to avoid undefined behavior when the flags are used in the
    program. It is used to gestionate the pipe and redirection flags. And does
    permit config diferent pipe combinations and redirections. Flexibility is
    the key. */

/* ft_struct_start function initializes the pipe and redirection flags. It takes
    one argument: a pointer to a t_pipe_red structure. It initializes the pipe
    and redirection flags to 0. This is necessary to avoid undefined behavior
    when the flags are used in the program. */
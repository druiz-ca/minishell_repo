/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:59:54 by kevlar            #+#    #+#             */
/*   Updated: 2024/09/30 16:21:15 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Parseamos el prompt para comprobar errorres del estilo:

	- Comillas mas cerradas (check_quotes).
	- Que el primer caracter no sea un pipe (check_first_pipe).
	- Que las pipes sean las permitidas y las redirecciones esten bien
	  abiertas y cerradas (validating_pipes_reds):
*/
int	check_cmd(t_shell *shell)
{
	int	pos;
	int	state;

	pos = 0;
	state = NO_QUOTE;
		// empieza estableciendo el estado de las comillas en 0 (sin comillas).
	while (shell->prompt[pos])
	{
		if (shell->prompt[pos] == '\"' || shell->prompt[pos] == '\'')
			state = check_quotes(shell->prompt[pos], state);
				// compruebe si el carácter quote es una comilla simple o doble 
				// y actualiza el estado en consecuencia ( 0 , 1 o 2).
		pos++;
	}
	if (check_first_pipe(shell->prompt) == 0)
		return (0);
	else
		return (validating_pipes_reds(shell->prompt));
			// comprueba Que las pipes sean las permitidas y las redirecciones 
			// esten bien abiertas y cerradas 
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_pipes_reds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:14:59 by jmartos-          #+#    #+#             */
/*   Updated: 2024/09/29 13:58:38 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Manejar los pipes y la redirecciones (sino tiene comillas)*/
int	handle_pipe_red(char c, t_pipe_red *value, char *prompt, int *pos)
{
	if (c == '|')
	{
		if (value->pipe == 1 || !check_first_pipe(prompt))
			// si hay una pipe y está en la primera posición
			return (0);
		set_pipe_red(value, 1); 
			// marca en la estrcutura q hay una pipe
	}
	else if (c == '<' || c == '>')
	{
		if (value->red == 1 || !check_mixes(prompt, pos))
			// si hay redirecciónes y las mezclas son incorrectas
			return (0);
		set_pipe_red(value, 2); 
			// marca en la estrcutura q hay una redirección
	}
	else // si no hay ni pipe ni redirección
		set_pipe_red(value, 3);
			// marca en la estrcutura q no hay ni pipe ni redirección
	return (1);
}

/* Actualiza el estado de las comillas */
int	update_quote_state(char c, int quote_state)
{
	return (check_quotes(c, quote_state));
}

/* Comprueba q las pipes sean las permitidas y las redirecciones
estén bien abiertas y cerradas */
int	validating_pipes_reds(char *prompt)
{
	int			pos;
	int			quote_state;
	t_pipe_red	value;

	pos = 0;
	quote_state = NO_QUOTE; // (0)
	init_pipe_red(&value);
		// Inicializa la estructura para controlar los pipes y redicrecciones (red).
	while (prompt[pos])
	{
		quote_state = update_quote_state(prompt[pos], quote_state);
			// actualiza el estado de las comillas (quote) revisando todo el prompt.
		if (quote_state == NO_QUOTE) // si no tiene comillas (NO_QUOTE)
		{
			if (handle_pipe_red(prompt[pos], &value, prompt, &pos) == 0)
				// si devuelve 0 es q hay un error en las pipes o redirecciones
				return (0);
		}
		pos++;
	}
	return (check_last_pipe_red(prompt));
		// verifica q el último carácter no sea una pipe o redirección.
}

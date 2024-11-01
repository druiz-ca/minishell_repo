/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:52:51 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/11/01 12:53:09 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_str(char *str)
{
	int	cont;

	cont = 0;
	if (str == NULL)
		return (0);
	while (str[cont])
	{
		if (str[cont] >= '0' && str[cont] <= '9')
			cont++;
		else
			return (0);
	}
	return (1);
}
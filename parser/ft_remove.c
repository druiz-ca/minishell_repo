/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:51:58 by sternero          #+#    #+#             */
/*   Updated: 2024/11/02 11:22:42 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ft_remove_last(char **vector)
{
	printf("ft_remove_last\n");
	int     i;
	int     len;
	char    **out;

	i = 0;
	len = ft_vector_len(vector);
	out = ft_calloc(sizeof(char *), len);
	while (i < len - 1)
	{
		out[i] = ft_strdup(vector[i]);
		i++;
	}
	ft_free_vector(vector);
	return (out);
}

void    ft_remove_quotes(char *str)
{
	printf("ft_remove_quotes\n");
	int     i;
	int     j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				str[j++] = str[i++];
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				str[j++] = str[i++];
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

char    *ft_delete_str(char *str, size_t init, size_t end)
{
	printf("ft_delete_str\n");
	char    *out;
	size_t  len;
	size_t  mpos;
	size_t  npos;
	size_t  nlen;

	len = ft_strlen(str);
	mpos = 0;
	npos = 0;
	nlen = len - (end - init + 1);
	out = (char *)ft_calloc(sizeof(char), nlen + 1);
	while (mpos < init)
		out[npos++] = str[mpos++];
	mpos = end + 1;
	while (mpos < len)
		out[npos++] = str[mpos++];
	out[npos] = '\0';
	return (out);
}

void    ft_remove_matrix(char **matrix)
{
	printf("ft_remove_matrix\n");
	int     i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

/* The ft_remove_last() function removes the last element from an array of strings.
	It takes one argument: an array of strings. It returns a new array of strings
	with the last element removed. */

/* The ft_remove_qotes() function removes the single and double quotes from a 
	string. It takes one argument: a string and returns void. */

/* The ft_delete_str() function deletes a substring from a string. It takes 
	three arguments: a string, an initial position, and an end position. It
	returns a new string with the substring removed. */

/* The ft_remove_matrix() function frees the memory allocated for a matrix of
	strings. It takes one argument: a matrix of strings. The function frees the
	memory allocated for each string in the matrix and then frees the memory
	allocated for the matrix. */
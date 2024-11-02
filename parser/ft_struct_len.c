/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:21:20 by sternero          #+#    #+#             */
/*   Updated: 2024/11/02 11:23:03 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_len_double(char *str, int i)
{
    printf("ft_len_double\n");
    int len;

    len = 0;
    i++;
    while (str[i] && str[i] != '"')
    {
        len++;
        i++;
    }
    return (len);
}

int     ft_len_single(char *str, int i)
{
    printf("ft_len_single\n");
    int len;

    len = 0;
    i++;
    while (str[i] && str[i] != '\'')
    {
        len++;
        i++;
    }
    return (len);
}

int     ft_len_pipe(char *str, int i)
{
    printf("ft_len_pipe\n");
    int len;

    len = 0;
    i++;
    while (str[i] && str[i] != '|')
    {
        len++;
        i++;
    }
    return (len);
}

int     ft_len_redirection_1(char *str, int i)
{
    printf("ft_len_redirection_1\n");
    int len;

    len = 0;
    i++;
    while (str[i] && str[i] != '>')
    {
        len++;
        i++;
    }
    return (len);
}

int     ft_len_redirection_2(char *str, int i)
{
    printf("ft_len_redirection_2\n");
    int len;

    len = 0;
    i++;
    while (str[i] && str[i] != '<')
    {
        len++;
        i++;
    }
    return (len);
}

/* The ft_len_double() function calculates the length of a word in a string. It
    takes two arguments: a string and an index. It returns the length of the word
    enclosed in double quotes. */

/* The ft_len_single() function calculates the length of a word in a string. It
    takes two arguments: a string and an index. It returns the length of the word
    enclosed in single quotes. */

/* The ft_len_pipe() function calculates the length of a word in a string. It
    takes two arguments: a string and an index. It returns the length of the word
    enclosed in pipe characters. */

/* The ft_len_redirection_1() function calculates the length of a word in a string.
    It takes two arguments: a string and an index. It returns the length of the word
    enclosed in a > character. */

/* The ft_len_redirection_2() function calculates the length of a word in a string.
    It takes two arguments: a string and an index. It returns the length of the word
    enclosed in a < character. */
    

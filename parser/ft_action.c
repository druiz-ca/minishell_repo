/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:38 by sternero          #+#    #+#             */
/*   Updated: 2024/11/03 14:10:46 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_break_down(char *str, int *i)
{
	printf("ft_break_down\n");
	if (str[*i] == '>')
		return (ft_redirection_1(str, i));
	if (str[*i] == '<')
		return (ft_redirection_2(str, i));
	if (str[*i] == '|')
		return (ft_process_pipe(str, i));
	else
		return (ft_break_down(str, i));
}

void    ft_parse_input(t_minishell *minishell)
{
	minishell->full_cmd = ft_shell_split(minishell->prompt);
	if (minishell->prompt[ft_strlen(minishell->prompt) - 1] == ' ')
		minishell->full_cmd = ft_remove_last(minishell->full_cmd);
	printf("ft_parse_input\n");
	ft_env_var(minishell, minishell->env);
}

void    ft_action_parse(t_minishell *minishell, char *line)
{
	printf("ft_action parse %s %s\n", minishell->prompt, line);
	minishell->prompt = line;
	minishell->error_parse = 0;
	ft_spc_remove(minishell->prompt);
	if (ft_check_cmd(minishell))//no va )si pruebo "lñ" no me da error
	{
		ft_printf("Error: invalid command\n");
		minishell->error_parse = EXIT_FAILURE;
		minishell->prompt = NULL;
		return ;
	}
	ft_parse_input(minishell);
	minishell->split_cmd = ft_copy_mtx(minishell->split_cmd);
	//ft_free_vector(minishell->full_cmd);
	//ft_free_vector(minishell->split_cmd);
}

void    ft_spc_remove(char *spaces)
{
	printf("ft_spc_remove\n");
	int     rmv;

	if (!spaces)
		return ;
	rmv = ft_strlen(spaces);
	while (rmv > 0 && spaces[rmv - 1] == ' ')
	{
		rmv--;
	}
	spaces[rmv] = '\0';
}

void    ft_spc_remove_plus(char **vector, char *spaces)
{
	printf("ft_spc_remove_plus\n");
	char *tmp;

	tmp = ft_strjoin(vector[ft_vector_len(vector) - 1], spaces);
	free(vector[ft_vector_len(vector) - 1]);
	vector[ft_vector_len(vector) - 1] = tmp;
}


int		main(int argc, char *arbv[], char **envp) // el main debe recibir las envp!!
{
	t_minishell minishell;
	int i;
	/* COMPROBAR/CREAR funcion que almacene las variables de entorno
	en la estructura t_env y cambiar en al ft_parse el parámetro minishell->full_cmd
	que envia x el de t_env */
	
	minishell.prompt = NULL;
	minishell.full_cmd = NULL;
	minishell.split_cmd = NULL;
	minishell.error_parse = 0;
	minishell.env = NULL;
	i = 0;
	while (envp[i] != NULL)
		i++;
	minishell.env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		minishell.env[i] = ft_strdup(envp[i]);
		i++;
	}
	if (argc == 1)
	{
		while (1)
		{
			ft_parse_input2(&minishell);
			printf("main %s\n", minishell.prompt);
			//minishell.prompt = readline("minishell$ ");
			if (!minishell.prompt)
				break ;
			if (ft_strlen(minishell.prompt) > 0)
			{
				add_history(minishell.prompt);
				ft_action_parse(&minishell, minishell.prompt);
				printf("aqui2\n");
				pause();
			}
			free(minishell.prompt);
			ft_action_parse(&minishell, minishell.prompt);
			if (minishell.error_parse == 0)
				execute(minishell.cmds, &minishell);
		}
	}
	else
	{
		ft_action_parse(&minishell, arbv[1]);
	}
	//ft_free_vector(minishell.env);
	return (0);
}

/* The ft_break_down() function breaks down the command into tokens. It takes
   two arguments: a string and a pointer to an index. Depend on the character
	in the string, it calls the process functions to extract the tokens.
	It returns the token extracted from the string. */

/* The ft_parse_input() function is used to parse the input from the user. It
   takes one argument: a pointer to a t_minishell structure. It calls the
   ft_shell_split() function to split the input, the ft_remove_last() function
   to remove the last element of the matrix of strings, and the ft_env_var()
   function to substitute the environment variables. */

/* The ft_action_parse() function processes the input from the user. It takes
   two arguments: a pointer to a t_minishell structure and a string. It calls
   the ft_spc_remove() function to remove the spaces from the input, the
   ft_check_cmd() function to check if the command is valid, the ft_parse_
   input() function to parse the input, the ft_copy_mtx() function to copy the
   matrix of strings, and the ft_free_vector() function to free the memory
   allocated for the matrix of strings. */

/* The ft_spc_remove() function removes the spaces from the input. It takes one
	argument: a string that contains the input, and using a while loop, it
	removes the spaces from the end of the string. */

/* The ft_spc_remove_plus() function removes the spaces from the input. It takes
	two arguments: an array of strings and a string. It removes the spaces from
	the end of the last element of the array of strings. 
	
	The difference between the ft_spc_remove() and ft_spc_remove_plus() 
	functions is that the ft_spc_remove() function removes the spaces from the
	end of the string, while the ft_spc_remove_plus() function removes the
	spaces from the end of the last element of the array of strings. */
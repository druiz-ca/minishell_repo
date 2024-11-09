/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:03:39 by rguerrer          #+#    #+#             */
/*   Updated: 2024/11/09 09:42:56 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

/* Borramos los espacios que puede haber al final del prompt: retrocedo desde
el final de la cad mientras hayan espacios y ahí pongo \0 */
void	delete_end_spaces(char *str)
{
	int	len;

	if (str == NULL)
		return ;
	len = strlen(str);
	while (len > 0 && str[len - 1] == ' ')
		len--;
	str[len] = '\0';
}

/* Comprueba que no haya espacios ni tabuladores, sino devuelve 1(error)*/
static int	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	init_struct(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	shell->cmds = NULL;
	shell->prompt = NULL;
	shell->parsed_prompt = NULL;
	while (envp[i] != NULL)
		i++; // lleva i hasta la última linea de las envp
	shell->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		shell->env[i] = ft_strdup(envp[i]); // copia las variables de entorno a la matrix env
		i++;
	}
	shell->full_cmd = NULL;
	shell->cmd_path = NULL;
	shell->g_status = 0;
	save_fds(shell);
	reset_fds(shell);
	shell->exit = 0;
	shell->exec_signal = 0;
	shell->oldpwd = NULL;
	update_shlvl(shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	if (argc != 1 || argv[1] != NULL)
		return (ft_putstr_fd(RED "minishell: invalid arguments\n" NC, STDERR_FILENO), EXIT_FAILURE);
	init_struct(&shell, envp);
	while (shell.exit == 0)
	{
		if_signal();
		line = readline("Minishell$~ ");
			//muestra un prompt ("Minishell$~ ") y espera a que el usuario escriba una línea de texto y presione Enter.
			//Este prompt indica al usuario que el shell está listo para recibir comandos
			//devuelve un puntero a una cadena que contiene la línea de texto ingresada por el usuario
		if (line == NULL)
			break ;
		else if (ft_check_line(line) == 0) // comprueba q no hay espacios ni tabuladores
		{
			add_history(line);
				// agregar el comando más recientemente ingresado a la lista de historial.
				// sirve para q al presionar la flecha arriba para recuperar el comando 
				// ls -l del historial y pueda ejecutarlo nuevamente o modificarlo.
			init_prompt(&shell, line);
			if (shell.parse_error == 0)
				execute(shell.cmds, &shell);
		}
		if (line) // liberamos la memoria de la linea
			free(line);
	}
	ft_free_struct(&shell);
	return (ft_strd_free(shell.env), 0);
}

/*
-----------------------------FUNCIONES NUEVA --------------------------

	- READLINE: Lee una linea de texto desde la entrada estándar y la devuelve.
	- ADD_HISTORY: Agrega una línea al historial.
	- SIFEMPTYSET: Inicializa el conjunto de señales especificado a vacío.
	- SIGACTIONS: Establece el manejador de señales.

	
*/
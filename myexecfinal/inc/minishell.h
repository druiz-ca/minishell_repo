/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:51:36 by rguerrer          #+#    #+#             */
/*   Updated: 2024/11/09 14:38:30 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	valgrind --leak-check=full ./minishell
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE \
	700 // Macro utilizada para evitar errores por
		// inicializaciones o estructuras incompletas.

# include "libft/includes/libft.h" // libft
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>  // redline
# include <readline/readline.h> // redline
# include <signal.h>            // señales
# include <stdio.h>             // redline
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define NO_QUOTE 0
# define DQ_OPEN 1
# define SQ_OPEN 2

# define STDIN_FILENO 0  // entrada estandar de informacion (por la terminal)
# define STDOUT_FILENO 1 // salida estandar de informacion (en la terminal)
# define STDERR_FILENO 2 // error en la salida estandar (en la terminal)

# define SHELL_NAME "minishell"
# define SHELL_PROMPT "minishell$ "

# define NC "\033[0m"
# define RED "\033[31;1m"

/*
	Usaremos esta estructura para guardar los estados de pipes y redirecciones.
*/
typedef struct s_pipe_red
{
	int		pipe;
	int		red;
}			t_pipe_red;

/*
	Esta estructura de la expansion de las variabes de entorno.
*/
typedef struct s_var
{
	char	*key;
	char	*value;
}			t_var;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**incmd;
	char	**outcmd;
}			t_cmd;

/*
	- *prompt		= linea de comandos leida por el shell, sin parsear.
	- **env			= matriz de punteros a las variables de entorno del shell.
	- pid			= id del proceso actual de la consola.
	- *cmds			= puntero a la estructura de comandos.
	- **full_prompt	= matriz bidimensional de la linea de comandos ya parseada
						y spliteada.
	- *cmd_path		= ruta del primer comandos encontrado en el input.
	- inline		= file descriptor a leer para ejecutar un comando.
	- outline		= file descriptor a escribir para ejecutar un comando.
*/
typedef struct s_shell
{
	char	**split_cmd;
	char	*prompt;
	char	*parsed_prompt;
	char	**env;
	char	**full_cmd;
	char	*cmd_path;
	int		g_status;
	int		infile;
	int		fdin;
	int		outfile;
	int		fdout;
	int		fdnextin;
	pid_t	pid;
	int		exit;
	int		exec_signal;
	char	*oldpwd;
	int		prev_fd;
	int		parse_error;
	t_cmd	**cmds;
}			t_shell;

void		ft_free_envs(t_var **list_var);
int			main(int argc, char **argv, char **envp);
void		ft_free_struct(t_shell *shell);
void		free_cmd(t_cmd *cmd);
void		delete_end_spaces(char *str);
void		init_pipe_red(t_pipe_red *value);
void		init_prompt(t_shell *shell, char *line);
int			check_cmd(t_shell *shell);
int			check_quotes(char quote, int state);
int			check_first_pipe(char *prompt);
int			check_last_pipe_red(char *prompt);
int			check_mixes(char *prompt, int *pos);
int			validating_pipes_reds(char *prompt);
void		set_pipe_red(t_pipe_red *value, int flag);
int			handle_pipe_red(char c, t_pipe_red *value, char *prompt, int *pos);
int			update_quote_state(char c, int quote_state);
int			validating_pipes_reds(char *prompt);
char		*process_token(char *prompt, int *pos);
char		**super_split(char *prompt);
void		parse_input(t_shell *shell);
char		*process_dq(char *prompt, int *pos);
char		*process_sq(char *prompt, int *pos);
char		*process_pipe(char *prompt, int *pos);
char		*process_red1(char *prompt, int *pos);
char		*process_red2(char *prompt, int *pos);
int			strlen_end_word(char *prompt, int pos);
char		*process_char(char *prompt, int *pos);
t_var		**init_envp(char **envp);
char		*key_x_value(t_var **env_list, char *str, t_shell *shell);
void		expand_env_var(t_shell *shell, char **envp);
char		*get_var(t_var **list_var, char *key);
char		*find_varname(char *str, int pos);
void		remove_quotes(char *str);
void		executor_split(t_shell *shell);
void		allocate_memory(t_cmd **cmds, char **split_cmd);
char		*insert_str(char *main, char *piece, size_t pos);
char		*delete_str(char *main, size_t start, size_t finish);
void		handler(int signal);
void		if_signal(void);

/* builtins */
/* void		handle_getcwd_error(t_shell *shell);
void		handle_cd_error(char *path, t_shell *shell);
void		ft_cd(char **full_cmd, t_shell *shell);
void		ft_echo(char **args, t_shell *shell);
void		ft_env(t_shell *shell, char **full_cmd);
void		ft_exit(char **cmd, t_shell *shell);
void		ft_export(char **full_cmd, t_shell *shell);
void		ft_pwd(t_shell *shell);
void		ft_unset(char **name_var, t_shell *shell);
int			is_builtin(char *cmd);
void		execute_builtin(t_shell *shell, t_cmd **cmds, int i);
void		ft_env_error(int bad_env, char *env);
int			is_bad_env(char *env);
void		ft_new_env(char *name_var, char *value_var, t_shell *shell);
 */
/* executor */
int			pipe_counter(char **str);
void		execute_bin(t_shell *shell, t_cmd **cmds, int i);
void		execute(t_cmd **cmds, t_shell *shell);
void		reset_fds(t_shell *shell);
void		exc(char *path, t_cmd **cmd, t_shell *shell, int i);

/*redirection*/
void		apply_redirections(char **redir, t_shell *shell);
void		apply_pipe(t_shell *shell);
void		apply_heredoc(char *delimiter, t_shell *shell);
void		reset_redirections(t_shell *shell);
void		setup_redirections(t_shell *shell);
/*clean*/
void		ft_close_resets(t_shell *shell);
/*utils*/
void		reset_env(t_shell *shell, t_cmd **cmds);
void		update_shlvl(t_shell *shell);
char		**ft_undo(t_cmd **cmds, int i);
int			error_msg(char *path);

//--------------------------------------------------------------


// -------------------------------- Execution --------------------------------//

//---------------------------------  builtins  -------------------------------//

// cd_errors

void    write_oldpwd_error(t_shell *shell);
void    write_too_many_args(t_shell *shell);
void    write_cdhome_error(char *home_path, t_shell *shell);
void    write_backpwd_err(char *back_path, t_shell *shell);
void    write_cd_err(t_shell *shell);

// cd

void	ft_cd(char **full_command, t_shell *shell); // el mio 
char	*ft_get_environment(char *str_pwd, char **env_paths);
void	exec_cd_home(t_shell *shell);
void	back_pwd(t_shell *shell);
void	renew_path(t_shell *shell);

// delete_env_unset

void    ft_delete_env_unset(char **name_var, t_shell *shell);

// echo

void    ft_echo(char **full_command, t_shell *shell);

//  exit

void    ft_exit(char **full_command, t_shell *shell);

// env

void    ft_print_env(t_shell *shell, char **paths);
int     ft_check_path(t_shell *shell, char **paths);

//  pwd

void    ft_pwd(t_shell *shell);

//  some _errors

void    write_pwd_err(t_shell *shell);
void    write_numeric_err(t_shell *shell, char **command);
void    write_exit_toomany_err(t_shell *shell);

// update_env_errors

void    env_err0(char *command, int i);
void    env_err1(char *command, int i);
void    env_err2(char *command, int i);
void    env_err3();
void 	ft_print_env2(t_shell *shell);


// export

void 	ft_print_env_err2(t_shell *shell, int env_err, char *command);
void    ft_update_env_export(t_shell *shell, char **commands);
int     check_env(char *env);
int    	ft_print_env_err(t_shell *shell, char *path);

// env2

void    ft_free_env(char **env);
char    *ft_new_env(char *name, char *value);
void    ft_create_env(char *name, char *value, t_shell *shell);
int     ft_check_update_env(char *name, char *value, t_shell *shell);
void    ft_update_env(char *command, t_shell *shell);

//----------------------------  executor fts  -------------------------------//

// execute_bin

void    execute_bin_cmd_main(t_cmd **commands, t_shell *shell, int i);
char    **get_bin_paths(t_shell *shell);
int     write_bin_error(char *cmd, t_shell *shell);
char    *join_binpath_and_cmd(char *cmd, char *bin_path);
void	ft_str_free(char **str);


// execute_bin2

void    execute_bin_cmd(char *cmd_path, t_cmd **commands, t_shell *shell, int i);
char    **create_matrix_cmd_and_args(t_cmd **commands, int i);
void    execute_child_proces(char *path, char **exc, t_shell *shell);

// execute_builtins

void    execute(t_cmd **commands, t_shell *shell);
void    config_pipe(t_shell *shell);
void    check_if_builtin(t_cmd **commands, t_shell *shell, int i);
void    reset_oldpwd_and_lastcmd(t_shell *shell, t_cmd **commands);
void    reset_oldpwd(t_shell *shell, int i);

// heredoc

void    apply_heredoc(char *delimiter, t_shell *shell);
void    error_pipe(t_shell *shell);

// redirections

void    choose_redirections(char **cmd, t_shell *shell);
void    save_fds(t_shell *shell);
void    redir_outfile(char **cmd, t_shell *shell, int i);
void    redir_infile(char **cmd, t_shell *shell, int i);
void    reset_redirections(t_shell *shell);

// check_and_exec_builtins

void    choose_builtin(t_shell *shell, t_cmd **commands, int i);
int     check_if_is_builtin(char *command);




#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:06:58 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/14 20:07:30 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <sys/wait.h>
# define READ 0
# define WRITE 1

typedef struct s_enviroment
{
	int			argc;
	char		**argv;
	char		**envp;
}	t_enviroment;

typedef struct s_program_descriptors
{
	int			infile_fd;
	int			outfile_fd;
	int			pip[2];
}	t_program_descriptors;

/******************************************************************************\
* PIPEX 																	   *
\******************************************************************************/

void		pipex(
				char *infile_name,
				char **commands,
				char *outfile_name,
				t_enviroment program_env
				);

/******************************************************************************\
* PARSER 																	   *
\******************************************************************************/

char		*get_var_from_env(char *name, char **envp);
char		*join_paths(char *path1, char *path2);
char		*get_binary_path(char *path, char *bin_name);

/******************************************************************************\
* COMMANDS 																	   *
\******************************************************************************/

typedef struct s_command
{
	char	**envp;
	char	**argv;
	char	*name;
	pid_t	process;
	int		index;
}	t_command;

typedef struct s_commands
{
	t_command		*self;
	unsigned int	length;
}	t_commands;

t_commands	parse_commands(char **commands_str, t_enviroment program_env);
t_command	*reset_command(t_command *command);
t_command	*free_command(t_command *command);
t_commands	*free_commands(t_commands *commands);
void		execute_commands(
				t_commands commands,
				t_program_descriptors *descriptors
				);
void		try_to_execute(t_command command, t_commands commands);

/******************************************************************************\
* UTILS 																	   *
\******************************************************************************/

int			ft_chrcnt(char *string, char c);
pid_t		ft_throw_to_child(
				void (*f) (t_command command, t_commands commands),
				t_command command,
				t_commands commands,
				t_program_descriptors *descriptors,
				int is_last_command
				);
void		ft_error(char *message);
void		ft_exit_perror(char *message, int number);
void		ft_exit_error(char *message, int number);
void		ft_error_message(char *message, char *argument);
char		**ft_spliti(char *s, char c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:06:58 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/12/05 20:38:01 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <sys/wait.h>
# define READ 0
# define WRITE 1

typedef struct s_command
{
	char	**envp;
	char	**argv;
	char	*name;
}	t_command;


typedef struct s_enviroment
{
	int			argc;
	char		**argv;
	char		**envp;
}	t_enviroment;

t_command	parse_command_string(char *command, t_enviroment program_env);

/******************************************************************************\
* PIPEX 																	   *
\******************************************************************************/
void	pipex(char *infile_name, char **commands, char *outfile_name, t_enviroment program_env);

/******************************************************************************\
* STD																		   *
\******************************************************************************/

void	std__write_in(char *string);
int		std__switch_in_scope(int active);
int		std__switch_out_scope(int active);

/******************************************************************************\
* PARSER 																	   *
\******************************************************************************/

char	*get_var_from_env(char *name, char **envp);
char	*join_paths(char *path1, char *path2);
char	*get_binary_path(char *path, char *bin_name);

/******************************************************************************\
* UTILS 																	   *
\******************************************************************************/

int		ft_chrcnt(char *string, char c);
void	ft_throw_to_child(void (*f) (t_command command), t_command command);
void	ft_error(char *message);
void	ft_exit_error(char *message, int number);
void	ft_error_message(char *message, char *argument);
char	**ft_spliti(char *s, char c);

#endif

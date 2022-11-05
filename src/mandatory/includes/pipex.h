/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatos-s <kmatos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:06:58 by kmatos-s          #+#    #+#             */
/*   Updated: 2022/11/04 21:59:53 by kmatos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <sys/wait.h>

typedef struct s_enviroment
{
	char	**argv;
	char	**envp;
	char	*current_binary;
}	t_enviroment;

t_enviroment	*g__enviroment(void);

/******************************************************************************\
* PIPEX 																	   *
\******************************************************************************/
void	pipex(char *infile, char **commands, char *outfile, char *path);

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
void	ft_throw_to_child(void (*f) (void));

#endif

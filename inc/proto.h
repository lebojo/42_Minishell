/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/07/18 00:48:03 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

/*===================================INCLUDES====================================*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "libft/libft.h"

/*===================================SOURCES====================================*/

void	parse(t_cmds *cmds, char *input);
void	free_cmds(t_cmds *cmds);

/*=======EXEC=======*/

/*	EXEC_CMD			*/
void	simple_cmd(t_cmds *cmds, char **env);

/*	UTILS_EXEC			*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);

/*	GET_CMD			*/
void	select_cmd(t_cmd *cmd, char ***envp);

/*=====BUILTINS=====*/

// /*	CD				*/
void	ft_cd(char *new_path);

/*	ECHO			*/
void	ft_echo(t_cmd *cmd, char ***envp);

// /*	ENV				*/
void	ft_env(char **env);

// /*	EXIT			*/
void	ft_exit(void);

/*	EXPORT			*/
void	ft_export(t_cmd *cmd, char ***env);
char	**copy_tab(char **tab);
int		strdiff(const char *s1, const char *s2);

/*	HASHMAP			*/
char	*hm_get_value(char **map, char *key);

/*	PWD				*/
void	ft_pwd(void);
char	*actual_folder(void);

/*	UNSET			*/
void	ft_unset(t_cmd *cmd, char ***env);

#endif
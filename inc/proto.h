/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 18:50:39 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "struct.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*===================================SOURCES====================================*/

/*=======EXEC=======*/

/*	GET_ENV			*/
char	*find_path(char **envp, char *s, int x);

/*	GET_CMD			*/
void	select_cmd(t_envp *env, t_cmd *cmd);

/*=====BUILTINS=====*/

/*	CD				*/
void	ft_cd(t_cmd *cmd, t_envp *env);

/*	ECHO			*/
void	ft_echo(t_cmd *cmd, t_envp *env);

/*	ENV				*/
void	ft_env(t_cmd *cmd, t_envp *env);

/*	EXIT			*/
void	ft_exit(t_cmd *cmd, t_envp *env);

/*	EXPORT			*/
void	ft_export(t_cmd *cmd, t_envp *env);

/*	PWD				*/
void	ft_pwd(t_cmd *cmd, t_envp *env);

/*	UNSET			*/
void	ft_unset(t_cmd *cmd, t_envp *env);

void	parse(t_cmd *cmd, char *input);

#endif
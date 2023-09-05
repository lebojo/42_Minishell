/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:16 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 00:59:11 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_sep
{
	None,
	Pipe,	// == |
	S_left,	// == <
	S_right,// == >
	D_left,	// == <<
	D_right	// == >>
};

typedef struct s_exec
{
    int     **tube;
    int     s_tube;
    int     fd_in;
    int     fd_out;
    pid_t   *pid;
    char    *env_p;
    char    *cmd;
    char    **cmd_p;
    char    **cmd_a;
    char    *res;
    int     bytes;
}    t_exec;

typedef struct  s_cmd
{
    char    *name;
    char    *arg;
}    t_cmd;

typedef struct	s_cmds
{
	int			nb_cmd;
	int			nb_pipe;
    int         test;
	t_cmd		*cmd;
	enum e_sep	*sep;
}	t_cmds;

#endif
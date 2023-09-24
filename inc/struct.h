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

typedef struct s_pipe
{
    int **fd;
    int *pid;
}    t_pipe;

typedef struct  s_cmd
{
    char    *name;
    char    *arg;
	int		which_pipe;
}    t_cmd;

typedef struct	s_cmds
{
	int			nb_cmd;
	int			nb_pipe;
	t_cmd		*cmd;
	enum e_sep	*sep;
}	t_cmds;

#endif
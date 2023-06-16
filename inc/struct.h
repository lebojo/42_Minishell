/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:16 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 00:59:11 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_sep
{
	Pipe,	// == |
	S_left,	// == <
	S_right,// == >
	D_left,	// == <<
	D_right	// == >>
};

typedef struct	s_envp
{
    char    *pwd;
    char    **bin_path;
}   t_envp;

typedef struct	s_cmd
{
    char    *name;
    char    *arg;
}    t_cmd;

typedef struct	s_cmds
{
	int			nb_cmd;
	int			nb_pipe;
	t_cmd		*cmd;
	enum e_sep	*sep;
}	t_cmds;

#endif
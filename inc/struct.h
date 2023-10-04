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

extern int	g_status;

enum e_sep
{
	None,
	Pipe,
	S_left,
	S_right,
	D_left,
	D_right
};

enum e_quote
{
	none,
	simple,
	double_q
};

typedef struct s_inc
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;
	int	n;
	int	o;
	int	p;
	int	q;
	int	r;
	int	s;
	int	t;
	int	u;
	int	v;
	int	w;
	int	x;
	int	y;
	int	z;
}	t_inc;

typedef struct s_pipe
{
	int	**fd;
	int	*pid;
}	t_pipe;

typedef struct s_cmd
{
	char	*name;
	char	*arg;
	int		which_pipe;
}	t_cmd;

typedef struct s_cmds
{
	int			nb_cmd;
	int			nb_pipe;
	t_cmd		*cmd;
	enum e_sep	*sep;
}	t_cmds;

#endif
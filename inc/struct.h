/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:16 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 18:19:14 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum	e_type
{
	Simple,
	Piped
};

typedef struct s_prms
{
	char	*opt;
	char	*value;
}	t_prms;

typedef struct s_cmd
{
	char	*name;
	int		nb_prms;
	t_prms	*prms;
}	t_cmd;

#endif
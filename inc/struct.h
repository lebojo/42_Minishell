/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:16 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 18:30:45 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_envp
{
    char    *pwd;
    char    **bin_path;
}   t_envp;

typedef struct s_prms
{
    char    *opt;
    char    *value;
}    t_prms;

typedef struct s_cmd
{
    char    *name;
    int     nb_prms;
    t_prms    *prms;
}    t_cmd;

#endif
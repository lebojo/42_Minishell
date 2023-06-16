/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:16 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 04:10:06 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_sep
{
    Pipe,    // == |
    S_left,    // == <
    S_right,// == >
    D_left,    // == <<
    D_right    // == >>
};

typedef struct s_exec
{
    int     tube[2];
    int     fd_in;
    int     fd_out;
    pid_t   pid1;
    pid_t   pid2;
    char    *env_p;
    char    *cmd;
    char    **cmd_p;
    char    **cmd_a;
}    t_exec;

typedef struct  s_cmd
{
    char    *name;
    char    *arg;
}    t_cmd;

typedef struct  s_cmds
{
    int             nb_cmd;
    int             nb_pipe;
    t_cmd           *cmd;
    enum e_sep      *sep;
}    t_cmds;

#endif
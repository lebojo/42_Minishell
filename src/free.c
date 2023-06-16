/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:46:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/16 04:20:37 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void free_cmds(t_cmds *cmds) 
{
    if (cmds == NULL)
        return;
    int i = 0;
    while (i < cmds->nb_cmd) {
        if (cmds->cmd[i].name != NULL) {
            free(cmds->cmd[i].name);
        }
        if (cmds->cmd[i].arg != NULL) {
            free(cmds->cmd[i].arg);
        }
        i++;
    }
    free(cmds->cmd);
    if (cmds->sep != NULL) {
        free(cmds->sep);
    }
}
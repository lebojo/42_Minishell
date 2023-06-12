/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 20:19:42 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main(int ac, char **av, char **envp) 
{
    char    *input;  // Déclarer un pointeur de chaîne de caractères pour stocker l'entrée utilisateur$
    char    *tmp;
    t_envp  env;
	t_cmd	cmd;
    int     i;

    
    (void)ac;
    (void)av;   
    tmp = find_path(envp, "PATH", 4);
    env.pwd = find_path(envp, "PWD", 3);
    env.bin_path = ft_split(tmp, ':');
    printf("%s\n", env.bin_path[0]);
    printf("%s\n", env.pwd);
    while (1) {
        input = readline("?> : ");  // Afficher le prompt et lire l'entrée de l'utilisateur
        parse(&cmd, input);
        //printf("cmd.name = %s | cmd.nb_prms = %d\n", cmd.name, cmd.nb_prms);
        select_cmd(&env, &cmd);
        if (ft_strcmp(input, "q") == 1) 
        {
            free(input);  // Libérer la mémoire allouée par readline()
            break;
        }
        i = -1;
        while (++i < cmd.nb_prms)
        {
            printf("cmd.prms[%d].opt = %s | cmd.prms[%d].value = %s\n", i, cmd.prms[i].opt, i, cmd.prms[i].value);
            free(cmd.prms[i].opt);
            free(cmd.prms[i].value);
        }
        free(cmd.prms);
        free(cmd.name); 
        free(input);  // Libérer la mémoire allouée par readline()
    }
        
    return 0;
}

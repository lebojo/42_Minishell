/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 19:02:33 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main(int ac, char **av, char **envp) 
{
    char    *input;  // Déclarer un pointeur de chaîne de caractères pour stocker l'entrée utilisateur$
    char    *tmp;
    t_envp  env;
	t_cmd	cmd;

    
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
        if (ft_strcmp(input, "q") == 1) {
            free(input);  // Libérer la mémoire allouée par readline()
            break;
        }
        
        printf("Vous avez saisi : %s\n", input);  // Afficher l'entrée utilisateur
        
        free(input);  // Libérer la mémoire allouée par readline()
    }
        
    return 0;
}

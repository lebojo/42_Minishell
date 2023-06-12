/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/07 15:22:48 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main() {
    char* input;  // Déclarer un pointeur de chaîne de caractères pour stocker l'entrée utilisateur
    
    while (1) {
        input = readline("Entrez une valeur (ou 'q' pour quitter) : ");  // Afficher le prompt et lire l'entrée de l'utilisateur
        
        if (ft_strncmp(input, "q", 2) == 0) {
            free(input);  // Libérer la mémoire allouée par readline()
            break;
        }
        
        printf("Vous avez saisi : %s\n", input);  // Afficher l'entrée utilisateur
        
        free(input);  // Libérer la mémoire allouée par readline()
    }
    
    return 0;
}
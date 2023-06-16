/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 22:39:25 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main(int ac, char **av, char **envp) 
{
	char	*input;
	t_cmds	cmds;

	(void)ac;
	(void)av;
	while (1) {
		input = readline("?> : ");
		// parse(&cmds, input);
		if (ft_strcmp(input, "q") == 1) {
			free(input);
			break;
		}
		select_cmd(&cmds, envp);
		free(input);
	}
	return 0;
}
*/
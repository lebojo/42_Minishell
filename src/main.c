/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 17:42:21 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int	main(void)
{
	t_cmd	cmd;
	char	*tmp;

	tmp = ft_strdup("git checkout -b test");
	parse(&cmd, tmp);
	printf("cmd: %s, subcommand: %s, opt: %s, value: %s\n", cmd.name,
		cmd.prms[0].value, cmd.prms[1].opt, cmd.prms[1].value);
	return (0);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lebojo <lebojo@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/12 15:57:48 by jordan			#+#	#+#			 */
/*   Updated: 2023/06/15 19:34:42 by lebojo		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/proto.h"

void	parse(t_cmd *cmd, char *input, int start)
{
	char	**split;
	char	**tmp;
	int		j;

	split = ft_split(input, ' ');
	j = 0;
	cmd->name = ft_strdup(split[start++]);
	while (split[start] && split[start][0] != '|')
		cmd->arg = add_str(cmd->arg, split[start++], 1);
	free(split);
}

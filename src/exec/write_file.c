/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   write_file.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jchapell <jchapell@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/06 10:42:32 by abourgue		  #+#	#+#			 */
/*   Updated: 2023/11/07 19:19:58 by jchapell		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/proto.h"

void	write_in_file(t_cmds *cmds, int x, char ***env, int out)
{
	int		id[2];

	id[0] = 0;
	if (cmds->cmd[x + 1].name != NULL)
		id[1] = open(cmds->cmd[x + 1].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		id[1] = open(cmds->cmd[x].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return ;
	}
	if (id[1] == -1)
		return ;
	if (cmds->sep[x + 1] != Pipe && cmds->sep[x + 1] == S_right)
		return ;
	if (exec_inpipe_builtins(out, id[1], &cmds->cmd[0], env))
		return ;
	else
		exec_in_fork(out, id, &cmds->cmd[0], *env);
}

void	exec_herefork(int fd, char *txt, t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		p[2];
	int		in[2];
	char	buf[BUFSIZ];
	ssize_t	n;
	int		status;

	if (pipe(p) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		if (pipe(in) == -1)
			exit(printf("Error: heredoc: pipe in\n"));
		write(in[1], txt, strlen(txt));
		close(in[1]);
		dup2(in[0], STDIN_FILENO);
		close(in[0]);
		exec_cmd(cmd, env);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(p[1]);
		n = 1;
		while (n > 0)
		{
			n = read(p[0], buf, BUFSIZ);
			if (write(fd, buf, n) == -1) 
				exit(printf("Error: heredoc: write\n"));
		}
		if (n == -1)
			exit(printf("Error: heredoc: read\n"));
		close(p[0]);
		waitpid(pid, &status, 0);
		update_last_exit(status, &env);
	}
}

void	write_in_here(t_cmds *cmds, char *str, int i, char **env)
{
	int		fd;

	fd = 0;
	if (ft_strcmp(cmds->cmd[i + 2].arg, ">"))
		fd = open(cmds->cmd[i + 2].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(cmds->cmd[i + 2].arg, ">>"))
		fd = open(cmds->cmd[i + 2].name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	// faire pour les builtins
	exec_herefork(fd, str, &cmds->cmd[i + 1], env);
}

void	append_to_file(t_cmds *c, int x, char ***env)
{
	int		id[2];

	id[0] = 0;
	if (c->cmd[x + 1].name != NULL)
		id[1] = open(c->cmd[x + 1].name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		id[1] = open(c->cmd[x].name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return ;
	}
	if (id[1] == -1)
		return ;
	if (c->sep[x + 1] != Pipe && c->sep[x + 1] == D_right)
		return ;
	if (exec_inpipe_builtins(STDOUT_FILENO, id[1], &c->cmd[0], env))
		return ;
	else
		exec_in_fork(STDOUT_FILENO, id, &c->cmd[0], *env);
}

void	read_file(char *name, t_cmd *cmd, char ***env)
{
	int	id[2];

	id[0] = 0;
	id[1] = open(name, O_RDONLY);
	if (id[1] == -1)
		return ;
	if (exec_inpipe_builtins(STDIN_FILENO, id[1], cmd, env))
		return ;
	else
		exec_in_fork(STDIN_FILENO, id, cmd, *env);
}
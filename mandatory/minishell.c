/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammiou <hhammiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:55:50 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 14:38:30 by hhammiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	d_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	clean_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free_str(tmp->args);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free_str(tmp->outfile);
		if (tmp->heredoc)
			free_str(tmp->heredoc);
		if (tmp->heredoc_expand)
			free(tmp->heredoc_expand);
		if (tmp->fd)
			free(tmp->fd);
		tmp = tmp->next;
		cmd->next = NULL;
		free(cmd);
		cmd = tmp;
	}
}

void	f_clean(t_cmd *cmds)
{
	close_fds(cmds->fd);
	clean_cmd(cmds);
}

static void	execute_and_cleanup(t_minishell *mshell)
{
	char	**ennnnv;
	t_cmd	*tmp;

	mshell->cmds->env = mshell->new_env;
	ennnnv = env_to_arr(mshell->cmds->env);
	tmp = mshell->cmds;
	while (tmp)
	{
		tmp->env = mshell->new_env;
		tmp->or_env = ennnnv;
		tmp = tmp->next;
	}
	exec(mshell->cmds);
	mshell->new_env = mshell->cmds->env;
	free_str(ennnnv);
	f_clean(mshell->cmds);
	free(mshell->line);
	mshell->line = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mshell;

	if (ac != 1 && av[0][0])
		exit(1);
	mshell.new_env = create_env(env);
	increment_shlvl(&mshell.new_env);
	if (!env || !*env)
		mshell.new_env->is_env_fails = 1;
	while (1337)
	{
		intial_signals();
		signal(SIGQUIT, SIG_IGN);
		mshell.line = readline("\033[1;1;3;32m7ALLAL_SHELL $> \033[0m");
		if (!mshell.line)
			d_exit();
		add_history(mshell.line);
		mshell.cmds = parse_line(&mshell);
		if (!mshell.cmds)
		{
			free(mshell.line);
			continue ;
		}
		execute_and_cleanup(&mshell);
	}
	return (0);
}

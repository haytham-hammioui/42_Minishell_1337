/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:27:21 by smaksiss          #+#    #+#             */
/*   Updated: 2025/10/03 22:27:31 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	wait_children(t_cmd *cmds)
{
	t_cmd	*current;
	int		status;

	current = cmds;
	status = 0;
	while (current)
	{
		if (current->pid > 0 && current->args)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status) && check_built_in(current))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_code = 128 + WTERMSIG(status);
				if (g_exit_code == 131)
					write(STDERR_FILENO, "Quit: 3\n", 8);
			}
			else
				g_exit_code = FAILURE;
			if (g_exit_code == 141)
				g_exit_code = 1;
		}
		current = current->next;
	}
}

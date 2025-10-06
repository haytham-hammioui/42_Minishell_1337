/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:14:02 by smaksiss          #+#    #+#             */
/*   Updated: 2025/09/09 10:59:52 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	close_fds(t_fd *fd)
{
	if (fd->fdin != -1)
		close(fd->fdin);
	if (fd->fdout != -1)
		close(fd->fdout);
	if (fd->pipefd[0] != -1)
		close(fd->pipefd[0]);
	if (fd->pipefd[1] != -1)
		close(fd->pipefd[1]);
}

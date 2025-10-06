/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:48:29 by smaksiss          #+#    #+#             */
/*   Updated: 2025/06/29 11:30:27 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	ft_putchar(char c, int fd)
{
	if (fd == -1)
		return ;
	else
		write(fd, &c, 1);
}

void	ft_putnbr(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, fd);
	}
	ft_putchar(nb % 10 + '0', fd);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*head;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	while (head->next)
		head = head->next;
	head->next = new;
	new->next = NULL;
}

void	ft_lstclear(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

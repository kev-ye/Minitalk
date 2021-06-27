/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:15:42 by kaye              #+#    #+#             */
/*   Updated: 2021/06/27 22:58:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	exit_with_msg(char *msg)
{
	if (msg)
		ft_putstr(msg);
	exit(EXIT_FAILURE);
}

static void	send_char(unsigned int c, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	bit = 7;
	while(bit >= 0)
	{
		if (((c >> bit) % 2) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		--bit;
	}
}

static void	send_str(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		send_char(str[i++], pid);
}

static void	check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid && pid[i])
	{
		if (pid[i] < 48 || pid[i] > 57)
			exit_with_msg(B_RED"Not a valid pid !\n"NONE);
		++i;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		exit_with_msg(B_RED"Number of args is not valid!\n"NONE);
	check_pid(av[1]);
	send_str(ft_atoi(av[1]), av[2]);
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalgar <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 00:03:49 by isalgar           #+#    #+#             */
/*   Updated: 2022/06/03 05:20:32 by isalgar          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<unistd.h>

void	ft_putnbr(int nbr)
{
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	write (1, &"0123456789"[nbr % 10], 1);
}

void	ft_server(int signal, siginfo_t *info, void *unused)
{
	static int	i = 128;
	static char	c = 0;

	(void)unused;
	if (signal == SIGUSR1)
		c = c | i;
	i /= 2;
	if (i == 0)
	{
		write(1, &c, 1);
		i = 128;
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			write(1, "Error signal\n", 15);
	}
}

int	main(void)
{
	struct sigaction	come;
	int					pid;

	come.sa_flags = SA_SIGINFO;
	come.sa_sigaction = ft_server;
	sigaction(SIGUSR1, &come, 0);
	sigaction(SIGUSR2, &come, 0);
	pid = getpid();
	write(1, "Server PID: ", 13);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		;
}

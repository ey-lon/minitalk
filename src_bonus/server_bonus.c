/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:08 by abettini          #+#    #+#             */
/*   Updated: 2023/01/24 10:25:10 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../Libft/libft.h"

static char	*ft_free_join(char *old_msg, char *new_char)
{
	char	*full_msg;

	if (!old_msg)
		old_msg = ft_calloc(1, 1);
	full_msg = ft_strjoin(old_msg, new_char);
	free(old_msg);
	return (full_msg);
}

static void	ft_sighandler(int signal, siginfo_t *info, void *context)
{
	static char	*full_msg;
	static char	msg;
	static int	i;

	if (signal == SIGUSR2)
		msg = msg | 1 << i;
	i++;
	if (i >= 8)
	{
		if (msg)
			full_msg = ft_free_join(full_msg, &msg);
		else if (msg == '\0')
		{
			kill(info->si_pid, SIGUSR1);
			printf("%s\n", full_msg);
			free(full_msg);
			full_msg = 0;
		}
		i = 0;
		msg = 0;
	}
	kill(info->si_pid, SIGUSR2);
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sa.sa_sigaction = ft_sighandler;
	pid = getpid();
	ft_printf("%d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}

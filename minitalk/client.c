#include "minitalk.h"

void	end_message(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, SIGUSR1) < 0)
			kill_error();
		usleep(70);
	}
}

static void	send_message(int pid, const char *str)
{
	int	mask;

	while (*str)
	{
		mask = 128;
		while (mask)
		{
			if (*str & mask)
			{
				if (kill(pid, SIGUSR1) < 0)
					kill_error();
			}
			else
				if (kill(pid, SIGUSR2) < 0)
					kill_error();
			mask >>= 1;
			usleep(70);
		}
		str++;
	}
	end_message(pid);
}

static int	check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i] != 0)
	{
		if (pid[i] < '0' || pid[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	catcher(int sig)
{
	(void)sig;
	write(1, "The acknowledgement is received\n", 32);
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
	{
		write(2, "You must enter 2 arguments. Try again!\n", 39);
		return (1);
	}
	if (check_pid(argv[1]) || pid > 99999 || pid <= 0)
	{
		write(2, "Incorrect pid. Try again!\n", 26);
		return (1);
	}
	signal(SIGUSR1, catcher);
	send_message(pid, argv[2]);
	pause();
	return (0);
}

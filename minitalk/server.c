#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	sighandler(int sig, siginfo_t *siginfo, void *code)
{
	static char	ascii = 0;
	static int	count = 128;

	(void)code;
	if (sig == SIGUSR1)
		ascii += count;
	count >>= 1;
	if (ascii == -1)
	{
		if (kill(siginfo->si_pid, SIGUSR1))
			kill_error();
		count = 128;
		ascii = 0;
		return ;
	}
	if (count == 0)
	{
		ft_putchar(ascii);
		count = 128;
		ascii = 0;
	}
}

void	ft_print_pid(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_print_pid(-n);
	}
	else if (n > 9)
	{
		ft_print_pid(n / 10);
		ft_print_pid(n % 10);
	}
	else
		ft_putchar(n + '0');
}

int	newset(int sig,
	void(*sighandler)(int sig, siginfo_t *siginfo, void *))
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = sighandler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	return (sigaction(sig, &act, 0));
}

int	main(void)
{
	ft_print_pid(getpid());
	ft_putchar('\n');
	if (newset(SIGUSR1, sighandler) == -1
		|| newset(SIGUSR2, sighandler) == -1)
	{
		write(2, "sigaction ERROR\n", 16);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}

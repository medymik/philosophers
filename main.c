#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (!args_isvalid(argc, argv))
	{
		print_error("Error : arguments are not valid\n");
		return (1);
	}
	g_n = ft_atoi(argv[1]);
	g_die = ft_atoi(argv[2]);
	g_eat = ft_atoi(argv[3]);
	g_sleep = ft_atoi(argv[4]);
	g_count = (argc == 6) ? ft_atoi(argv[5]) : -1;

	philosophers_init();
	philosophers_start();
	while (g_someone_died)
	{
		usleep(100);
	}
	philosophers_clear();
	free(g_forks);
	return (0);
}

#include "philosophers.h"

int	args_isvalid(int argc, char **argv)
{
	int i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (!ft_isnumeric(argv[i]))
			return (0);
	}
	return (1);
}



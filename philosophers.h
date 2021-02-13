#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

// utils
int	ft_isnumeric(char *str);
int		ft_atoi(const char *str);
void		ft_putnbr_fd(unsigned long long n, int fd);
void	ft_putstr(char *str);

// args
int	args_isvalid(int argc, char **argv);
// print
void	print_error(char *str);
// philosophers
void	philosophers_init(void);
void	philosophers_clear(void);
void	philosophers_start(void);
// time
unsigned long get_time(void);

typedef enum		e_state
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED
}					t_state;

typedef struct		s_philo
{
	int				id;
	unsigned long	last_meal;
	unsigned long	limit;
	int				eating;
	int				left;
	int				right;
	pthread_t		th;
	pthread_t		th_health;
	pthread_mutex_t		mutex;
}			t_philo;

pthread_mutex_t	*g_forks;
pthread_mutex_t	g_io_lock;
t_philo		*g_ps;
int		g_n;
int		g_die;
int		g_eat;
int		g_sleep;
int		g_count;
int		g_someone_died;
unsigned long	g_start;

void	print_message(t_philo *p, int state);

#endif

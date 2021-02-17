#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
# define SLEEP_TIME g_sleep * 1000
# define EAT_TIME g_eat * 1000

int g_n;
int g_die;
int g_eat;
int g_sleep;
int g_eat_count;

typedef enum    e_state
{
    EAT,
    SLEEP,
    THINK,
    DIED,
    FORK
}               t_state;

typedef struct s_philo
{
    int         id;
    unsigned long last_meal;
    unsigned long limit;
    pid_t       pid;
    pthread_t   health;
}              t_philo;

t_philo *g_ps;
sem_t   *g_forks;
sem_t   *g_stop;
sem_t   *g_io_lock;
sem_t   *g_seat_count;

unsigned long g_start;

int		ft_isnumeric(char *str);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(unsigned long long n, int fd);
void	ft_putstr(char *str);
void	print_message(t_philo *p, int state);
unsigned long   get_time(void);
void			philosophers_init(void);
void            philosophers_start(void);
void            philosophers_routine(t_philo *p);
#endif
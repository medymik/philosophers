#include "philosophers.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

unsigned long get_time(void)
{
    struct timeval n;

    gettimeofday(&n,  NULL);
    return ((n.tv_sec * 1000) + (n.tv_usec * 0.001));
}

void    semaphores_init(void)
{
    sem_unlink("/forks");
    sem_unlink("/stop");
    sem_unlink("/g_io_lock");
    g_forks = sem_open("/forks", O_CREAT, 0600, g_n);
    g_stop = sem_open("/stop", O_CREAT, 0600, 0);
    g_io_lock = sem_open("/g_io_lock", O_CREAT, 0600, 1);
}

void    philosophers_init(void)
{
    int i;

    i = 0;
    g_ps = malloc(sizeof(t_philo) * g_n);
    while (i < g_n)
    {
        g_ps[i].id = i;
        i++;
    }
}

void    *health_check(void *data)
{
    t_philo *p;

    p = data;
    while (1)
    {
        if (get_time() > p->limit)
        {
            print_message(p, DIED);
            sem_post(g_stop);
            return (NULL);
        }
    }
    return (NULL);
}

void    philosophers_routine(t_philo *p)
{
    p->last_meal = get_time();
    p->limit = p->last_meal + g_die;
    pthread_create(&p->health, NULL, health_check, p);
    pthread_detach(p->health);
    while (1)
    {
        sem_wait(g_forks);
        print_message(p, FORK);
        sem_wait(g_forks);
        print_message(p, FORK);
        print_message(p, EAT);
        p->last_meal = get_time();
        p->limit = p->last_meal + g_die;
        usleep(g_eat * 1000);
        sem_post(g_forks);
        sem_post(g_forks);
        print_message(p, SLEEP);
        usleep(g_sleep * 1000);
        print_message(p, THINK);
    }
}

void    philosophers_start(void)
{
    int i;

    i = -1;
    g_start = get_time();
    while (++i < g_n)
    {
        g_ps[i].pid = fork();
        if (!g_ps[i].pid)
        {
            philosophers_routine(&g_ps[i]);
            exit(0);
        }
        usleep(100);
    }
}

int     main(int argc, char **argv)
{
    g_n = ft_atoi(argv[1]);
    g_die = ft_atoi(argv[2]);
    g_eat = ft_atoi(argv[3]);
    g_sleep = ft_atoi(argv[4]);
    g_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
    philosophers_init();
    semaphores_init();
    philosophers_start();
    sem_wait(g_stop);
    int i = 0;
    while (++i < g_n)
        kill(g_ps[i].pid, SIGKILL);
    // while (1)
    //     usleep(1000);
    return (0);
}
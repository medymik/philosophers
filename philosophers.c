#include "philosophers.h"

void	mutexes_init(void)
{
	int i;

	g_forks = malloc(sizeof(pthread_mutex_t) * g_n);
	pthread_mutex_init(&g_io_lock, NULL);
	i = -1;
	while (++i < g_n)
		pthread_mutex_init(&g_forks[i], NULL);
		i++;
}

void	mutexes_clear(void)
{
	int i;

	i = -1;
	while (++i < g_n)
		pthread_mutex_destroy(&g_forks[i]);
	pthread_mutex_destroy(&g_io_lock);
	free(g_forks);
}

void	philosophers_init(void)
{
	int i;
	int tmp;

	g_ps = malloc(sizeof(t_philo) * g_n);
	i = -1;
	mutexes_init();
	while (++i < g_n)
	{
		g_ps[i].id = i;
		g_ps[i].left = i;
		g_ps[i].right = (i + 1) % g_n;
		pthread_mutex_init(&g_ps[i].mutex, NULL);
	}
	g_someone_died = 1;
}

int		take_fork(t_philo *p)
{
	if (g_someone_died)
	{
		pthread_mutex_lock(&g_forks[p->left]);
		print_message(p, FORK);
		if (g_someone_died)
		{
			pthread_mutex_lock(&g_forks[p->right]);
			print_message(p, FORK);
			return (1);
		}
	}
	return (0);
}

int		release_fork(t_philo *p)
{
	if (g_someone_died)
	{
		pthread_mutex_unlock(&g_forks[p->left]);
		pthread_mutex_unlock(&g_forks[p->right]);
			return (1);
	}
	return (0);
}

int		eat(t_philo *p)
{
	if (g_someone_died)
	{
		pthread_mutex_lock(&p->mutex);
		p->eating = 1;
		print_message(p, EAT);
		p->last_meal = get_time();
		p->limit = p->last_meal + g_die;
		usleep(g_eat * 1000);
		p->eating = 0;
		pthread_mutex_unlock(&p->mutex);
		return (1);
	}
	return (0);
}

int		go_sleep(t_philo *p)
{
	if (g_someone_died)
	{
		print_message(p, SLEEP);
		usleep(g_sleep * 1000);
		return (1);
	}
	return (0);
}

void	*check_health(void *data)
{
	t_philo *p = data;
	while (g_someone_died)
	{
		// printf("%lu == %lu\n", get_time(), p->last_meal);
		pthread_mutex_lock(&p->mutex);
		if (!p->eating && get_time() > p->limit)
		{
			print_message(p, DIED);
			g_someone_died = 0;
			return (NULL);
		}
		pthread_mutex_unlock(&p->mutex);
	}
	return (NULL);
}

void	*philosophers_routine(void *data)
{
	t_philo *p = data;
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
	pthread_create(&p->th_health, NULL, check_health, p);
	pthread_detach(p->th_health);
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
	while (g_someone_died)
	{
		if (!take_fork(p))
			return (NULL);
		if (!eat(p))
			return (NULL);
		if (!release_fork(p))
			return (NULL);
		if (!go_sleep(p))
			return (NULL);
		print_message(p, THINK);
	}
	return (NULL);
}

void	philosophers_start(void)
{
	int i;

	g_start = get_time();
	i = -1;
	while (++i < g_n)
	{
		pthread_create(&g_ps[i].th, NULL, philosophers_routine, &g_ps[i]);
		pthread_detach(g_ps[i].th);
		usleep(100);
	}
}

void	philosophers_clear(void)
{
	int i;

	i = -1;
	while (++i < g_n)
		pthread_mutex_destroy(&g_ps[i].mutex);
	free(g_ps);
	mutexes_clear();
}

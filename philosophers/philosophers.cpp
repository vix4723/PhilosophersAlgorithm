#include "PhiloHeader.h"

void *philo_tasks(int fork_id)
{
	
}

int main(int argc, char **argv)
{
	int num_philo = 5;
	pthread_t philo[num_philo];
	int time_to_die = 5000, time_to_eat = 1000, time_to_sleep = 1000;
	int num_fork[num_philo];

	for (int i = 1; i <= num_philo; i++){
		num_fork[i] = i;
		pthread_create(&philo[i], NULL, philo_tasks, &num_fork[i]);
	}

	for (int i = 0; i < num_philo; i++) {
        pthread_join(philo[i], NULL);
    }

	return 0;
}
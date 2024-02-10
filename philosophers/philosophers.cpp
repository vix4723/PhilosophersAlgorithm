#include "PhiloHeader.h"

void *philo_tasks(void *var)
{
	cout << "manu es virgen" << endl;
}

// void philosopher_creator(pthread_t *philo) {
// 	pthread_create(philo, NULL, philo_tasks, NULL);
// }

int main(int argc, char **argv)
{
	int num_philo = 5;

	for (int i = 0; i < num_philo; i++){
		pthread_t *philo[i];
		pthread_create(philo[i], NULL, philo_tasks, NULL);
	}

	cout << "hellow world" << endl;
	return 0;
}
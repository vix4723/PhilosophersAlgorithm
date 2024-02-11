#include "PhiloHeader.h"

const int num_philo = 5;
pthread_mutex_t mutex[num_philo];

void* philo_tasks(void* arg)
{
	int id = *((int *)arg);
	int left_fork = id;
	int right_fork = (id + 1) % num_philo;

	while (true)
	{
		// Thinking
		std::cout << "Philosopher " << id << " is thinking." << std::endl;
		usleep(1000000); // Sleep for 1 second

		// Attempt to pick up forks
		if (id % 2 == 0) {
			pthread_mutex_lock(&mutex[left_fork]);
			pthread_mutex_lock(&mutex[right_fork]);
		} else {
			pthread_mutex_lock(&mutex[right_fork]);
			pthread_mutex_lock(&mutex[left_fork]);
		}

		// Eating
		std::cout << "Philosopher " << id << " is eating." << std::endl;
		usleep(1000000); // Sleep for 1 second

		// Release forks
		pthread_mutex_unlock(&mutex[left_fork]);
		pthread_mutex_unlock(&mutex[right_fork]);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	int num_fork[num_philo];
	pthread_t philo[num_philo];

	//Inicializando los mutex
	for(int i = 0; i < num_philo; i++) {
		pthread_mutex_init(&mutex[i], NULL);
	}

	//Creating the threads
	for (int i = 0; i < num_philo; i++){
		num_fork[i] = i;
		pthread_create(&philo[i], NULL, philo_tasks, &num_fork[i]);
	}

	sleep(10);

	// Join the threads
	for (int i = 0; i < num_philo; i++) {
        pthread_join(philo[i], NULL);
    }

	for(int i = 0; i < num_philo; i++) {
	//Destruyendo los mutex
		pthread_mutex_destroy(&mutex[i]);
	}

	return 0;
}
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_EAT_COUNT 5

using namespace std;

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int eat_counter[NUM_PHILOSOPHERS] = {0};
pthread_mutex_t eat_counter_mutex;

void *philosopher(void *arg)
{
	int philosopher_id = *((int *)arg);
	int left_fork = philosopher_id;
	int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

	for (int i = 0; i < NUM_EAT_COUNT; ++i)
	{
		// Thinking
		cout << "Philosopher " << philosopher_id << " is thinking." << endl;
		sleep(1);

		// Pick up/Lock forks
		pthread_mutex_lock(&forks[left_fork]);
		pthread_mutex_lock(&forks[right_fork]);

		// Eating
		cout << "Philosopher " << philosopher_id << " is eating." << endl;
		sleep(1);

		// Release/Unlock forks
		pthread_mutex_unlock(&forks[left_fork]);
		pthread_mutex_unlock(&forks[right_fork]);

		// Increment eat counter
		pthread_mutex_lock(&eat_counter_mutex);
		eat_counter[philosopher_id]++;
		pthread_mutex_unlock(&eat_counter_mutex);
	}

	return NULL;
}

int main()
{
	// Initialize mutexes for each fork
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

	// Initialize eat counter mutex
	pthread_mutex_init(&eat_counter_mutex, NULL);

	// Create philosopher threads
	int philosopher_ids[NUM_PHILOSOPHERS];
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		philosopher_ids[i] = i;
		pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
	}

	// Join philosopher threads
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		pthread_join(philosophers[i], NULL);
	}

	// Destroy mutexes
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		pthread_mutex_destroy(&forks[i]);
	}

	// Destroy eat counter mutex
	pthread_mutex_destroy(&eat_counter_mutex);

	cout << "All philosophers are happy and have eaten" << endl;

	return 0;
}

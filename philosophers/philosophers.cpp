#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <ctime>

using namespace std;

#define NUM_PHILOSOPHERS 5
#define NUM_EAT_COUNT 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int eat_counter[NUM_PHILOSOPHERS] = {0};
pthread_mutex_t eat_counter_mutex;
bool philosopher_dead[NUM_PHILOSOPHERS] = {false};
pthread_mutex_t print_mutex;

void print_state(int philosopher_id, const string &state)
{
	auto now = chrono::system_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

	pthread_mutex_lock(&print_mutex);
	cout << elapsed << " Philosopher " << philosopher_id << " " << state << endl;
	pthread_mutex_unlock(&print_mutex);
}

void *philosopher(void *arg)
{
	int philosopher_id = *((int *)arg);
	int left_fork = philosopher_id;
	int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;
	int first_fork = (philosopher_id == NUM_PHILOSOPHERS - 1) ? right_fork : left_fork;
	int second_fork = (philosopher_id == NUM_PHILOSOPHERS - 1) ? left_fork : right_fork;

	for (int i = 0; i < NUM_EAT_COUNT && !philosopher_dead[philosopher_id]; ++i)
	{
		// Thinking
		print_state(philosopher_id, "is thinking");
		sleep(1);

		// Pick up forks
		pthread_mutex_lock(&forks[first_fork]);
		print_state(philosopher_id, "has taken a fork");
		if (pthread_mutex_trylock(&forks[second_fork]) != 0)
		{
			pthread_mutex_unlock(&forks[first_fork]);
			continue; // Try again later if the second fork is not available
		}
		print_state(philosopher_id, "has taken a fork");

		// Eating
		print_state(philosopher_id, "is eating");
		sleep(1);

		// Release forks
		pthread_mutex_unlock(&forks[first_fork]);
		pthread_mutex_unlock(&forks[second_fork]);

		// Increment eat counter
		pthread_mutex_lock(&eat_counter_mutex);
		eat_counter[philosopher_id]++;
		pthread_mutex_unlock(&eat_counter_mutex);
	}

	if (!philosopher_dead[philosopher_id])
	{
		print_state(philosopher_id, "died");
		philosopher_dead[philosopher_id] = true;
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

	// Initialize print mutex
	pthread_mutex_init(&print_mutex, NULL);

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

	// Destroy print mutex
	pthread_mutex_destroy(&print_mutex);

	cout << "All philosophers are happy and have eaten" << endl;

	return 0;
}

#include "PhiloHeader.h"

thread philosopher_creator(pthread_t philosophers)
{
	pthread_create(philosophers, NULL, philosopher_function, philosophers);
}

void philosopher_function(pthread_t philosopher) {
	//this_thread::sleep_for(chrono::seconds(1));
	int id = ((int)arg); // Convertir el argumento a un entero

	cout << "Hola desde el hilo " << id << "!" << endl;

	pthread_exit(NULL); // Terminar el hilo
}

int main(int argc, char **argv)
{
	pthread_t philosopher1;

	// Handle the number of arguments
	if (argc != 5 || argc != 6)
	{
		cerr << RED << "The program does not have the correct number of arguments. Try again." << endl;
		return 0;
	}

	for(int i = 0; i <= argv[1]; i++){
		pthread_t philosopher[i] = new pthread_t;
		philosopher_creator(philosopher[i]);
	}

	return 0;
}
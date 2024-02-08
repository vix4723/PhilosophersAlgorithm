#include "PhiloHeader.h"

thread philosopher_creator(int philosophers)
{
	for (int i = 0; i < philosophers; i++)
	{
		thread* philosopher = new thread;
	}
}

thread philosopher_sleep(thread philosopher) {
	this_thread::sleep_for(chrono::seconds(1));
}

int main(int argc, char **argv)
{
	//Handle the number of arguments
	if (argc != 5 || argc != 6) {
		cerr << RED << "The program does not have the correct number of arguments. Try again." << endl;
		return 0;
	}
	

	//thread thread1(funcion, "hilo 1\n");
	//thread thread2(funcion, "hilo 2\n");
	//thread1.join();
	//thread2.join();
	//si
	//la vix manda
	return 0;
}
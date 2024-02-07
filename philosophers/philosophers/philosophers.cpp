#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

using namespace std;

void funcion(const char *str)
{
	while (1)
	{
		cout << str;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

void funcion2(const int num)
{
	while (1)
	{
		cout << num;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main(int arg, char **argv)
{
	thread thread1(funcion, "hilo 1\n");
	thread thread2(funcion, "hilo 2\n");
	thread1.join();
	thread2.join();
	//la vix manda
	return 0;
}
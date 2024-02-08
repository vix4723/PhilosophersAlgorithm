#include <iostream>
#include <pthread.h>

using namespace std;

// Función que ejecutarán los hilos
void *tarea(void *arg)
{
    int id = *((int *)arg); // Convertir el argumento a un entero

    cout << "Hola desde el hilo " << id << "!" << endl;

    pthread_exit(NULL); // Terminar el hilo
}

int main()
{
    const int num_hilos = 5;
    pthread_t hilos[num_hilos]; // Arreglo para almacenar los identificadores de los hilos

    // Crear los hilos
    for (int i = 0; i < num_hilos; ++i)
    {
        int *arg = new int(i);                               // Argumento para cada hilo (un entero)
        pthread_create(&hilos[i], NULL, tarea, (void *)arg); // Crear el hilo con la función tarea
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < num_hilos; ++i)
    {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo termine su ejecución
    }

    return 0;
}

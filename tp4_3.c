#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ESTRUCTURAS Y NODOS

struct Tarea{
    int tareaId; //Numerado en ciclo iterativo
    char *descripcion; //
    int duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    Nodo *Siguiente;
}typedef Nodo;

// DECLARACION DE FUNCIONES

Nodo *CrearListaVacia(){
    return NULL;
}

// MAIN

int main(){

    Nodo *TareasPendientes, *TareasRealizadas;
    
    
    do
    {
        
    } while ();
    
    return 0;
}

// FUNCIONES


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int tareaId; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; // entre 10 – 100
}typedef Tarea;

void Cargar(Tarea **lista, int cant);
void Realizadas(Tarea **lista, Tarea **realizadas, int cant);
void Mostrar(Tarea **lista, int cant);
void BuscarPalabra(Tarea **lista, int cant);
void BuscarId(Tarea **lista, int cant);

int main(){
    int cantTareas = 0;
    printf("Ingrese cantidad de tareas a cargar:\n");
    scanf("%d",&cantTareas);

    Tarea **tareas_solicitadas, **tareas_realizadas;

    tareas_solicitadas = (Tarea **)malloc(sizeof(Tarea *)* cantTareas);
    tareas_realizadas = (Tarea **)malloc(sizeof(Tarea *)* cantTareas);

    for (int i = 0; i < cantTareas; i++)
    {
        tareas_solicitadas[i] = NULL;
        tareas_realizadas[i] = NULL;
    }

    Cargar(tareas_solicitadas, cantTareas);

    Realizadas(tareas_solicitadas, tareas_realizadas, cantTareas);

    printf("\n*********TAREAS REALIZADAS*********\n");
    Mostrar(tareas_realizadas, cantTareas);

    printf("\n*********TAREAS PENDIENTES*********\n");
    Mostrar(tareas_solicitadas, cantTareas);

    BuscarPalabra(tareas_solicitadas, cantTareas);
    BuscarId(tareas_solicitadas, cantTareas);

    for (int i = 0; i < cantTareas; i++)
    {
        free(tareas_solicitadas[i]);
        free(tareas_realizadas[i]);
    }
    
    free(tareas_solicitadas);
    free(tareas_realizadas);
    return 0;
}

void Cargar(Tarea **lista, int cant){
    int i;
    char desc[100];
    for (i = 0; i < cant; i++)
    {
        srand(time(NULL));
        lista[i] = (Tarea *)malloc(sizeof(Tarea));
        lista[i]->tareaId = (i+1);
        printf("============Tarea: [ %d ]============\n",lista[i]->tareaId);
        printf("Ingrese una descripcion: ");
        fflush(stdin);
        gets(desc);
        fflush(stdin);
        lista[i]->descripcion = (char *)malloc(sizeof(char) * strlen(desc));
        strcpy(lista[i]->descripcion,desc);
        lista[i]->duracion = 10 + rand() % 91;
    }
}

void Realizadas(Tarea **lista, Tarea **realizadas, int cant){
    int opcion, i;
    printf("\n---------LISTADO DE TAREAS---------\n");
    for (i = 0; i < cant; i++)
    {
        printf("============Tarea: [ %d ]============\n",lista[i]->tareaId);
        printf("---Descripcion: %s\n",lista[i]->descripcion);
        printf("---Duracion: %d\n", lista[i]->duracion);

        printf("Se realizo esta Tarea?\n 1- SI , 2- NO\n");
        fflush(stdin);
        scanf("%d",&opcion);

        if (opcion == 1)
        {
            realizadas[i] = lista[i];
            lista[i] = NULL;
        }else {
            realizadas[i] = NULL;
        }
    }
}

void Mostrar(Tarea **lista, int cant){
    int i;
    for (i = 0; i < cant; i++)
    {
        if (lista[i] != NULL)
        {
            printf("============Tarea: [ %d ]============\n",lista[i]->tareaId);
            printf("---Descripcion: %s\n", lista[i]->descripcion);
            printf("---Duracion: %d\n", lista[i]->duracion);
        }
    }
}

void BuscarPalabra(Tarea **lista, int cant){
    int i, seguir = 1;
    char palabraBuscar[20];
    char *busqueda;
    fflush(stdin);
    printf("\nIngrese palabra a buscar:\n");
    gets(palabraBuscar);

    for (i = 0; i < cant; i++)
    {
        if (seguir == 1 && lista[i] != NULL)
        {
            busqueda = strstr(lista[i]->descripcion, palabraBuscar);
            if (busqueda != NULL)
            {   
                printf("\n***BUSQUEDA: %s***\n",palabraBuscar);
                printf("============Tarea: [ %d ]============\n",lista[i]->tareaId);
                printf("---Descripcion: %s\n", lista[i]->descripcion);
                printf("---Duracion: %d\n", lista[i]->duracion);
                seguir = 0;
            }
        }
    }
}

void BuscarId(Tarea **lista, int cant){
    int i, idTarea;
    printf("\nIngrese ID de tarea a buscar: ");
    fflush(stdin);
    scanf("%d",&idTarea);
    idTarea--;

    if (lista[idTarea] == NULL)
    {
        printf("ID de Tarea no existe");
    } else {
        printf("============Tarea: [ %d ]============\n",lista[idTarea]->tareaId);
        printf("---Descripcion: %s\n", lista[idTarea]->descripcion);
        printf("---Duracion: %d\n", lista[idTarea]->duracion);
    }
}
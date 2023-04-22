#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cont = 0;

// ESTRUCTURAS

struct Tarea
{
    int tareaId;       // Numerado en ciclo iterativo
    char *descripcion; //
    int duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
}typedef Nodo;

// DECLARACION DE FUNCIONES

Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
void InsertarNodo(Nodo **Start, Tarea tarea);
Nodo *EliminarNodo(Nodo **Start, int id);

Tarea Cargar();
void Mostrar(Nodo *tareas);
void ControlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas);
void Mover(Nodo **tareasPendientes, Nodo **tareasRealizadas, int id);
void LiberarMemoria(Nodo *tarea);
Nodo *BuscarId(Nodo *tareasPendientes, Nodo *tareasRealizadas, int idBuscado);
Nodo *BuscarPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *palabraClave);
void MostrarBusqueda(Nodo *Start);

// MAIN

int main(){
    char *palabraClave = (char *)malloc(sizeof(char) * 100);
    int idBuscado, menu;

    Nodo *tareasPendientes, *tareasRealizadas;
    Nodo *busquedaId;
    Nodo *busquedaPalabra;
    tareasPendientes = CrearListaVacia();
    tareasRealizadas = CrearListaVacia();

    do
    {
        printf("\n\t\t================MENU================\n");
        printf("\t\t1 - Cargar tareas.\n");
        printf("\t\t2 - Controlar tareas.\n");
        printf("\t\t3 - Mostrar tareas pendientes y realizadas.\n");
        printf("\t\t4 - Buscar tareas por ID.\n");
        printf("\t\t5 - Buscar tareas por palabra clave.\n");
        printf("\t\t6 - Salir.\n");
        printf("\t\t====================================\n");
        printf("Elija una opcion: ");
        fflush(stdin);
        scanf("%d",&menu);
        fflush(stdin);
        printf("\n====================================\n");
        
        switch (menu)
        {
        case 1:
            do
            {
                Tarea tarea = Cargar();
                InsertarNodo(&tareasPendientes, tarea);
                printf("\nDesea agregar otra tarea?\n1 - SI , 2 - NO\n");
                fflush(stdin);
                scanf("%d",&menu);
                fflush(stdin);
            } while (menu == 1);
            break;
        case 2:
            ControlarTareas(&tareasPendientes, &tareasRealizadas);
            break;
        case 3:
            printf("\n*********TAREAS REALIZADAS*********\n");
            Mostrar(tareasRealizadas);
            printf("\n*********TAREAS PENDIENTES*********\n");
            Mostrar(tareasPendientes);
            break;
        case 4:
            printf("Ingrese ID buscado: ");
            fflush(stdin);
            scanf("%d",&idBuscado);
            fflush(stdin);
            busquedaId = BuscarId(tareasPendientes, tareasRealizadas, idBuscado);
            MostrarBusqueda(busquedaId);
            break;
        case 5:
            printf("Ingrese palabra a buscar: ");
            fflush(stdin);
            gets(palabraClave);
            fflush(stdin);
            busquedaPalabra = BuscarPalabra(tareasPendientes, tareasRealizadas, palabraClave);
            MostrarBusqueda(busquedaPalabra);
            free(palabraClave);
            break;
        default:
            break;
        }
    } while (menu != 6);
    printf("Saliendo....\n");
    LiberarMemoria(tareasPendientes);
    LiberarMemoria(tareasRealizadas);
    return 0;
}

// FUNCIONES

Nodo *CrearListaVacia(){
    return NULL;
}

Nodo *CrearNodo(Tarea tarea){
    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo->T = tarea;
    NuevoNodo->siguiente = NULL;
    return NuevoNodo;
}

void InsertarNodo(Nodo **Start, Tarea tarea){  //inserta un nodo al comienzo
    Nodo *NuevoNodo = CrearNodo(tarea);
    NuevoNodo->siguiente = *Start;
    *Start = NuevoNodo;
}

Tarea Cargar(){
    srand(time(NULL));
    Tarea tarea;
    char *Buff;
    tarea.tareaId = cont;
    Buff = (char *)malloc(sizeof(char) * 100);
    printf("============Tarea: [ %d ]============\n",tarea.tareaId);
    printf("Ingrese una descripcion: ");
    fflush(stdin);
    gets(Buff);
    fflush(stdin);
    tarea.descripcion = (char *)malloc(sizeof(char) * (strlen(Buff)+1));
    strcpy(tarea.descripcion, Buff);
    tarea.duracion = 10 + rand() % 91;
    cont++;
    free(Buff);
    return tarea;
}

void Mostrar(Nodo *tareas){
    Nodo *auxTareas = tareas;
    int vacio = 0;
    while (auxTareas != NULL)
    {
        printf("===Tarea: [ %d ]===\n",auxTareas->T.tareaId);
        printf("---Descripcion: %s\n", auxTareas->T.descripcion);
        printf("---Duracion: %d\n", auxTareas->T.duracion);
        auxTareas = auxTareas->siguiente;
        vacio++;
    }
    if (vacio == 0)
    {
        printf("Lista Vacia.\n");
    }
    
}

void ControlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas){
    int id, opcion;

    Nodo *auxPendientes = *tareasPendientes;
    Nodo *auxRealizadas = *tareasRealizadas;

    printf("\n*********TAREAS PENDIENTES*********\n");
    Mostrar(*tareasPendientes);
    printf("\nIndique ID de tarea a controlar: ");
    fflush(stdin);
    scanf("%d",&id);
    fflush(stdin);
    printf("Se realizo esta tarea?\n 1 - SI , 2 - NO\n");
    scanf("%d",&opcion);
    fflush(stdin);

    if (opcion == 1)
    {
        Mover(tareasPendientes, tareasRealizadas, id);
    }
}

Nodo *EliminarNodo(Nodo **Start, int id){
    Nodo *aux = *Start;
    Nodo *auxAnterior = *Start;
    while (aux && aux->T.tareaId != id)
    {
        auxAnterior = aux;
        aux = aux->siguiente;
    }
    if (aux)
    {   
        if (*Start == aux)
        {
            *Start = aux->siguiente;
        }else{
            auxAnterior->siguiente = aux->siguiente;
        }
        aux->siguiente = NULL;
    }
    return aux;
}

void Mover(Nodo **tareasPendientes, Nodo **tareasRealizadas, int id){
    Nodo *aux = EliminarNodo(tareasPendientes, id);
    InsertarNodo(tareasRealizadas, aux->T);

    printf("Mover Exitoso!\n");
}

void LiberarMemoria(Nodo *tarea){
    Nodo *aux = tarea;
    Nodo *auxAnterior = tarea;
    Nodo *auxActual = tarea;
    while (aux)
    {
        if (aux->T.descripcion)
        {
            free(aux->T.descripcion);
        }
        aux = aux->siguiente;
    }
    
    while (auxActual)
    {
        auxAnterior = auxActual;
        auxActual = auxActual->siguiente;
        free(auxAnterior);
    }
}

Nodo *BuscarId(Nodo *tareasPendientes, Nodo *tareasRealizadas, int idBuscado){
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;
    
    while (auxPendientes)
    {
        if (idBuscado == auxPendientes->T.tareaId)
        {
            return auxPendientes;
        }
        auxPendientes = auxPendientes->siguiente;
    }
    while (auxRealizadas)
    {
        if (idBuscado == auxRealizadas->T.tareaId)
        {
            return auxRealizadas;
        }
        auxRealizadas = auxRealizadas->siguiente;
    }
    return NULL;
}

Nodo *BuscarPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *palabraClave){
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;

    while (auxPendientes)
    {
        if (strstr(auxPendientes->T.descripcion, palabraClave))
        {
            return auxPendientes;
        }
        auxPendientes = auxPendientes->siguiente;
    }
    while (auxRealizadas)
    {
        if (strstr(auxRealizadas->T.descripcion, palabraClave))
        {
            return auxRealizadas;
        }
        auxRealizadas = auxRealizadas->siguiente;
    }
    return NULL;
}

void MostrarBusqueda(Nodo *Start){
    if (Start)
    {
        printf("===Tarea: [ %d ]===\n",Start->T.tareaId);
        printf("---Descripcion: %s\n",Start->T.descripcion);
        printf("---Duracion: %d\n", Start->T.duracion);
    }else{
        printf("No Existe la tarea, Palabra clave o ID no encontrado\n");
    }
}
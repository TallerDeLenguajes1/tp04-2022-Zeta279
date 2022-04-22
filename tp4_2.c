#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructuras
struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

// Declaración de funciones
void mostrarTarea(Tarea* t);
Tarea* busquedaPorPalabra(Tarea** listaTareas, char *palabra, int cantidad);
Tarea* busquedaPorId(Tarea** listaTareas, int ID, int cantidad);

// Función principal
int main(){
    int cantidadTareas, ID;
    char aux[100];
    char tareaRealizada;
    Tarea **listaTareas, **tareasRealizadas, *t;

    // Ingreso y control de la cantidad de tareas
    printf("Ingresar la cantidad de tareas: ");
    scanf("%d", &cantidadTareas);

    if(cantidadTareas <= 0){
        printf("Ingresar una cantidad valida de tareas: ");
        scanf("%d", &cantidadTareas);
    }

    // Listas de punteros de tipo Tarea
    listaTareas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);
    tareasRealizadas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);

    srand(time(NULL));

    // Ingreso de las tareas
    for(int i = 0; i < cantidadTareas; i++){
        listaTareas[i] = (Tarea*) malloc(sizeof(struct Tarea));
        tareasRealizadas[i] = NULL;
        listaTareas[i]->TareaID = i + 1;

        printf("Descripcion de la tarea %d: ", i + 1);
        fflush(stdin);
        gets(aux);

        listaTareas[i]->Descripcion = malloc(strlen(aux) + 1);
        strcpy(listaTareas[i]->Descripcion, aux);

        listaTareas[i]->Duracion = 10 + rand() % 91;
    }

    // Mostrar las tareas, y comprobar si se realizaron
    for(int i = 0; i < cantidadTareas; i++){
        printf("\nTarea %d:\n", i + 1);
        mostrarTarea(listaTareas[i]);

        printf("Se realizo la tarea? (S: Si / N: No): ");
        fflush(stdin);
        tareaRealizada = getchar();

        while(tareaRealizada != 'S' && tareaRealizada != 'N'
        && tareaRealizada != 's' && tareaRealizada != 'n'){
            printf("Ingresar una opcion valida (S: Si / N: No): ");
            fflush(stdin);
            tareaRealizada = getchar();
        }

        if(tareaRealizada == 'S' || tareaRealizada == 's'){
            tareasRealizadas[i] = listaTareas[i];
            listaTareas[i] = NULL;
        }
    }

    // Mostrar las tareas realizadas
    printf("\nTareas realizadas:");
    for(int i = 0; i < cantidadTareas; i++){
        if(tareasRealizadas[i] == NULL) continue;

        printf("\n");
        mostrarTarea(tareasRealizadas[i]);
    }

    // Mostrar las tareas pendientes
    printf("\nTareas pendientes:");
    for(int i = 0; i < cantidadTareas; i++){
        if(listaTareas[i] == NULL) continue;

        printf("\n");
        mostrarTarea(listaTareas[i]);
    }

    // Buscar la tarea por descripción
    printf("\nIngresar palabra clave: ");
    fflush(stdin);
    gets(aux);

    t = busquedaPorPalabra(listaTareas, aux, cantidadTareas);
    if(t != NULL) mostrarTarea(t);
    t = busquedaPorPalabra(tareasRealizadas, aux, cantidadTareas);
    if(t != NULL) mostrarTarea(t);

    // Buscar tarea por ID
    printf("\nIngresar ID para buscar tarea: ");
    scanf("%d", &ID);

    t = busquedaPorId(listaTareas, ID, cantidadTareas);
    if(t != NULL) mostrarTarea(t);
    t = busquedaPorId(tareasRealizadas, ID, cantidadTareas);
    if(t != NULL) mostrarTarea(t);

    return 0;
}

// Definición de funciones
void mostrarTarea(Tarea* t){
    printf("ID: %d\n", t->TareaID);
    printf("Descripcion: %s\n", t->Descripcion);
    printf("Duracion: %d\n", t->Duracion);
}

Tarea* busquedaPorPalabra(Tarea** listaTareas, char *palabra, int cantidad){
    for(int i = 0; i < cantidad; i++){
        if(listaTareas[i] != NULL && strcmp(palabra, listaTareas[i]->Descripcion) == 0) return listaTareas[i];
    }
    return NULL;
}

Tarea* busquedaPorId(Tarea** listaTareas, int ID, int cantidad){
    for(int i = 0; i < cantidad; i++){
        if(listaTareas[i] != NULL && ID == listaTareas[i]->TareaID) return listaTareas[i];
    }
    
    return NULL;
}
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
Tarea* buscarTarea(Tarea** listaTareas, int ID, int cantidad);
void mostrarTarea(Tarea* t);

// Función principal
int main(){
    int cantidadTareas, ID;
    char aux[100];
    char tareaRealizada;
    Tarea **listaTareas, **tareasRealizadas;

    // Ingreso y control de la cantidad de tareas
    printf("Ingresar la cantidad de tareas: ");
    scanf("%d", &cantidadTareas);

    if(cantidadTareas <= 0){
        printf("Ingresar una cantidad valida de tareas: ");
        scanf("%d", &cantidadTareas);
    }

    // Arrays de punteros de tipo Tarea
    listaTareas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);
    tareasRealizadas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);

    srand(time(NULL));

    // Ingreso de tareas
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
    printf("Tareas realizadas:\n");
    for(int i = 0; i < cantidadTareas; i++){
        if(tareasRealizadas[i] == NULL) continue;

        printf("\n");
        mostrarTarea(tareasRealizadas[i]);
    }

    // Mostrar las tareas pendientes
    printf("\nTareas pendientes:\n");
    for(int i = 0; i < cantidadTareas; i++){
        if(listaTareas[i] == NULL) continue;

        printf("\n");
        mostrarTarea(listaTareas[i]);
    }

    // Buscar tarea por ID
    printf("Ingresar ID para buscar tarea: ");
    scanf("%d", &ID);

    mostrarTarea(buscarTarea(listaTareas, ID, cantidadTareas));

    return 0;
}

// Definición de funciones
void mostrarTarea(Tarea* t){
    printf("ID: %d\n", t->TareaID);
    printf("Descripcion: %s\n", t->Descripcion);
    printf("Duracion: %d\n", t->Duracion);
}

Tarea* buscarTarea(Tarea** listaTareas, int ID, int cantidad){
    for(int i = 0; i < cantidad; i++){
        if(ID == listaTareas[i]->TareaID) return listaTareas[i];
    }
    
    return NULL;
}
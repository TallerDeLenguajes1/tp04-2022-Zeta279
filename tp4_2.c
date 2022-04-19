#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

int main(){
    int cantidadTareas;
    char aux[100];
    char tareaRealizada;
    Tarea **listaTareas, **tareasRealizadas;

    printf("Ingresar la cantidad de tareas: ");
    scanf("%d", &cantidadTareas);

    if(cantidadTareas <= 0){
        printf("Ingresar una cantidad valida de tareas: ");
        scanf("%d", &cantidadTareas);
    }

    listaTareas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);
    tareasRealizadas = (Tarea**) malloc(sizeof(struct Tarea*) * cantidadTareas);

    srand(time(NULL));

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

    for(int i = 0; i < cantidadTareas; i++){
        printf("\nTarea %d:\n", i + 1);
        printf("ID: %d\n", listaTareas[i]->TareaID);
        printf("Descripcion: %s\n", listaTareas[i]->Descripcion);
        printf("Duracion: %d\n", listaTareas[i]->Duracion);

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

    printf("Tareas realizadas:\n");
    for(int i = 0; i < cantidadTareas; i++){
        if(tareasRealizadas[i] == NULL) continue;

        printf("\nID: %d\n", tareasRealizadas[i]->TareaID);
        printf("Descripcion: %s\n", tareasRealizadas[i]->Descripcion);
        printf("Duracion: %d\n", tareasRealizadas[i]->Duracion);
    }

    printf("\nTareas pendientes:\n");
    for(int i = 0; i < cantidadTareas; i++){
        if(listaTareas[i] == NULL) continue;

        printf("\nID: %d\n", listaTareas[i]->TareaID);
        printf("Descripcion: %s\n", listaTareas[i]->Descripcion);
        printf("Duracion: %d\n", listaTareas[i]->Duracion);
    }

    return 0;
}
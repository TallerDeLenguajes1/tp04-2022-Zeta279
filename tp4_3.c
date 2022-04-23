#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructuras
struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *siguiente;
}typedef Nodo;

// Declaración de funciones
Nodo* insertar(Nodo* head, Tarea T);
Nodo* borrarPrimerNodo(Nodo* head);
Nodo* borrarNodo(Nodo* head, int ID);
void mostrarTotales(Nodo* head);
void mostrarTarea(Tarea t);
Nodo* busquedaPorId(Nodo* head, int ID);
Nodo* busquedaPorPalabra(Nodo* head, char *palabra);

// Función principal
int main(){
    int cantidad;
    char aux[100];
    char tareaRealizada;
    int ID;
    Tarea nuevaTarea;
    Nodo *tareasPendientes, *tareasRealizadas, *nodoAux;

    tareasPendientes = NULL;
    tareasRealizadas = NULL;

    // Ingreso de la cantidad de tareas
    printf("Ingresar la cantidad de tareas: ");
    scanf("%d", &cantidad);

    while(cantidad <= 0){
        printf("Ingresar una cantidad valida de tareas: ");
        scanf("%d", &cantidad);
    }

    srand(time(NULL));

    // Ingreso de las tareas
    for(int i = 0; i < cantidad; i++){
        nuevaTarea.TareaID = i + 1;

        printf("Tarea %d - Ingresar descripcion: ", i + 1);
        fflush(stdin);
        gets(aux);
        nuevaTarea.Descripcion = (char*) malloc(strlen(aux) + 1);
        strcpy(nuevaTarea.Descripcion, aux);

        nuevaTarea.Duracion = 10 + rand() % 91;

        tareasPendientes = insertar(tareasPendientes, nuevaTarea);
    }

    // Comprobar tareas realizadas y no realizadas
    nodoAux = tareasPendientes;
    for(int i = 0; i < cantidad; i++){
        printf("Tarea %d\n", cantidad - i);
        mostrarTarea(nodoAux->T);

        printf("Se realizo la tarea? (S: Si / N: No): ");
        fflush(stdin);
        tareaRealizada = getchar();

        while(tareaRealizada != 'S' && tareaRealizada != 'N'
        && tareaRealizada != 's' && tareaRealizada != 'n'){
            printf("Ingresar una opcion valida (S: Si / N: No): ");
            fflush(stdin);
            tareaRealizada = getchar();
        }

        printf("\n");

        if(tareaRealizada == 'S' || tareaRealizada == 's'){
            tareasRealizadas = insertar(tareasRealizadas, nodoAux->T);
            nodoAux = nodoAux->siguiente;
            tareasPendientes = borrarNodo(tareasPendientes, cantidad - i);
        }
        else{
            nodoAux = nodoAux->siguiente;
        }
        
    }

    // Mostrar tareas realizadas y tareas pendientes
    printf("Tareas pendientes:\n");
    nodoAux = tareasPendientes;
    while(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
        printf("\n");
        nodoAux = nodoAux->siguiente;
    }

    printf("Tareas realizadas:\n");
    nodoAux = tareasRealizadas;
    while(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
        printf("\n");
        nodoAux = nodoAux->siguiente;
    }

    // Busqueda por ID y por palabra clave
    printf("Ingrese un ID para buscar la tarea: ");
    scanf("%d", &ID);

    printf("\nEn tareas pendientes: \n");
    nodoAux = busquedaPorId(tareasPendientes, ID);
    if(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
    }
    else{
        printf("No se encontraron tareas con el ID %d\n", ID);
    }

    printf("\nEn tareas realizadas: \n");
    nodoAux = busquedaPorId(tareasRealizadas, ID);
    if(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
    }
    else{
        printf("No se encontraron tareas con el ID %d\n\n", ID);
    }

    printf("\nIngrese una palabra para buscar la tarea: ");
    fflush(stdin);
    gets(aux);

    nodoAux = busquedaPorPalabra(tareasPendientes, aux);
    printf("\nEn tareas pendientes: \n");
    if(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
    }
    else{
        printf("No se encontraron tareas con la descripcion %s\n\n", aux);
    }

    nodoAux = busquedaPorPalabra(tareasRealizadas, aux);
    printf("\nEn tareas realizadas: \n");
    if(nodoAux != NULL){
        mostrarTarea(nodoAux->T);
    }
    else{
        printf("No se encontraron tareas con la descripcion %s\n\n", aux);
    }

    // Liberar memoria
    while(tareasPendientes != NULL){
        tareasPendientes = borrarPrimerNodo(tareasPendientes);
    }

    while(tareasRealizadas != NULL){
        tareasRealizadas = borrarPrimerNodo(tareasRealizadas);
    }

    return 0;
}

// Definición de funciones
Nodo* insertar(Nodo* head, Tarea T){
    Nodo* nuevoNodo;

    nuevoNodo = (Nodo*) malloc(sizeof(struct Nodo));
    nuevoNodo->T = T;
    nuevoNodo->siguiente = head;

    return nuevoNodo;
}

Nodo* borrarPrimerNodo(Nodo* head){
    Nodo* aux;

    aux = head;
    head = head->siguiente;
    free(aux);

    return head;
}

Nodo* borrarNodo(Nodo* head, int ID){
    Nodo *aux, *auxBorrar;

    if(head == NULL) return head;

    aux = head;

    if(head->T.TareaID == ID){
        head = head->siguiente;
        free(aux);
    }
    else{
        while(aux->siguiente != NULL){
            if(aux->siguiente->T.TareaID == ID){
                auxBorrar = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente;
                free(auxBorrar);
                break;
            }

            aux = aux->siguiente;
        }
    }

    return head;
}

void mostrarTotales(Nodo* head){
    while(head != NULL){
        printf("ID: %d\n", head->T.TareaID);
        printf("Descripcion: %s\n", head->T.Descripcion);
        printf("Duracion: %d\n\n", head->T.Duracion);

        head = head->siguiente;
    }
}

void mostrarTarea(Tarea t){
    printf("ID: %d\n", t.TareaID);
    printf("Descripcion: %s\n", t.Descripcion);
    printf("Duracion: %d\n", t.Duracion);
}

Nodo* busquedaPorId(Nodo* head, int ID){
    while(head != NULL){
        if(head->T.TareaID == ID) return head;
        head = head->siguiente;
    }
}

Nodo* busquedaPorPalabra(Nodo* head, char *palabra){
    while(head != NULL){
        if(strcmp(head->T.Descripcion, palabra) == 0) return head;
        head = head->siguiente;
    }
}
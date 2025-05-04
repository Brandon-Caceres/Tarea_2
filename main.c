#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "extra.h"
#include "hashmap.h"

typedef struct
{
    char id[200000];
    List* artistas;
    char album_name[200];
    char track_name[200];
    float tempo;
    char track_genere[200];
}datos_cancion;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Base de Datos de Canciones");
    puts("========================================");
  
    puts("1) Cargar Canciones");
    puts("2) Buscar por genero");
    puts("3) Buscar por artista");
    puts("4) Buscar por tempo");
    puts("5) Salir");
  }

void cargar_canciones(HashMap *map_id, HashMap *map_genere){
    FILE  * archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL){
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');
    long contador = 1;

    while((campos = leer_linea_csv(archivo, ',')) != NULL){
        datos_cancion *cancion = (datos_cancion *)malloc(sizeof(datos_cancion));
        strcpy(cancion->id, campos[0]);
        cancion->artistas = split_string(campos[2], ";");
        strcpy(cancion->album_name, campos[3]);
        strcpy(cancion->track_name, campos[4]);
        cancion->tempo = atof(campos[18]);
        strcpy(cancion->track_genere, campos[20]);
        
        insertMap(map_id, cancion->id, cancion);

        Pair *par = searchMap(map_genere, cancion->track_genere);
        if (par == NULL){
            List * lista = list_create();
            list_pushBack(lista, cancion);
            insertMap(map_genere, cancion->track_genere, lista);
        }
        else{
            List *lista = par->value;
            list_pushBack(lista, cancion);
        }
        printf("Procesando cancion %d.\n", contador);
        contador++;
    }

    fclose(archivo);
    printf("Canciones cargadas con exito. \n");
}


int main(){
    char opcion;

    HashMap * map_id = createMap(50000);
    HashMap * map_genere = createMap(50000);

    do{
        mostrarMenuPrincipal();
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
            cargar_canciones(map_id, map_genere);
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            puts("Saliendo de Spotifind...");
            break;
        default:
            puts("Opcion no valida. Intente de nuevo.");
            break;
        }
        presioneTeclaParaContinuar();
    }while(opcion != '6');

    return 0;
}
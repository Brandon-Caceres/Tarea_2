#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "extra.h"
#include "hashmap.h"

typedef struct
{
    char id[100];
    List* artistas;
    char album_name[100];
    char track_name[100];
    float tempo;
    List* track_genere;
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

void cargar_canciones(HashMap *map_genere, HashMap *map_artist){
    FILE  * archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL){
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');
    long contador = 0;

    while((campos = leer_linea_csv(archivo, ',')) != NULL){
        datos_cancion *cancion = (datos_cancion *)malloc(sizeof(datos_cancion));
        strcpy(cancion->id, campos[0]);
        cancion->artistas = split_string(campos[2], ";");
        strcpy(cancion->album_name, campos[3]);
        strcpy(cancion->track_name, campos[4]);
        cancion->tempo = atof(campos[18]);
        cancion->track_genere = split_string(campos[20], ";");

        List *generos = cancion->track_genere;
        char *genero = list_first(generos);
        while (genero != NULL){
            Pair *par = searchMap(map_genere, genero);
            if (par == NULL){
                List * lista = list_create();
                list_pushBack(lista, cancion);
                insertMap(map_genere, genero, lista);
            }
            else{
                List *lista = par->value;
                list_pushBack(lista, cancion);
            }
            genero = list_next(generos);
        }
        
        List *artistas = cancion->artistas;
        char *artista = list_first(artistas);
        while (artista != NULL){
            Pair *par_ar = searchMap(map_artist, artista);
            if (par_ar == NULL){
                List * lista_ar = list_create();
                list_pushBack(lista_ar, cancion);
                insertMap(map_artist, artista, lista_ar);
            }
            else{
                List * lista_ar = par_ar->value;
                list_pushBack(lista_ar, cancion);
            }
            artista = list_next(artistas);
        }
        printf("Procesando cancion %d.\n", contador);
        contador++;
    }

    fclose(archivo);
    printf("Canciones cargadas con exito. \n");
}

char* lista_string(List *lista){
    if (lista == NULL) return NULL;
    
    char* resultado = (char*)malloc(sizeof(char));
    resultado[0] = '\0';
    
    char* aux = list_first(lista);
    while (aux != NULL){
        strcat(resultado, aux);
        aux = list_next(lista);
        if (aux != NULL)
            strcat(resultado, ", ");
    }
    return resultado;
}

void buscar_genero(HashMap *map_genere){
    char genero[100];
    getchar();
    printf("Ingrese el genero de la cancion: ");
    scanf("%[^\n]s", genero);
    getchar();

    Pair * par = searchMap(map_genere, genero);

    if (par != NULL){
        List *canciones = par->value;
        datos_cancion * cancion = list_first(canciones);

        while (cancion != NULL){
            char * artista_str = lista_string(cancion->artistas);
            char * genero_str = lista_string(cancion->track_genere);

            printf("ID: %s, Nombre de la cancion: %s, Artista/as: %s, Album: %s, Genero: %s, Tempo: %.2f\n",
                   cancion->id, cancion->track_name, artista_str, cancion->album_name, genero_str, cancion->tempo);
            cancion = list_next(canciones);
        }
    } 
    else {
        printf("No se encontraron canciones con el genero '%s'.\n", genero);
    }
}

void buscar_artista(HashMap *map_artist){
    char artista[100];
    getchar();
    printf("Ingrese el artista de la cancion: ");
    scanf("%[^\n]s", artista);
    getchar();

    Pair * par = searchMap(map_artist, artista);

    if (par != NULL){
        List * canciones = par->value;
        datos_cancion * cancion = list_first(canciones);

        while (cancion != NULL){
            char * artista_str = lista_string(cancion->artistas);
            char * genero_str = lista_string(cancion->track_genere);

            printf("ID: %s, Nombre de la cancion: %s, Artista/as: %s, Album: %s, Genero: %s, Tempo: %.2f\n",
                cancion->id, cancion->track_name, artista_str, cancion->album_name, genero_str, cancion->tempo);
            cancion = list_next(canciones);
        }
    }
    else{
        printf("No se encontraron canciones con el artista '%s'.\n", artista);
    }
}

int main(){
    char opcion;

    HashMap * map_genere = createMap(50000);
    HashMap * map_artist = createMap(50000);

    do{
        mostrarMenuPrincipal();
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
            cargar_canciones(map_genere, map_artist);
            break;
        case '2':
            buscar_genero(map_genere);
            break;
        case '3':
            buscar_artista(map_artist);
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
    }while(opcion != '5');

    return 0;
}
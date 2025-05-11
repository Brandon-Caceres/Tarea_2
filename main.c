#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "extra.h"
#include "hashmap.h"

//Se define la estructura de los datos que se guardan por cada cancion
typedef struct
{
    char id[100];
    List* artistas;
    char album_name[300];
    char track_name[300];
    float tempo;
    List* track_genere;
}datos_cancion;

//Funcion para mostrar el menu principal y limpiar la panttalla
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

/*Funcion que se encarga de cargar las canciones que se encuentran en el archivo csv y 
las organiza en mapas y listas para poder utilizarlas en distintas operaciones, esto lo 
hace leyendo cada linea del csv, por cada una de estas se acceden a los campos necesarios,
y los añade a su mapa o lista correspondiente */
void cargar_canciones(HashMap *map_genere, HashMap *map_artist, List * lista_lentas, List * lista_moderadas, List * lista_rapidas){
    FILE  * archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL){
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');

    //Lee linea por linea el archivo csv
    while((campos = leer_linea_csv(archivo, ',')) != NULL){
        datos_cancion *cancion = (datos_cancion *)malloc(sizeof(datos_cancion));
        strncpy(cancion->id, campos[0], sizeof(cancion->id));
        cancion->artistas = split_string(campos[2], ";");
        strncpy(cancion->album_name, campos[3], sizeof(cancion->album_name));
        strncpy(cancion->track_name, campos[4], sizeof(cancion->track_name));
        cancion->tempo = atof(campos[18]);
        cancion->track_genere = split_string(campos[20], ";");

        //Se agregan los datos al mapa de generos
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
        
        //Se agregan los datos al mapa de artistas
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

        //Clasifica la cancion segun su tempo
        if (cancion->tempo < 80){
            list_pushBack(lista_lentas, cancion);
        }
        else if (cancion->tempo >= 80 && cancion->tempo <= 120){
            list_pushBack(lista_moderadas, cancion);
        }
        else if (cancion->tempo > 120){
            list_pushBack(lista_rapidas, cancion);
        }
    }

    fclose(archivo);
    printf("Canciones cargadas con exito. \n");
}

//Funcion auxiliar que se encarga de convertir una lista de strings a un solo string separado por comas
char* lista_string(List *lista) {
    if (lista == NULL) return NULL;

    size_t total_len = 1;
    char *aux = list_first(lista);

    // Paso 1: calcular longitud total
    while (aux != NULL) {
        total_len += strlen(aux) + 2;
        aux = list_next(lista);
    }

    char *resultado = (char*)malloc(total_len);
    if (resultado == NULL) return NULL;
    resultado[0] = '\0';

    // Paso 2: concatenar strings
    aux = list_first(lista);
    while (aux != NULL) {
        strcat(resultado, aux);
        aux = list_next(lista);
        if (aux != NULL)
            strcat(resultado, ", ");
    }

    return resultado;
}

/*Funcion que busca y muestra las canciones pertenecientes 
a el genero ingresado por el usuario por el usuario*/
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

            free(artista_str);
            free(genero_str);
        }
    }
    else {
        printf("No se encontraron canciones con el genero '%s'.\n", genero);
    }
}

/*Funcion que busca y muestra las canciones del artista que ingrese el usuario*/
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

            free(artista_str);
            free(genero_str);
        }
    }
    else{
        printf("No se encontraron canciones con el artista '%s'.\n", artista);
    }
}

/*Funcion encargada de buscar canciones por su tempo, esta muestra un submenu 
para seleccionar entre los 3 tipos de tempo existentes(lentas, moderadas, rapidas)
y luego imprime las caqnciones pertenecientes a la categoria seleccionada por el ususario*/
void buscar_tempo(List * lista_lentas, List * lista_moderadas, List * lista_rapidas){
    limpiarPantalla();
    int opcion;

    printf("Buscar canciones por tempo: \n");
    printf("1) Canciones lentas\n");
    printf("2) Canciones moderadas\n");
    printf("3) Canciones rapidas\n");
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);
    getchar();

    List * lista = NULL;

    if (opcion == 1){
        lista = lista_lentas;
    }
    else if (opcion == 2){
        lista = lista_moderadas;
    }
    else if (opcion == 3){
        lista = lista_rapidas;
    }
    else{
        printf("Opcion invalida, intene nuevamente\n");
        return;
    }

    datos_cancion * cancion = list_first(lista);
    while (cancion != NULL){
        char * artista_str = lista_string(cancion->artistas);
        char * genero_str = lista_string(cancion->track_genere);

        printf("ID: %s, Nombre de la cancion: %s, Artista/as: %s, Album: %s, Genero: %s, Tempo: %.2f\n",
            cancion->id, cancion->track_name, artista_str, cancion->album_name, genero_str, cancion->tempo);
        
        free(artista_str);
        free(genero_str);

        cancion = list_next(lista);
    }
}

/*Funcion encargada de liberar la memoria de las listas, recibe la lista
y la recorre eliminando cada lista interna, al final limpia la lista*/
void liberar_lista(List* lista) {
    datos_cancion *cancion = list_first(lista);
    while (cancion != NULL) {
        list_clean(cancion->artistas);
        free(cancion->artistas);

        list_clean(cancion->track_genere);
        free(cancion->track_genere);

        free(cancion);
        cancion = list_next(lista);
    }
    list_clean(lista);
}

/*Funcion que libera toda la memoria utilizada en el programa por los mapas y listas */
void liberar_memoria(HashMap *map_genere, HashMap *map_artist, List *lista_lentas, List *lista_moderadas, List *lista_rapidas) {
    // Primero liberamos las canciones a través de las listas de tempo (única fuente)
    liberar_lista(lista_lentas);
    liberar_lista(lista_moderadas);
    liberar_lista(lista_rapidas);

    Pair *par;
    // Limpiar mapa de géneros
    par = firstMap(map_genere);
    while (par != NULL) {
        list_clean(par->value);
        par = nextMap(map_genere);
    }

    // Limpiar mapa de artistas
    par = firstMap(map_artist);
    while (par != NULL) {
        list_clean(par->value);
        par = nextMap(map_artist);
    }

    // Liberar los mapas
    free(map_genere);
    free(map_artist);
}

/*Funcion principal del programa, en este se crean 2 mapas y 3 listas para usarlas segun se necesite,
se muestra el menu y se le solicita una opcion al usuario, dependiendo de lo que quiera el usuario 
es la funcion a la que se llama, si el usuario abandona el programa se limpian los mapas y las listas*/
int main(){
    char opcion;
    int cargadas = 0;

    HashMap * map_genere = createMap(50000);
    HashMap * map_artist = createMap(50000);
    List * lista_lentas = list_create();
    List * lista_moderadas = list_create();
    List * lista_rapidas = list_create();

    do{
        mostrarMenuPrincipal();
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case '1':
            if(cargadas){
                puts("Las canciones ya han sido cargadas. No es posible volver a cargarlas.");
            }
            else{
                cargar_canciones(map_genere, map_artist, lista_lentas, lista_moderadas, lista_rapidas);
                cargadas = 1;
            }
            break;
        case '2':
            buscar_genero(map_genere);
            break;
        case '3':
            buscar_artista(map_artist);
            break;
        case '4':
            buscar_tempo(lista_lentas, lista_moderadas, lista_rapidas);
            break;
        case '5':
            puts("Saliendo de Spotifind...");
            liberar_memoria(map_genere, map_artist, lista_lentas, lista_moderadas, lista_rapidas);
            break;
        default:
            puts("Opcion no valida. Intente de nuevo.");
            break;
        }
        presioneTeclaParaContinuar();
    }while(opcion != '5');

    return 0;
}
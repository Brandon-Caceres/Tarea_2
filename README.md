# Tarea_2

## Descripción de la Tarea
Spotifind es un sistema de base de datos de canciones que permite buscar y explorar canciones. ya sea, por género, artistas o tempo. Las canciones son cargadas desde un archivo CSV y se organizan internamente a traves de hashmaps y listas para lograr ofrecer una búsqueda eficiente. Esto para poder permitir a losa usuarios encontrar fácilmente las canciones según lo que necesiten.

## Funciones implementadas
1. Carga de canciones desde un archivo CSV.
2. Búsqueda de canciones por género.
3. Búsqueda de canciones por artista.
4. Búsqueda de canciones clasificada por tempo (lento, moderado, rápido).
5. Liberación de memoria usada por las estructuras internas.

## Compilar el código 

1. Tener Visual Studio Code descargado junto con la extensión de C/C++.
2. Descarga y descomprime el archivo ".zip" en una carpeta a eleccion.
3. Abre el proyecto en Visual Studio Code: 
    - Inicia Visual Studio Code. 
    - Selecciona (Archivos > abrir carpeta..) y elige la carpeta en la que descomprimiste el proyecto.
4. Compila el codigo: 
    - Abre el archivo principal (main.c). 
    - Abre la terminal integrada (Ctrl+Mayus+ñ o Terminal > Nueva Terminal). 
    - En la terminal, compila el codigo con el siguiente comando:
```bash
gcc *.c -o main.exe
```

5. finalmente para ejecutar el codigo hace falta escribir el comando 
```bash
./main.exe
```

## Problemas conocidos 
1. No se puede volver a cargar el archivo CSV más de una vez por ejecución (evita duplicados).
2. Posible pérdida de memoria si se cierra abruptamente sin liberar memoria.
3. No hay validación de campos vacíos o malformateados en el CSV.

## Estructura del código
- main.c       # Programa principal
- list.h       # Prototipos de lista enlazada
- list.c       # Implementación de lista enlazada
- hashmap.h    # Prototipos de mapas hash
- hashmap.c    # Implementación de mapas hash
- extra.h      # Prototipos de funciones auxiliares
- extra.c      # Implementación de funbciones auxiliares
- README.md    # Este archivo de texto


### Ejemplo de uso 
1) Cargar Canciones
   > Seleccionar opción: 1
   > "Canciones cargadas con exito"
   
2) Buscar por género
   > Seleccionar opción 2
   > Ingrese género: Pop
   > Se listan canciones del género solicitado.

3) Buscar por artista
   > Seleccionar opción 3
   > Ingrese nombre del artista: Dua Lipa
   > Se listan canciones de ese artista.

4) Buscar por tempo
   > Seleccionar opción 4
   > Elegir entre:

   * 1. Lentas
   * 2. Moderadas
   * 3. Rápidas


## Contribuciones

### [Brandon Cáceres]
- Implementación de lectura CSV y separación de datos.
- Desarrollo de las estructuras de datos: listas y mapas hash.
- Clasificación de canciones por tempo.
- Funcionalidades de búsqueda y visualización.
- Manejo de memoria y liberación estructurada.

## Aspectos a Mejorar
1. Validar formato del CSV al cargar canciones.
2. Permitir guardar canciones nuevas desde la consola.
3. Implementar guardado de playlists personalizadas.
4. Crear menú de ayuda para usuarios nuevos.


# Fin
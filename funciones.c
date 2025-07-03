#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena(char *cadena, int num){
    fflush(stdin); // Limpiar el buffer de entrada
    fgets(cadena, num, stdin); // Leer la cadena desde la entrada estándar
    int len = strlen(cadena) - 1;
    cadena[len] = '\0'; // Eliminar el salto de línea al final
}

int menu(){
    int opc;
    printf("\nMenu de Opciones:\n");
    printf("=====================================\n");
    printf("1. Crear Jugadores\n");
    printf("2. Crear Equipos\n");
    printf("3. Listar Jugadores\n");
    printf("4. Listar Equipos\n");
    printf("5. Crear Partidos\n");
    printf("6. Listar Partidos\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    fflush(stdin); // Limpiar el buffer de entrada
    return opc;
}

void crearJugadores(){
    struct Jugador jugadores[] = {{1,"Juan P","Delantero",0},
                                {2,"Luis A","Defensa",0},
                                {3,"Pedro R","Portero",0},
                                {4,"Cris R","Centrocampista",0},
                                {5,"Leo M","Delantero",0},
                                {6,"Alex A","Defensa",0},
                                {7,"Javi M","Portero",0},
                                {8,"Sergi B","Centrocampista",0},
                                {9,"Andres I","Delantero",0},
                                {10,"David S","Defensa",0},
                                {11,"Carlos G","Portero",0},
                                {12,"Raul C","Centrocampista",0},
                                {13,"Miguel A","Delantero",0},
                                {14,"Jose L","Defensa",0},
                                {15,"Fernando P","Portero",0},
                                {16,"Victor H","Centrocampista",0},
                                {17,"Alvaro T","Delantero",0},
                                {18,"Pablo M","Defensa",0},
                                {19,"Sergio R","Portero",0},
                                {20,"Manuel J","Centrocampista",0},
                                {21,"Jorge D","Delantero",0},
                                {22,"Antonio F","Defensa",0},
                                {23,"Eduardo V","Portero",0},
                                {24,"Hector G","Centrocampista",0},
                                {25,"Raul M","Delantero",0},
                                {26,"Carlos A","Defensa",0},
                                {27,"Luis C","Portero",0},
                                {28,"Sergio T","Centrocampista",0},
                                {29,"David P","Delantero",0},
                                {30,"Juan D","Defensa",0}};
    guardarJugadores(jugadores, 30);
    printf("Jugadores creados y guardados correctamente.\n");
}

void imprimirJugadores(struct Jugador jugadores[], int numJugadores){
    printf("\nLista de Jugadores:\n");
    printf("=====================================\n");
    for (int i = 0; i < numJugadores; i++) {
        printf("ID: %d, Nombre: %s, Posicion: %s\n", 
               jugadores[i].id, jugadores[i].nombre, 
               jugadores[i].posicion);
    }
}

void guardarJugadores(struct Jugador jugadores[], int numJugadores){
    FILE *archivo = fopen("jugadores.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los jugadores.\n");
        return;
    }
    fwrite(jugadores, sizeof(struct Jugador), numJugadores, archivo);
    fclose(archivo);
}

int cargarJugadores(struct Jugador jugadores[], int *numJugadores){
    FILE *archivo = fopen("jugadores.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los jugadores.\n");
        return 0;
    }
    *numJugadores = fread(jugadores, sizeof(struct Jugador), 30, archivo);
    fclose(archivo);
    return 1;
}

void crearEquipos(){
    struct Jugador jugadores[30];
    struct Equipo equipos[8];
    int numJugadores = 0;
    cargarJugadores(jugadores, &numJugadores);

    if (numJugadores < 6) {
        printf("No hay suficientes jugadores para crear equipos.\n");
        return;
    }

    for (int i = 0; i < 8; i++) {
        equipos[i].id = i + 1;
        printf("Ingrese el nombre del equipo %d: ", i + 1);
        leerCadena(equipos[i].nombre, sizeof(equipos[i].nombre));
        printf("Selecciones los jugadores para el equipo %d:\n", i + 1);
        for (int j = 0; j < 6; j++) {
            int jugadorId;
            printf("Jugador %d (ID): ", j + 1);
            scanf("%d", &jugadorId);
            fflush(stdin); // Limpiar el buffer de entrada
            
            // Validar que el ID del jugador sea válido
            if (jugadorId < 1 || jugadorId > numJugadores) {
                printf("ID de jugador invalido. Debe estar entre 1 y %d.\n", numJugadores);
                j--; // Repetir la iteración para este jugador
                continue;
            }
            
            equipos[i].jugadores[j] = jugadores[jugadorId - 1]; // Asignar el jugador al equipo
        }
        printf("Equipo %d creado con exito.\n", i + 1);
    }
    guardarEquipos(equipos, 8);
    printf("Equipos guardados correctamente.\n");

}

void imprimirEquipos(struct Equipo equipos[], int numEquipos){
    printf("\nLista de Equipos:\n");
    printf("=====================================\n");
    for (int i = 0; i < numEquipos; i++) {
        printf("ID: %d, Nombre: %s\n", equipos[i].id, equipos[i].nombre);
        printf("Jugadores:\n");
        for (int j = 0; j < 6; j++) {
            printf("  ID: %d, Nombre: %s, Posicion: %s\n", 
                   equipos[i].jugadores[j].id, 
                   equipos[i].jugadores[j].nombre, 
                   equipos[i].jugadores[j].posicion);
        }
        printf("-------------------------------------\n");
    }
    if (numEquipos == 0) {
        printf("No hay equipos registrados.\n");
    }
}

void guardarEquipos(struct Equipo equipos[], int numEquipos){
    FILE *archivo = fopen("equipos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los equipos.\n");
        return;
    }
    fwrite(equipos, sizeof(struct Equipo), numEquipos, archivo);
    fclose(archivo);
}

int leerEquipos(struct Equipo equipos[], int *numEquipos){
    FILE *archivo = fopen("equipos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los equipos.\n");
        return 0;
    }
    *numEquipos = fread(equipos, sizeof(struct Equipo), 8, archivo);
    fclose(archivo);
    return 1;
}

void crearPartidos(){
    int numEquipos = 0;
    struct Equipo equipos[8];
    struct Partido partidos[4];
    leerEquipos(equipos, &numEquipos);
    int indexEquipo1, indexEquipo2;
    
    if (numEquipos < 2) {
        printf("No hay suficientes equipos para crear partidos.\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        partidos[i].id = i + 1;
        printf("Partido %d:\n", i + 1);
        imprimirEquipos(equipos, numEquipos);
        printf("Seleccione el equipo 1 (ID): ");
        scanf("%d", &indexEquipo1);
        partidos[i].equipo1 = equipos[indexEquipo1 - 1]; // Asignar el equipo 1
        printf("Ingrese los goles del equipo 1: ");
        scanf("%d", &partidos[i].golesEquipo1);
        fflush(stdin); // Limpiar el buffer de entrada
        printf("Seleccione el equipo 2 (ID): ");
        scanf("%d", &indexEquipo2);
        partidos[i].equipo2 = equipos[indexEquipo2 - 1]; // Asignar el equipo 2
        printf("Ingrese los goles del equipo 2: ");
        scanf("%d", &partidos[i].golesEquipo2);
        fflush(stdin); // Limpiar el buffer de entrada

    }
    guardarPartidos(partidos, 4);
    printf("Partidos creados y guardados correctamente.\n");
     
}

void imprimirPartidos(struct Partido partidos[], int numPartidos){
    printf("\nLista de Partidos:\n");
    printf("=====================================\n");
    for (int i = 0; i < numPartidos; i++) {
        printf("ID: %d\n", partidos[i].id);
        printf("Equipo 1: %s (Goles: %d)\n", partidos[i].equipo1.nombre, partidos[i].golesEquipo1);
        printf("Equipo 2: %s (Goles: %d)\n", partidos[i].equipo2.nombre, partidos[i].golesEquipo2);
        printf("-------------------------------------\n");
    }
    if (numPartidos == 0) {
        printf("No hay partidos registrados.\n");
    }
}

void guardarPartidos(struct Partido partidos[], int numPartidos){
    FILE *archivo = fopen("partidos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los partidos.\n");
        return;
    }
    fwrite(partidos, sizeof(struct Partido), numPartidos, archivo);
    fclose(archivo);
}

int leerPartidos(struct Partido partidos[], int *numPartidos){
    FILE *archivo = fopen("partidos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los partidos.\n");
        return 0;
    }
    *numPartidos = fread(partidos, sizeof(struct Partido), 4, archivo);
    fclose(archivo);
    return 1;
}

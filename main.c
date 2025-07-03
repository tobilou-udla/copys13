#include <stdio.h>
#include "funciones.h"

int main() {

    struct Jugador jugadores[30];
    struct Equipo equipos[8];
    struct Partido partidos[4];
    int numJugadores = 0;
    int numEquipos = 0;
    int numPartidos = 0;

    int opc;
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1:
                crearJugadores();
                printf("Jugadores creados correctamente.\n");
                break;
            case 2:
                crearEquipos();
                printf("Equipos creados correctamente.\n");
                break;
            case 3:
                if(cargarJugadores(jugadores, &numJugadores)) {
                    imprimirJugadores(jugadores, numJugadores);
                } else {
                    printf("No se pudieron cargar los jugadores.\n");
                }
                break;
            case 4:
                if(leerEquipos(equipos, &numEquipos)) {
                    imprimirEquipos(equipos, numEquipos);
                } else {
                    printf("No se pudieron cargar los equipos.\n");
                }
                break;
            case 5:
                crearPartidos();
                printf("Partidos creados correctamente.\n");
                break;
            case 6:
                if(leerPartidos(partidos, &numPartidos)) {
                    imprimirPartidos(partidos, numPartidos);
                } else {
                    printf("No se pudieron cargar los partidos.\n");
                }
                break;
            case 7:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc!= 7);
    
    
    return 0;
}

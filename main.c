#include <stdio.h>
#include "funciones.h"

int main() {
    struct LecturaPolucion lecturas[100];
    struct ZonaMonitoreo zonas[10];
    struct Alerta alertas[50];
    int numLecturas = 0;
    int numZonas = 0;
    int numAlertas = 0;

    int opc;
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1:
                crearDatosPolucion();
                printf("Datos de contaminación creados correctamente.\n");
                break;
            case 2:
                crearZonasMonitoreo();
                printf("Zonas de monitoreo creadas correctamente.\n");
                break;
            case 3:
                if(cargarLecturas(lecturas, &numLecturas)) {
                    imprimirLecturas(lecturas, numLecturas);
                } else {
                    printf("No se pudieron cargar las lecturas.\n");
                }
                break;
            case 4:
                if(leerZonas(zonas, &numZonas)) {
                    imprimirZonas(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas.\n");
                }
                break;
            case 5:
                generarPredicciones();
                printf("Predicciones generadas correctamente.\n");
                break;
            case 6:
                if(leerAlertas(alertas, &numAlertas)) {
                    imprimirAlertas(alertas, numAlertas);
                } else {
                    printf("No se pudieron cargar las alertas.\n");
                }
                break;
            case 7:
                generarReporte();
                break;
            case 8:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc != 8);
    
    return 0;
}

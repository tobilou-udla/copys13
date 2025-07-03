#include <stdio.h>
#include "funciones.h"

int main() {
    // Arreglos para almacenar datos del sistema
    struct ZonaMonitoreo zonas[20];
    struct RegistroHistorico registros[1000];
    struct Alerta alertas[100];
    int numZonas = 0;
    int numRegistros = 0;
    int numAlertas = 0;

    int opc;
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1:
                crearZonasMonitoreo();
                printf("Zonas de monitoreo creadas correctamente.\n");
                break;
            case 2:
                registrarLectura();
                printf("Lectura registrada correctamente.\n");
                break;
            case 3:
                if(cargarZonas(zonas, &numZonas)) {
                    mostrarZonas(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas de monitoreo.\n");
                }
                break;
            case 4:
                if(cargarRegistroHistorico(registros, &numRegistros)) {
                    mostrarHistorico(registros, numRegistros);
                } else {
                    printf("No se pudieron cargar los registros históricos.\n");
                }
                break;
            case 5:
                if(cargarZonas(zonas, &numZonas)) {
                    generarPrediccion(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para generar predicciones.\n");
                }
                break;
            case 6:
                if(cargarZonas(zonas, &numZonas)) {
                    generarAlertas(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para generar alertas.\n");
                }
                break;
            case 7:
                if(cargarZonas(zonas, &numZonas) && cargarRegistroHistorico(registros, &numRegistros)) {
                    generarReporte(zonas, numZonas, registros, numRegistros);
                } else {
                    printf("No se pudieron cargar todos los datos para generar el reporte.\n");
                }
                break;
            case 8:
                if(cargarZonas(zonas, &numZonas)) {
                    exportarDatos(zonas, numZonas);
                } else {
                    printf("No se pudieron cargar las zonas para exportar.\n");
                }
                break;
            case 9:
                printf("Saliendo del Sistema de Monitoreo de Contaminación del Aire.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc != 9);
    
    return 0;
}

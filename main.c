#include <stdio.h>
#include "funciones.h"

int main() {

    struct Empleado empleados[50];
    struct Departamento departamentos[10];
    struct Asistencia asistencias[200];
    int numEmpleados = 0;
    int numDepartamentos = 0;
    int numAsistencias = 0;

    int opc;
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1:
                crearEmpleados();
                printf("Empleados creados correctamente.\n");
                break;
            case 2:
                crearDepartamentos();
                printf("Departamentos creados correctamente.\n");
                break;
            case 3:
                if(cargarEmpleados(empleados, &numEmpleados)) {
                    imprimirEmpleados(empleados, numEmpleados);
                } else {
                    printf("No se pudieron cargar los empleados.\n");
                }
                break;
            case 4:
                if(leerDepartamentos(departamentos, &numDepartamentos)) {
                    imprimirDepartamentos(departamentos, numDepartamentos);
                } else {
                    printf("No se pudieron cargar los departamentos.\n");
                }
                break;
            case 5:
                registrarAsistencia();
                printf("Asistencia registrada correctamente.\n");
                break;
            case 6:
                if(leerAsistencias(asistencias, &numAsistencias)) {
                    imprimirAsistencias(asistencias, numAsistencias);
                } else {
                    printf("No se pudieron cargar las asistencias.\n");
                }
                break;
            case 7:
                consultarVacaciones();
                break;
            case 8:
                procesarNomina();
                break;
            case 9:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }

    } while (opc!= 9);
    
    
    return 0;
}

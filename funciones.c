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
    printf("\n==== SISTEMA INTEGRADO DE GESTIÓN DE RECURSOS HUMANOS ====\n");
    printf("==========================================================\n");
    printf("1. Crear Empleados\n");
    printf("2. Crear Departamentos\n");
    printf("3. Listar Empleados\n");
    printf("4. Listar Departamentos\n");
    printf("5. Registrar Asistencia\n");
    printf("6. Listar Asistencias\n");
    printf("7. Consultar Vacaciones\n");
    printf("8. Procesar Nómina\n");
    printf("9. Salir\n");
    printf("==========================================================\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    fflush(stdin); // Limpiar el buffer de entrada
    return opc;
}

void crearEmpleados(){
    struct Empleado empleados[] = {
        {1, "Juan Pérez", "Gerente General", 8500.00, 1, "2020-01-15", 15, 0},
        {2, "María García", "Contador", 4500.00, 2, "2021-03-10", 12, 5},
        {3, "Carlos López", "Desarrollador", 5200.00, 3, "2021-06-20", 10, 8},
        {4, "Ana Rodríguez", "Analista RRHH", 4800.00, 4, "2020-11-05", 18, 2},
        {5, "Luis Martínez", "Vendedor", 3800.00, 5, "2022-01-12", 8, 12},
        {6, "Carmen Sánchez", "Diseñadora", 4200.00, 3, "2021-09-18", 14, 6},
        {7, "Roberto Torres", "Supervisor", 5500.00, 1, "2019-07-30", 20, 4},
        {8, "Elena Morales", "Asistente", 3200.00, 4, "2022-05-25", 5, 1},
        {9, "Miguel Herrera", "Técnico", 4000.00, 3, "2021-12-08", 9, 15},
        {10, "Patricia Ruiz", "Coordinadora", 4700.00, 2, "2020-08-14", 16, 3},
        {11, "Jorge Castillo", "Analista", 4300.00, 2, "2021-11-22", 11, 7},
        {12, "Sandra Vega", "Recepcionista", 3000.00, 4, "2022-02-18", 6, 0},
        {13, "Daniel Flores", "Programador", 5000.00, 3, "2020-12-03", 13, 9},
        {14, "Isabel Ramos", "Contadora Jr", 3900.00, 2, "2022-04-07", 7, 2},
        {15, "Andrés Jiménez", "Vendedor Sr", 4500.00, 5, "2019-10-15", 22, 18}
    };
    guardarEmpleados(empleados, 15);
    printf("Empleados creados y guardados correctamente.\n");
}

void imprimirEmpleados(struct Empleado empleados[], int numEmpleados){
    printf("\n==== LISTA DE EMPLEADOS ====\n");
    printf("=====================================\n");
    for (int i = 0; i < numEmpleados; i++) {
        printf("ID: %d\n", empleados[i].id);
        printf("Nombre: %s\n", empleados[i].nombre);
        printf("Puesto: %s\n", empleados[i].puesto);
        printf("Salario: $%.2f\n", empleados[i].salario);
        printf("Departamento ID: %d\n", empleados[i].departamentoId);
        printf("Fecha Ingreso: %s\n", empleados[i].fechaIngreso);
        printf("Días Vacaciones: %d\n", empleados[i].diasVacaciones);
        printf("Horas Extras: %d\n", empleados[i].horasExtras);
        printf("-------------------------------------\n");
    }
    if (numEmpleados == 0) {
        printf("No hay empleados registrados.\n");
    }
}

void guardarEmpleados(struct Empleado empleados[], int numEmpleados){
    FILE *archivo = fopen("empleados.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los empleados.\n");
        return;
    }
    fwrite(empleados, sizeof(struct Empleado), numEmpleados, archivo);
    fclose(archivo);
}

int cargarEmpleados(struct Empleado empleados[], int *numEmpleados){
    FILE *archivo = fopen("empleados.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los empleados.\n");
        return 0;
    }
    *numEmpleados = fread(empleados, sizeof(struct Empleado), 50, archivo);
    fclose(archivo);
    return 1;
}

void crearDepartamentos(){
    struct Departamento departamentos[] = {
        {1, "Gerencia General", 0, {}},
        {2, "Contabilidad", 0, {}},
        {3, "Tecnología", 0, {}},
        {4, "Recursos Humanos", 0, {}},
        {5, "Ventas", 0, {}}
    };
    
    // Asignar empleados a departamentos basándose en los empleados creados
    struct Empleado empleados[50];
    int numEmpleados = 0;
    
    if (cargarEmpleados(empleados, &numEmpleados)) {
        for (int i = 0; i < numEmpleados; i++) {
            int deptId = empleados[i].departamentoId;
            if (deptId >= 1 && deptId <= 5) {
                int deptIndex = deptId - 1;
                if (departamentos[deptIndex].numEmpleados < 20) {
                    departamentos[deptIndex].empleados[departamentos[deptIndex].numEmpleados] = empleados[i];
                    departamentos[deptIndex].numEmpleados++;
                }
            }
        }
    }
    
    guardarDepartamentos(departamentos, 5);
    printf("Departamentos creados y guardados correctamente.\n");
}

void imprimirDepartamentos(struct Departamento departamentos[], int numDepartamentos){
    printf("\n==== LISTA DE DEPARTAMENTOS ====\n");
    printf("=====================================\n");
    for (int i = 0; i < numDepartamentos; i++) {
        printf("ID: %d, Nombre: %s\n", departamentos[i].id, departamentos[i].nombre);
        printf("Número de empleados: %d\n", departamentos[i].numEmpleados);
        printf("Empleados:\n");
        for (int j = 0; j < departamentos[i].numEmpleados; j++) {
            printf("  ID: %d, Nombre: %s, Puesto: %s\n", 
                   departamentos[i].empleados[j].id, 
                   departamentos[i].empleados[j].nombre, 
                   departamentos[i].empleados[j].puesto);
        }
        printf("-------------------------------------\n");
    }
    if (numDepartamentos == 0) {
        printf("No hay departamentos registrados.\n");
    }
}

void guardarDepartamentos(struct Departamento departamentos[], int numDepartamentos){
    FILE *archivo = fopen("departamentos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los departamentos.\n");
        return;
    }
    fwrite(departamentos, sizeof(struct Departamento), numDepartamentos, archivo);
    fclose(archivo);
}

int leerDepartamentos(struct Departamento departamentos[], int *numDepartamentos){
    FILE *archivo = fopen("departamentos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los departamentos.\n");
        return 0;
    }
    *numDepartamentos = fread(departamentos, sizeof(struct Departamento), 10, archivo);
    fclose(archivo);
    return 1;
}

void registrarAsistencia(){
    struct Asistencia asistencias[] = {
        {1, 1, "2024-01-15", "08:00", "17:00", 0},
        {2, 2, "2024-01-15", "08:15", "17:15", 15},
        {3, 3, "2024-01-15", "08:30", "17:30", 30},
        {4, 4, "2024-01-15", "08:00", "17:00", 0},
        {5, 5, "2024-01-15", "08:45", "17:45", 45},
        {6, 6, "2024-01-15", "08:00", "17:00", 0},
        {7, 7, "2024-01-15", "08:10", "17:10", 10},
        {8, 8, "2024-01-15", "08:00", "17:00", 0},
        {9, 9, "2024-01-15", "08:20", "17:20", 20},
        {10, 10, "2024-01-15", "08:00", "17:00", 0}
    };
    guardarAsistencias(asistencias, 10);
    printf("Asistencias registradas y guardadas correctamente.\n");
}

void imprimirAsistencias(struct Asistencia asistencias[], int numAsistencias){
    printf("\n==== REGISTRO DE ASISTENCIAS ====\n");
    printf("=====================================\n");
    for (int i = 0; i < numAsistencias; i++) {
        printf("ID: %d\n", asistencias[i].id);
        printf("Empleado ID: %d\n", asistencias[i].empleadoId);
        printf("Fecha: %s\n", asistencias[i].fecha);
        printf("Hora Entrada: %s\n", asistencias[i].horaEntrada);
        printf("Hora Salida: %s\n", asistencias[i].horaSalida);
        printf("Minutos Atraso: %d\n", asistencias[i].minutosAtraso);
        if (asistencias[i].minutosAtraso > 0) {
            printf("*** EMPLEADO CON ATRASO ***\n");
        }
        printf("-------------------------------------\n");
    }
    if (numAsistencias == 0) {
        printf("No hay asistencias registradas.\n");
    }
}

void guardarAsistencias(struct Asistencia asistencias[], int numAsistencias){
    FILE *archivo = fopen("asistencias.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las asistencias.\n");
        return;
    }
    fwrite(asistencias, sizeof(struct Asistencia), numAsistencias, archivo);
    fclose(archivo);
}

int leerAsistencias(struct Asistencia asistencias[], int *numAsistencias){
    FILE *archivo = fopen("asistencias.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las asistencias.\n");
        return 0;
    }
    *numAsistencias = fread(asistencias, sizeof(struct Asistencia), 200, archivo);
    fclose(archivo);
    return 1;
}

void consultarVacaciones(){
    struct Empleado empleados[50];
    int numEmpleados = 0;
    
    if (!cargarEmpleados(empleados, &numEmpleados)) {
        printf("No se pudieron cargar los empleados.\n");
        return;
    }
    
    printf("\n==== CONSULTA DE VACACIONES ====\n");
    printf("=====================================\n");
    
    for (int i = 0; i < numEmpleados; i++) {
        printf("Empleado: %s (ID: %d)\n", empleados[i].nombre, empleados[i].id);
        printf("Días de vacaciones disponibles: %d\n", empleados[i].diasVacaciones);
        printf("Fecha de ingreso: %s\n", empleados[i].fechaIngreso);
        
        if (empleados[i].diasVacaciones > 15) {
            printf("*** EMPLEADO CON MUCHAS VACACIONES PENDIENTES ***\n");
        } else if (empleados[i].diasVacaciones < 5) {
            printf("*** EMPLEADO CON POCAS VACACIONES DISPONIBLES ***\n");
        }
        printf("-------------------------------------\n");
    }
}

void procesarNomina(){
    struct Empleado empleados[50];
    int numEmpleados = 0;
    
    if (!cargarEmpleados(empleados, &numEmpleados)) {
        printf("No se pudieron cargar los empleados.\n");
        return;
    }
    
    printf("\n==== PROCESAMIENTO DE NÓMINA ====\n");
    printf("=====================================\n");
    
    float totalNomina = 0;
    
    for (int i = 0; i < numEmpleados; i++) {
        float salarioBase = empleados[i].salario;
        float pagoHorasExtras = empleados[i].horasExtras * 25.0; // $25 por hora extra
        float salarioTotal = salarioBase + pagoHorasExtras;
        
        printf("Empleado: %s (ID: %d)\n", empleados[i].nombre, empleados[i].id);
        printf("Salario Base: $%.2f\n", salarioBase);
        printf("Horas Extras: %d (Pago: $%.2f)\n", empleados[i].horasExtras, pagoHorasExtras);
        printf("Salario Total: $%.2f\n", salarioTotal);
        
        totalNomina += salarioTotal;
        printf("-------------------------------------\n");
    }
    
    printf("TOTAL NÓMINA DEL MES: $%.2f\n", totalNomina);
    printf("=====================================\n");
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

// Umbrales de contaminación (valores estándar de la OMS)
#define UMBRAL_CO2_NORMAL 400.0
#define UMBRAL_CO2_MODERADO 1000.0
#define UMBRAL_CO2_PELIGROSO 5000.0

#define UMBRAL_SO2_NORMAL 20.0
#define UMBRAL_SO2_MODERADO 80.0
#define UMBRAL_SO2_PELIGROSO 200.0

#define UMBRAL_NO2_NORMAL 40.0
#define UMBRAL_NO2_MODERADO 100.0
#define UMBRAL_NO2_PELIGROSO 200.0

#define UMBRAL_PM25_NORMAL 12.0
#define UMBRAL_PM25_MODERADO 35.0
#define UMBRAL_PM25_PELIGROSO 55.0

void leerCadena(char *cadena, int num){
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

void obtenerFechaActual(char *fecha) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(fecha, "%04d-%02d-%02d %02d:%02d", 
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min);
}

int menu(){
    int opc;
    printf("\n=== Sistema de Monitoreo de Calidad del Aire ===\n");
    printf("================================================\n");
    printf("1. Crear datos de contaminación\n");
    printf("2. Crear zonas de monitoreo\n");
    printf("3. Listar lecturas de contaminación\n");
    printf("4. Listar zonas de monitoreo\n");
    printf("5. Generar predicciones\n");
    printf("6. Ver alertas\n");
    printf("7. Generar reporte completo\n");
    printf("8. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}

void crearDatosPolucion(){
    struct LecturaPolucion lecturas[20];
    char fecha[20];
    obtenerFechaActual(fecha);
    
    // Crear datos de ejemplo para diferentes zonas
    struct LecturaPolucion datos_ejemplo[] = {
        {1, 1, "", 420.5, 15.2, 35.8, 18.5},
        {2, 1, "", 438.7, 18.1, 42.3, 22.1},
        {3, 1, "", 445.2, 16.8, 38.9, 19.7},
        {4, 2, "", 512.3, 25.4, 58.2, 28.9},
        {5, 2, "", 498.1, 22.7, 55.1, 26.3},
        {6, 2, "", 530.8, 28.2, 62.4, 31.5},
        {7, 3, "", 380.2, 12.1, 28.7, 14.2},
        {8, 3, "", 395.6, 13.8, 31.5, 16.1},
        {9, 3, "", 402.3, 11.9, 29.2, 15.8},
        {10, 4, "", 625.7, 42.3, 89.1, 45.2},
        {11, 4, "", 658.2, 45.8, 92.7, 48.6},
        {12, 4, "", 642.1, 43.9, 87.5, 46.8},
        {13, 5, "", 358.9, 8.2, 22.1, 11.5},
        {14, 5, "", 362.4, 9.1, 24.7, 12.8},
        {15, 5, "", 355.2, 7.8, 21.3, 10.9},
        {16, 1, "", 425.8, 16.5, 39.2, 20.1},
        {17, 2, "", 521.6, 26.8, 59.8, 29.7},
        {18, 3, "", 388.4, 13.2, 30.1, 15.4},
        {19, 4, "", 634.5, 44.1, 90.3, 47.2},
        {20, 5, "", 359.7, 8.6, 23.4, 12.1}
    };
    
    // Asignar fechas a todos los datos
    for (int i = 0; i < 20; i++) {
        strcpy(datos_ejemplo[i].fecha, fecha);
        lecturas[i] = datos_ejemplo[i];
    }
    
    guardarLecturas(lecturas, 20);
    printf("20 lecturas de contaminación creadas y guardadas correctamente.\n");
}

void crearZonasMonitoreo(){
    struct ZonaMonitoreo zonas[5];
    
    // Crear zonas de ejemplo
    struct ZonaMonitoreo zonas_ejemplo[] = {
        {1, "Centro Histórico", "Plaza Principal - Coordenadas: 0.2182, -78.5126", {}, 0},
        {2, "Zona Industrial Norte", "Parque Industrial - Coordenadas: 0.2350, -78.5020", {}, 0},
        {3, "Zona Residencial Sur", "Barrio La Floresta - Coordenadas: 0.2010, -78.5180", {}, 0},
        {4, "Zona Comercial", "Av. Amazonas - Coordenadas: 0.2200, -78.5100", {}, 0},
        {5, "Zona Universitaria", "Campus UDLA - Coordenadas: 0.2120, -78.5200", {}, 0}
    };
    
    for (int i = 0; i < 5; i++) {
        zonas[i] = zonas_ejemplo[i];
    }
    
    guardarZonas(zonas, 5);
    printf("5 zonas de monitoreo creadas y guardadas correctamente.\n");
}

void imprimirLecturas(struct LecturaPolucion lecturas[], int numLecturas){
    printf("\n=== Lecturas de Contaminación ===\n");
    printf("=================================================================\n");
    for (int i = 0; i < numLecturas; i++) {
        printf("ID: %d | Zona: %d | Fecha: %s\n", 
               lecturas[i].id, lecturas[i].zona_id, lecturas[i].fecha);
        printf("  CO2: %.2f ppm | SO2: %.2f ppm | NO2: %.2f ppm | PM2.5: %.2f µg/m³\n", 
               lecturas[i].co2, lecturas[i].so2, lecturas[i].no2, lecturas[i].pm25);
        printf("-----------------------------------------------------------------\n");
    }
    if (numLecturas == 0) {
        printf("No hay lecturas registradas.\n");
    }
}

void guardarLecturas(struct LecturaPolucion lecturas[], int numLecturas){
    FILE *archivo = fopen("lecturas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las lecturas.\n");
        return;
    }
    fwrite(lecturas, sizeof(struct LecturaPolucion), numLecturas, archivo);
    fclose(archivo);
}

int cargarLecturas(struct LecturaPolucion lecturas[], int *numLecturas){
    FILE *archivo = fopen("lecturas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las lecturas.\n");
        return 0;
    }
    *numLecturas = fread(lecturas, sizeof(struct LecturaPolucion), 100, archivo);
    fclose(archivo);
    return 1;
}

void imprimirZonas(struct ZonaMonitoreo zonas[], int numZonas){
    printf("\n=== Zonas de Monitoreo ===\n");
    printf("=================================================================\n");
    for (int i = 0; i < numZonas; i++) {
        printf("ID: %d | Nombre: %s\n", zonas[i].id, zonas[i].nombre);
        printf("Ubicación: %s\n", zonas[i].ubicacion);
        printf("Lecturas históricas: %d\n", zonas[i].num_lecturas);
        printf("-----------------------------------------------------------------\n");
    }
    if (numZonas == 0) {
        printf("No hay zonas registradas.\n");
    }
}

void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas){
    FILE *archivo = fopen("zonas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las zonas.\n");
        return;
    }
    fwrite(zonas, sizeof(struct ZonaMonitoreo), numZonas, archivo);
    fclose(archivo);
}

int leerZonas(struct ZonaMonitoreo zonas[], int *numZonas){
    FILE *archivo = fopen("zonas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las zonas.\n");
        return 0;
    }
    *numZonas = fread(zonas, sizeof(struct ZonaMonitoreo), 10, archivo);
    fclose(archivo);
    return 1;
}

float calcularPrediccion(struct LecturaPolucion lecturas[], int numLecturas, char* contaminante) {
    if (numLecturas == 0) return 0.0;
    
    // Algoritmo de promedio ponderado - más peso a lecturas recientes
    float suma_ponderada = 0.0;
    float suma_pesos = 0.0;
    
    for (int i = 0; i < numLecturas; i++) {
        float peso = (float)(i + 1) / numLecturas; // Peso creciente para datos más recientes
        float valor = 0.0;
        
        if (strcmp(contaminante, "CO2") == 0) {
            valor = lecturas[i].co2;
        } else if (strcmp(contaminante, "SO2") == 0) {
            valor = lecturas[i].so2;
        } else if (strcmp(contaminante, "NO2") == 0) {
            valor = lecturas[i].no2;
        } else if (strcmp(contaminante, "PM25") == 0) {
            valor = lecturas[i].pm25;
        }
        
        suma_ponderada += valor * peso;
        suma_pesos += peso;
    }
    
    return suma_ponderada / suma_pesos;
}

char* obtenerNivelAlerta(char* contaminante, float nivel) {
    if (strcmp(contaminante, "CO2") == 0) {
        if (nivel < UMBRAL_CO2_NORMAL) return "Normal";
        else if (nivel < UMBRAL_CO2_MODERADO) return "Moderado";
        else return "Peligroso";
    } else if (strcmp(contaminante, "SO2") == 0) {
        if (nivel < UMBRAL_SO2_NORMAL) return "Normal";
        else if (nivel < UMBRAL_SO2_MODERADO) return "Moderado";
        else return "Peligroso";
    } else if (strcmp(contaminante, "NO2") == 0) {
        if (nivel < UMBRAL_NO2_NORMAL) return "Normal";
        else if (nivel < UMBRAL_NO2_MODERADO) return "Moderado";
        else return "Peligroso";
    } else if (strcmp(contaminante, "PM25") == 0) {
        if (nivel < UMBRAL_PM25_NORMAL) return "Normal";
        else if (nivel < UMBRAL_PM25_MODERADO) return "Moderado";
        else return "Peligroso";
    }
    return "Desconocido";
}

char* obtenerRecomendacion(char* contaminante, float nivel) {
    char* nivel_alerta = obtenerNivelAlerta(contaminante, nivel);
    
    if (strcmp(nivel_alerta, "Normal") == 0) {
        return "Condiciones normales. Mantener monitoreo regular.";
    } else if (strcmp(nivel_alerta, "Moderado") == 0) {
        if (strcmp(contaminante, "CO2") == 0) {
            return "Nivel moderado de CO2. Mejorar ventilación en espacios cerrados.";
        } else if (strcmp(contaminante, "SO2") == 0) {
            return "Nivel moderado de SO2. Controlar emisiones industriales.";
        } else if (strcmp(contaminante, "NO2") == 0) {
            return "Nivel moderado de NO2. Reducir tráfico vehicular.";
        } else if (strcmp(contaminante, "PM25") == 0) {
            return "Nivel moderado de PM2.5. Evitar actividades al aire libre prolongadas.";
        }
    } else if (strcmp(nivel_alerta, "Peligroso") == 0) {
        if (strcmp(contaminante, "CO2") == 0) {
            return "ALERTA: CO2 peligroso. Evacuación inmediata de espacios cerrados.";
        } else if (strcmp(contaminante, "SO2") == 0) {
            return "ALERTA: SO2 peligroso. Suspender actividades industriales.";
        } else if (strcmp(contaminante, "NO2") == 0) {
            return "ALERTA: NO2 peligroso. Prohibir circulación vehicular.";
        } else if (strcmp(contaminante, "PM25") == 0) {
            return "ALERTA: PM2.5 peligroso. Permanecer en interiores, usar mascarillas.";
        }
    }
    return "Consultar con especialistas ambientales.";
}

void generarPredicciones(){
    struct LecturaPolucion lecturas[100];
    struct ZonaMonitoreo zonas[10];
    struct Alerta alertas[50];
    int numLecturas = 0;
    int numZonas = 0;
    int alertaId = 1;
    char fecha[20];
    
    obtenerFechaActual(fecha);
    
    // Cargar datos
    if (!cargarLecturas(lecturas, &numLecturas)) {
        printf("No se pudieron cargar las lecturas para generar predicciones.\n");
        return;
    }
    
    if (!leerZonas(zonas, &numZonas)) {
        printf("No se pudieron cargar las zonas para generar predicciones.\n");
        return;
    }
    
    printf("\n=== Generando Predicciones ===\n");
    
    // Generar predicciones para cada zona
    for (int zona = 1; zona <= numZonas; zona++) {
        // Filtrar lecturas por zona
        struct LecturaPolucion lecturasZona[100];
        int numLecturasZona = 0;
        
        for (int i = 0; i < numLecturas; i++) {
            if (lecturas[i].zona_id == zona) {
                lecturasZona[numLecturasZona] = lecturas[i];
                numLecturasZona++;
            }
        }
        
        if (numLecturasZona == 0) continue;
        
        // Calcular predicciones para cada contaminante
        char* contaminantes[] = {"CO2", "SO2", "NO2", "PM25"};
        for (int c = 0; c < 4; c++) {
            float prediccion = calcularPrediccion(lecturasZona, numLecturasZona, contaminantes[c]);
            char* nivel = obtenerNivelAlerta(contaminantes[c], prediccion);
            
            // Crear alerta si es necesario
            if (strcmp(nivel, "Normal") != 0) {
                struct Alerta alerta;
                alerta.id = alertaId++;
                alerta.zona_id = zona;
                strcpy(alerta.tipo_contaminante, contaminantes[c]);
                alerta.nivel_actual = lecturasZona[numLecturasZona-1].co2; // Último valor
                if (strcmp(contaminantes[c], "SO2") == 0) alerta.nivel_actual = lecturasZona[numLecturasZona-1].so2;
                else if (strcmp(contaminantes[c], "NO2") == 0) alerta.nivel_actual = lecturasZona[numLecturasZona-1].no2;
                else if (strcmp(contaminantes[c], "PM25") == 0) alerta.nivel_actual = lecturasZona[numLecturasZona-1].pm25;
                
                alerta.nivel_predicho = prediccion;
                strcpy(alerta.nivel_alerta, nivel);
                strcpy(alerta.recomendacion, obtenerRecomendacion(contaminantes[c], prediccion));
                strcpy(alerta.fecha, fecha);
                
                alertas[alertaId-2] = alerta;
            }
        }
    }
    
    // Guardar alertas
    if (alertaId > 1) {
        guardarAlertas(alertas, alertaId - 1);
        printf("Se generaron %d alertas basadas en las predicciones.\n", alertaId - 1);
    } else {
        printf("No se generaron alertas. Todos los niveles están dentro de rangos normales.\n");
    }
}

void imprimirAlertas(struct Alerta alertas[], int numAlertas){
    printf("\n=== Alertas de Contaminación ===\n");
    printf("=================================================================\n");
    for (int i = 0; i < numAlertas; i++) {
        printf("ALERTA #%d - Zona: %d | Fecha: %s\n", 
               alertas[i].id, alertas[i].zona_id, alertas[i].fecha);
        printf("Contaminante: %s | Nivel: %s\n", 
               alertas[i].tipo_contaminante, alertas[i].nivel_alerta);
        printf("Valor actual: %.2f | Predicción: %.2f\n", 
               alertas[i].nivel_actual, alertas[i].nivel_predicho);
        printf("Recomendación: %s\n", alertas[i].recomendacion);
        printf("-----------------------------------------------------------------\n");
    }
    if (numAlertas == 0) {
        printf("No hay alertas registradas.\n");
    }
}

void guardarAlertas(struct Alerta alertas[], int numAlertas){
    FILE *archivo = fopen("alertas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las alertas.\n");
        return;
    }
    fwrite(alertas, sizeof(struct Alerta), numAlertas, archivo);
    fclose(archivo);
}

int leerAlertas(struct Alerta alertas[], int *numAlertas){
    FILE *archivo = fopen("alertas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las alertas.\n");
        return 0;
    }
    *numAlertas = fread(alertas, sizeof(struct Alerta), 50, archivo);
    fclose(archivo);
    return 1;
}

void generarReporte(){
    struct LecturaPolucion lecturas[100];
    struct ZonaMonitoreo zonas[10];
    struct Alerta alertas[50];
    int numLecturas = 0;
    int numZonas = 0;
    int numAlertas = 0;
    
    printf("\n");
    printf("========================================================================\n");
    printf("                    REPORTE DE CALIDAD DEL AIRE                        \n");
    printf("========================================================================\n");
    
    char fecha[20];
    obtenerFechaActual(fecha);
    printf("Fecha de generación: %s\n", fecha);
    printf("========================================================================\n");
    
    // Cargar y mostrar resumen de zonas
    if (leerZonas(zonas, &numZonas)) {
        printf("\n--- RESUMEN DE ZONAS DE MONITOREO ---\n");
        printf("Total de zonas monitoreadas: %d\n", numZonas);
        for (int i = 0; i < numZonas; i++) {
            printf("  %d. %s - %s\n", zonas[i].id, zonas[i].nombre, zonas[i].ubicacion);
        }
    }
    
    // Cargar y mostrar resumen de lecturas
    if (cargarLecturas(lecturas, &numLecturas)) {
        printf("\n--- RESUMEN DE LECTURAS ---\n");
        printf("Total de lecturas registradas: %d\n", numLecturas);
        
        // Calcular promedios generales
        float promCO2 = 0, promSO2 = 0, promNO2 = 0, promPM25 = 0;
        for (int i = 0; i < numLecturas; i++) {
            promCO2 += lecturas[i].co2;
            promSO2 += lecturas[i].so2;
            promNO2 += lecturas[i].no2;
            promPM25 += lecturas[i].pm25;
        }
        
        if (numLecturas > 0) {
            promCO2 /= numLecturas;
            promSO2 /= numLecturas;
            promNO2 /= numLecturas;
            promPM25 /= numLecturas;
            
            printf("Promedios generales:\n");
            printf("  CO2: %.2f ppm (%s)\n", promCO2, obtenerNivelAlerta("CO2", promCO2));
            printf("  SO2: %.2f ppm (%s)\n", promSO2, obtenerNivelAlerta("SO2", promSO2));
            printf("  NO2: %.2f ppm (%s)\n", promNO2, obtenerNivelAlerta("NO2", promNO2));
            printf("  PM2.5: %.2f µg/m³ (%s)\n", promPM25, obtenerNivelAlerta("PM25", promPM25));
        }
    }
    
    // Cargar y mostrar alertas
    if (leerAlertas(alertas, &numAlertas)) {
        printf("\n--- ALERTAS ACTIVAS ---\n");
        if (numAlertas > 0) {
            printf("Total de alertas: %d\n", numAlertas);
            int alertasNormales = 0, alertasModeradas = 0, alertasPeligrosas = 0;
            
            for (int i = 0; i < numAlertas; i++) {
                if (strcmp(alertas[i].nivel_alerta, "Normal") == 0) alertasNormales++;
                else if (strcmp(alertas[i].nivel_alerta, "Moderado") == 0) alertasModeradas++;
                else if (strcmp(alertas[i].nivel_alerta, "Peligroso") == 0) alertasPeligrosas++;
            }
            
            printf("  Alertas normales: %d\n", alertasNormales);
            printf("  Alertas moderadas: %d\n", alertasModeradas);
            printf("  Alertas peligrosas: %d\n", alertasPeligrosas);
            
            if (alertasPeligrosas > 0) {
                printf("\n⚠️  ATENCIÓN: Hay %d alertas peligrosas que requieren acción inmediata.\n", alertasPeligrosas);
            }
        } else {
            printf("No hay alertas registradas.\n");
        }
    }
    
    printf("\n--- RECOMENDACIONES GENERALES ---\n");
    printf("• Mantener el monitoreo continuo en todas las zonas\n");
    printf("• Revisar alertas diariamente\n");
    printf("• Implementar medidas preventivas en zonas con niveles moderados\n");
    printf("• Coordinar con autoridades ambientales para zonas peligrosas\n");
    printf("• Educar a la población sobre calidad del aire\n");
    
    printf("\n========================================================================\n");
    printf("                         FIN DEL REPORTE                               \n");
    printf("========================================================================\n");
}
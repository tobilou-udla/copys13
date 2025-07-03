#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

// Umbrales críticos para contaminantes (basados en estándares internacionales)
#define UMBRAL_CO2_PRECAUCION 1000
#define UMBRAL_CO2_ALERTA 1500
#define UMBRAL_CO2_EMERGENCIA 2000

#define UMBRAL_SO2_PRECAUCION 80
#define UMBRAL_SO2_ALERTA 150
#define UMBRAL_SO2_EMERGENCIA 250

#define UMBRAL_NO2_PRECAUCION 100
#define UMBRAL_NO2_ALERTA 200
#define UMBRAL_NO2_EMERGENCIA 300

#define UMBRAL_PM25_PRECAUCION 25
#define UMBRAL_PM25_ALERTA 50
#define UMBRAL_PM25_EMERGENCIA 75

void leerCadena(char *cadena, int num){
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

void obtenerFechaHora(char *fecha, char *hora) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    sprintf(fecha, "%02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    sprintf(hora, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

int menu(){
    int opc;
    printf("\n========================================\n");
    printf("  SISTEMA DE MONITOREO DE CONTAMINACIÓN\n");
    printf("========================================\n");
    printf("1. Crear Zonas de Monitoreo\n");
    printf("2. Registrar Lectura de Contaminantes\n");
    printf("3. Mostrar Zonas de Monitoreo\n");
    printf("4. Ver Historial de Registros\n");
    printf("5. Generar Predicciones\n");
    printf("6. Generar Alertas\n");
    printf("7. Generar Reporte Completo\n");
    printf("8. Exportar Datos\n");
    printf("9. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}

void crearZonasMonitoreo(){
    struct ZonaMonitoreo zonas[20];
    int numZonas = 5; // Crear 5 zonas de ejemplo
    
    // Zona 1: Centro Histórico
    zonas[0].id = 1;
    strcpy(zonas[0].nombre, "Centro Histórico");
    strcpy(zonas[0].ubicacion, "Plaza Principal, Quito");
    zonas[0].contaminantes.co2 = 450.5;
    zonas[0].contaminantes.so2 = 25.3;
    zonas[0].contaminantes.no2 = 45.7;
    zonas[0].contaminantes.pm25 = 15.2;
    zonas[0].factoresClimaticos.temperatura = 18.5;
    zonas[0].factoresClimaticos.humedad = 65.0;
    zonas[0].factoresClimaticos.velocidadViento = 8.2;
    strcpy(zonas[0].factoresClimaticos.direccionViento, "NE");
    obtenerFechaHora(zonas[0].fecha, zonas[0].hora);
    
    // Zona 2: Zona Industrial Norte
    zonas[1].id = 2;
    strcpy(zonas[1].nombre, "Zona Industrial Norte");
    strcpy(zonas[1].ubicacion, "Sector Industrial, Quito");
    zonas[1].contaminantes.co2 = 850.7;
    zonas[1].contaminantes.so2 = 65.8;
    zonas[1].contaminantes.no2 = 125.4;
    zonas[1].contaminantes.pm25 = 35.6;
    zonas[1].factoresClimaticos.temperatura = 20.1;
    zonas[1].factoresClimaticos.humedad = 58.3;
    zonas[1].factoresClimaticos.velocidadViento = 12.5;
    strcpy(zonas[1].factoresClimaticos.direccionViento, "SO");
    obtenerFechaHora(zonas[1].fecha, zonas[1].hora);
    
    // Zona 3: Zona Residencial Sur
    zonas[2].id = 3;
    strcpy(zonas[2].nombre, "Zona Residencial Sur");
    strcpy(zonas[2].ubicacion, "Sector Residencial, Quito");
    zonas[2].contaminantes.co2 = 380.2;
    zonas[2].contaminantes.so2 = 18.9;
    zonas[2].contaminantes.no2 = 32.1;
    zonas[2].contaminantes.pm25 = 12.8;
    zonas[2].factoresClimaticos.temperatura = 19.3;
    zonas[2].factoresClimaticos.humedad = 70.2;
    zonas[2].factoresClimaticos.velocidadViento = 6.8;
    strcpy(zonas[2].factoresClimaticos.direccionViento, "E");
    obtenerFechaHora(zonas[2].fecha, zonas[2].hora);
    
    // Zona 4: Aeropuerto
    zonas[3].id = 4;
    strcpy(zonas[3].nombre, "Aeropuerto");
    strcpy(zonas[3].ubicacion, "Aeropuerto Internacional, Quito");
    zonas[3].contaminantes.co2 = 1200.5;
    zonas[3].contaminantes.so2 = 95.4;
    zonas[3].contaminantes.no2 = 180.7;
    zonas[3].contaminantes.pm25 = 45.3;
    zonas[3].factoresClimaticos.temperatura = 16.8;
    zonas[3].factoresClimaticos.humedad = 55.7;
    zonas[3].factoresClimaticos.velocidadViento = 15.2;
    strcpy(zonas[3].factoresClimaticos.direccionViento, "O");
    obtenerFechaHora(zonas[3].fecha, zonas[3].hora);
    
    // Zona 5: Parque Nacional
    zonas[4].id = 5;
    strcpy(zonas[4].nombre, "Parque Nacional");
    strcpy(zonas[4].ubicacion, "Parque Metropolitano, Quito");
    zonas[4].contaminantes.co2 = 320.8;
    zonas[4].contaminantes.so2 = 12.1;
    zonas[4].contaminantes.no2 = 22.5;
    zonas[4].contaminantes.pm25 = 8.9;
    zonas[4].factoresClimaticos.temperatura = 17.2;
    zonas[4].factoresClimaticos.humedad = 75.5;
    zonas[4].factoresClimaticos.velocidadViento = 5.3;
    strcpy(zonas[4].factoresClimaticos.direccionViento, "N");
    obtenerFechaHora(zonas[4].fecha, zonas[4].hora);
    
    guardarZonas(zonas, numZonas);
    printf("Zonas de monitoreo creadas y guardadas correctamente.\n");
}

void registrarLectura(){
    struct ZonaMonitoreo zonas[20];
    struct RegistroHistorico registros[1000];
    int numZonas = 0;
    int numRegistros = 0;
    
    if(!cargarZonas(zonas, &numZonas)) {
        printf("Error: No se pudieron cargar las zonas. Cree zonas primero.\n");
        return;
    }
    
    cargarRegistroHistorico(registros, &numRegistros);
    
    printf("\n=== REGISTRO DE NUEVA LECTURA ===\n");
    mostrarZonas(zonas, numZonas);
    
    int zonaId;
    printf("Seleccione la zona (ID): ");
    scanf("%d", &zonaId);
    
    if(zonaId < 1 || zonaId > numZonas) {
        printf("ID de zona inválido.\n");
        return;
    }
    
    // Actualizar datos de la zona seleccionada
    printf("Ingrese nuevos valores de contaminantes:\n");
    printf("CO2 (ppm): ");
    scanf("%f", &zonas[zonaId-1].contaminantes.co2);
    printf("SO2 (µg/m³): ");
    scanf("%f", &zonas[zonaId-1].contaminantes.so2);
    printf("NO2 (µg/m³): ");
    scanf("%f", &zonas[zonaId-1].contaminantes.no2);
    printf("PM2.5 (µg/m³): ");
    scanf("%f", &zonas[zonaId-1].contaminantes.pm25);
    
    printf("Ingrese factores climáticos:\n");
    printf("Temperatura (°C): ");
    scanf("%f", &zonas[zonaId-1].factoresClimaticos.temperatura);
    printf("Humedad (%%): ");
    scanf("%f", &zonas[zonaId-1].factoresClimaticos.humedad);
    printf("Velocidad del viento (km/h): ");
    scanf("%f", &zonas[zonaId-1].factoresClimaticos.velocidadViento);
    printf("Dirección del viento: ");
    leerCadena(zonas[zonaId-1].factoresClimaticos.direccionViento, 10);
    
    // Actualizar fecha y hora
    obtenerFechaHora(zonas[zonaId-1].fecha, zonas[zonaId-1].hora);
    
    // Guardar en histórico
    struct RegistroHistorico nuevoRegistro;
    nuevoRegistro.id = numRegistros + 1;
    nuevoRegistro.zonaId = zonaId;
    nuevoRegistro.contaminantes = zonas[zonaId-1].contaminantes;
    nuevoRegistro.factoresClimaticos = zonas[zonaId-1].factoresClimaticos;
    strcpy(nuevoRegistro.fecha, zonas[zonaId-1].fecha);
    strcpy(nuevoRegistro.hora, zonas[zonaId-1].hora);
    
    registros[numRegistros] = nuevoRegistro;
    numRegistros++;
    
    // Guardar datos actualizados
    guardarZonas(zonas, numZonas);
    guardarRegistroHistorico(registros, numRegistros);
    
    printf("Lectura registrada exitosamente.\n");
}

void mostrarZonas(struct ZonaMonitoreo zonas[], int numZonas){
    printf("\n=== ZONAS DE MONITOREO ===\n");
    printf("============================================\n");
    for (int i = 0; i < numZonas; i++) {
        printf("ID: %d | Zona: %s\n", zonas[i].id, zonas[i].nombre);
        printf("Ubicación: %s\n", zonas[i].ubicacion);
        printf("Fecha/Hora: %s %s\n", zonas[i].fecha, zonas[i].hora);
        printf("Contaminantes:\n");
        printf("  CO2: %.2f ppm\n", zonas[i].contaminantes.co2);
        printf("  SO2: %.2f µg/m³\n", zonas[i].contaminantes.so2);
        printf("  NO2: %.2f µg/m³\n", zonas[i].contaminantes.no2);
        printf("  PM2.5: %.2f µg/m³\n", zonas[i].contaminantes.pm25);
        printf("Factores Climáticos:\n");
        printf("  Temperatura: %.1f°C\n", zonas[i].factoresClimaticos.temperatura);
        printf("  Humedad: %.1f%%\n", zonas[i].factoresClimaticos.humedad);
        printf("  Viento: %.1f km/h (%s)\n", zonas[i].factoresClimaticos.velocidadViento, zonas[i].factoresClimaticos.direccionViento);
        printf("--------------------------------------------\n");
    }
    if (numZonas == 0) {
        printf("No hay zonas de monitoreo registradas.\n");
    }
}

void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas){
    FILE *archivo = fopen("zonas_monitoreo.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las zonas.\n");
        return;
    }
    fwrite(zonas, sizeof(struct ZonaMonitoreo), numZonas, archivo);
    fclose(archivo);
}

int cargarZonas(struct ZonaMonitoreo zonas[], int *numZonas){
    FILE *archivo = fopen("zonas_monitoreo.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar las zonas.\n");
        return 0;
    }
    *numZonas = fread(zonas, sizeof(struct ZonaMonitoreo), 20, archivo);
    fclose(archivo);
    return 1;
}

void guardarRegistroHistorico(struct RegistroHistorico registros[], int numRegistros){
    FILE *archivo = fopen("historico.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el histórico.\n");
        return;
    }
    fwrite(registros, sizeof(struct RegistroHistorico), numRegistros, archivo);
    fclose(archivo);
}

int cargarRegistroHistorico(struct RegistroHistorico registros[], int *numRegistros){
    FILE *archivo = fopen("historico.dat", "rb");
    if (archivo == NULL) {
        *numRegistros = 0;
        return 0;
    }
    *numRegistros = fread(registros, sizeof(struct RegistroHistorico), 1000, archivo);
    fclose(archivo);
    return 1;
}

void mostrarHistorico(struct RegistroHistorico registros[], int numRegistros){
    printf("\n=== HISTORIAL DE REGISTROS ===\n");
    printf("=====================================================\n");
    for (int i = 0; i < numRegistros; i++) {
        printf("Registro ID: %d | Zona ID: %d\n", registros[i].id, registros[i].zonaId);
        printf("Fecha/Hora: %s %s\n", registros[i].fecha, registros[i].hora);
        printf("Contaminantes: CO2=%.2f, SO2=%.2f, NO2=%.2f, PM2.5=%.2f\n",
               registros[i].contaminantes.co2, registros[i].contaminantes.so2,
               registros[i].contaminantes.no2, registros[i].contaminantes.pm25);
        printf("Clima: T=%.1f°C, H=%.1f%%, V=%.1f km/h (%s)\n",
               registros[i].factoresClimaticos.temperatura,
               registros[i].factoresClimaticos.humedad,
               registros[i].factoresClimaticos.velocidadViento,
               registros[i].factoresClimaticos.direccionViento);
        printf("-----------------------------------------------------\n");
    }
    if (numRegistros == 0) {
        printf("No hay registros históricos disponibles.\n");
    }
}

float calcularPromedioRomano(struct RegistroHistorico registros[], int numRegistros, int zonaId, char tipoContaminante[]){
    float suma = 0.0;
    int count = 0;
    float pesos[] = {0.1, 0.2, 0.3, 0.4}; // Pesos para las últimas 4 mediciones (más peso a las recientes)
    
    // Buscar las últimas mediciones de la zona específica
    for (int i = numRegistros - 1; i >= 0 && count < 4; i--) {
        if (registros[i].zonaId == zonaId) {
            float valor = 0.0;
            
            if (strcmp(tipoContaminante, "CO2") == 0) {
                valor = registros[i].contaminantes.co2;
            } else if (strcmp(tipoContaminante, "SO2") == 0) {
                valor = registros[i].contaminantes.so2;
            } else if (strcmp(tipoContaminante, "NO2") == 0) {
                valor = registros[i].contaminantes.no2;
            } else if (strcmp(tipoContaminante, "PM25") == 0) {
                valor = registros[i].contaminantes.pm25;
            }
            
            suma += valor * pesos[3-count]; // Aplicar peso (más reciente = más peso)
            count++;
        }
    }
    
    if (count == 0) return 0.0;
    return suma; // Ya está ponderado
}

void generarPrediccion(struct ZonaMonitoreo zonas[], int numZonas){
    struct RegistroHistorico registros[1000];
    int numRegistros = 0;
    
    if(!cargarRegistroHistorico(registros, &numRegistros)) {
        printf("No hay datos históricos para generar predicciones.\n");
        return;
    }
    
    printf("\n=== PREDICCIONES BASADAS EN PROMEDIOS PONDERADOS ===\n");
    printf("=========================================================\n");
    
    for (int i = 0; i < numZonas; i++) {
        printf("Zona: %s (ID: %d)\n", zonas[i].nombre, zonas[i].id);
        printf("Predicciones para las próximas horas:\n");
        
        float predCO2 = calcularPromedioRomano(registros, numRegistros, zonas[i].id, "CO2");
        float predSO2 = calcularPromedioRomano(registros, numRegistros, zonas[i].id, "SO2");
        float predNO2 = calcularPromedioRomano(registros, numRegistros, zonas[i].id, "NO2");
        float predPM25 = calcularPromedioRomano(registros, numRegistros, zonas[i].id, "PM25");
        
        printf("  CO2: %.2f ppm", predCO2);
        if (predCO2 > UMBRAL_CO2_ALERTA) printf(" [ALERTA]");
        else if (predCO2 > UMBRAL_CO2_PRECAUCION) printf(" [PRECAUCIÓN]");
        printf("\n");
        
        printf("  SO2: %.2f µg/m³", predSO2);
        if (predSO2 > UMBRAL_SO2_ALERTA) printf(" [ALERTA]");
        else if (predSO2 > UMBRAL_SO2_PRECAUCION) printf(" [PRECAUCIÓN]");
        printf("\n");
        
        printf("  NO2: %.2f µg/m³", predNO2);
        if (predNO2 > UMBRAL_NO2_ALERTA) printf(" [ALERTA]");
        else if (predNO2 > UMBRAL_NO2_PRECAUCION) printf(" [PRECAUCIÓN]");
        printf("\n");
        
        printf("  PM2.5: %.2f µg/m³", predPM25);
        if (predPM25 > UMBRAL_PM25_ALERTA) printf(" [ALERTA]");
        else if (predPM25 > UMBRAL_PM25_PRECAUCION) printf(" [PRECAUCIÓN]");
        printf("\n");
        
        printf("---------------------------------------------------------\n");
    }
}

void generarAlertas(struct ZonaMonitoreo zonas[], int numZonas){
    struct Alerta alertas[100];
    int numAlertas = 0;
    
    printf("\n=== SISTEMA DE ALERTAS ===\n");
    printf("=============================\n");
    
    for (int i = 0; i < numZonas; i++) {
        // Verificar CO2
        if (zonas[i].contaminantes.co2 > UMBRAL_CO2_PRECAUCION) {
            alertas[numAlertas].id = numAlertas + 1;
            alertas[numAlertas].zonaId = zonas[i].id;
            strcpy(alertas[numAlertas].tipoContaminante, "CO2");
            alertas[numAlertas].valorActual = zonas[i].contaminantes.co2;
            
            if (zonas[i].contaminantes.co2 > UMBRAL_CO2_EMERGENCIA) {
                alertas[numAlertas].umbralCritico = UMBRAL_CO2_EMERGENCIA;
                strcpy(alertas[numAlertas].nivelAlerta, "EMERGENCIA");
                sprintf(alertas[numAlertas].mensaje, "EMERGENCIA: CO2 extremadamente alto en %s. Evacuar área inmediatamente.", zonas[i].nombre);
            } else if (zonas[i].contaminantes.co2 > UMBRAL_CO2_ALERTA) {
                alertas[numAlertas].umbralCritico = UMBRAL_CO2_ALERTA;
                strcpy(alertas[numAlertas].nivelAlerta, "ALERTA");
                sprintf(alertas[numAlertas].mensaje, "ALERTA: Niveles altos de CO2 en %s. Evitar actividades al aire libre.", zonas[i].nombre);
            } else {
                alertas[numAlertas].umbralCritico = UMBRAL_CO2_PRECAUCION;
                strcpy(alertas[numAlertas].nivelAlerta, "PRECAUCIÓN");
                sprintf(alertas[numAlertas].mensaje, "PRECAUCIÓN: CO2 elevado en %s. Monitorear continuamente.", zonas[i].nombre);
            }
            
            obtenerFechaHora(alertas[numAlertas].fecha, alertas[numAlertas].hora);
            numAlertas++;
        }
        
        // Verificar SO2
        if (zonas[i].contaminantes.so2 > UMBRAL_SO2_PRECAUCION) {
            alertas[numAlertas].id = numAlertas + 1;
            alertas[numAlertas].zonaId = zonas[i].id;
            strcpy(alertas[numAlertas].tipoContaminante, "SO2");
            alertas[numAlertas].valorActual = zonas[i].contaminantes.so2;
            
            if (zonas[i].contaminantes.so2 > UMBRAL_SO2_EMERGENCIA) {
                alertas[numAlertas].umbralCritico = UMBRAL_SO2_EMERGENCIA;
                strcpy(alertas[numAlertas].nivelAlerta, "EMERGENCIA");
                sprintf(alertas[numAlertas].mensaje, "EMERGENCIA: SO2 peligroso en %s. Riesgo respiratorio extremo.", zonas[i].nombre);
            } else if (zonas[i].contaminantes.so2 > UMBRAL_SO2_ALERTA) {
                alertas[numAlertas].umbralCritico = UMBRAL_SO2_ALERTA;
                strcpy(alertas[numAlertas].nivelAlerta, "ALERTA");
                sprintf(alertas[numAlertas].mensaje, "ALERTA: SO2 alto en %s. Personas sensibles evitar exposición.", zonas[i].nombre);
            } else {
                alertas[numAlertas].umbralCritico = UMBRAL_SO2_PRECAUCION;
                strcpy(alertas[numAlertas].nivelAlerta, "PRECAUCIÓN");
                sprintf(alertas[numAlertas].mensaje, "PRECAUCIÓN: SO2 moderado en %s.", zonas[i].nombre);
            }
            
            obtenerFechaHora(alertas[numAlertas].fecha, alertas[numAlertas].hora);
            numAlertas++;
        }
        
        // Verificar NO2
        if (zonas[i].contaminantes.no2 > UMBRAL_NO2_PRECAUCION) {
            alertas[numAlertas].id = numAlertas + 1;
            alertas[numAlertas].zonaId = zonas[i].id;
            strcpy(alertas[numAlertas].tipoContaminante, "NO2");
            alertas[numAlertas].valorActual = zonas[i].contaminantes.no2;
            
            if (zonas[i].contaminantes.no2 > UMBRAL_NO2_EMERGENCIA) {
                alertas[numAlertas].umbralCritico = UMBRAL_NO2_EMERGENCIA;
                strcpy(alertas[numAlertas].nivelAlerta, "EMERGENCIA");
                sprintf(alertas[numAlertas].mensaje, "EMERGENCIA: NO2 crítico en %s. Cerrar ventanas y permanecer en interiores.", zonas[i].nombre);
            } else if (zonas[i].contaminantes.no2 > UMBRAL_NO2_ALERTA) {
                alertas[numAlertas].umbralCritico = UMBRAL_NO2_ALERTA;
                strcpy(alertas[numAlertas].nivelAlerta, "ALERTA");
                sprintf(alertas[numAlertas].mensaje, "ALERTA: NO2 elevado en %s. Limitar ejercicio al aire libre.", zonas[i].nombre);
            } else {
                alertas[numAlertas].umbralCritico = UMBRAL_NO2_PRECAUCION;
                strcpy(alertas[numAlertas].nivelAlerta, "PRECAUCIÓN");
                sprintf(alertas[numAlertas].mensaje, "PRECAUCIÓN: NO2 en aumento en %s.", zonas[i].nombre);
            }
            
            obtenerFechaHora(alertas[numAlertas].fecha, alertas[numAlertas].hora);
            numAlertas++;
        }
        
        // Verificar PM2.5
        if (zonas[i].contaminantes.pm25 > UMBRAL_PM25_PRECAUCION) {
            alertas[numAlertas].id = numAlertas + 1;
            alertas[numAlertas].zonaId = zonas[i].id;
            strcpy(alertas[numAlertas].tipoContaminante, "PM25");
            alertas[numAlertas].valorActual = zonas[i].contaminantes.pm25;
            
            if (zonas[i].contaminantes.pm25 > UMBRAL_PM25_EMERGENCIA) {
                alertas[numAlertas].umbralCritico = UMBRAL_PM25_EMERGENCIA;
                strcpy(alertas[numAlertas].nivelAlerta, "EMERGENCIA");
                sprintf(alertas[numAlertas].mensaje, "EMERGENCIA: PM2.5 peligroso en %s. Usar mascarillas N95.", zonas[i].nombre);
            } else if (zonas[i].contaminantes.pm25 > UMBRAL_PM25_ALERTA) {
                alertas[numAlertas].umbralCritico = UMBRAL_PM25_ALERTA;
                strcpy(alertas[numAlertas].nivelAlerta, "ALERTA");
                sprintf(alertas[numAlertas].mensaje, "ALERTA: PM2.5 insalubre en %s. Grupos sensibles evitar salir.", zonas[i].nombre);
            } else {
                alertas[numAlertas].umbralCritico = UMBRAL_PM25_PRECAUCION;
                strcpy(alertas[numAlertas].nivelAlerta, "PRECAUCIÓN");
                sprintf(alertas[numAlertas].mensaje, "PRECAUCIÓN: PM2.5 moderado en %s.", zonas[i].nombre);
            }
            
            obtenerFechaHora(alertas[numAlertas].fecha, alertas[numAlertas].hora);
            numAlertas++;
        }
    }
    
    if (numAlertas > 0) {
        mostrarAlertas(alertas, numAlertas);
        guardarAlertas(alertas, numAlertas);
        printf("Se generaron %d alertas.\n", numAlertas);
    } else {
        printf("✓ Todas las zonas están dentro de los parámetros normales.\n");
    }
}

void mostrarAlertas(struct Alerta alertas[], int numAlertas){
    printf("\n=== ALERTAS GENERADAS ===\n");
    printf("==========================\n");
    for (int i = 0; i < numAlertas; i++) {
        printf("🚨 ALERTA ID: %d\n", alertas[i].id);
        printf("Zona ID: %d | Contaminante: %s\n", alertas[i].zonaId, alertas[i].tipoContaminante);
        printf("Nivel: %s\n", alertas[i].nivelAlerta);
        printf("Valor actual: %.2f | Umbral: %.2f\n", alertas[i].valorActual, alertas[i].umbralCritico);
        printf("Mensaje: %s\n", alertas[i].mensaje);
        printf("Fecha/Hora: %s %s\n", alertas[i].fecha, alertas[i].hora);
        printf("--------------------------\n");
    }
}

void guardarAlertas(struct Alerta alertas[], int numAlertas){
    FILE *archivo = fopen("alertas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar alertas.\n");
        return;
    }
    fwrite(alertas, sizeof(struct Alerta), numAlertas, archivo);
    fclose(archivo);
}

int cargarAlertas(struct Alerta alertas[], int *numAlertas){
    FILE *archivo = fopen("alertas.dat", "rb");
    if (archivo == NULL) {
        *numAlertas = 0;
        return 0;
    }
    *numAlertas = fread(alertas, sizeof(struct Alerta), 100, archivo);
    fclose(archivo);
    return 1;
}

void generarReporte(struct ZonaMonitoreo zonas[], int numZonas, struct RegistroHistorico registros[], int numRegistros){
    printf("\n========================================\n");
    printf("       REPORTE COMPLETO DE CONTAMINACIÓN\n");
    printf("========================================\n");
    
    // Estadísticas generales
    printf("\n=== ESTADÍSTICAS GENERALES ===\n");
    printf("Total de zonas monitoreadas: %d\n", numZonas);
    printf("Total de registros históricos: %d\n", numRegistros);
    
    // Promedios por contaminante
    float promCO2 = 0, promSO2 = 0, promNO2 = 0, promPM25 = 0;
    for (int i = 0; i < numZonas; i++) {
        promCO2 += zonas[i].contaminantes.co2;
        promSO2 += zonas[i].contaminantes.so2;
        promNO2 += zonas[i].contaminantes.no2;
        promPM25 += zonas[i].contaminantes.pm25;
    }
    
    if (numZonas > 0) {
        promCO2 /= numZonas;
        promSO2 /= numZonas;
        promNO2 /= numZonas;
        promPM25 /= numZonas;
        
        printf("\n=== PROMEDIOS ACTUALES ===\n");
        printf("CO2: %.2f ppm\n", promCO2);
        printf("SO2: %.2f µg/m³\n", promSO2);
        printf("NO2: %.2f µg/m³\n", promNO2);
        printf("PM2.5: %.2f µg/m³\n", promPM25);
    }
    
    // Zona más contaminada
    printf("\n=== ANÁLISIS POR ZONA ===\n");
    int zonaMasContaminada = 0;
    float mayorContaminacion = 0;
    
    for (int i = 0; i < numZonas; i++) {
        float nivelContaminacion = zonas[i].contaminantes.co2/1000 + 
                                 zonas[i].contaminantes.so2/100 + 
                                 zonas[i].contaminantes.no2/200 + 
                                 zonas[i].contaminantes.pm25/50;
        
        if (nivelContaminacion > mayorContaminacion) {
            mayorContaminacion = nivelContaminacion;
            zonaMasContaminada = i;
        }
        
        printf("Zona %s: Índice de contaminación = %.2f\n", 
               zonas[i].nombre, nivelContaminacion);
    }
    
    if (numZonas > 0) {
        printf("\n🔴 ZONA MÁS CONTAMINADA: %s\n", zonas[zonaMasContaminada].nombre);
        printf("Índice de contaminación: %.2f\n", mayorContaminacion);
    }
    
    // Recomendaciones
    printf("\n=== RECOMENDACIONES ===\n");
    if (promCO2 > UMBRAL_CO2_ALERTA) {
        printf("⚠️  CO2: Implementar restricciones vehiculares\n");
    }
    if (promSO2 > UMBRAL_SO2_ALERTA) {
        printf("⚠️  SO2: Revisar emisiones industriales\n");
    }
    if (promNO2 > UMBRAL_NO2_ALERTA) {
        printf("⚠️  NO2: Controlar tráfico en horas pico\n");
    }
    if (promPM25 > UMBRAL_PM25_ALERTA) {
        printf("⚠️  PM2.5: Alertar sobre actividades al aire libre\n");
    }
    
    // Generar alertas automáticamente
    printf("\n=== VERIFICACIÓN DE ALERTAS ===\n");
    generarAlertas(zonas, numZonas);
    
    printf("\n========================================\n");
    printf("       FIN DEL REPORTE\n");
    printf("========================================\n");
}

void exportarDatos(struct ZonaMonitoreo zonas[], int numZonas){
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo de exportación.\n");
        return;
    }
    
    fprintf(archivo, "REPORTE DE CONTAMINACIÓN DEL AIRE\n");
    fprintf(archivo, "==================================\n\n");
    
    char fecha[20], hora[10];
    obtenerFechaHora(fecha, hora);
    fprintf(archivo, "Fecha de generación: %s %s\n\n", fecha, hora);
    
    for (int i = 0; i < numZonas; i++) {
        fprintf(archivo, "ZONA: %s\n", zonas[i].nombre);
        fprintf(archivo, "Ubicación: %s\n", zonas[i].ubicacion);
        fprintf(archivo, "Última actualización: %s %s\n", zonas[i].fecha, zonas[i].hora);
        fprintf(archivo, "Contaminantes:\n");
        fprintf(archivo, "  CO2: %.2f ppm\n", zonas[i].contaminantes.co2);
        fprintf(archivo, "  SO2: %.2f µg/m³\n", zonas[i].contaminantes.so2);
        fprintf(archivo, "  NO2: %.2f µg/m³\n", zonas[i].contaminantes.no2);
        fprintf(archivo, "  PM2.5: %.2f µg/m³\n", zonas[i].contaminantes.pm25);
        fprintf(archivo, "Factores Climáticos:\n");
        fprintf(archivo, "  Temperatura: %.1f°C\n", zonas[i].factoresClimaticos.temperatura);
        fprintf(archivo, "  Humedad: %.1f%%\n", zonas[i].factoresClimaticos.humedad);
        fprintf(archivo, "  Viento: %.1f km/h (%s)\n", 
                zonas[i].factoresClimaticos.velocidadViento, 
                zonas[i].factoresClimaticos.direccionViento);
        fprintf(archivo, "----------------------------------------\n\n");
    }
    
    fclose(archivo);
    printf("Datos exportados exitosamente a 'reporte_contaminacion.txt'\n");
}

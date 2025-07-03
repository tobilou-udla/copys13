# Sistema de Monitoreo de Calidad del Aire

## Descripción

Sistema integral de monitoreo y predicción de contaminación del aire diseñado para ayudar a las autoridades a tomar decisiones oportunas para proteger la salud pública y el medio ambiente en zonas urbanas.

## Características Principales

### 1. Monitoreo en Tiempo Real
- Tracking de múltiples contaminantes: CO2, SO2, NO2, PM2.5
- Monitoreo de múltiples zonas urbanas
- Almacenamiento de datos históricos

### 2. Sistema de Predicción
- Algoritmos de predicción basados en promedios ponderados
- Análisis de tendencias históricas
- Predicción de niveles futuros de contaminación

### 3. Sistema de Alertas
- Clasificación automática de niveles: Normal, Moderado, Peligroso
- Alertas basadas en umbrales de la OMS
- Generación automática de alertas según predicciones

### 4. Sistema de Recomendaciones
- Recomendaciones específicas por tipo de contaminante
- Guías de acción para diferentes niveles de alerta
- Recomendaciones para autoridades y población

### 5. Reportes Completos
- Análisis estadístico de datos
- Resúmenes por zona de monitoreo
- Reportes de alertas activas
- Recomendaciones generales

## Estructura del Sistema

### Estructuras de Datos

- **LecturaPolucion**: Almacena lecturas de contaminación con timestamp, zona y niveles de contaminantes
- **ZonaMonitoreo**: Representa áreas de monitoreo con ubicación e historial
- **Alerta**: Contiene alertas generadas con niveles y recomendaciones

### Funcionalidades del Menú

1. **Crear datos de contaminación**: Genera datos de ejemplo para testing
2. **Crear zonas de monitoreo**: Establece zonas urbanas de monitoreo
3. **Listar lecturas**: Visualiza datos históricos de contaminación
4. **Listar zonas**: Muestra información de zonas monitoreadas
5. **Generar predicciones**: Ejecuta algoritmos de predicción y genera alertas
6. **Ver alertas**: Muestra alertas activas con recomendaciones
7. **Generar reporte completo**: Crea reporte integral del sistema
8. **Salir**: Termina el programa

## Umbrales de Contaminación

El sistema utiliza umbrales basados en estándares internacionales:

### CO2 (ppm)
- Normal: < 400
- Moderado: 400-1000
- Peligroso: > 1000

### SO2 (ppm)
- Normal: < 20
- Moderado: 20-80
- Peligroso: > 80

### NO2 (ppm)
- Normal: < 40
- Moderado: 40-100
- Peligroso: > 100

### PM2.5 (µg/m³)
- Normal: < 12
- Moderado: 12-35
- Peligroso: > 35

## Algoritmo de Predicción

El sistema utiliza un algoritmo de **promedio ponderado** que:
- Asigna mayor peso a lecturas más recientes
- Calcula tendencias por zona y contaminante
- Genera predicciones para la próxima lectura

## Compilación y Ejecución

```bash
# Compilar el programa
gcc -o main main.c funciones.c -Wall -Wextra

# Ejecutar el sistema
./main
```

## Flujo de Trabajo Recomendado

1. **Configuración inicial**:
   - Crear zonas de monitoreo
   - Generar datos de contaminación iniciales

2. **Operación diaria**:
   - Revisar lecturas actuales
   - Generar predicciones
   - Verificar alertas
   - Generar reportes

3. **Análisis periódico**:
   - Generar reportes completos
   - Analizar tendencias
   - Actualizar recomendaciones

## Beneficios para Autoridades

- **Detección temprana**: Identificación proactiva de problemas
- **Toma de decisiones informada**: Datos históricos y predictivos
- **Gestión integrada**: Sistema completo de monitoreo y alertas
- **Comunicación efectiva**: Reportes claros y recomendaciones específicas

## Impacto en Salud Pública

- Protección de poblaciones vulnerables
- Prevención de crisis ambientales
- Educación y concientización ciudadana
- Mejora de políticas ambientales urbanas
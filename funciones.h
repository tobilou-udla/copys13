// Estructura para lecturas de contaminación
struct LecturaPolucion
{
    int id;
    int zona_id;
    char fecha[20];
    float co2;    // CO2 en ppm
    float so2;    // SO2 en ppm
    float no2;    // NO2 en ppm
    float pm25;   // PM2.5 en µg/m³
};

// Estructura para zonas de monitoreo
struct ZonaMonitoreo
{
    int id;
    char nombre[50];
    char ubicacion[100];
    struct LecturaPolucion lecturas[24]; // 24 lecturas históricas (últimas 24 horas)
    int num_lecturas;
};

// Estructura para alertas y recomendaciones
struct Alerta
{
    int id;
    int zona_id;
    char tipo_contaminante[10];
    float nivel_actual;
    float nivel_predicho;
    char nivel_alerta[20];  // "Normal", "Moderado", "Peligroso"
    char recomendacion[200];
    char fecha[20];
};

// Funciones para manejo de datos de contaminación
void leerCadena(char *cadena, int num);
void crearDatosPolucion();
void crearZonasMonitoreo();
void imprimirZonas(struct ZonaMonitoreo zonas[], int numZonas);
void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas);
int leerZonas(struct ZonaMonitoreo zonas[], int *numZonas);
void generarPredicciones();
void imprimirAlertas(struct Alerta alertas[], int numAlertas);
void guardarAlertas(struct Alerta alertas[], int numAlertas);
int leerAlertas(struct Alerta alertas[], int *numAlertas);
int menu();
void imprimirLecturas(struct LecturaPolucion lecturas[], int numLecturas);
void guardarLecturas(struct LecturaPolucion lecturas[], int numLecturas);
int cargarLecturas(struct LecturaPolucion lecturas[], int *numLecturas);
void generarReporte();
float calcularPrediccion(struct LecturaPolucion lecturas[], int numLecturas, char* contaminante);
void verificarUmbrales(struct ZonaMonitoreo zonas[], int numZonas);
char* obtenerRecomendacion(char* contaminante, float nivel);

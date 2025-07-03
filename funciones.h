// Estructura para almacenar datos de contaminantes
struct Contaminante
{
    float co2;      // Dióxido de carbono (ppm)
    float so2;      // Dióxido de azufre (µg/m³)
    float no2;      // Dióxido de nitrógeno (µg/m³)
    float pm25;     // Partículas PM2.5 (µg/m³)
};

// Estructura para factores climáticos
struct FactoresClimaticos
{
    float temperatura;    // Temperatura (°C)
    float humedad;       // Humedad relativa (%)
    float velocidadViento; // Velocidad del viento (km/h)
    char direccionViento[10]; // Dirección del viento
};

// Estructura para una zona de monitoreo
struct ZonaMonitoreo
{
    int id;
    char nombre[50];
    char ubicacion[100];
    struct Contaminante contaminantes;
    struct FactoresClimaticos factoresClimaticos;
    char fecha[20];      // Fecha de la medición
    char hora[10];       // Hora de la medición
};

// Estructura para almacenar datos históricos
struct RegistroHistorico
{
    int id;
    int zonaId;
    struct Contaminante contaminantes;
    struct FactoresClimaticos factoresClimaticos;
    char fecha[20];
    char hora[10];
};

// Estructura para alertas
struct Alerta
{
    int id;
    int zonaId;
    char tipoContaminante[10];
    float valorActual;
    float umbralCritico;
    char nivelAlerta[20];  // NORMAL, PRECAUCION, ALERTA, EMERGENCIA
    char mensaje[200];
    char fecha[20];
    char hora[10];
};

// Funciones principales del sistema de monitoreo de contaminación
void leerCadena(char *cadena, int num);
void obtenerFechaHora(char *fecha, char *hora);
int menu();

// Funciones para manejo de zonas de monitoreo
void crearZonasMonitoreo();
void registrarLectura();
void mostrarZonas(struct ZonaMonitoreo zonas[], int numZonas);
void guardarZonas(struct ZonaMonitoreo zonas[], int numZonas);
int cargarZonas(struct ZonaMonitoreo zonas[], int *numZonas);

// Funciones para manejo de datos históricos
void guardarRegistroHistorico(struct RegistroHistorico registros[], int numRegistros);
int cargarRegistroHistorico(struct RegistroHistorico registros[], int *numRegistros);
void mostrarHistorico(struct RegistroHistorico registros[], int numRegistros);

// Funciones de predicción
float calcularPromedioRomano(struct RegistroHistorico registros[], int numRegistros, int zonaId, char tipoContaminante[]);
void generarPrediccion(struct ZonaMonitoreo zonas[], int numZonas);

// Funciones de alertas
void generarAlertas(struct ZonaMonitoreo zonas[], int numZonas);
void mostrarAlertas(struct Alerta alertas[], int numAlertas);
void guardarAlertas(struct Alerta alertas[], int numAlertas);
int cargarAlertas(struct Alerta alertas[], int *numAlertas);

// Funciones de reportes
void generarReporte(struct ZonaMonitoreo zonas[], int numZonas, struct RegistroHistorico registros[], int numRegistros);
void exportarDatos(struct ZonaMonitoreo zonas[], int numZonas);

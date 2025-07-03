struct Jugador
{
    int id;
    char nombre[50];
    char posicion[20];
    int goles;
};

struct Equipo
{
    int id;
    char nombre[50];
    struct Jugador jugadores[6];
};

struct Partido
{
    int id;
    struct Equipo equipo1;
    struct Equipo equipo2;
    int golesEquipo1;
    int golesEquipo2;
};

void leerCadena(char *cadena, int num);
void crearJugadores();
void crearEquipos();
void imprimirEquipos(struct Equipo equipos[], int numEquipos);
void guardarEquipos(struct Equipo equipos[], int numEquipos);
int leerEquipos(struct Equipo equipos[], int *numEquipos);
void crearPartidos();
void imprimirPartidos(struct Partido partidos[4], int numPartidos);
void guardarPartidos(struct Partido partidos[4], int numPartidos);
int leerPartidos(struct Partido partidos[4], int *numPartidos);
int menu();
void imprimirJugadores(struct Jugador jugadores[], int numJugadores);
void guardarJugadores(struct Jugador jugadores[], int numJugadores);
int cargarJugadores(struct Jugador jugadores[], int *numJugadores);

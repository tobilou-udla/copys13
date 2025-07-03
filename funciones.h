struct Empleado
{
    int id;
    char nombre[50];
    char puesto[30];
    float salario;
    int departamentoId;
    char fechaIngreso[12];
    int diasVacaciones;
    int horasExtras;
};

struct Departamento
{
    int id;
    char nombre[50];
    int numEmpleados;
    struct Empleado empleados[20];
};

struct Asistencia
{
    int id;
    int empleadoId;
    char fecha[12];
    char horaEntrada[10];
    char horaSalida[10];
    int minutosAtraso;
};

void leerCadena(char *cadena, int num);
void crearEmpleados();
void crearDepartamentos();
void imprimirDepartamentos(struct Departamento departamentos[], int numDepartamentos);
void guardarDepartamentos(struct Departamento departamentos[], int numDepartamentos);
int leerDepartamentos(struct Departamento departamentos[], int *numDepartamentos);
void registrarAsistencia();
void imprimirAsistencias(struct Asistencia asistencias[], int numAsistencias);
void guardarAsistencias(struct Asistencia asistencias[], int numAsistencias);
int leerAsistencias(struct Asistencia asistencias[], int *numAsistencias);
int menu();
void imprimirEmpleados(struct Empleado empleados[], int numEmpleados);
void guardarEmpleados(struct Empleado empleados[], int numEmpleados);
int cargarEmpleados(struct Empleado empleados[], int *numEmpleados);
void consultarVacaciones();
void procesarNomina();

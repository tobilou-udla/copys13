# Sistema Integrado de Gestión de Recursos Humanos (SIGRH)

## Descripción
Sistema integral de gestión de recursos humanos desarrollado en C, diseñado para abordar los desafíos en la gestión del talento humano en empresas medianas y grandes. El sistema proporciona herramientas para el control de vacaciones, registro de asistencias, monitoreo de atrasos y visualización de información salarial.

## Características Principales

### 1. Gestión de Personal
- **Registro de Empleados**: Almacena información completa de empleados incluyendo datos personales, puesto, salario, departamento, fecha de ingreso, días de vacaciones y horas extras.
- **Organización por Departamentos**: Gestión departamental con asignación automática de empleados.

### 2. Control de Asistencia
- **Registro de Entrada/Salida**: Seguimiento detallado de horarios de trabajo.
- **Monitoreo de Atrasos**: Identificación automática de empleados con llegadas tardías.
- **Alertas de Cumplimiento**: Notificaciones visuales para empleados con atrasos.

### 3. Gestión de Vacaciones
- **Consulta de Días Disponibles**: Visualización de días de vacaciones acumulados por empleado.
- **Alertas de Gestión**: Identificación de empleados con exceso o escasez de días de vacaciones.
- **Histórico de Ingresos**: Información de antigüedad para cálculo de beneficios.

### 4. Compensaciones y Nómina
- **Cálculo Automático**: Procesamiento de salarios base más horas extras.
- **Reportes Individuales**: Desglose detallado por empleado.
- **Total de Nómina**: Cálculo del costo total mensual de personal.

### 5. Reportes y Análisis
- **Informes Departamentales**: Listado de empleados por departamento.
- **Análisis de Asistencia**: Reportes de puntualidad y asistencia.
- **Indicadores de Vacaciones**: Seguimiento de políticas de descanso.

## Módulos del Sistema

### Módulo de Empleados
- Crear y gestionar registros de empleados
- Consultar información personal y laboral
- Actualizar datos de personal

### Módulo de Departamentos
- Organización departamental
- Asignación automática de empleados
- Reportes por departamento

### Módulo de Asistencia
- Registro de horarios de entrada y salida
- Cálculo automático de atrasos
- Alertas de cumplimiento

### Módulo de Vacaciones
- Consulta de días disponibles
- Identificación de casos especiales
- Análisis de tendencias

### Módulo de Nómina
- Cálculo de salarios base
- Procesamiento de horas extras
- Reportes de compensación total

## Compilación y Uso

### Requisitos
- Compilador GCC
- Sistema operativo compatible con C ANSI

### Compilación
```bash
gcc -o sigrh main.c funciones.c -Wall -Wextra
```

### Ejecución
```bash
./sigrh
```

### Menú Principal
El sistema presenta las siguientes opciones:

1. **Crear Empleados**: Genera base de datos inicial con empleados de ejemplo
2. **Crear Departamentos**: Organiza empleados por departamentos
3. **Listar Empleados**: Muestra información completa de todos los empleados
4. **Listar Departamentos**: Visualiza estructura organizacional
5. **Registrar Asistencia**: Crea registros de asistencia con horarios
6. **Listar Asistencias**: Muestra registros de entrada/salida y atrasos
7. **Consultar Vacaciones**: Analiza días de vacaciones por empleado
8. **Procesar Nómina**: Calcula salarios y genera reporte de costos
9. **Salir**: Termina la aplicación

## Estructura de Datos

### Empleado
```c
struct Empleado {
    int id;                    // Identificador único
    char nombre[50];           // Nombre completo
    char puesto[30];           // Cargo o posición
    float salario;             // Salario base mensual
    int departamentoId;        // ID del departamento
    char fechaIngreso[12];     // Fecha de contratación
    int diasVacaciones;        // Días de vacaciones acumulados
    int horasExtras;           // Horas extras del mes
};
```

### Departamento
```c
struct Departamento {
    int id;                           // Identificador único
    char nombre[50];                  // Nombre del departamento
    int numEmpleados;                 // Cantidad de empleados
    struct Empleado empleados[20];    // Array de empleados
};
```

### Asistencia
```c
struct Asistencia {
    int id;                    // Identificador único
    int empleadoId;            // ID del empleado
    char fecha[12];            // Fecha del registro
    char horaEntrada[10];      // Hora de entrada
    char horaSalida[10];       // Hora de salida
    int minutosAtraso;         // Minutos de retraso
};
```

## Características Técnicas

### Persistencia de Datos
- Archivos binarios para almacenamiento eficiente
- Separación de datos por módulo (empleados.dat, departamentos.dat, asistencias.dat)
- Carga automática de datos al iniciar

### Validaciones
- Verificación de IDs válidos
- Validación de rangos de datos
- Manejo de errores de archivo

### Alertas y Notificaciones
- Identificación visual de empleados con atrasos
- Alertas de vacaciones excesivas o insuficientes
- Notificaciones de procesamiento exitoso

## Beneficios del Sistema

### Eficiencia Operativa
- Automatización de cálculos manuales
- Reducción de errores humanos
- Rapidez en la generación de reportes

### Transparencia
- Información clara y accesible
- Trazabilidad de datos
- Reportes detallados

### Cumplimiento Normativo
- Seguimiento de horarios laborales
- Control de vacaciones
- Documentación de compensaciones

### Toma de Decisiones
- Análisis de costos de personal
- Identificación de patrones de asistencia
- Planificación de recursos humanos

## Futuras Mejoras

### Fase 2 - Expansión
- Interfaz web para administración
- Aplicación móvil para empleados
- Base de datos SQL
- Reportes avanzados con gráficos

### Fase 3 - Integración
- Sistema de notificaciones automáticas
- Integración con sistemas de nómina externos
- API para terceros
- Análisis predictivo

## Licencia
Este sistema está desarrollado con fines educativos y de demostración. Para uso comercial, contactar al desarrollador.

## Contacto
Para soporte técnico o consultas sobre el sistema, contactar al equipo de desarrollo.
# Sistema Integrado de Gestión de Recursos Humanos (SIGRH)

## Descripción

El Sistema Integrado de Gestión de Recursos Humanos (SIGRH) es una solución completa para la gestión de empleados, horarios, vacaciones, nóminas y control de asistencia biométrica. El sistema está diseñado con una arquitectura modular que permite escalabilidad y mantenimiento eficiente.

## Características Principales

### 🗄️ Base de Datos Centralizada
- Diseño relacional con tablas para empleados, horarios, vacaciones y compensaciones
- Claves primarias y relaciones para garantizar integridad de datos
- Soporte para SQLite, PostgreSQL y MySQL

### 🏗️ Arquitectura Modular
- **Gestión de Empleados**: CRUD completo para información de empleados
- **Control de Horarios**: Configuración y gestión de horarios de trabajo
- **Gestión de Vacaciones**: Solicitudes, aprobaciones y seguimiento
- **Sistema de Nómina**: Cálculo de salarios, bonificaciones y deducciones
- **Control Biométrico**: Registro de asistencia con dispositivos biométricos

### 🌐 Interfaces Múltiples
- **Portal Web Administrativo**: Interfaz completa para administradores
- **API REST**: Servicios web para integración con otras aplicaciones
- **API Móvil**: Servicios específicos para aplicaciones móviles

### 📬 Sistema de Notificaciones
- Notificaciones por correo electrónico (SMTP)
- Notificaciones por SMS (Twilio/Amazon SNS)
- Plantillas personalizables para diferentes tipos de notificaciones

## Estructura del Proyecto

```
sigrh/
├── modules/                    # Módulos funcionales
│   ├── employees/             # Gestión de empleados
│   ├── schedules/             # Gestión de horarios
│   ├── vacations/             # Gestión de vacaciones
│   ├── payroll/               # Gestión de nómina
│   └── biometrics/            # Control biométrico
├── interfaces/                # Interfaces de usuario
│   ├── web/                   # Portal web administrativo
│   └── mobile/                # API móvil
├── notifications/             # Sistema de notificaciones
│   ├── email/                 # Notificaciones por email
│   └── sms/                   # Notificaciones por SMS
├── database/                  # Esquemas y datos de ejemplo
├── config/                    # Configuración del sistema
└── main.py                    # Aplicación principal
```

## Instalación

1. **Clonar el repositorio**
   ```bash
   git clone https://github.com/tobilou-udla/copys13.git
   cd copys13
   ```

2. **Crear entorno virtual**
   ```bash
   python -m venv venv
   source venv/bin/activate  # En Windows: venv\Scripts\activate
   ```

3. **Instalar dependencias**
   ```bash
   cd sigrh
   pip install -r requirements.txt
   ```

4. **Configurar variables de entorno**
   ```bash
   cp config/.env.example config/.env
   # Editar config/.env con tus configuraciones
   ```

5. **Inicializar base de datos**
   ```bash
   # El sistema creará automáticamente la base de datos SQLite
   # Para otros motores, configurar DATABASE_TYPE en .env
   ```

## Uso

### Aplicación de Consola

```bash
cd sigrh
python main.py
```

### Portal Web Administrativo

```bash
cd sigrh/interfaces/web
python app.py
```

El portal estará disponible en: http://localhost:5000

### API Móvil

```bash
cd sigrh/interfaces/mobile
python mobile_api.py
```

La API móvil estará disponible en: http://localhost:8000
Documentación: http://localhost:8000/docs

## Configuración

### Base de Datos

El sistema soporta múltiples tipos de base de datos:

- **SQLite** (por defecto): Ideal para desarrollo y pruebas
- **PostgreSQL**: Para producción con alta concurrencia
- **MySQL**: Alternativa robusta para producción

### Notificaciones

#### Email
- Configurar servidor SMTP en variables de entorno
- Soporta Gmail, Outlook, y servidores SMTP personalizados

#### SMS
- **Twilio**: Proveedor principal de SMS
- **Amazon SNS**: Alternativa para entornos AWS

### Seguridad

- Autenticación JWT para APIs
- Encriptación de contraseñas
- Configuración de intentos de login
- Tiempo de bloqueo configurable

## Módulos Principales

### 👥 Gestión de Empleados
- Crear, leer, actualizar y eliminar empleados
- Gestión de información personal y laboral
- Búsqueda y filtrado avanzado

### 🕒 Control de Asistencia
- Registro biométrico de entrada y salida
- Cálculo automático de horas trabajadas
- Detección de tardanzas y ausencias
- Reportes de asistencia

### 📅 Gestión de Horarios
- Configuración de horarios por empleado
- Horarios flexibles y rotativos
- Validación de conflictos
- Cálculo de horas semanales

### 🏖️ Gestión de Vacaciones
- Solicitudes de vacaciones
- Proceso de aprobación
- Cálculo de balance de vacaciones
- Calendario de vacaciones

### 💰 Gestión de Nómina
- Cálculo de salarios base
- Bonificaciones y deducciones
- Cálculo de impuestos
- Generación de comprobantes

## API Endpoints

### Empleados
- `GET /api/employees` - Listar empleados
- `POST /api/employees` - Crear empleado
- `GET /api/employees/{id}` - Obtener empleado
- `PUT /api/employees/{id}` - Actualizar empleado
- `DELETE /api/employees/{id}` - Eliminar empleado

### Asistencia
- `POST /api/attendance/checkin` - Registrar entrada
- `POST /api/attendance/checkout` - Registrar salida
- `GET /api/attendance/history/{employee_id}` - Historial de asistencia

### Vacaciones
- `POST /api/vacations` - Solicitar vacaciones
- `GET /api/vacations/pending` - Solicitudes pendientes
- `POST /api/vacations/{id}/approve` - Aprobar solicitud
- `POST /api/vacations/{id}/reject` - Rechazar solicitud

### Nómina
- `POST /api/payroll/{employee_id}/generate` - Generar nómina
- `GET /api/payroll/{employee_id}/history` - Historial de nómina

## Contribución

1. Fork el repositorio
2. Crear una rama para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. Commit tus cambios (`git commit -am 'Agregar nueva funcionalidad'`)
4. Push a la rama (`git push origin feature/nueva-funcionalidad`)
5. Crear un Pull Request

## Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo `LICENSE` para más detalles.

## Soporte

Para soporte técnico o preguntas sobre el sistema:

- Crear un issue en GitHub
- Enviar email a: soporte@sigrh.com
- Documentación completa: [Wiki del proyecto](https://github.com/tobilou-udla/copys13/wiki)

## Roadmap

### Versión 1.1 (Próxima)
- [ ] Integración con Active Directory
- [ ] Reportes avanzados con gráficos
- [ ] Aplicación móvil nativa
- [ ] Integración con sistemas de planilla externos

### Versión 1.2 (Futura)
- [ ] Módulo de evaluación de desempeño
- [ ] Sistema de capacitación y certificaciones
- [ ] Inteligencia artificial para predicción de ausentismo
- [ ] Dashboard ejecutivo en tiempo real

---

**Desarrollado con ❤️ para modernizar la gestión de recursos humanos**
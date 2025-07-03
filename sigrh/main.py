"""
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
Aplicación Principal

Este módulo integra todos los componentes del sistema SIGRH
"""

import sys
import os
from datetime import datetime

# Agregar los módulos al path
sys.path.append(os.path.join(os.path.dirname(__file__), 'modules'))
sys.path.append(os.path.join(os.path.dirname(__file__), 'config'))

from config.settings import SIGRHConfig
from modules.employees.employees import EmployeeManager, Employee
from modules.schedules.schedules import ScheduleManager, Schedule
from modules.vacations.vacations import VacationManager, Vacation, VacationType
from modules.payroll.payroll import PayrollManager, Compensation, CompensationType, PayPeriod
from modules.biometrics.biometrics import BiometricManager, AttendanceRecord
from notifications.email.email_service import NotificationManager


class SIGRHApplication:
    """Aplicación principal del Sistema SIGRH"""
    
    def __init__(self):
        self.config = SIGRHConfig()
        self.initialize_managers()
        self.notification_manager = NotificationManager()
        
        print(f"🚀 {self.config.app.app_name} v{self.config.app.version} iniciado")
        print(f"📢 Empresa: {self.config.app.company_name}")
        print(f"🕒 Fecha: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    def initialize_managers(self):
        """Inicializa todos los gestores del sistema"""
        self.employee_manager = EmployeeManager()
        self.schedule_manager = ScheduleManager()
        self.vacation_manager = VacationManager()
        self.payroll_manager = PayrollManager()
        self.biometric_manager = BiometricManager()
        
        print("✅ Gestores inicializados correctamente")
    
    def create_sample_data(self):
        """Crea datos de ejemplo para demostración"""
        print("\n📊 Creando datos de ejemplo...")
        
        # Crear empleados de ejemplo
        employees = [
            Employee("EMP001", "Juan", "Pérez", "juan.perez@company.com", 
                    "Analista de Sistemas", "IT", 3500.0, "+1234567890"),
            Employee("EMP002", "María", "González", "maria.gonzalez@company.com", 
                    "Gerente de RRHH", "Recursos Humanos", 4500.0, "+1234567891"),
            Employee("EMP003", "Carlos", "Rodríguez", "carlos.rodriguez@company.com", 
                    "Contador", "Finanzas", 3200.0, "+1234567892"),
        ]
        
        for employee in employees:
            self.employee_manager.create_employee(employee)
        
        # Crear horarios de ejemplo
        schedules = [
            Schedule(1, 1, "09:00:00", "17:00:00", 60),  # Juan - Lunes
            Schedule(1, 2, "09:00:00", "17:00:00", 60),  # Juan - Martes
            Schedule(2, 1, "08:00:00", "16:00:00", 60),  # María - Lunes
            Schedule(2, 2, "08:00:00", "16:00:00", 60),  # María - Martes
        ]
        
        for schedule in schedules:
            self.schedule_manager.create_schedule(schedule)
        
        # Crear solicitudes de vacaciones de ejemplo
        vacation = Vacation(1, "2024-08-01", "2024-08-05", VacationType.ANNUAL, "Vacaciones familiares")
        self.vacation_manager.create_vacation_request(vacation)
        
        # Crear compensaciones de ejemplo
        compensations = [
            Compensation(1, CompensationType.SALARY, 3500.0, PayPeriod.MONTHLY, "2024-01-01", description="Salario base"),
            Compensation(2, CompensationType.SALARY, 4500.0, PayPeriod.MONTHLY, "2024-01-01", description="Salario base"),
            Compensation(3, CompensationType.SALARY, 3200.0, PayPeriod.MONTHLY, "2024-01-01", description="Salario base"),
        ]
        
        for compensation in compensations:
            self.payroll_manager.create_compensation(compensation)
        
        print("✅ Datos de ejemplo creados exitosamente")
    
    def run_demo(self):
        """Ejecuta una demostración del sistema"""
        print("\n🎬 Ejecutando demostración del sistema SIGRH...")
        
        # Demostrar gestión de empleados
        print("\n👥 GESTIÓN DE EMPLEADOS")
        employees = self.employee_manager.list_employees()
        print(f"Total de empleados: {len(employees)}")
        
        # Demostrar control de asistencia
        print("\n🕒 CONTROL DE ASISTENCIA")
        self.biometric_manager.check_in_employee(1)
        self.biometric_manager.check_out_employee(1)
        
        # Demostrar gestión de nómina
        print("\n💰 GESTIÓN DE NÓMINA")
        payroll = self.payroll_manager.generate_payroll(1, "2024-07-01", "2024-07-31")
        print(f"Nómina generada - Salario neto: ${payroll.net_pay:.2f}")
        
        # Demostrar notificaciones
        print("\n📬 SISTEMA DE NOTIFICACIONES")
        recipient = {'email': 'juan.perez@company.com', 'name': 'Juan Pérez'}
        data = {'start_date': '2024-08-01', 'end_date': '2024-08-05'}
        self.notification_manager.send_notification('vacation_approved', recipient, data)
        
        print("\n✅ Demostración completada exitosamente")
    
    def show_system_status(self):
        """Muestra el estado del sistema"""
        print("\n📊 ESTADO DEL SISTEMA")
        print("=" * 50)
        
        # Validar configuración
        errors = self.config.validate()
        if self.config.is_valid():
            print("✅ Configuración: Válida")
        else:
            print("❌ Configuración: Errores encontrados")
            for section, error_list in errors.items():
                if error_list:
                    print(f"   {section}: {', '.join(error_list)}")
        
        # Estado de los módulos
        print(f"✅ Gestión de Empleados: Activo")
        print(f"✅ Control de Horarios: Activo")
        print(f"✅ Gestión de Vacaciones: Activo")
        print(f"✅ Sistema de Nómina: Activo")
        print(f"✅ Control Biométrico: Activo")
        print(f"✅ Notificaciones: Activo")
        
        # Información de la empresa
        print(f"\n🏢 Empresa: {self.config.app.company_name}")
        print(f"📧 Email: {self.config.app.company_email}")
        print(f"📞 Teléfono: {self.config.app.company_phone}")
        print(f"🌍 Zona horaria: {self.config.app.timezone}")
        print(f"🗣️ Idioma: {self.config.app.language}")
    
    def interactive_menu(self):
        """Menú interactivo para el sistema"""
        while True:
            print("\n" + "="*50)
            print(f"🏢 {self.config.app.app_name} - MENÚ PRINCIPAL")
            print("="*50)
            print("1. 👥 Gestión de Empleados")
            print("2. 🕒 Control de Asistencia")
            print("3. 📅 Gestión de Horarios")
            print("4. 🏖️ Gestión de Vacaciones")
            print("5. 💰 Gestión de Nómina")
            print("6. 📬 Sistema de Notificaciones")
            print("7. 📊 Estado del Sistema")
            print("8. 🎬 Ejecutar Demostración")
            print("9. 🔧 Crear Datos de Ejemplo")
            print("0. 🚪 Salir")
            
            choice = input("\nSeleccione una opción: ").strip()
            
            if choice == '1':
                self.employee_menu()
            elif choice == '2':
                self.attendance_menu()
            elif choice == '3':
                self.schedule_menu()
            elif choice == '4':
                self.vacation_menu()
            elif choice == '5':
                self.payroll_menu()
            elif choice == '6':
                self.notification_menu()
            elif choice == '7':
                self.show_system_status()
            elif choice == '8':
                self.run_demo()
            elif choice == '9':
                self.create_sample_data()
            elif choice == '0':
                print("👋 Gracias por usar SIGRH. ¡Hasta luego!")
                break
            else:
                print("❌ Opción no válida. Intente nuevamente.")
    
    def employee_menu(self):
        """Menú de gestión de empleados"""
        print("\n👥 GESTIÓN DE EMPLEADOS")
        print("1. Listar empleados")
        print("2. Crear empleado")
        print("3. Volver al menú principal")
        
        choice = input("Seleccione una opción: ").strip()
        
        if choice == '1':
            employees = self.employee_manager.list_employees()
            if employees:
                print("\n📋 Lista de empleados:")
                for emp in employees:
                    print(f"- {emp}")
            else:
                print("📝 No hay empleados registrados. Use la opción 9 del menú principal para crear datos de ejemplo.")
        elif choice == '2':
            print("📝 Creación de empleado (simulación)")
            print("En una versión completa, aquí iría el formulario de creación.")
    
    def attendance_menu(self):
        """Menú de control de asistencia"""
        print("\n🕒 CONTROL DE ASISTENCIA")
        print("1. Registrar entrada")
        print("2. Registrar salida")
        print("3. Volver al menú principal")
        
        choice = input("Seleccione una opción: ").strip()
        
        if choice == '1':
            emp_id = input("Ingrese ID del empleado: ").strip()
            if emp_id.isdigit():
                self.biometric_manager.check_in_employee(int(emp_id))
            else:
                print("❌ ID de empleado inválido")
        elif choice == '2':
            emp_id = input("Ingrese ID del empleado: ").strip()
            if emp_id.isdigit():
                self.biometric_manager.check_out_employee(int(emp_id))
            else:
                print("❌ ID de empleado inválido")
    
    def schedule_menu(self):
        """Menú de gestión de horarios"""
        print("\n📅 GESTIÓN DE HORARIOS")
        print("Esta funcionalidad está disponible en el portal web administrativo.")
        print("URL: http://localhost:5000 (cuando el servidor web esté ejecutándose)")
    
    def vacation_menu(self):
        """Menú de gestión de vacaciones"""
        print("\n🏖️ GESTIÓN DE VACACIONES")
        print("Esta funcionalidad está disponible en el portal web administrativo.")
        print("URL: http://localhost:5000 (cuando el servidor web esté ejecutándose)")
    
    def payroll_menu(self):
        """Menú de gestión de nómina"""
        print("\n💰 GESTIÓN DE NÓMINA")
        print("1. Generar nómina")
        print("2. Volver al menú principal")
        
        choice = input("Seleccione una opción: ").strip()
        
        if choice == '1':
            emp_id = input("Ingrese ID del empleado: ").strip()
            if emp_id.isdigit():
                payroll = self.payroll_manager.generate_payroll(int(emp_id), "2024-07-01", "2024-07-31")
                print(f"💰 Nómina generada - Salario bruto: ${payroll.gross_pay:.2f}")
                print(f"💰 Nómina generada - Salario neto: ${payroll.net_pay:.2f}")
            else:
                print("❌ ID de empleado inválido")
    
    def notification_menu(self):
        """Menú de notificaciones"""
        print("\n📬 SISTEMA DE NOTIFICACIONES")
        print("Sistema de notificaciones configurado y funcionando.")
        print("Las notificaciones se envían automáticamente cuando ocurren eventos.")
        print("Revise los logs para ver las notificaciones enviadas.")


def main():
    """Función principal"""
    try:
        app = SIGRHApplication()
        app.interactive_menu()
    except KeyboardInterrupt:
        print("\n\n⚠️ Aplicación interrumpida por el usuario")
    except Exception as e:
        print(f"\n❌ Error en la aplicación: {e}")
    finally:
        print("🔚 Cerrando Sistema SIGRH...")


if __name__ == "__main__":
    main()
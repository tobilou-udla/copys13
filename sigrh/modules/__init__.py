"""
Módulos del Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

__version__ = "1.0.0"
__author__ = "Equipo SIGRH"
__email__ = "desarrollo@sigrh.com"

# Importar clases principales para fácil acceso
from .employees.employees import Employee, EmployeeManager
from .schedules.schedules import Schedule, ScheduleManager
from .vacations.vacations import Vacation, VacationManager, VacationType
from .payroll.payroll import Compensation, PayrollManager, CompensationType, PayPeriod
from .biometrics.biometrics import AttendanceRecord, BiometricManager, AttendanceStatus

__all__ = [
    'Employee',
    'EmployeeManager',
    'Schedule',
    'ScheduleManager',
    'Vacation',
    'VacationManager',
    'VacationType',
    'Compensation',
    'PayrollManager',
    'CompensationType',
    'PayPeriod',
    'AttendanceRecord',
    'BiometricManager',
    'AttendanceStatus'
]
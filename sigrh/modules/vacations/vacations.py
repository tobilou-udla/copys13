"""
Módulo de Gestión de Vacaciones
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

from datetime import datetime, date
from typing import List, Dict, Optional
from enum import Enum


class VacationType(Enum):
    """Tipos de vacaciones disponibles"""
    ANNUAL = "annual"
    SICK = "sick"
    PERSONAL = "personal"
    MATERNITY = "maternity"
    PATERNITY = "paternity"
    BEREAVEMENT = "bereavement"
    EMERGENCY = "emergency"


class VacationStatus(Enum):
    """Estados de solicitud de vacaciones"""
    PENDING = "pending"
    APPROVED = "approved"
    REJECTED = "rejected"
    CANCELLED = "cancelled"


class Vacation:
    """Clase para representar una solicitud de vacaciones"""
    
    def __init__(self, employee_id: int, start_date: str, end_date: str,
                 vacation_type: VacationType, reason: str = None):
        self.employee_id = employee_id
        self.start_date = start_date
        self.end_date = end_date
        self.vacation_type = vacation_type
        self.reason = reason
        self.status = VacationStatus.PENDING
        self.approved_by = None
        self.approved_at = None
        self.days_requested = self.calculate_days()
    
    def calculate_days(self) -> int:
        """Calcula el número de días solicitados"""
        start = datetime.strptime(self.start_date, '%Y-%m-%d')
        end = datetime.strptime(self.end_date, '%Y-%m-%d')
        return (end - start).days + 1
    
    def approve(self, approved_by: int):
        """Aprueba la solicitud de vacaciones"""
        self.status = VacationStatus.APPROVED
        self.approved_by = approved_by
        self.approved_at = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    def reject(self, rejected_by: int):
        """Rechaza la solicitud de vacaciones"""
        self.status = VacationStatus.REJECTED
        self.approved_by = rejected_by
        self.approved_at = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    def cancel(self):
        """Cancela la solicitud de vacaciones"""
        self.status = VacationStatus.CANCELLED
    
    def to_dict(self) -> Dict:
        """Convierte la solicitud a diccionario"""
        return {
            'employee_id': self.employee_id,
            'start_date': self.start_date,
            'end_date': self.end_date,
            'days_requested': self.days_requested,
            'vacation_type': self.vacation_type.value,
            'status': self.status.value,
            'reason': self.reason,
            'approved_by': self.approved_by,
            'approved_at': self.approved_at
        }


class VacationManager:
    """Gestor de solicitudes de vacaciones"""
    
    def __init__(self, db_path: str = "sigrh.db"):
        self.db_path = db_path
    
    def create_vacation_request(self, vacation: Vacation) -> bool:
        """Crea una nueva solicitud de vacaciones"""
        try:
            # Validar la solicitud
            if self.validate_vacation_request(vacation):
                print(f"Solicitud de vacaciones creada para empleado {vacation.employee_id}")
                print(f"Período: {vacation.start_date} al {vacation.end_date}")
                print(f"Días solicitados: {vacation.days_requested}")
                return True
            else:
                print("Error: Solicitud de vacaciones inválida")
                return False
        except Exception as e:
            print(f"Error al crear solicitud de vacaciones: {e}")
            return False
    
    def validate_vacation_request(self, vacation: Vacation) -> bool:
        """Valida una solicitud de vacaciones"""
        # Verificar que las fechas sean válidas
        start = datetime.strptime(vacation.start_date, '%Y-%m-%d')
        end = datetime.strptime(vacation.end_date, '%Y-%m-%d')
        
        if start >= end:
            return False
        
        # Verificar que las fechas no sean en el pasado
        if start.date() < date.today():
            return False
        
        # Verificar que no haya solapamiento con otras vacaciones aprobadas
        # Aquí iría la lógica de consulta a la base de datos
        return True
    
    def get_employee_vacations(self, employee_id: int) -> List[Vacation]:
        """Obtiene todas las vacaciones de un empleado"""
        vacations = []
        # Aquí iría la lógica de consulta a la base de datos
        return vacations
    
    def get_pending_requests(self) -> List[Vacation]:
        """Obtiene todas las solicitudes pendientes"""
        pending_vacations = []
        # Aquí iría la lógica de consulta a la base de datos
        return pending_vacations
    
    def approve_vacation(self, vacation_id: int, approved_by: int) -> bool:
        """Aprueba una solicitud de vacaciones"""
        try:
            # Aquí iría la lógica de actualización en la base de datos
            print(f"Solicitud de vacaciones aprobada: ID {vacation_id}")
            return True
        except Exception as e:
            print(f"Error al aprobar solicitud: {e}")
            return False
    
    def reject_vacation(self, vacation_id: int, rejected_by: int) -> bool:
        """Rechaza una solicitud de vacaciones"""
        try:
            # Aquí iría la lógica de actualización en la base de datos
            print(f"Solicitud de vacaciones rechazada: ID {vacation_id}")
            return True
        except Exception as e:
            print(f"Error al rechazar solicitud: {e}")
            return False
    
    def calculate_vacation_balance(self, employee_id: int) -> Dict:
        """Calcula el balance de vacaciones de un empleado"""
        # Obtener días de vacaciones anuales permitidos
        annual_days = 22  # Ejemplo: 22 días anuales
        
        # Obtener días ya utilizados este año
        used_days = 0
        # Aquí iría la lógica de consulta a la base de datos
        
        # Obtener días en solicitudes pendientes
        pending_days = 0
        # Aquí iría la lógica de consulta a la base de datos
        
        return {
            'annual_allowance': annual_days,
            'used_days': used_days,
            'pending_days': pending_days,
            'available_days': annual_days - used_days - pending_days
        }
    
    def get_vacation_calendar(self, start_date: str, end_date: str) -> List[Dict]:
        """Obtiene el calendario de vacaciones para un período"""
        calendar = []
        # Aquí iría la lógica de consulta a la base de datos
        return calendar


if __name__ == "__main__":
    # Ejemplo de uso
    manager = VacationManager()
    
    # Crear solicitud de vacaciones de ejemplo
    vacation = Vacation(
        employee_id=1,
        start_date="2024-08-01",
        end_date="2024-08-05",
        vacation_type=VacationType.ANNUAL,
        reason="Vacaciones familiares"
    )
    
    print(f"Solicitud de vacaciones: {vacation.to_dict()}")
    manager.create_vacation_request(vacation)
    
    # Calcular balance de vacaciones
    balance = manager.calculate_vacation_balance(1)
    print(f"Balance de vacaciones: {balance}")
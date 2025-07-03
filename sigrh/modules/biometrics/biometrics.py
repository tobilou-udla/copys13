"""
Módulo de Gestión Biométrica
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

from datetime import datetime, date, timedelta
from typing import List, Dict, Optional
from enum import Enum


class AttendanceStatus(Enum):
    """Estados de asistencia disponibles"""
    PRESENT = "present"
    ABSENT = "absent"
    LATE = "late"
    HALF_DAY = "half-day"
    OVERTIME = "overtime"


class AttendanceRecord:
    """Clase para representar un registro de asistencia"""
    
    def __init__(self, employee_id: int, date: str, check_in_time: str = None,
                 check_out_time: str = None, notes: str = None):
        self.employee_id = employee_id
        self.date = date
        self.check_in_time = check_in_time
        self.check_out_time = check_out_time
        self.hours_worked = 0.0
        self.overtime_hours = 0.0
        self.status = AttendanceStatus.PRESENT
        self.notes = notes
        self.created_at = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    def check_in(self, time: str = None):
        """Registra la entrada del empleado"""
        if time is None:
            time = datetime.now().strftime('%H:%M:%S')
        self.check_in_time = time
        print(f"Entrada registrada: {time}")
    
    def check_out(self, time: str = None):
        """Registra la salida del empleado"""
        if time is None:
            time = datetime.now().strftime('%H:%M:%S')
        self.check_out_time = time
        self.calculate_hours_worked()
        print(f"Salida registrada: {time}")
    
    def calculate_hours_worked(self):
        """Calcula las horas trabajadas"""
        if self.check_in_time and self.check_out_time:
            check_in = datetime.strptime(f"{self.date} {self.check_in_time}", '%Y-%m-%d %H:%M:%S')
            check_out = datetime.strptime(f"{self.date} {self.check_out_time}", '%Y-%m-%d %H:%M:%S')
            
            # Si el checkout es al día siguiente
            if check_out < check_in:
                check_out += timedelta(days=1)
            
            work_duration = check_out - check_in
            self.hours_worked = work_duration.total_seconds() / 3600
            
            # Restar tiempo de descanso (1 hora por defecto)
            if self.hours_worked > 6:
                self.hours_worked -= 1
            
            # Calcular horas extras (más de 8 horas)
            if self.hours_worked > 8:
                self.overtime_hours = self.hours_worked - 8
                self.status = AttendanceStatus.OVERTIME
    
    def to_dict(self) -> Dict:
        """Convierte el registro a diccionario"""
        return {
            'employee_id': self.employee_id,
            'date': self.date,
            'check_in_time': self.check_in_time,
            'check_out_time': self.check_out_time,
            'hours_worked': round(self.hours_worked, 2),
            'overtime_hours': round(self.overtime_hours, 2),
            'status': self.status.value,
            'notes': self.notes,
            'created_at': self.created_at
        }


class BiometricDevice:
    """Simulador de dispositivo biométrico"""
    
    def __init__(self, device_id: str, location: str):
        self.device_id = device_id
        self.location = location
        self.is_active = True
    
    def authenticate_employee(self, employee_id: int, biometric_data: str) -> bool:
        """Autentica un empleado usando datos biométricos"""
        # Simulación de autenticación biométrica
        # En una implementación real, aquí se procesarían datos de huella dactilar,
        # reconocimiento facial, etc.
        print(f"Autenticando empleado {employee_id} en dispositivo {self.device_id}")
        return True  # Simulación: siempre autentica correctamente
    
    def record_attendance(self, employee_id: int, biometric_data: str, 
                         action: str = "check_in") -> bool:
        """Registra asistencia usando datos biométricos"""
        if self.authenticate_employee(employee_id, biometric_data):
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            print(f"Asistencia registrada: Empleado {employee_id} - {action} - {timestamp}")
            return True
        return False


class BiometricManager:
    """Gestor de sistema biométrico y asistencia"""
    
    def __init__(self, db_path: str = "sigrh.db"):
        self.db_path = db_path
        self.devices = {}
    
    def register_device(self, device: BiometricDevice):
        """Registra un dispositivo biométrico"""
        self.devices[device.device_id] = device
        print(f"Dispositivo registrado: {device.device_id} en {device.location}")
    
    def create_attendance_record(self, record: AttendanceRecord) -> bool:
        """Crea un registro de asistencia"""
        try:
            print(f"Registro de asistencia creado para empleado {record.employee_id}")
            print(f"Fecha: {record.date}")
            return True
        except Exception as e:
            print(f"Error al crear registro de asistencia: {e}")
            return False
    
    def check_in_employee(self, employee_id: int, device_id: str = None) -> bool:
        """Registra la entrada de un empleado"""
        try:
            today = date.today().strftime('%Y-%m-%d')
            
            # Buscar si ya existe un registro para hoy
            existing_record = self.get_attendance_record(employee_id, today)
            
            if existing_record:
                if existing_record.check_in_time:
                    print("El empleado ya registró su entrada hoy")
                    return False
                else:
                    existing_record.check_in()
                    return True
            else:
                # Crear nuevo registro
                record = AttendanceRecord(employee_id, today)
                record.check_in()
                return self.create_attendance_record(record)
        except Exception as e:
            print(f"Error al registrar entrada: {e}")
            return False
    
    def check_out_employee(self, employee_id: int, device_id: str = None) -> bool:
        """Registra la salida de un empleado"""
        try:
            today = date.today().strftime('%Y-%m-%d')
            record = self.get_attendance_record(employee_id, today)
            
            if not record:
                print("No se encontró registro de entrada para hoy")
                return False
            
            if not record.check_in_time:
                print("El empleado no ha registrado su entrada")
                return False
            
            if record.check_out_time:
                print("El empleado ya registró su salida hoy")
                return False
            
            record.check_out()
            return True
        except Exception as e:
            print(f"Error al registrar salida: {e}")
            return False
    
    def get_attendance_record(self, employee_id: int, date: str) -> Optional[AttendanceRecord]:
        """Obtiene el registro de asistencia de un empleado para una fecha"""
        # Aquí iría la lógica de consulta a la base de datos
        # Por ahora retornamos None para simular que no hay registro
        return None
    
    def get_employee_attendance(self, employee_id: int, 
                               start_date: str, end_date: str) -> List[AttendanceRecord]:
        """Obtiene los registros de asistencia de un empleado en un período"""
        records = []
        # Aquí iría la lógica de consulta a la base de datos
        return records
    
    def calculate_attendance_summary(self, employee_id: int, 
                                   start_date: str, end_date: str) -> Dict:
        """Calcula un resumen de asistencia para un empleado"""
        records = self.get_employee_attendance(employee_id, start_date, end_date)
        
        total_days = len(records)
        present_days = len([r for r in records if r.status == AttendanceStatus.PRESENT])
        late_days = len([r for r in records if r.status == AttendanceStatus.LATE])
        absent_days = len([r for r in records if r.status == AttendanceStatus.ABSENT])
        total_hours = sum(r.hours_worked for r in records)
        total_overtime = sum(r.overtime_hours for r in records)
        
        return {
            'employee_id': employee_id,
            'period': f"{start_date} to {end_date}",
            'total_days': total_days,
            'present_days': present_days,
            'late_days': late_days,
            'absent_days': absent_days,
            'total_hours_worked': round(total_hours, 2),
            'total_overtime_hours': round(total_overtime, 2),
            'attendance_rate': round((present_days / total_days * 100), 2) if total_days > 0 else 0
        }
    
    def generate_attendance_report(self, start_date: str, end_date: str) -> Dict:
        """Genera un reporte de asistencia para todos los empleados"""
        # Aquí iría la lógica para generar un reporte completo
        return {
            'period': f"{start_date} to {end_date}",
            'total_employees': 0,
            'average_attendance_rate': 0.0,
            'total_hours_worked': 0.0,
            'total_overtime_hours': 0.0
        }
    
    def detect_anomalies(self, employee_id: int, days: int = 30) -> List[Dict]:
        """Detecta anomalías en los patrones de asistencia"""
        anomalies = []
        # Aquí iría la lógica para detectar patrones anómalos
        # Por ejemplo: entradas muy tempranas, salidas muy tardías, etc.
        return anomalies


if __name__ == "__main__":
    # Ejemplo de uso
    manager = BiometricManager()
    
    # Registrar dispositivo biométrico
    device = BiometricDevice("BIO001", "Entrada Principal")
    manager.register_device(device)
    
    # Simular registro de entrada
    manager.check_in_employee(1, "BIO001")
    
    # Crear registro de asistencia manual
    record = AttendanceRecord(1, "2024-07-03")
    record.check_in("08:30:00")
    record.check_out("17:15:00")
    
    print(f"Registro de asistencia: {record.to_dict()}")
    
    # Calcular resumen de asistencia
    summary = manager.calculate_attendance_summary(1, "2024-07-01", "2024-07-31")
    print(f"Resumen de asistencia: {summary}")
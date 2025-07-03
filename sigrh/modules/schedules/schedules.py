"""
Módulo de Gestión de Horarios
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

from datetime import datetime, time
from typing import List, Dict, Optional


class Schedule:
    """Clase para representar un horario de empleado"""
    
    def __init__(self, employee_id: int, day_of_week: int, start_time: str, 
                 end_time: str, break_duration: int = 60, is_active: bool = True):
        self.employee_id = employee_id
        self.day_of_week = day_of_week  # 0=Domingo, 1=Lunes, ..., 6=Sábado
        self.start_time = start_time
        self.end_time = end_time
        self.break_duration = break_duration  # en minutos
        self.is_active = is_active
    
    def get_day_name(self) -> str:
        """Obtiene el nombre del día de la semana"""
        days = ['Domingo', 'Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes', 'Sábado']
        return days[self.day_of_week]
    
    def calculate_work_hours(self) -> float:
        """Calcula las horas de trabajo del día"""
        start = datetime.strptime(self.start_time, '%H:%M:%S')
        end = datetime.strptime(self.end_time, '%H:%M:%S')
        work_duration = end - start
        work_hours = work_duration.total_seconds() / 3600
        break_hours = self.break_duration / 60
        return work_hours - break_hours
    
    def to_dict(self) -> Dict:
        """Convierte el horario a diccionario"""
        return {
            'employee_id': self.employee_id,
            'day_of_week': self.day_of_week,
            'day_name': self.get_day_name(),
            'start_time': self.start_time,
            'end_time': self.end_time,
            'break_duration': self.break_duration,
            'work_hours': self.calculate_work_hours(),
            'is_active': self.is_active
        }


class ScheduleManager:
    """Gestor de horarios de empleados"""
    
    def __init__(self, db_path: str = "sigrh.db"):
        self.db_path = db_path
    
    def create_schedule(self, schedule: Schedule) -> bool:
        """Crea un nuevo horario"""
        try:
            # Validar que no haya conflictos de horarios
            if self.validate_schedule(schedule):
                print(f"Horario creado para empleado {schedule.employee_id}: {schedule.get_day_name()}")
                return True
            else:
                print("Error: Conflicto de horarios")
                return False
        except Exception as e:
            print(f"Error al crear horario: {e}")
            return False
    
    def validate_schedule(self, schedule: Schedule) -> bool:
        """Valida que el horario no tenga conflictos"""
        # Verificar que la hora de inicio sea anterior a la hora de fin
        start = datetime.strptime(schedule.start_time, '%H:%M:%S')
        end = datetime.strptime(schedule.end_time, '%H:%M:%S')
        
        if start >= end:
            return False
        
        # Verificar que no haya solapamiento con otros horarios del mismo empleado
        # Aquí iría la lógica de consulta a la base de datos
        return True
    
    def get_employee_schedule(self, employee_id: int) -> List[Schedule]:
        """Obtiene todos los horarios de un empleado"""
        schedules = []
        # Aquí iría la lógica de consulta a la base de datos
        return schedules
    
    def update_schedule(self, schedule_id: int, updates: Dict) -> bool:
        """Actualiza un horario"""
        try:
            print(f"Horario actualizado: ID {schedule_id}")
            return True
        except Exception as e:
            print(f"Error al actualizar horario: {e}")
            return False
    
    def delete_schedule(self, schedule_id: int) -> bool:
        """Elimina un horario"""
        try:
            print(f"Horario eliminado: ID {schedule_id}")
            return True
        except Exception as e:
            print(f"Error al eliminar horario: {e}")
            return False
    
    def get_weekly_schedule(self, employee_id: int) -> Dict:
        """Obtiene el horario semanal completo de un empleado"""
        schedules = self.get_employee_schedule(employee_id)
        weekly_schedule = {}
        
        for schedule in schedules:
            if schedule.is_active:
                weekly_schedule[schedule.get_day_name()] = schedule.to_dict()
        
        return weekly_schedule
    
    def calculate_weekly_hours(self, employee_id: int) -> float:
        """Calcula las horas totales de trabajo semanales"""
        schedules = self.get_employee_schedule(employee_id)
        total_hours = 0
        
        for schedule in schedules:
            if schedule.is_active:
                total_hours += schedule.calculate_work_hours()
        
        return total_hours


if __name__ == "__main__":
    # Ejemplo de uso
    manager = ScheduleManager()
    
    # Crear horario de ejemplo
    schedule = Schedule(
        employee_id=1,
        day_of_week=1,  # Lunes
        start_time="09:00:00",
        end_time="17:00:00",
        break_duration=60
    )
    
    print(f"Horario: {schedule.get_day_name()}")
    print(f"Horas de trabajo: {schedule.calculate_work_hours()}")
    
    manager.create_schedule(schedule)
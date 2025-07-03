"""
Módulo de Gestión de Nómina
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

from datetime import datetime, date
from typing import List, Dict, Optional
from enum import Enum


class CompensationType(Enum):
    """Tipos de compensación disponibles"""
    SALARY = "salary"
    BONUS = "bonus"
    OVERTIME = "overtime"
    COMMISSION = "commission"
    ALLOWANCE = "allowance"
    DEDUCTION = "deduction"


class PayPeriod(Enum):
    """Períodos de pago disponibles"""
    WEEKLY = "weekly"
    BIWEEKLY = "biweekly"
    MONTHLY = "monthly"
    QUARTERLY = "quarterly"
    ANNUAL = "annual"
    ONE_TIME = "one-time"


class Compensation:
    """Clase para representar una compensación"""
    
    def __init__(self, employee_id: int, compensation_type: CompensationType,
                 amount: float, pay_period: PayPeriod, effective_date: str,
                 currency: str = "USD", description: str = None, end_date: str = None):
        self.employee_id = employee_id
        self.compensation_type = compensation_type
        self.amount = amount
        self.currency = currency
        self.pay_period = pay_period
        self.effective_date = effective_date
        self.end_date = end_date
        self.is_active = True
        self.description = description
    
    def to_dict(self) -> Dict:
        """Convierte la compensación a diccionario"""
        return {
            'employee_id': self.employee_id,
            'compensation_type': self.compensation_type.value,
            'amount': self.amount,
            'currency': self.currency,
            'pay_period': self.pay_period.value,
            'effective_date': self.effective_date,
            'end_date': self.end_date,
            'is_active': self.is_active,
            'description': self.description
        }


class PayrollRecord:
    """Clase para representar un registro de nómina"""
    
    def __init__(self, employee_id: int, pay_period_start: str, pay_period_end: str):
        self.employee_id = employee_id
        self.pay_period_start = pay_period_start
        self.pay_period_end = pay_period_end
        self.gross_pay = 0.0
        self.net_pay = 0.0
        self.total_deductions = 0.0
        self.total_taxes = 0.0
        self.compensations = []
        self.deductions = []
        self.created_at = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    def add_compensation(self, compensation: Compensation):
        """Agrega una compensación al registro"""
        self.compensations.append(compensation)
        if compensation.compensation_type != CompensationType.DEDUCTION:
            self.gross_pay += compensation.amount
    
    def add_deduction(self, description: str, amount: float):
        """Agrega una deducción al registro"""
        deduction = {
            'description': description,
            'amount': amount,
            'type': 'deduction'
        }
        self.deductions.append(deduction)
        self.total_deductions += amount
    
    def calculate_taxes(self, tax_rate: float = 0.15):
        """Calcula los impuestos (simplificado)"""
        self.total_taxes = self.gross_pay * tax_rate
    
    def calculate_net_pay(self):
        """Calcula el salario neto"""
        self.net_pay = self.gross_pay - self.total_deductions - self.total_taxes
    
    def to_dict(self) -> Dict:
        """Convierte el registro a diccionario"""
        return {
            'employee_id': self.employee_id,
            'pay_period_start': self.pay_period_start,
            'pay_period_end': self.pay_period_end,
            'gross_pay': self.gross_pay,
            'net_pay': self.net_pay,
            'total_deductions': self.total_deductions,
            'total_taxes': self.total_taxes,
            'compensations': [comp.to_dict() for comp in self.compensations],
            'deductions': self.deductions,
            'created_at': self.created_at
        }


class PayrollManager:
    """Gestor de nómina y compensaciones"""
    
    def __init__(self, db_path: str = "sigrh.db"):
        self.db_path = db_path
    
    def create_compensation(self, compensation: Compensation) -> bool:
        """Crea una nueva compensación"""
        try:
            print(f"Compensación creada para empleado {compensation.employee_id}")
            print(f"Tipo: {compensation.compensation_type.value}")
            print(f"Monto: {compensation.amount} {compensation.currency}")
            return True
        except Exception as e:
            print(f"Error al crear compensación: {e}")
            return False
    
    def get_employee_compensations(self, employee_id: int) -> List[Compensation]:
        """Obtiene todas las compensaciones de un empleado"""
        compensations = []
        # Aquí iría la lógica de consulta a la base de datos
        return compensations
    
    def update_compensation(self, compensation_id: int, updates: Dict) -> bool:
        """Actualiza una compensación"""
        try:
            print(f"Compensación actualizada: ID {compensation_id}")
            return True
        except Exception as e:
            print(f"Error al actualizar compensación: {e}")
            return False
    
    def deactivate_compensation(self, compensation_id: int) -> bool:
        """Desactiva una compensación"""
        try:
            print(f"Compensación desactivada: ID {compensation_id}")
            return True
        except Exception as e:
            print(f"Error al desactivar compensación: {e}")
            return False
    
    def generate_payroll(self, employee_id: int, pay_period_start: str, 
                        pay_period_end: str) -> PayrollRecord:
        """Genera un registro de nómina para un empleado"""
        payroll = PayrollRecord(employee_id, pay_period_start, pay_period_end)
        
        # Obtener compensaciones activas del empleado
        compensations = self.get_employee_compensations(employee_id)
        
        for compensation in compensations:
            if compensation.is_active:
                payroll.add_compensation(compensation)
        
        # Agregar deducciones estándar
        payroll.add_deduction("Seguro Social", payroll.gross_pay * 0.06)
        payroll.add_deduction("Seguro de Salud", 150.0)
        
        # Calcular impuestos y salario neto
        payroll.calculate_taxes()
        payroll.calculate_net_pay()
        
        return payroll
    
    def generate_payroll_batch(self, pay_period_start: str, 
                              pay_period_end: str) -> List[PayrollRecord]:
        """Genera nómina para todos los empleados activos"""
        payrolls = []
        # Aquí iría la lógica para obtener todos los empleados activos
        # y generar nómina para cada uno
        return payrolls
    
    def get_payroll_history(self, employee_id: int, limit: int = 12) -> List[PayrollRecord]:
        """Obtiene el historial de nómina de un empleado"""
        history = []
        # Aquí iría la lógica de consulta a la base de datos
        return history
    
    def calculate_annual_salary(self, employee_id: int) -> float:
        """Calcula el salario anual de un empleado"""
        compensations = self.get_employee_compensations(employee_id)
        annual_salary = 0.0
        
        for compensation in compensations:
            if compensation.is_active and compensation.compensation_type == CompensationType.SALARY:
                if compensation.pay_period == PayPeriod.MONTHLY:
                    annual_salary += compensation.amount * 12
                elif compensation.pay_period == PayPeriod.BIWEEKLY:
                    annual_salary += compensation.amount * 26
                elif compensation.pay_period == PayPeriod.WEEKLY:
                    annual_salary += compensation.amount * 52
        
        return annual_salary
    
    def generate_payroll_report(self, pay_period_start: str, 
                               pay_period_end: str) -> Dict:
        """Genera un reporte de nómina para un período"""
        payrolls = self.generate_payroll_batch(pay_period_start, pay_period_end)
        
        total_gross = sum(payroll.gross_pay for payroll in payrolls)
        total_net = sum(payroll.net_pay for payroll in payrolls)
        total_taxes = sum(payroll.total_taxes for payroll in payrolls)
        total_deductions = sum(payroll.total_deductions for payroll in payrolls)
        
        return {
            'pay_period_start': pay_period_start,
            'pay_period_end': pay_period_end,
            'total_employees': len(payrolls),
            'total_gross_pay': total_gross,
            'total_net_pay': total_net,
            'total_taxes': total_taxes,
            'total_deductions': total_deductions,
            'payrolls': [payroll.to_dict() for payroll in payrolls]
        }


if __name__ == "__main__":
    # Ejemplo de uso
    manager = PayrollManager()
    
    # Crear compensación de ejemplo
    salary = Compensation(
        employee_id=1,
        compensation_type=CompensationType.SALARY,
        amount=3500.0,
        pay_period=PayPeriod.MONTHLY,
        effective_date="2024-01-01",
        description="Salario base mensual"
    )
    
    manager.create_compensation(salary)
    
    # Generar nómina de ejemplo
    payroll = manager.generate_payroll(1, "2024-07-01", "2024-07-31")
    print(f"Nómina generada: {payroll.to_dict()}")
    
    # Calcular salario anual
    annual_salary = manager.calculate_annual_salary(1)
    print(f"Salario anual: ${annual_salary:,.2f}")
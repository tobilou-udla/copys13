"""
Backend Web para SIGRH
Flask API para el portal administrativo
"""

from flask import Flask, jsonify, request, render_template_string
from flask_cors import CORS
import sys
import os

# Agregar el directorio padre al path para importar los módulos SIGRH
sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..', 'modules'))

from employees.employees import EmployeeManager, Employee
from schedules.schedules import ScheduleManager, Schedule
from vacations.vacations import VacationManager, Vacation, VacationType
from payroll.payroll import PayrollManager, Compensation, CompensationType, PayPeriod
from biometrics.biometrics import BiometricManager, AttendanceRecord

app = Flask(__name__)
CORS(app)

# Inicializar managers
employee_manager = EmployeeManager()
schedule_manager = ScheduleManager()
vacation_manager = VacationManager()
payroll_manager = PayrollManager()
biometric_manager = BiometricManager()


@app.route('/')
def index():
    """Página principal del portal administrativo"""
    with open('admin_portal.html', 'r', encoding='utf-8') as f:
        return f.read()


@app.route('/api/employees', methods=['GET'])
def get_employees():
    """Obtiene la lista de empleados"""
    try:
        employees = employee_manager.list_employees()
        return jsonify({
            'success': True,
            'data': [emp.to_dict() for emp in employees]
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/employees', methods=['POST'])
def create_employee():
    """Crea un nuevo empleado"""
    try:
        data = request.get_json()
        employee = Employee(
            employee_number=data['employee_number'],
            first_name=data['first_name'],
            last_name=data['last_name'],
            email=data['email'],
            position=data['position'],
            department=data['department'],
            salary=data.get('salary', 0.0),
            phone=data.get('phone'),
            hire_date=data.get('hire_date')
        )
        
        success = employee_manager.create_employee(employee)
        
        return jsonify({
            'success': success,
            'message': 'Empleado creado exitosamente' if success else 'Error al crear empleado'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/schedules/<int:employee_id>', methods=['GET'])
def get_employee_schedule(employee_id):
    """Obtiene los horarios de un empleado"""
    try:
        schedules = schedule_manager.get_employee_schedule(employee_id)
        return jsonify({
            'success': True,
            'data': [schedule.to_dict() for schedule in schedules]
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/schedules', methods=['POST'])
def create_schedule():
    """Crea un nuevo horario"""
    try:
        data = request.get_json()
        schedule = Schedule(
            employee_id=data['employee_id'],
            day_of_week=data['day_of_week'],
            start_time=data['start_time'],
            end_time=data['end_time'],
            break_duration=data.get('break_duration', 60)
        )
        
        success = schedule_manager.create_schedule(schedule)
        
        return jsonify({
            'success': success,
            'message': 'Horario creado exitosamente' if success else 'Error al crear horario'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/vacations/pending', methods=['GET'])
def get_pending_vacations():
    """Obtiene las solicitudes de vacaciones pendientes"""
    try:
        vacations = vacation_manager.get_pending_requests()
        return jsonify({
            'success': True,
            'data': [vacation.to_dict() for vacation in vacations]
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/vacations', methods=['POST'])
def create_vacation_request():
    """Crea una solicitud de vacaciones"""
    try:
        data = request.get_json()
        vacation = Vacation(
            employee_id=data['employee_id'],
            start_date=data['start_date'],
            end_date=data['end_date'],
            vacation_type=VacationType(data['vacation_type']),
            reason=data.get('reason')
        )
        
        success = vacation_manager.create_vacation_request(vacation)
        
        return jsonify({
            'success': success,
            'message': 'Solicitud de vacaciones creada exitosamente' if success else 'Error al crear solicitud'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/vacations/<int:vacation_id>/approve', methods=['POST'])
def approve_vacation(vacation_id):
    """Aprueba una solicitud de vacaciones"""
    try:
        data = request.get_json()
        approved_by = data.get('approved_by', 1)  # ID del usuario que aprueba
        
        success = vacation_manager.approve_vacation(vacation_id, approved_by)
        
        return jsonify({
            'success': success,
            'message': 'Solicitud aprobada exitosamente' if success else 'Error al aprobar solicitud'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/payroll/<int:employee_id>/generate', methods=['POST'])
def generate_payroll(employee_id):
    """Genera la nómina para un empleado"""
    try:
        data = request.get_json()
        payroll = payroll_manager.generate_payroll(
            employee_id=employee_id,
            pay_period_start=data['pay_period_start'],
            pay_period_end=data['pay_period_end']
        )
        
        return jsonify({
            'success': True,
            'data': payroll.to_dict()
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/attendance/checkin', methods=['POST'])
def check_in():
    """Registra la entrada de un empleado"""
    try:
        data = request.get_json()
        employee_id = data['employee_id']
        device_id = data.get('device_id')
        
        success = biometric_manager.check_in_employee(employee_id, device_id)
        
        return jsonify({
            'success': success,
            'message': 'Entrada registrada exitosamente' if success else 'Error al registrar entrada'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/attendance/checkout', methods=['POST'])
def check_out():
    """Registra la salida de un empleado"""
    try:
        data = request.get_json()
        employee_id = data['employee_id']
        device_id = data.get('device_id')
        
        success = biometric_manager.check_out_employee(employee_id, device_id)
        
        return jsonify({
            'success': success,
            'message': 'Salida registrada exitosamente' if success else 'Error al registrar salida'
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/attendance/summary/<int:employee_id>', methods=['GET'])
def get_attendance_summary(employee_id):
    """Obtiene el resumen de asistencia de un empleado"""
    try:
        start_date = request.args.get('start_date')
        end_date = request.args.get('end_date')
        
        summary = biometric_manager.calculate_attendance_summary(employee_id, start_date, end_date)
        
        return jsonify({
            'success': True,
            'data': summary
        })
    except Exception as e:
        return jsonify({'success': False, 'error': str(e)}), 500


@app.route('/api/health', methods=['GET'])
def health_check():
    """Endpoint de salud para verificar que la API esté funcionando"""
    return jsonify({
        'status': 'healthy',
        'service': 'SIGRH Web API',
        'version': '1.0.0'
    })


if __name__ == '__main__':
    print("Iniciando servidor web SIGRH...")
    print("Portal administrativo disponible en: http://localhost:5000")
    print("API disponible en: http://localhost:5000/api/")
    app.run(debug=True, host='0.0.0.0', port=5000)
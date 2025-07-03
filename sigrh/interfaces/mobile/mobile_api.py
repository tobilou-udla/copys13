"""
Aplicación Móvil SIGRH - Backend
FastAPI para servicios móviles
"""

from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List, Optional
from datetime import datetime
import sys
import os

# Agregar el directorio padre al path para importar los módulos SIGRH
sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..', 'modules'))

from employees.employees import EmployeeManager
from biometrics.biometrics import BiometricManager
from vacations.vacations import VacationManager, VacationType

app = FastAPI(title="SIGRH Mobile API", version="1.0.0")

# Configurar CORS
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Inicializar managers
employee_manager = EmployeeManager()
biometric_manager = BiometricManager()
vacation_manager = VacationManager()


# Modelos Pydantic para validación
class LoginRequest(BaseModel):
    employee_number: str
    password: str  # En producción, se debe implementar autenticación adecuada


class AttendanceRequest(BaseModel):
    employee_id: int
    device_id: Optional[str] = None
    biometric_data: Optional[str] = None


class VacationRequest(BaseModel):
    employee_id: int
    start_date: str
    end_date: str
    vacation_type: str
    reason: Optional[str] = None


@app.get("/")
async def root():
    """Endpoint raíz"""
    return {
        "message": "SIGRH Mobile API",
        "version": "1.0.0",
        "endpoints": [
            "/docs",
            "/auth/login",
            "/attendance/checkin",
            "/attendance/checkout",
            "/attendance/history",
            "/vacations/request",
            "/vacations/balance",
            "/profile"
        ]
    }


@app.post("/auth/login")
async def login(request: LoginRequest):
    """Autenticación de empleado"""
    try:
        # Simulación de autenticación
        # En producción, se debe implementar autenticación real
        if request.employee_number and request.password:
            employee = employee_manager.get_employee_by_number(request.employee_number)
            if employee:
                return {
                    "success": True,
                    "token": "dummy_token_123",  # Token simulado
                    "employee": employee.to_dict(),
                    "message": "Login exitoso"
                }
        
        raise HTTPException(status_code=401, detail="Credenciales inválidas")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/attendance/checkin")
async def check_in(request: AttendanceRequest):
    """Registro de entrada"""
    try:
        success = biometric_manager.check_in_employee(
            request.employee_id, 
            request.device_id
        )
        
        if success:
            return {
                "success": True,
                "message": "Entrada registrada exitosamente",
                "timestamp": datetime.now().isoformat()
            }
        else:
            raise HTTPException(status_code=400, detail="Error al registrar entrada")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/attendance/checkout")
async def check_out(request: AttendanceRequest):
    """Registro de salida"""
    try:
        success = biometric_manager.check_out_employee(
            request.employee_id, 
            request.device_id
        )
        
        if success:
            return {
                "success": True,
                "message": "Salida registrada exitosamente",
                "timestamp": datetime.now().isoformat()
            }
        else:
            raise HTTPException(status_code=400, detail="Error al registrar salida")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/attendance/history/{employee_id}")
async def get_attendance_history(employee_id: int, days: int = 7):
    """Obtiene el historial de asistencia"""
    try:
        from datetime import date, timedelta
        
        end_date = date.today()
        start_date = end_date - timedelta(days=days)
        
        records = biometric_manager.get_employee_attendance(
            employee_id, 
            start_date.strftime('%Y-%m-%d'), 
            end_date.strftime('%Y-%m-%d')
        )
        
        return {
            "success": True,
            "data": [record.to_dict() for record in records],
            "period": f"{start_date} to {end_date}"
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/vacations/request")
async def request_vacation(request: VacationRequest):
    """Solicita vacaciones"""
    try:
        from vacations.vacations import Vacation
        
        vacation = Vacation(
            employee_id=request.employee_id,
            start_date=request.start_date,
            end_date=request.end_date,
            vacation_type=VacationType(request.vacation_type),
            reason=request.reason
        )
        
        success = vacation_manager.create_vacation_request(vacation)
        
        if success:
            return {
                "success": True,
                "message": "Solicitud de vacaciones enviada exitosamente",
                "vacation": vacation.to_dict()
            }
        else:
            raise HTTPException(status_code=400, detail="Error al crear solicitud")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/vacations/balance/{employee_id}")
async def get_vacation_balance(employee_id: int):
    """Obtiene el balance de vacaciones"""
    try:
        balance = vacation_manager.calculate_vacation_balance(employee_id)
        return {
            "success": True,
            "data": balance
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/profile/{employee_id}")
async def get_employee_profile(employee_id: int):
    """Obtiene el perfil del empleado"""
    try:
        employee = employee_manager.get_employee(employee_id)
        if employee:
            return {
                "success": True,
                "data": employee.to_dict()
            }
        else:
            raise HTTPException(status_code=404, detail="Empleado no encontrado")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/notifications/{employee_id}")
async def get_notifications(employee_id: int):
    """Obtiene las notificaciones del empleado"""
    try:
        # Simulación de notificaciones
        notifications = [
            {
                "id": 1,
                "type": "vacation_approved",
                "title": "Solicitud de vacaciones aprobada",
                "message": "Tu solicitud de vacaciones del 15-20 de julio ha sido aprobada",
                "timestamp": "2024-07-01T10:00:00",
                "read": False
            },
            {
                "id": 2,
                "type": "schedule_update",
                "title": "Actualización de horario",
                "message": "Tu horario ha sido actualizado para la próxima semana",
                "timestamp": "2024-06-30T15:30:00",
                "read": True
            }
        ]
        
        return {
            "success": True,
            "data": notifications
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/health")
async def health_check():
    """Endpoint de salud"""
    return {
        "status": "healthy",
        "service": "SIGRH Mobile API",
        "version": "1.0.0",
        "timestamp": datetime.now().isoformat()
    }


if __name__ == "__main__":
    import uvicorn
    print("Iniciando servidor móvil SIGRH...")
    print("API móvil disponible en: http://localhost:8000")
    print("Documentación disponible en: http://localhost:8000/docs")
    uvicorn.run(app, host="0.0.0.0", port=8000)
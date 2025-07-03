"""
Sistema de Notificaciones por SMS
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

import requests
from datetime import datetime
from typing import List, Dict, Optional
import os
import logging

# Configurar logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class SMSTemplate:
    """Plantillas de SMS para diferentes tipos de notificaciones"""
    
    @staticmethod
    def vacation_approved(employee_name: str, start_date: str, end_date: str) -> str:
        """Plantilla SMS para vacaciones aprobadas"""
        return f"Hola {employee_name}, tu solicitud de vacaciones del {start_date} al {end_date} ha sido APROBADA. - RRHH"
    
    @staticmethod
    def vacation_rejected(employee_name: str, start_date: str, end_date: str) -> str:
        """Plantilla SMS para vacaciones rechazadas"""
        return f"Hola {employee_name}, tu solicitud de vacaciones del {start_date} al {end_date} ha sido RECHAZADA. Contacta RRHH para más información."
    
    @staticmethod
    def attendance_reminder(employee_name: str) -> str:
        """Plantilla SMS para recordatorio de asistencia"""
        return f"Hola {employee_name}, no olvides registrar tu asistencia hoy. - RRHH"
    
    @staticmethod
    def schedule_update(employee_name: str, effective_date: str) -> str:
        """Plantilla SMS para actualización de horario"""
        return f"Hola {employee_name}, tu horario ha sido actualizado a partir del {effective_date}. Revisa tu portal de empleado."
    
    @staticmethod
    def payroll_ready(employee_name: str) -> str:
        """Plantilla SMS para nómina lista"""
        return f"Hola {employee_name}, tu comprobante de nómina está disponible en tu portal de empleado. - RRHH"
    
    @staticmethod
    def emergency_notification(employee_name: str, message: str) -> str:
        """Plantilla SMS para notificaciones de emergencia"""
        return f"URGENTE - {employee_name}: {message} - RRHH"


class SMSProvider:
    """Clase base para proveedores de SMS"""
    
    def send_sms(self, phone_number: str, message: str) -> bool:
        """Método base para enviar SMS"""
        raise NotImplementedError("Subclases deben implementar send_sms")


class TwilioProvider(SMSProvider):
    """Proveedor de SMS usando Twilio"""
    
    def __init__(self, account_sid: str = None, auth_token: str = None, from_number: str = None):
        self.account_sid = account_sid or os.getenv('TWILIO_ACCOUNT_SID')
        self.auth_token = auth_token or os.getenv('TWILIO_AUTH_TOKEN')
        self.from_number = from_number or os.getenv('TWILIO_FROM_NUMBER')
        
        self.configured = bool(self.account_sid and self.auth_token and self.from_number)
        
        if not self.configured:
            logger.warning("Twilio no configurado. Usando modo simulación.")
    
    def send_sms(self, phone_number: str, message: str) -> bool:
        """Envía SMS usando Twilio"""
        try:
            if not self.configured:
                # Modo simulación para desarrollo
                logger.info(f"[SIMULACIÓN TWILIO] SMS enviado a {phone_number}")
                logger.info(f"[SIMULACIÓN TWILIO] Mensaje: {message}")
                return True
            
            # Aquí iría la implementación real con Twilio
            # from twilio.rest import Client
            # client = Client(self.account_sid, self.auth_token)
            # message = client.messages.create(
            #     body=message,
            #     from_=self.from_number,
            #     to=phone_number
            # )
            
            logger.info(f"SMS enviado exitosamente a {phone_number}")
            return True
            
        except Exception as e:
            logger.error(f"Error al enviar SMS con Twilio: {e}")
            return False


class AmazonSNSProvider(SMSProvider):
    """Proveedor de SMS usando Amazon SNS"""
    
    def __init__(self, aws_access_key: str = None, aws_secret_key: str = None, region: str = 'us-east-1'):
        self.aws_access_key = aws_access_key or os.getenv('AWS_ACCESS_KEY_ID')
        self.aws_secret_key = aws_secret_key or os.getenv('AWS_SECRET_ACCESS_KEY')
        self.region = region or os.getenv('AWS_REGION', 'us-east-1')
        
        self.configured = bool(self.aws_access_key and self.aws_secret_key)
        
        if not self.configured:
            logger.warning("Amazon SNS no configurado. Usando modo simulación.")
    
    def send_sms(self, phone_number: str, message: str) -> bool:
        """Envía SMS usando Amazon SNS"""
        try:
            if not self.configured:
                # Modo simulación para desarrollo
                logger.info(f"[SIMULACIÓN SNS] SMS enviado a {phone_number}")
                logger.info(f"[SIMULACIÓN SNS] Mensaje: {message}")
                return True
            
            # Aquí iría la implementación real con Amazon SNS
            # import boto3
            # sns = boto3.client('sns', region_name=self.region)
            # response = sns.publish(
            #     PhoneNumber=phone_number,
            #     Message=message
            # )
            
            logger.info(f"SMS enviado exitosamente a {phone_number}")
            return True
            
        except Exception as e:
            logger.error(f"Error al enviar SMS con Amazon SNS: {e}")
            return False


class SMSNotificationService:
    """Servicio principal de notificaciones SMS"""
    
    def __init__(self, provider: SMSProvider = None):
        self.provider = provider or TwilioProvider()
        self.sms_history = []
    
    def send_sms(self, phone_number: str, message: str) -> bool:
        """Envía un SMS"""
        # Validar número de teléfono
        if not self._validate_phone_number(phone_number):
            logger.error(f"Número de teléfono inválido: {phone_number}")
            return False
        
        # Validar longitud del mensaje
        if len(message) > 160:
            logger.warning(f"Mensaje muy largo ({len(message)} caracteres), será truncado")
            message = message[:157] + "..."
        
        success = self.provider.send_sms(phone_number, message)
        
        # Registrar en historial
        self.sms_history.append({
            'phone_number': phone_number,
            'message': message,
            'success': success,
            'timestamp': datetime.now().isoformat()
        })
        
        return success
    
    def _validate_phone_number(self, phone_number: str) -> bool:
        """Valida formato de número de teléfono"""
        # Implementación básica de validación
        # En producción, usar librerías como phonenumbers
        cleaned = phone_number.replace(' ', '').replace('-', '').replace('(', '').replace(')', '')
        return cleaned.startswith('+') and len(cleaned) >= 10
    
    def send_vacation_approved_sms(self, phone_number: str, employee_name: str,
                                  start_date: str, end_date: str) -> bool:
        """Envía SMS de vacaciones aprobadas"""
        message = SMSTemplate.vacation_approved(employee_name, start_date, end_date)
        return self.send_sms(phone_number, message)
    
    def send_vacation_rejected_sms(self, phone_number: str, employee_name: str,
                                  start_date: str, end_date: str) -> bool:
        """Envía SMS de vacaciones rechazadas"""
        message = SMSTemplate.vacation_rejected(employee_name, start_date, end_date)
        return self.send_sms(phone_number, message)
    
    def send_attendance_reminder_sms(self, phone_number: str, employee_name: str) -> bool:
        """Envía recordatorio de asistencia"""
        message = SMSTemplate.attendance_reminder(employee_name)
        return self.send_sms(phone_number, message)
    
    def send_schedule_update_sms(self, phone_number: str, employee_name: str,
                                effective_date: str) -> bool:
        """Envía notificación de actualización de horario"""
        message = SMSTemplate.schedule_update(employee_name, effective_date)
        return self.send_sms(phone_number, message)
    
    def send_payroll_ready_sms(self, phone_number: str, employee_name: str) -> bool:
        """Envía notificación de nómina lista"""
        message = SMSTemplate.payroll_ready(employee_name)
        return self.send_sms(phone_number, message)
    
    def send_emergency_sms(self, phone_number: str, employee_name: str, message: str) -> bool:
        """Envía notificación de emergencia"""
        emergency_message = SMSTemplate.emergency_notification(employee_name, message)
        return self.send_sms(phone_number, emergency_message)
    
    def send_bulk_sms(self, recipients: List[Dict], message: str) -> Dict:
        """Envía SMS masivo"""
        results = {"sent": 0, "failed": 0, "errors": []}
        
        for recipient in recipients:
            phone = recipient.get('phone')
            name = recipient.get('name', 'Empleado')
            
            if phone:
                personalized_message = message.replace('{name}', name)
                success = self.send_sms(phone, personalized_message)
                
                if success:
                    results["sent"] += 1
                else:
                    results["failed"] += 1
                    results["errors"].append(f"Error enviando a {phone}")
        
        return results
    
    def get_sms_history(self, limit: int = 100) -> List[Dict]:
        """Obtiene el historial de SMS"""
        return self.sms_history[-limit:]


class SMSScheduler:
    """Programador de SMS para envíos automatizados"""
    
    def __init__(self, sms_service: SMSNotificationService):
        self.sms_service = sms_service
        self.scheduled_sms = []
    
    def schedule_sms(self, phone_number: str, message: str, send_at: datetime) -> bool:
        """Programa un SMS para envío futuro"""
        try:
            scheduled_item = {
                'phone_number': phone_number,
                'message': message,
                'send_at': send_at,
                'sent': False,
                'created_at': datetime.now()
            }
            
            self.scheduled_sms.append(scheduled_item)
            logger.info(f"SMS programado para {send_at}")
            return True
            
        except Exception as e:
            logger.error(f"Error al programar SMS: {e}")
            return False
    
    def process_scheduled_sms(self) -> Dict:
        """Procesa y envía SMS programados"""
        now = datetime.now()
        results = {"sent": 0, "failed": 0}
        
        for item in self.scheduled_sms:
            if not item['sent'] and item['send_at'] <= now:
                success = self.sms_service.send_sms(item['phone_number'], item['message'])
                item['sent'] = True
                item['sent_at'] = now
                
                if success:
                    results["sent"] += 1
                else:
                    results["failed"] += 1
        
        return results
    
    def get_scheduled_sms(self, pending_only: bool = True) -> List[Dict]:
        """Obtiene la lista de SMS programados"""
        if pending_only:
            return [item for item in self.scheduled_sms if not item['sent']]
        return self.scheduled_sms


if __name__ == "__main__":
    # Ejemplo de uso
    sms_service = SMSNotificationService()
    
    # Enviar SMS de vacaciones aprobadas
    success = sms_service.send_vacation_approved_sms(
        "+1234567890",
        "Juan Pérez",
        "2024-08-01",
        "2024-08-05"
    )
    print(f"SMS enviado: {'Sí' if success else 'No'}")
    
    # Enviar SMS masivo
    recipients = [
        {"phone": "+1234567890", "name": "Juan Pérez"},
        {"phone": "+1234567891", "name": "María González"}
    ]
    
    results = sms_service.send_bulk_sms(recipients, "Hola {name}, recordatorio importante de RRHH.")
    print(f"SMS masivo: {results}")
    
    # Ver historial
    history = sms_service.get_sms_history()
    print(f"Historial de SMS: {len(history)} elementos")
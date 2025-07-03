"""
Sistema de Notificaciones por Correo Electrónico
Sistema Integrado de Gestión de Recursos Humanos (SIGRH)
"""

import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders
from datetime import datetime
from typing import List, Dict, Optional
import os
import logging

# Configurar logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class EmailTemplate:
    """Plantillas de correo electrónico para diferentes tipos de notificaciones"""
    
    @staticmethod
    def vacation_approved(employee_name: str, start_date: str, end_date: str) -> Dict[str, str]:
        """Plantilla para vacaciones aprobadas"""
        subject = "Solicitud de Vacaciones Aprobada"
        body = f"""
        Estimado/a {employee_name},

        Su solicitud de vacaciones ha sido APROBADA.

        Detalles:
        - Fecha de inicio: {start_date}
        - Fecha de fin: {end_date}
        
        Disfrute de sus vacaciones.

        Saludos cordiales,
        Departamento de Recursos Humanos
        """
        return {"subject": subject, "body": body}
    
    @staticmethod
    def vacation_rejected(employee_name: str, start_date: str, end_date: str, reason: str = None) -> Dict[str, str]:
        """Plantilla para vacaciones rechazadas"""
        subject = "Solicitud de Vacaciones Rechazada"
        body = f"""
        Estimado/a {employee_name},

        Su solicitud de vacaciones ha sido RECHAZADA.

        Detalles:
        - Fecha de inicio: {start_date}
        - Fecha de fin: {end_date}
        {f"- Razón: {reason}" if reason else ""}
        
        Para más información, contacte al Departamento de Recursos Humanos.

        Saludos cordiales,
        Departamento de Recursos Humanos
        """
        return {"subject": subject, "body": body}
    
    @staticmethod
    def payroll_generated(employee_name: str, pay_period: str, net_pay: float) -> Dict[str, str]:
        """Plantilla para nómina generada"""
        subject = "Comprobante de Nómina Disponible"
        body = f"""
        Estimado/a {employee_name},

        Su comprobante de nómina está disponible.

        Detalles:
        - Período: {pay_period}
        - Salario neto: ${net_pay:,.2f}
        
        Puede acceder a su portal de empleado para ver los detalles completos.

        Saludos cordiales,
        Departamento de Recursos Humanos
        """
        return {"subject": subject, "body": body}
    
    @staticmethod
    def schedule_update(employee_name: str, effective_date: str) -> Dict[str, str]:
        """Plantilla para actualización de horario"""
        subject = "Actualización de Horario de Trabajo"
        body = f"""
        Estimado/a {employee_name},

        Su horario de trabajo ha sido actualizado.

        Fecha efectiva: {effective_date}
        
        Revise su portal de empleado para ver los nuevos horarios.

        Saludos cordiales,
        Departamento de Recursos Humanos
        """
        return {"subject": subject, "body": body}
    
    @staticmethod
    def attendance_alert(employee_name: str, date: str, issue: str) -> Dict[str, str]:
        """Plantilla para alertas de asistencia"""
        subject = "Alerta de Asistencia"
        body = f"""
        Estimado/a {employee_name},

        Se ha detectado una irregularidad en su asistencia.

        Fecha: {date}
        Detalle: {issue}
        
        Si hay algún error, contacte al Departamento de Recursos Humanos.

        Saludos cordiales,
        Departamento de Recursos Humanos
        """
        return {"subject": subject, "body": body}


class EmailNotificationService:
    """Servicio de notificaciones por correo electrónico"""
    
    def __init__(self, smtp_server: str = None, smtp_port: int = 587,
                 email: str = None, password: str = None):
        self.smtp_server = smtp_server or os.getenv('SMTP_SERVER', 'smtp.gmail.com')
        self.smtp_port = smtp_port or int(os.getenv('SMTP_PORT', '587'))
        self.email = email or os.getenv('EMAIL_ADDRESS', 'noreply@company.com')
        self.password = password or os.getenv('EMAIL_PASSWORD', '')
        
        # En producción, usar variables de entorno para las credenciales
        self.configured = bool(self.email and self.password)
        
        if not self.configured:
            logger.warning("Servicio de email no configurado. Usando modo simulación.")
    
    def send_email(self, to_email: str, subject: str, body: str, 
                   attachments: List[str] = None) -> bool:
        """Envía un correo electrónico"""
        try:
            if not self.configured:
                # Modo simulación para desarrollo
                logger.info(f"[SIMULACIÓN] Email enviado a {to_email}")
                logger.info(f"[SIMULACIÓN] Asunto: {subject}")
                logger.info(f"[SIMULACIÓN] Cuerpo: {body[:100]}...")
                return True
            
            # Crear mensaje
            msg = MIMEMultipart()
            msg['From'] = self.email
            msg['To'] = to_email
            msg['Subject'] = subject
            
            # Agregar cuerpo del mensaje
            msg.attach(MIMEText(body, 'plain'))
            
            # Agregar archivos adjuntos si existen
            if attachments:
                for file_path in attachments:
                    if os.path.exists(file_path):
                        with open(file_path, "rb") as attachment:
                            part = MIMEBase('application', 'octet-stream')
                            part.set_payload(attachment.read())
                            encoders.encode_base64(part)
                            part.add_header(
                                'Content-Disposition',
                                f'attachment; filename= {os.path.basename(file_path)}'
                            )
                            msg.attach(part)
            
            # Enviar email
            server = smtplib.SMTP(self.smtp_server, self.smtp_port)
            server.starttls()
            server.login(self.email, self.password)
            server.send_message(msg)
            server.quit()
            
            logger.info(f"Email enviado exitosamente a {to_email}")
            return True
            
        except Exception as e:
            logger.error(f"Error al enviar email: {e}")
            return False
    
    def send_vacation_approved_notification(self, employee_email: str, employee_name: str,
                                          start_date: str, end_date: str) -> bool:
        """Envía notificación de vacaciones aprobadas"""
        template = EmailTemplate.vacation_approved(employee_name, start_date, end_date)
        return self.send_email(employee_email, template['subject'], template['body'])
    
    def send_vacation_rejected_notification(self, employee_email: str, employee_name: str,
                                          start_date: str, end_date: str, reason: str = None) -> bool:
        """Envía notificación de vacaciones rechazadas"""
        template = EmailTemplate.vacation_rejected(employee_name, start_date, end_date, reason)
        return self.send_email(employee_email, template['subject'], template['body'])
    
    def send_payroll_notification(self, employee_email: str, employee_name: str,
                                 pay_period: str, net_pay: float) -> bool:
        """Envía notificación de nómina generada"""
        template = EmailTemplate.payroll_generated(employee_name, pay_period, net_pay)
        return self.send_email(employee_email, template['subject'], template['body'])
    
    def send_schedule_update_notification(self, employee_email: str, employee_name: str,
                                        effective_date: str) -> bool:
        """Envía notificación de actualización de horario"""
        template = EmailTemplate.schedule_update(employee_name, effective_date)
        return self.send_email(employee_email, template['subject'], template['body'])
    
    def send_attendance_alert(self, employee_email: str, employee_name: str,
                             date: str, issue: str) -> bool:
        """Envía alerta de asistencia"""
        template = EmailTemplate.attendance_alert(employee_name, date, issue)
        return self.send_email(employee_email, template['subject'], template['body'])
    
    def send_bulk_notification(self, recipients: List[Dict], subject: str, body: str) -> Dict:
        """Envía notificación masiva"""
        results = {"sent": 0, "failed": 0, "errors": []}
        
        for recipient in recipients:
            email = recipient.get('email')
            name = recipient.get('name', 'Empleado')
            
            if email:
                personalized_body = body.replace('{name}', name)
                success = self.send_email(email, subject, personalized_body)
                
                if success:
                    results["sent"] += 1
                else:
                    results["failed"] += 1
                    results["errors"].append(f"Error enviando a {email}")
        
        return results


class NotificationManager:
    """Gestor principal de notificaciones"""
    
    def __init__(self):
        self.email_service = EmailNotificationService()
        self.notification_history = []
    
    def send_notification(self, notification_type: str, recipient: Dict, 
                         data: Dict, channels: List[str] = None) -> bool:
        """Envía notificación usando los canales especificados"""
        channels = channels or ['email']
        success = False
        
        try:
            if 'email' in channels:
                success = self._send_email_notification(notification_type, recipient, data)
            
            # Aquí se pueden agregar otros canales como SMS, push notifications, etc.
            
            # Registrar en historial
            self.notification_history.append({
                'type': notification_type,
                'recipient': recipient,
                'channels': channels,
                'success': success,
                'timestamp': datetime.now().isoformat(),
                'data': data
            })
            
            return success
            
        except Exception as e:
            logger.error(f"Error al enviar notificación: {e}")
            return False
    
    def _send_email_notification(self, notification_type: str, recipient: Dict, data: Dict) -> bool:
        """Envía notificación por email según el tipo"""
        email = recipient.get('email')
        name = recipient.get('name')
        
        if not email or not name:
            logger.error("Información de destinatario incompleta")
            return False
        
        if notification_type == 'vacation_approved':
            return self.email_service.send_vacation_approved_notification(
                email, name, data['start_date'], data['end_date']
            )
        elif notification_type == 'vacation_rejected':
            return self.email_service.send_vacation_rejected_notification(
                email, name, data['start_date'], data['end_date'], data.get('reason')
            )
        elif notification_type == 'payroll_generated':
            return self.email_service.send_payroll_notification(
                email, name, data['pay_period'], data['net_pay']
            )
        elif notification_type == 'schedule_update':
            return self.email_service.send_schedule_update_notification(
                email, name, data['effective_date']
            )
        elif notification_type == 'attendance_alert':
            return self.email_service.send_attendance_alert(
                email, name, data['date'], data['issue']
            )
        else:
            logger.error(f"Tipo de notificación no soportado: {notification_type}")
            return False
    
    def get_notification_history(self, limit: int = 100) -> List[Dict]:
        """Obtiene el historial de notificaciones"""
        return self.notification_history[-limit:]


if __name__ == "__main__":
    # Ejemplo de uso
    manager = NotificationManager()
    
    # Enviar notificación de vacaciones aprobadas
    recipient = {
        'email': 'juan.perez@company.com',
        'name': 'Juan Pérez'
    }
    
    data = {
        'start_date': '2024-08-01',
        'end_date': '2024-08-05'
    }
    
    success = manager.send_notification('vacation_approved', recipient, data)
    print(f"Notificación enviada: {'Sí' if success else 'No'}")
    
    # Ver historial
    history = manager.get_notification_history()
    print(f"Historial de notificaciones: {len(history)} elementos")
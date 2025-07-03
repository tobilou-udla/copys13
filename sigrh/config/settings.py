"""
Configuración del Sistema SIGRH
Sistema Integrado de Gestión de Recursos Humanos
"""

import os
from typing import Dict, Any


class DatabaseConfig:
    """Configuración de la base de datos"""
    
    def __init__(self):
        self.database_url = os.getenv('DATABASE_URL', 'sqlite:///sigrh.db')
        self.database_type = os.getenv('DATABASE_TYPE', 'sqlite')
        self.host = os.getenv('DB_HOST', 'localhost')
        self.port = int(os.getenv('DB_PORT', '5432'))
        self.username = os.getenv('DB_USERNAME', 'sigrh_user')
        self.password = os.getenv('DB_PASSWORD', '')
        self.database_name = os.getenv('DB_NAME', 'sigrh')
    
    def get_connection_string(self) -> str:
        """Retorna la cadena de conexión según el tipo de base de datos"""
        if self.database_type == 'sqlite':
            return f'sqlite:///{self.database_name}.db'
        elif self.database_type == 'postgresql':
            return f'postgresql://{self.username}:{self.password}@{self.host}:{self.port}/{self.database_name}'
        elif self.database_type == 'mysql':
            return f'mysql://{self.username}:{self.password}@{self.host}:{self.port}/{self.database_name}'
        else:
            return self.database_url


class EmailConfig:
    """Configuración del servicio de email"""
    
    def __init__(self):
        self.smtp_server = os.getenv('SMTP_SERVER', 'smtp.gmail.com')
        self.smtp_port = int(os.getenv('SMTP_PORT', '587'))
        self.email_address = os.getenv('EMAIL_ADDRESS', 'noreply@company.com')
        self.email_password = os.getenv('EMAIL_PASSWORD', '')
        self.use_tls = os.getenv('EMAIL_USE_TLS', 'True').lower() == 'true'
        self.sender_name = os.getenv('EMAIL_SENDER_NAME', 'SIGRH - Recursos Humanos')


class SMSConfig:
    """Configuración del servicio de SMS"""
    
    def __init__(self):
        self.provider = os.getenv('SMS_PROVIDER', 'twilio')  # 'twilio' o 'sns'
        
        # Configuración Twilio
        self.twilio_account_sid = os.getenv('TWILIO_ACCOUNT_SID', '')
        self.twilio_auth_token = os.getenv('TWILIO_AUTH_TOKEN', '')
        self.twilio_from_number = os.getenv('TWILIO_FROM_NUMBER', '')
        
        # Configuración Amazon SNS
        self.aws_access_key_id = os.getenv('AWS_ACCESS_KEY_ID', '')
        self.aws_secret_access_key = os.getenv('AWS_SECRET_ACCESS_KEY', '')
        self.aws_region = os.getenv('AWS_REGION', 'us-east-1')


class SecurityConfig:
    """Configuración de seguridad"""
    
    def __init__(self):
        self.secret_key = os.getenv('SECRET_KEY', 'your-secret-key-here')
        self.jwt_secret_key = os.getenv('JWT_SECRET_KEY', 'your-jwt-secret-key-here')
        self.jwt_expiration_hours = int(os.getenv('JWT_EXPIRATION_HOURS', '24'))
        self.password_min_length = int(os.getenv('PASSWORD_MIN_LENGTH', '8'))
        self.max_login_attempts = int(os.getenv('MAX_LOGIN_ATTEMPTS', '5'))
        self.lockout_duration_minutes = int(os.getenv('LOCKOUT_DURATION_MINUTES', '30'))


class BiometricConfig:
    """Configuración del sistema biométrico"""
    
    def __init__(self):
        self.device_timeout = int(os.getenv('BIOMETRIC_DEVICE_TIMEOUT', '30'))
        self.max_failed_attempts = int(os.getenv('BIOMETRIC_MAX_FAILED_ATTEMPTS', '3'))
        self.enable_face_recognition = os.getenv('ENABLE_FACE_RECOGNITION', 'True').lower() == 'true'
        self.enable_fingerprint = os.getenv('ENABLE_FINGERPRINT', 'True').lower() == 'true'
        self.confidence_threshold = float(os.getenv('BIOMETRIC_CONFIDENCE_THRESHOLD', '0.8'))


class PayrollConfig:
    """Configuración del sistema de nómina"""
    
    def __init__(self):
        self.default_currency = os.getenv('DEFAULT_CURRENCY', 'USD')
        self.tax_rate = float(os.getenv('DEFAULT_TAX_RATE', '0.15'))
        self.social_security_rate = float(os.getenv('SOCIAL_SECURITY_RATE', '0.06'))
        self.health_insurance_cost = float(os.getenv('HEALTH_INSURANCE_COST', '150.0'))
        self.overtime_multiplier = float(os.getenv('OVERTIME_MULTIPLIER', '1.5'))
        self.annual_vacation_days = int(os.getenv('ANNUAL_VACATION_DAYS', '22'))


class ApplicationConfig:
    """Configuración general de la aplicación"""
    
    def __init__(self):
        self.app_name = os.getenv('APP_NAME', 'SIGRH')
        self.version = os.getenv('APP_VERSION', '1.0.0')
        self.debug = os.getenv('DEBUG', 'False').lower() == 'true'
        self.host = os.getenv('HOST', '0.0.0.0')
        self.port = int(os.getenv('PORT', '5000'))
        self.timezone = os.getenv('TIMEZONE', 'UTC')
        self.language = os.getenv('LANGUAGE', 'es')
        self.company_name = os.getenv('COMPANY_NAME', 'Mi Empresa')
        self.company_address = os.getenv('COMPANY_ADDRESS', '')
        self.company_phone = os.getenv('COMPANY_PHONE', '')
        self.company_email = os.getenv('COMPANY_EMAIL', '')


class SIGRHConfig:
    """Configuración principal del sistema SIGRH"""
    
    def __init__(self):
        self.database = DatabaseConfig()
        self.email = EmailConfig()
        self.sms = SMSConfig()
        self.security = SecurityConfig()
        self.biometric = BiometricConfig()
        self.payroll = PayrollConfig()
        self.app = ApplicationConfig()
    
    def to_dict(self) -> Dict[str, Any]:
        """Convierte la configuración a diccionario"""
        return {
            'database': {
                'type': self.database.database_type,
                'host': self.database.host,
                'port': self.database.port,
                'name': self.database.database_name
            },
            'email': {
                'smtp_server': self.email.smtp_server,
                'smtp_port': self.email.smtp_port,
                'sender_name': self.email.sender_name
            },
            'sms': {
                'provider': self.sms.provider
            },
            'security': {
                'password_min_length': self.security.password_min_length,
                'max_login_attempts': self.security.max_login_attempts,
                'lockout_duration_minutes': self.security.lockout_duration_minutes
            },
            'biometric': {
                'device_timeout': self.biometric.device_timeout,
                'max_failed_attempts': self.biometric.max_failed_attempts,
                'enable_face_recognition': self.biometric.enable_face_recognition,
                'enable_fingerprint': self.biometric.enable_fingerprint
            },
            'payroll': {
                'default_currency': self.payroll.default_currency,
                'tax_rate': self.payroll.tax_rate,
                'annual_vacation_days': self.payroll.annual_vacation_days
            },
            'app': {
                'name': self.app.app_name,
                'version': self.app.version,
                'company_name': self.app.company_name,
                'timezone': self.app.timezone,
                'language': self.app.language
            }
        }
    
    def validate(self) -> Dict[str, list]:
        """Valida la configuración y retorna errores encontrados"""
        errors = {
            'database': [],
            'email': [],
            'sms': [],
            'security': [],
            'biometric': [],
            'payroll': [],
            'app': []
        }
        
        # Validar configuración de base de datos
        if not self.database.database_name:
            errors['database'].append('Nombre de base de datos requerido')
        
        # Validar configuración de email
        if not self.email.email_address:
            errors['email'].append('Dirección de email requerida')
        if not self.email.smtp_server:
            errors['email'].append('Servidor SMTP requerido')
        
        # Validar configuración de seguridad
        if len(self.security.secret_key) < 32:
            errors['security'].append('Clave secreta debe tener al menos 32 caracteres')
        if self.security.password_min_length < 6:
            errors['security'].append('Longitud mínima de contraseña debe ser al menos 6')
        
        # Validar configuración de nómina
        if self.payroll.tax_rate < 0 or self.payroll.tax_rate > 1:
            errors['payroll'].append('Tasa de impuesto debe estar entre 0 y 1')
        if self.payroll.annual_vacation_days < 0:
            errors['payroll'].append('Días de vacaciones anuales debe ser positivo')
        
        # Validar configuración biométrica
        if self.biometric.confidence_threshold < 0 or self.biometric.confidence_threshold > 1:
            errors['biometric'].append('Umbral de confianza debe estar entre 0 y 1')
        
        # Validar configuración de aplicación
        if not self.app.app_name:
            errors['app'].append('Nombre de aplicación requerido')
        if not self.app.company_name:
            errors['app'].append('Nombre de empresa requerido')
        
        return errors
    
    def is_valid(self) -> bool:
        """Verifica si la configuración es válida"""
        errors = self.validate()
        return not any(error_list for error_list in errors.values())


# Instancia global de configuración
config = SIGRHConfig()


def load_config_from_file(config_file: str = '.env') -> SIGRHConfig:
    """Carga configuración desde archivo"""
    if os.path.exists(config_file):
        with open(config_file, 'r') as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith('#'):
                    key, value = line.split('=', 1)
                    os.environ[key] = value
    
    return SIGRHConfig()


if __name__ == "__main__":
    # Ejemplo de uso
    config = SIGRHConfig()
    
    print("Configuración SIGRH:")
    print(f"- Aplicación: {config.app.app_name} v{config.app.version}")
    print(f"- Empresa: {config.app.company_name}")
    print(f"- Base de datos: {config.database.database_type}")
    print(f"- Email: {config.email.smtp_server}:{config.email.smtp_port}")
    print(f"- SMS: {config.sms.provider}")
    
    # Validar configuración
    errors = config.validate()
    if config.is_valid():
        print("\n✅ Configuración válida")
    else:
        print("\n❌ Errores en la configuración:")
        for section, error_list in errors.items():
            if error_list:
                print(f"  {section}: {', '.join(error_list)}")
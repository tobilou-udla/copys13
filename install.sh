#!/bin/bash

# Script de instalación y configuración del Sistema SIGRH
# Sistema Integrado de Gestión de Recursos Humanos

echo "🚀 Iniciando instalación del Sistema SIGRH..."

# Verificar Python
if ! command -v python3 &> /dev/null; then
    echo "❌ Python 3 no está instalado. Por favor instala Python 3.8 o superior."
    exit 1
fi

echo "✅ Python encontrado: $(python3 --version)"

# Crear entorno virtual si no existe
if [ ! -d "venv" ]; then
    echo "📦 Creando entorno virtual..."
    python3 -m venv venv
fi

# Activar entorno virtual
echo "🔧 Activando entorno virtual..."
source venv/bin/activate

# Actualizar pip
echo "⬆️ Actualizando pip..."
pip install --upgrade pip

# Instalar dependencias
echo "📚 Instalando dependencias..."
cd sigrh
pip install -r requirements.txt

# Crear archivo de configuración si no existe
if [ ! -f ".env" ]; then
    echo "⚙️ Configurando variables de entorno..."
    cp config/.env.example .env
    echo "✏️ Por favor edita el archivo sigrh/.env con tus configuraciones."
fi

# Verificar instalación
echo "🧪 Verificando instalación..."
python -c "
from main import SIGRHApplication
app = SIGRHApplication()
print('✅ Sistema SIGRH instalado correctamente')
print(f'📋 Versión: {app.config.app.version}')
print(f'🏢 Empresa: {app.config.app.company_name}')
"

echo ""
echo "🎉 ¡Instalación completada!"
echo ""
echo "📖 Para ejecutar el sistema:"
echo "   • Consola interactiva:    python main.py"
echo "   • Portal web:             python interfaces/web/app.py"
echo "   • API móvil:              python interfaces/mobile/mobile_api.py"
echo ""
echo "🐳 Para usar Docker:"
echo "   • docker-compose up sigrh-web"
echo "   • docker-compose up sigrh-mobile"
echo "   • docker-compose up sigrh-console"
echo ""
echo "📚 Documentación: https://github.com/tobilou-udla/copys13/wiki"
echo ""
echo "¡Que tengas un excelente día gestionando recursos humanos! 👥"
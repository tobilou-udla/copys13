FROM python:3.12-slim

WORKDIR /app

# Instalar dependencias del sistema
RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Copiar archivos de requisitos
COPY sigrh/requirements.txt .

# Instalar dependencias de Python
RUN pip install --no-cache-dir -r requirements.txt

# Copiar código fuente
COPY sigrh/ .

# Crear directorio para la base de datos
RUN mkdir -p /app/data

# Exponer puertos
EXPOSE 5000 8000

# Variables de entorno por defecto
ENV FLASK_APP=interfaces/web/app.py
ENV DATABASE_URL=sqlite:///data/sigrh.db
ENV DEBUG=False

# Comando por defecto (web interface)
CMD ["python", "interfaces/web/app.py"]
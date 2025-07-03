-- Datos de ejemplo para SIGRH
-- Insertar empleados de ejemplo

INSERT INTO employees (employee_number, first_name, last_name, email, phone, hire_date, position, department, salary, status) VALUES
('EMP001', 'Juan', 'Pérez', 'juan.perez@company.com', '+1234567890', '2023-01-15', 'Analista de Sistemas', 'IT', 3500.00, 'active'),
('EMP002', 'María', 'González', 'maria.gonzalez@company.com', '+1234567891', '2023-02-01', 'Gerente de RRHH', 'Recursos Humanos', 4500.00, 'active'),
('EMP003', 'Carlos', 'Rodríguez', 'carlos.rodriguez@company.com', '+1234567892', '2023-03-10', 'Contador', 'Finanzas', 3200.00, 'active'),
('EMP004', 'Ana', 'Martínez', 'ana.martinez@company.com', '+1234567893', '2023-04-05', 'Desarrollador Senior', 'IT', 4000.00, 'active'),
('EMP005', 'Luis', 'Sánchez', 'luis.sanchez@company.com', '+1234567894', '2023-05-20', 'Asistente Administrativo', 'Administración', 2800.00, 'active');

-- Insertar horarios de ejemplo
INSERT INTO schedules (employee_id, day_of_week, start_time, end_time, break_duration) VALUES
-- Juan Pérez (ID: 1) - Lunes a Viernes 9:00-17:00
(1, 1, '09:00:00', '17:00:00', 60),
(1, 2, '09:00:00', '17:00:00', 60),
(1, 3, '09:00:00', '17:00:00', 60),
(1, 4, '09:00:00', '17:00:00', 60),
(1, 5, '09:00:00', '17:00:00', 60),
-- María González (ID: 2) - Lunes a Viernes 8:00-16:00
(2, 1, '08:00:00', '16:00:00', 60),
(2, 2, '08:00:00', '16:00:00', 60),
(2, 3, '08:00:00', '16:00:00', 60),
(2, 4, '08:00:00', '16:00:00', 60),
(2, 5, '08:00:00', '16:00:00', 60);

-- Insertar vacaciones de ejemplo
INSERT INTO vacations (employee_id, start_date, end_date, days_requested, vacation_type, status, reason) VALUES
(1, '2024-07-15', '2024-07-19', 5, 'annual', 'approved', 'Vacaciones familiares'),
(2, '2024-08-01', '2024-08-15', 10, 'annual', 'pending', 'Vacaciones de verano'),
(3, '2024-06-10', '2024-06-12', 3, 'sick', 'approved', 'Permiso médico');

-- Insertar compensaciones de ejemplo
INSERT INTO compensations (employee_id, compensation_type, amount, currency, pay_period, effective_date, description) VALUES
(1, 'salary', 3500.00, 'USD', 'monthly', '2023-01-15', 'Salario base mensual'),
(2, 'salary', 4500.00, 'USD', 'monthly', '2023-02-01', 'Salario base mensual'),
(3, 'salary', 3200.00, 'USD', 'monthly', '2023-03-10', 'Salario base mensual'),
(4, 'salary', 4000.00, 'USD', 'monthly', '2023-04-05', 'Salario base mensual'),
(5, 'salary', 2800.00, 'USD', 'monthly', '2023-05-20', 'Salario base mensual'),
(1, 'bonus', 500.00, 'USD', 'one-time', '2023-12-15', 'Bono navideño'),
(2, 'bonus', 750.00, 'USD', 'one-time', '2023-12-15', 'Bono navideño');
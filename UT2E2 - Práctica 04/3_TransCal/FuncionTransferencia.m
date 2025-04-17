% Carga de datos
data = csvread('datos_termicos.csv', 1, 0); % Omite encabezado
t = data(:,1);               % Tiempo
T_BMP = data(:,2);           % Temperatura BMP180
T_LM35 = data(:,3);          % Temperatura LM35

% Puedes elegir con qué sensor trabajar, por ejemplo el BMP:
T = T_BMP;

% Graficar la respuesta
plot(t, T, 'b', 'linewidth', 2);
xlabel('Tiempo (s)');
ylabel('Temperatura (°C)');
title('Respuesta al escalón térmico');
grid on;

% Estimar parámetros
T0 = T(1);                 % Temperatura inicial
Tf = T(end);               % Temperatura final
delta_T = Tf - T0;

% Temperatura a 63.2% del cambio total
T63 = T0 + 0.632 * delta_T;

% Buscar el tiempo donde se alcanza esa temperatura
idx = find(T >= T63, 1);
tau = t(idx);              % Constante de tiempo
K = delta_T;               % Ganancia (escalón unitaria = 1°C de entrada)

printf("Ganancia K = %.2f\n", K);
printf("Constante de tiempo τ = %.2f s\n", tau);

% Mostrar función de transferencia estimada
printf("Función de transferencia: G(s) = %.2f / (%.2f s + 1)\n", K, tau);


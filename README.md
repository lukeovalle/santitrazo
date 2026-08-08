# Santitrazo
Seguidor de línea usando un atmega328p

## Estructura del directorio
placa/      proyecto de KiCAD
codigo/     código de Arduino


## [TODO](TODO)
 - [ ] describir mejor el proyecto

## Mediciones 
Placa + sensores
    5V 0.9A
    
Motores
    5V  0.3A
    6V  1.3A


## Valores PID
P    | I      | D   | tiempo | pista grande
0.85 | 1e-3   | 6   | 4.6    |
0.9  | 2e-3   | 6   | 4.8    | 28
0.95 | 1.2e-3 | 6.2 | 5.2    |
0.85 | 1e-3   | 6   | --     | 27.88
0.92 | 1.2e-3 | 6.1 | 5.2    |
0.92 | 1.2e-3 | 6.1 | 4.7    | 28.3 (rigidizar ruedas traseras, lubricar placa, bat 7,1 V)
1    | 1.2e-3 | 6.2 | ------ |     (bat 7,8 V)
1.1  | 1.2e-3 | 6.8 | 5.7    |     (bat 7,8 V)
1    | 1.2e-3 | 3   | 4.6    |  (07/08/26 PID cada 10ms, promediado de sensores)
1.05 | 1.2e-3 | 5   | 4.6    | 
1.1  | 1.2e-3 | 6   | 4.4    |
1.1  | 1.5e-3 | 7   | 4.4    |
1.1  | 1.5e-3 | 8   | 4.4    | 24.3  (8.14V)

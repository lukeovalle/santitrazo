// config.h

#ifndef CONFIG__H_
#define CONFIG__H_

#define CONTROL_PERIODO_MS  10

// Límite de la salida del PID, que se resta/suma a vel_max (255) en cada motor.
//   510 (= 2 * 255): caso extremo, una rueda a +255 y la otra a -255.
//   255:             el motor interno nunca pasa de 0, o sea sin marcha atrás.
#define PID_MAX 510

// Variables del PID
#define PID_KP  1.5
#define PID_KD  15.0
#define PID_KI  1.3e-4

// Velocidades normal y turbo. valor máximo = 255
#define VEL_NORMAL  160
#define VEL_TURBO   215

// Tiempos de entrada y duración del turbo
#define TURBO_MS_ENTRADA  1500  // recta limpia antes de activar
#define TURBO_MS_DURACION 1000  // máximo en turbo

// la duración son los ticks acumulados en la entrada + el tiempo real de duración
#define TURBO_TICKS_ENTRADA   (TURBO_MS_ENTRADA / CONTROL_PERIODO_MS)
#define TURBO_TICKS_DURACION  (TURBO_TICKS_ENTRADA + TURBO_MS_DURACION / CONTROL_PERIODO_MS)

// error admitido para entrar y para salir del turbo
#define TURBO_ERROR_ENTRADA 100
#define TURBO_ERROR_SALIDA  150

#endif

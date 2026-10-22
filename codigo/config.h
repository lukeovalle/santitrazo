// config.h

#ifndef CONFIG__H_
#define CONFIG__H_


// Límite de la salida del PID, que se resta/suma a vel_max (255) en cada motor.
//   510 (= 2 * 255): caso extremo, una rueda a +255 y la otra a -255.
//   255:             el motor interno nunca pasa de 0, o sea sin marcha atrás.
#define PID_MAX 510

// Variables del PID
#define PID_KP 1.0
#define PID_KD 12.0
#define PID_KI 1.3e-2

// velocidades normal y turbo. valor máximo = 255
#define VEL_NORMAL 195
#define VEL_TURBO  240

// 1ms = 1 tick
// la duración son los ticks acumulados en la entrada + el tiempo real de duración
#define TURBO_TICKS_ENTRADA  1000
#define TURBO_TICKS_DURACION (TURBO_TICKS_ENTRADA + 2 * 1000)

#endif

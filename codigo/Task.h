// Task.h

#ifndef TASK__H_
#define TASK__H_

class Task {
  public:
    // periodTicks: cada cuántos ticks (ms) se ejecuta update() de la tarea
    Task(unsigned long periodTicks = 1) : mPeriodTicks(periodTicks) {}

    // la clase que hereda debe definir estos dos métodos
    virtual void init() = 0;
    virtual void update() = 0;

    void addTicks(unsigned long);
    void consumeTick(void);
    unsigned long pendingTicks(void);

    // el Executor llama a este método, que llama a update() cuando pasan los ticks
    void run(void);

  private:
    unsigned long mTick = 0;
    unsigned long mPeriodTicks;
    unsigned long mPeriodCount = 0;
};

#endif

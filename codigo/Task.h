// Task.h

#ifndef TASK__H_
#define TASK__H_

class Task {
  public:
    virtual void init() = 0;
    virtual void update() = 0;

    void addTicks(unsigned long);
    void consumeTick(void);
    unsigned long pendingTicks(void);

  private:
    unsigned long mTick = 0;
};

#endif

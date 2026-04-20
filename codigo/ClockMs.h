// ClockMs.h

#ifndef CLOCKMS__H_
#define CLOCKMS__H_

class ClockMs {
  public:
    ClockMs(void) : mLastMs(0) {}
    void init(void);
    bool ms_passed(void);
    unsigned long pending_ticks(void);


  private:
    unsigned long mLastMs;
};

#endif

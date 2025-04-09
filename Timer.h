#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool const start_check() {return is_started;};
    bool const pause_check() {return is_paused;};

private:
    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;
};

#endif // TIMER_H_INCLUDED

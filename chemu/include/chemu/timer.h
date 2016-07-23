#ifndef _TIMER_H
#define _TIMER_H

#ifndef _CHIPTIMER_IMPL
#define _CHIPTIMER_IMPL
typedef struct ChipTimer_s *ChipTimer;
#endif

// timer interval in microseconds (60Hz ~ 16,666 microseconds)
#define CHIP_TIMER_INTERVAL 16666

ChipTimer chiptimer_create(int initialValue);

void chiptimer_destroy(ChipTimer timer);

int chiptimer_get(ChipTimer timer);

void chiptimer_set(ChipTimer timer, int value);

void chiptimer_start(ChipTimer timer);

void chiptimer_stop(ChipTimer timer);


#endif
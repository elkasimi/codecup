#ifndef __TIMER_H__
#define __TIMER_H__

void Timer_start();
void Timer_stop();
Int Timer_get_delta_time();
Int Timer_get_total_time();
Int Timer_get_max_time_for_move(Position* pos);
void Timer_set_alarm(Int t);
void Timer_clear_alarm();
Bool Timer_is_time_over();

#endif

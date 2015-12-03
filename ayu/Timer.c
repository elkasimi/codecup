#include "Common.h"

#include "Timer.h"
#include "Position.h"

#define FIRST_PHASE_MOVES 60
#define FIRST_PHASE_TIME 900
#define LAST_PHASE_MOVES 100
#define LAST_PHASE_TIME 200
#define MIN_TIME 100

volatile Bool time_over;

#if WINDOWS_VERSION

HANDLE hTimer = NULL;
HANDLE hTimerQueue = NULL;

VOID CALLBACK alarm_callback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	(void)lpParam;
	(void)TimerOrWaitFired;
	time_over = TRUE;
}

#else
typedef struct sigaction handler_t;
handler_t old_handler, new_handler;

void alarm_callback(Int sig) {
	time_over = TRUE;
}

#endif

static clock_t start_clock;
static clock_t end_clock;
static Int total_time = 0;

void Timer_start() {
	start_clock = clock();
}

void Timer_stop() {
	end_clock = clock();
}

Int Timer_get_delta_time() {
	ULong64 delta_time = end_clock - start_clock;
	delta_time *= 1000;
	delta_time /= CLOCKS_PER_SEC;
	total_time += (Int)delta_time;
	return (Int)delta_time;
}

Int Timer_get_total_time() {
	return total_time;
}

Int Timer_get_max_time_for_move(Position* pos) {
	Int max_time;
	if (pos->moves < FIRST_PHASE_MOVES) {
		max_time = FIRST_PHASE_TIME;
	} else if (pos->moves < LAST_PHASE_MOVES) {
		max_time = LAST_PHASE_TIME;
	} else {
		max_time = MIN_TIME;
	}
	return max_time;
}

void Timer_set_alarm(Int t) {
#if WINDOWS_VERSION
	int arg = 123;
	// Create the timer queue.
	hTimerQueue = CreateTimerQueue();
	if (NULL == hTimerQueue) {
		fprintf(stderr, "CreateTimerQueue failed (%d)\n", GetLastError());
	}
	// Set a timer to call the timer routine in 10 seconds.
	if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
	                           (WAITORTIMERCALLBACK)alarm_callback, &arg, t, 0, 0)) {
		fprintf(stderr, "CreateTimerQueueTimer failed (%d)\n", GetLastError());
	}
#else
	struct itimerval new_timer, old_timer;
	//Install signal handler
	new_handler.sa_handler = alarm_callback;
	sigaction(SIGALRM, &new_handler, &old_handler);
	//Set timer with setitimer
	new_timer.it_interval.tv_sec = 0;
	new_timer.it_interval.tv_usec = 0;
	new_timer.it_value.tv_sec = (time_t)(t / 1000);
	new_timer.it_value.tv_usec = (suseconds_t)((t % 1000) * 1000);
	setitimer(ITIMER_REAL, &new_timer, &old_timer);
#endif
	time_over = FALSE;
}

void Timer_clear_alarm() {
#if WINDOWS_VERSION
	// Delete all timers in the timer queue.
	if (!DeleteTimerQueue(hTimerQueue)) {
		fprintf(stderr, "DeleteTimerQueue failed (%d)\n", GetLastError());
	}
	hTimer = NULL;
	hTimerQueue = NULL;
#else
	struct itimerval stop_timer = { { 0, 0 }, { 0, 0 } };
	setitimer(ITIMER_REAL, &stop_timer, NULL);
	sigaction(SIGALRM, &old_handler, NULL);
#endif
}

Bool Timer_is_time_over() {
	return time_over;
}

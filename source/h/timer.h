#include <stdlib.h>
//#include <windows.h>										// Header File For Windows
#include <stdio.h>											// sHeader File For Standard Input / Output
#include <stdarg.h>											// Header File For Variable Argument Routines
#include "globals.h"  
#include <new>

#include <math.h>
#include <string.h>

#ifdef SWITCH
#include <nn/fs.h>
#include <nn/nn_Assert.h>
#include <nn/nn_Log.h>
#include <nn/os.h>
#elif defined PS4
#include <time.h>
#elif defined XB1
#include <time.h>
#elif DREAMCAST
//#include <time.h>
#include <kos.h>
#endif

#define	MIN_TIME			0x80000000				// min. time value (32 bit)
#define	MAX_TIME			0x7fffffff				// max. time value (32 bit)
//extern float timer_addition; 
													// Structure Is Named timer */
#ifdef SWITCH
static int t0;
int gTime = 0;
#elif defined PS4 || defined XB1 || defined DREAMCAST
struct timespec t0;
#endif

#ifdef XB1
#define CLOCK_MONOTONIC 1

int clock_gettime(int type, struct timespec* ts)
{
	if (type != CLOCK_MONOTONIC)
	{
		return -1;
	}

	LARGE_INTEGER frequency, currentTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&currentTime);

	ts->tv_sec = (long)(currentTime.QuadPart / frequency.QuadPart);
	ts->tv_nsec = (long)(((currentTime.QuadPart % frequency.QuadPart) * 1000000000) / frequency.QuadPart);

	return 0;
}
#elif DREAMCAST
#define CLOCK_MONOTONIC 1
int clock_gettime(int type, struct timespec *ts) {
    if (type != CLOCK_MONOTONIC) {
        // Only support CLOCK_MONOTONIC for simplicity
        return -1;
    }

    uint64 ms = timer_ms_gettime64();
    ts->tv_sec = ms / 1000;
    ts->tv_nsec = (ms % 1000) * 1000000;

    return 0;
}
#endif

#ifdef SWITCH
int		 CTimerGet(void)
#elif defined PS4 || defined XB1 || defined DREAMCAST
void 		 CTimerGet(struct timespec *ts)
#endif 

{
#ifdef SWITCH
	nn::os::Tick time = nn::os::GetSystemTick();

	int64_t ms = time.ToTimeSpan().GetMicroSeconds();

	return ((int)ms);
#elif defined PS4 || defined XB1 || defined DREAMCAST
	clock_gettime(CLOCK_MONOTONIC, ts);
#endif

}
#ifdef SWITCH
float	 CTimerDifference(int time1, int time2)
#elif defined PS4 || defined XB1 || defined DREAMCAST
double CTimerDifference(struct timespec time1, struct timespec time2)
#endif
{
#ifdef SWITCH
	float	f;
	f = 0.000001f;

	if (time2 >= time1)
		return ((float)(time2 - time1) * f);

	return ((float)((MAX_TIME - time1) + (time2 - MIN_TIME) + 1) * f);
#elif defined PS4 || defined XB1 || defined DREAMCAST
	double elapsed = (time2.tv_sec - time1.tv_sec) * 1000.0;
	elapsed += (time2.tv_nsec - time1.tv_nsec) / 1000000.0;
	return elapsed;
#endif
}
  
void TimerInit(void)										// Initialize Our Timer (Get It Ready)
{
#ifdef SWITCH
	t0 = CTimerGet();
#elif defined PS4 || defined XB1 || defined DREAMCAST
	CTimerGet(&t0);
#endif
} 
   
//#if 1 
#ifdef SWITCH
float TimerGetTime()// Get Time In Milliseconds
#elif defined PS4 || defined XB1 || defined DREAMCAST
double TimerGetTime()
#endif
{
#ifdef SWITCH
	return (CTimerDifference(t0, CTimerGet()) * 1000.0f);
#elif defined PS4 || defined XB1 || defined DREAMCAST
	struct timespec t1;
	CTimerGet(&t1);
	return CTimerDifference(t0, t1);
#endif
}


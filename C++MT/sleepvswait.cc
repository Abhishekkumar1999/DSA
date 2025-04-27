/*SLEEP IS:
"I'm done with my timeslice, and please don't give me another one for at least n milli seconds." The OS doesn't even try to schedule the sleeping thread until requested time has passed.
POINTS:
    1. It will keep the lock and sleep.
    2. Sleep is directly to thread, it is a th read function.
*/

/*
WAIT IS: 
"I'm done with my timeslice. Don't give m e another timeslice until someone calls notify() notifyAll()."
As with sleep(), the OS won't even try to schedule your task unless someone calls notify) (or one of a few other wakeup scenarios occurs).
POINTS:
1. It releases the lock and wait.
2. Wait is on condition variable, it is like there is a condition variable in a thread and wait is ap plied to that CV but it ends up puting thread in w aiting state.
*/
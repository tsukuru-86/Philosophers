*This project has been created as part of the 42 curriculum by tsukuru.*

# Philosophers

## Description

This project is an implementation of the dining philosophers problem.  The
mandatory program uses one thread per philosopher and one mutex per fork.  The
bonus program uses one process per philosopher and represents the pool of forks
with a named semaphore.  Both programs synchronize status output and stop when
a philosopher dies or when every philosopher has eaten the requested number of
meals.

The project demonstrates concurrent programming, resource ordering, starvation
detection, precise timing, process supervision, mutexes, and POSIX semaphores.

## Instructions

Build both programs from the repository root:

```sh
make
make bonus
```

They can also be built independently with `make -C philo` and
`make -C philo_bonus`.

Run either implementation with:

```sh
./philo/philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]
./philo_bonus/philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]
```

All times are in milliseconds.  For example, `./philo/philo 5 800 200 200 7`
stops after every philosopher has completed seven meals, unless one dies first.

## Design notes

The mandatory implementation orders fork acquisition to prevent circular wait.
Every shared value is protected by a mutex.  The main thread acts as the death
monitor and launches all philosophers behind a synchronized start gate.

The bonus implementation uses named semaphores for forks, output, shared access,
and start synchronization.  A waiter semaphore prevents every process from
holding exactly one fork.  Each child has a monitor thread; the parent reaps
children and terminates the remaining processes after the first death.

## Resources

- POSIX Threads Programming: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html
- POSIX Semaphores: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/semaphore.h.html
- The Dining Philosophers Problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- Linux manual pages for `pthread_create`, `sem_open`, `fork`, and `waitpid`

AI was used to review the subject requirements, identify synchronization hazards,
help design test cases, and review the implementation.  The concurrency model,
code, and test results were then checked directly against the project subject.

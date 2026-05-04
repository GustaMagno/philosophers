*This project has been created as part of the 42 curriculum by gustoliv.*

# Philosophers

## Description

Philosophers is an implementation of the classic Dining Philosophers problem.
The goal of the project is to explore concurrency and synchronization concepts
using threads and mutexes.

In this simulation, a number of philosophers sit around a table. Each philosopher
alternates between thinking, eating, and sleeping. In order to eat, a philosopher
must pick up two forks, one on each side.

The challenge is to coordinate access to the forks (shared resources) in a way that
prevents common concurrency issues such as race conditions and deadlocks.

This project uses POSIX threads to create one thread per philosopher and mutexes
to control access to forks.

---
## Instructions


### Compilation

Run:

```bash
make
```
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```
### Arguments:

number_of_philosophers — number of philosophers and forks

time_to_die — time in milliseconds before a philosopher dies if they do not eat

time_to_eat — time in milliseconds spent eating

time_to_sleep — time in milliseconds spent sleeping

number_of_times_each_philosopher_must_eat — optional argument to stop the simulation after each philosopher has eaten a certain number of times

### Resources

The following resources were used to better understand the concepts involved in this project:

POSIX Threads (pthread) documentation

Articles and tutorials about thread synchronization and mutexes

Operating Systems concepts related to concurrency and scheduling

Explanations of the Dining Philosophers problem and common solutions

### Use of AI

AI tools were used as a learning aid during the development of this project.

They were mainly used to:
- clarify theoretical concepts related to concurrency (threads, mutexes, race conditions, deadlocks)
- better understand how POSIX threads work
- review explanations of operating system scheduling and synchronization mechanisms
- assist in improving documentation and wording in the README file

AI was **not used to generate or write the core implementation of the project**.  
All design decisions, architecture, and code were written and implemented manually.
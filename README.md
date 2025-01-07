# Philosophers Project

The **Philosophers** project is part of the **École 42** curriculum. In this project, you will implement a simulation of the dining philosophers problem using **pthreads** in **C**. This project will test your understanding of concurrency, multithreading, and synchronization.

The main goal is to model a scenario where philosophers are sitting at a table, thinking and eating, while sharing resources (a fork). The challenge is to ensure that the philosophers can eat without causing deadlocks or race conditions.

## Project Description

The **Philosophers** project involves simulating the behavior of philosophers who spend their time thinking and eating. They are seated around a circular table with a fork between each pair of philosophers. A philosopher can only eat if they have both forks. After eating, they continue thinking and repeat the cycle.

The challenge is to ensure that the philosophers can eat without causing:

- **Deadlock**: No philosopher should be blocked from eating forever.
- **Starvation**: Some philosophers should not be perpetually blocked from eating while others are eating.
- **Conditions**: Proper synchronization should be applied to avoid issues when multiple philosophers try to use the same fork at the same time.

You will need to implement this solution using **pthreads** for concurrency and use **mutexes** and **condition variables** to handle synchronization between the threads.

## Objectives

- **Philosophers and Forks**: Each philosopher needs two forks to eat. The forks are shared between philosophers, and only one philosopher can use a fork at a time.
- **Thinking, Eating, and Sleeping**: Philosophers alternate between thinking, eating, and sleeping.
- **Time Management**: Philosophers should think and eat for a random amount of time, and there should be a mechanism to stop the simulation after a certain number of meals are eaten by each philosopher or after a timeout.
- **Avoid Deadlock and Starvation**: The simulation must ensure that philosophers can eat without causing deadlocks or starvation.

### Key Points:
- Use **pthreads** to simulate the philosophers and fork actions.
- Apply synchronization mechanisms like **mutexes** to ensure that only one philosopher can pick up a fork at a time.
- Ensure that the philosophers do not get stuck in deadlock and that they don't starve.

## Technologies Used

- **C**: The project is implemented in the C programming language.
- **Pthreads**: The project uses POSIX threads for concurrency and multithreading.
- **Mutexes**: Used to ensure that only one philosopher can use a fork at a time.
- **Time Functions**: To manage the time for thinking, eating, and sleeping.

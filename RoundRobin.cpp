#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum +1) % N
#define MAXTIME  3 * 1000000

int state[N];
int phil[N] = { 0, 1, 2, 3, 4};
int remainingTime[N] = { 0, 0, 0, 0, 0};
int rnd = 0;

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
  if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
     {
	state[phnum] = EATING;       

	usleep(1);

	printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        
	if(remainingTime[phnum] != 0) {
	  rnd = remainingTime[phnum];
	  remainingTime[phnum] = 0;
	}
	else {
		rnd = (rand() % 7) * 1000000;
	}
	
	if(MAXTIME < rnd) {
		remainingTime[phnum] = rnd - MAXTIME;
		rnd = MAXTIME;
	}
	

	printf("Philosopher %d isEating for %i seconds and has a remaining time of %i\n", phnum + 1, rnd / 1000000, remainingTime[phnum] / 1000000);

	usleep(rnd);

	sem_post(&S[phnum]);
     }
}

void take_fork(int phnum)
{
  sem_wait(&mutex);

  state[phnum] = HUNGRY;

  printf("Philosopher %d is Hungry\n", phnum + 1);

  test(phnum);

  sem_post(&mutex);

  sem_wait(&S[phnum]);

  usleep(700000);
}

void put_fork(int phnum)
{
  sem_wait(&mutex);

  state[phnum] = THINKING;

  printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);

  printf("Philosopher %d is thinking\n", phnum + 1);

  test(LEFT);

  test(RIGHT);

  sem_post(&mutex);
}

void* philosopher(void* num)
{

  while (1) {

	int * i = reinterpret_cast<int*>(num);
	
	usleep(700000);

	take_fork(*i);

	usleep(0);

	put_fork(*i);
   }
}

int main()
{
  int i;
  pthread_t thread_id[N];

  sem_init(&mutex, 0, 1);

  std::srand(0);

  for (i = 0; i<N; i++)
  {
    sem_init(&S[i], 0, 0);
  }

  for(i = 0; i<N; i++)
  {
    pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    printf("Philosopher %d is thinking\n", i + 1);
  }

  for (i = 0; i < N; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
}

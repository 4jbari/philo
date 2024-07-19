#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// the initial balance is 0
int balance = 0;

// write the new balance (after as simulated 1/4 second delay)
void write_balance(int new_balance)
{
  usleep(250000);
  balance = new_balance;
}

// returns the balance (after a simulated 1/4 seond delay)
int read_balance()
{
//   usleep(250000);
  return balance;
}
struct arg{
    int amount;
    pthread_mutex_t *mutex;
};

// carry out a deposit
void* deposit(void *amount)
{
  // retrieve the bank balance
    struct arg *am = (struct arg *)amount;
    pthread_mutex_t *mutex = am->mutex;
    pthread_mutex_lock(mutex);
    int amount1 = am-> amount;
    printf("1:%d\n", am-> amount);

  int account_balance = read_balance();

  // make the update locally
  account_balance +=  amount1;

  // write the new bank balance
  write_balance(account_balance);
  pthread_mutex_unlock(mutex);

  return NULL;
}

int main()
{
  // output the balance before the deposits
  int before = read_balance();
    pthread_mutex_t mutex;
  printf("Before: %d\n", before);

  // we'll create two threads to conduct a deposit using the deposit function
  pthread_t thread1;
  pthread_t thread2;

  // the deposit amounts... the correct total afterwards should be 500
  struct arg deposit1 = {300, &mutex};
  struct arg deposit2 = {200, &mutex};

    pthread_mutex_init(&mutex, NULL);
  // create threads to run the deposit function with these deposit amounts
  pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
//   usleep(250000);
  pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

  // join the threads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // output the balance after the deposits
  int after = read_balance();
  printf("After: %d\n", after);

  return 0;
}
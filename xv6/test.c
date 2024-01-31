#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
//#include "ulib.c"
#define SLEEP_TIME 100

lock * lk1;
lock * lk2;
lock * lk3;

void f1(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  int slp = *(int*)arg2;
  lock_acquire(lk1);
  printf(1 ,"call function 1 with value %d\n", num);
  sleep(slp);
  lock_release(lk2);
  exit();
}

void f2(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  int slp = *(int*)arg2;
  lock_acquire(lk2);
  printf(1 ,"call function 2 with value %d\n", num);
  sleep(slp);
  lock_release(lk3);
  exit();
}

void f3(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  int slp = *(int*)arg2;
  lock_acquire(lk3);
  printf(1 ,"call function 3 with value %d\n", num);
  sleep(slp);
  lock_release(lk1);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lk1);
  lock_init(lk2);
  lock_init(lk3);
  printf(1 , "adf");
  int arg2 = 1;
  int pids[15];

  printf(1, "below should be sequential print statements:\n");
  for (int i = 0; i < 5; i++)
  {
    pids[i * 3 + 0] = thread_create(&f1, (void *)&i, (void *)&arg2);
    pids[i * 3 + 1] = thread_create(&f2, (void *)&i, (void *)&arg2);
    pids[i * 3 + 2] = thread_create(&f3, (void *)&i, (void *)&arg2);
  }
  for (int i = 0; i < 5; i++)
  {
    join(pids[i * 3 + 0]);
    join(pids[i * 3 + 1]);
    join(pids[i * 3 + 2]);
  }

  exit();
}

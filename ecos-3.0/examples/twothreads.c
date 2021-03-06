#include <cyg/kernel/kapi.h>
#include <cyg/infra/diag.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* now declare (and allocate space for) some kernel objects,
   like the two threads we will use */
cyg_thread thread_s[2];		/* space for two thread objects */

char stack[2][4096];		/* space for two 4K stacks */

/* now the handles for the threads */
cyg_handle_t simple_threadA, simple_threadB;

/* and now variables for the procedure which is the thread */
cyg_thread_entry_t simple_program;

/* and now a mutex to protect calls to the C library */
cyg_mutex_t cliblock;

/* we install our own startup routine which sets up threads */
void cyg_user_start(void)
{
  diag_printf("Bro, we entering in a twothreads' cyg_user_start() function\n");

  cyg_mutex_init(&cliblock);

  diag_printf("Bro, mutex initialized' cyg_user_start() function\n");

  cyg_thread_create(4,
                    simple_program,
                    (cyg_addrword_t) 0,
		            "Thread A",
                    (void *) stack[0],
                    4096,
		            &simple_threadA,
                    &thread_s[0] );

  diag_printf("Bro, threadA created' cyg_user_start() function\n");


  cyg_thread_create(4,
                    simple_program,
                    (cyg_addrword_t) 1,
		            "Thread B",
                    (void *) stack[1],
                    4096,
		            &simple_threadB,
                    &thread_s[1]);
  diag_printf("Bro, threadB created' cyg_user_start() function\n");

  cyg_thread_resume(simple_threadA);

  diag_printf("Bro, threadA resumed' cyg_user_start() function\n");

  cyg_thread_resume(simple_threadB);

  diag_printf("Bro, threadB resumed' cyg_user_start() function\n");
}

/* this is a simple program which runs in a thread */
void simple_program(cyg_addrword_t data)
{
  int message = (int) data;
  int delay;

  diag_printf("Beginning execution; thread data is %d\n", message);

  cyg_thread_delay(200);

  for (;;) {
    delay = 200 + 50;

    /* note: printf() must be protected by a
       call to cyg_mutex_lock() */
    cyg_mutex_lock(&cliblock); {
      diag_printf("Thread %d: and now a delay of %d clock ticks\n",
	     message, delay);
    }
    cyg_mutex_unlock(&cliblock);
    cyg_thread_delay(delay);
  }
}

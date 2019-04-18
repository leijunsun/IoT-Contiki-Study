/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
static int count = 0;
char string_out[20];

static struct ctimer test_ctimer;

#ifdef ETIMER_TEST_ENABLE
static struct etimer test_etimer;
#endif

#ifdef CTIMER_TEST_ENABLE
static void periodic_ctimer_test(void *ptr)
{
  if (ptr != NULL)
     printf("%s\n", (char *)ptr);

  count++;
  sprintf(string_out, "%d ctimer callback", count);
  ctimer_set(&test_ctimer, CLOCK_SECOND, periodic_ctimer_test, string_out);

#ifdef ETIMER_TEST_ENABLE
  etimer_set(&test_etimer, CLOCK_SECOND / 2);
#endif
}
#endif
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Hello, world\n");
#ifdef CTIMER_TEST_ENABLE
  count++;
  sprintf(string_out, "%d ctimer callback", count);
  ctimer_set(&test_ctimer, CLOCK_SECOND, periodic_ctimer_test, string_out);
  printf("ctimer is not block function\n");
#endif
  
#ifdef ETIMER_TEST_ENABLE
  etimer_set(&test_etimer, CLOCK_SECOND / 2);
  while(1) {
      PROCESS_WAIT_EVENT();
      if(ev == PROCESS_EVENT_TIMER) {
          printf("etimer get event: PROCESS_EVENT_TIMER \n");
      }
  }
#endif

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

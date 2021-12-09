#include <stdint.h>
#include <stdio.h>
// #include <xparameters.h>
#include "config.h"
#include "interrupts.h"
#include "utils.h"
#include "xparameters.h"

// Compute the timer clock freq.
#define TIMER_CLOCK_FREQUENCY (XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)
// Compute timer load value.
#define TIMER_LOAD_VALUE ((CONFIG_TIMER_PERIOD * TIMER_CLOCK_FREQUENCY) - 1.0)

static volatile int nest_depth = 0;

void tick_all() {
  // if (nest_depth > 0) {
  printf("ISR nesting depth: %d\n", nest_depth);
  // }

  ++nest_depth;
  // utils_msleep(120);
  printf("pre-delay\n");
  utils_msDelay(1000);
  printf("post-delay\n");
  --nest_depth;

  // TODO: fill
}

int main() {
  interrupts_initAll(true);
  interrupts_setPrivateTimerLoadValue(TIMER_LOAD_VALUE);
  interrupts_enableTimerGlobalInts();
  // Keep track of your personal interrupt count. Want to make sure that you
  // don't miss any interrupts.
  int32_t personalInterruptCount = 0;
  // Start the private ARM timer running.
  interrupts_startArmPrivateTimer();
  // Enable interrupts at the ARM.
  interrupts_enableArmInts();
  while (1) {
    // TODO: compute chess moves
    utils_sleep();
  }
}

// Interrupt routine
void isr_function() { tick_all(); }
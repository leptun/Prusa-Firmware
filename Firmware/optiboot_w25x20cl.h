#ifndef OPTIBOOT_W25X20CL_H
#define OPTIBOOT_W25X20CL_H


/* Watchdog settings */
#define WATCHDOG_OFF    (0)
#define WATCHDOG_16MS   (_BV(WDE))
#define WATCHDOG_32MS   (_BV(WDP0) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_64MS   (_BV(WDP1) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_125MS  (_BV(WDP1) | _BV(WDP0) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_250MS  (_BV(WDP2) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_500MS  (_BV(WDP2) | _BV(WDP0) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_1S     (_BV(WDP2) | _BV(WDP1) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_2S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_4S     (_BV(WDP3) | _BV(WDE) | _BV(WDIE))
#define WATCHDOG_8S     (_BV(WDP3) | _BV(WDP0) | _BV(WDE) | _BV(WDIE))

extern uint8_t optiboot_w25x20cl_enter();
extern void watchdogConfig(uint8_t x);

#endif /* OPTIBOOT_W25X20CL_H */

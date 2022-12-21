/*
  pdk-logic-probe

  Copyright (C) 2022  serisman  <github@serisman.com>

  LED is Green when Probe pin is LOW.
  LED is Red when Probe pin is HIGH.
  LED is Blue when Probe pin is Floating.

  ----------------------------------------------------------------------
  CC BY 4.0
  Licensed under a Creative Commons Attribution 4.0 International license:
  http://creativecommons.org/licenses/by/4.0/
*/

#include <stdint.h>
#include <stdbool.h>
#include <pdk/device.h>
#include <easy-pdk/calibrate.h>

#if !defined(PFS154) && !defined(PFS173) && !defined(PMS150C) && !defined(PMS15A) && !defined(PMS152) && !defined(PMS154C) && !defined(PMS171B)
  #error "Device not currently supported!"
#endif

// Note: All pins are on Port A
#define PIN_R       0
#define PIN_G       4
#define PIN_B       6
#define PIN_OUT     3
#define PIN_PROBE   7

// Main program
void main() {

  // Disable wake-up on un-used pins to save power
#if defined(PBDIER)
  PBDIER = 0x00;
#endif
#if defined(PCDIER)
  PCDIER = 0x00;
#endif

  // Initialize Pins
  PAPH = 0x00;                              // Disable pull-up resistors
  PADIER = (uint8_t)(1<<PIN_PROBE);         // Enable digital input on PROBE
  PAC = (uint8_t)((1<<PIN_OUT)|(1<<PIN_R)|(1<<PIN_G)|(1<<PIN_B));  // Set OUT and RGB LED Pins as outputs
  PA = (1<<PIN_R)|(1<<PIN_G)|(1<<PIN_B);    // LEDs off by default

  // Main processing loop
  while (1) {

		PA |= (1<<PIN_OUT);                     // Turn OUT on (i.e. try to pull PROBE high)
		__nop();__nop();__nop();__nop();
		bool probeHigh = PA & (1<<PIN_PROBE);   // Test PROBE

		PA &= ~(1<<PIN_OUT);                    // Turn OUT off (i.e. try to pull PROBE low)
		__nop();__nop();__nop();__nop();
		bool probeLow = !(PA & (1<<PIN_PROBE)); // Test PROBE

		// Update LEDs
		if (probeHigh & probeLow) {
			PA = (1<<PIN_R)|(1<<PIN_G);           // Blue LED   (PROBE is Floating)
		} else if (probeLow) {
			PA = (1<<PIN_R)|(1<<PIN_B);           // Green LED  (PROBE is LOW)
		} else if (probeHigh) {
			PA = (1<<PIN_G)|(1<<PIN_B);           // Red LED    (PROBE is HIGH)
		}
  }
}

// Startup code - Setup/calibrate system clock
unsigned char _sdcc_external_startup(void) {

  // Set FUSE:
  // - 1.8v LVR (if available)
  // - Normal IO Drive (if available)
  // - Fast Bootup (if available)
  // - Security Off
#if defined(FUSE_LVR_1V8) && defined(FUSE_IO_DRV_NORMAL) && defined(FUSE_BOOTUP_FAST)
  PDK_SET_FUSE(FUSE_BOOTUP_FAST | FUSE_IO_DRV_NORMAL | FUSE_LVR_1V8 | FUSE_SECURITY_OFF);
#elif defined(FUSE_LVR_1V8)
  PDK_SET_FUSE(FUSE_LVR_1V8 | FUSE_SECURITY_OFF);
#elif defined(FUSE_IO_DRV_NORMAL) && defined(FUSE_BOOTUP_FAST)
  PDK_SET_FUSE(FUSE_BOOTUP_FAST | FUSE_IO_DRV_NORMAL | FUSE_SECURITY_OFF);
#elif defined(FUSE_BOOTUP_FAST)
  PDK_SET_FUSE(FUSE_BOOTUP_FAST | FUSE_SECURITY_OFF);
#else
  PDK_SET_FUSE(FUSE_SECURITY_OFF);
#endif

  // Set LVR:
  // - 1.8v (if available)
  // - otherwise 2.0v (if available)
#if defined(MISCLVR_1V8)
  MISCLVR = (uint8_t) MISCLVR_1V8;
#elif defined(MISCLVR_2V)
  MISCLVR = (uint8_t) MISCLVR_2V;
#endif

  // Initialize the system clock (CLKMD register) for 1MHz operation
  PDK_SET_SYSCLOCK(SYSCLOCK_IHRC_1MHZ);

  // Insert placeholder code to tell EasyPdkProg to calibrate the IHRC internal oscillator for 1MHz operation.
  EASY_PDK_CALIBRATE_IHRC(1000000, TARGET_VDD_MV);

  return 0;   // Return 0 to inform SDCC to continue with normal initialization.
}

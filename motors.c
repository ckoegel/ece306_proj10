//------------------------------------------------------------------------------
//
//  Description: This file contains the motor functionality
//
//
//  Cameron Koegel
//  Feb 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

// Function Prototypes
void All_Wheels_Off(void);
void Drive_Fwd(void);
void Drive_Rev(void);
void CW_Spin(void);
void CCW_Spin(void);

void All_Wheels_Off(void) {
  P6OUT &= ~R_FORWARD;
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_REVERSE;
  P6OUT &= ~L_REVERSE;
}

void Drive_Fwd(void) {
  P6OUT |= R_FORWARD;
  P6OUT |= L_FORWARD;
}

void Drive_Rev(void) {
  P6OUT |= R_REVERSE;
  P6OUT |= L_REVERSE;
}

void CW_Spin(void) {
  P6OUT |= L_FORWARD;
  P6OUT |= R_REVERSE;
}

void CCW_Spin(void) {
  P6OUT |= R_FORWARD;
  P6OUT |= L_REVERSE;
}
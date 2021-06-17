//------------------------------------------------------------------------------
//
//  Description: This file contains the initializing fucntion
//
//
//  Cameron Koegel
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

// Function Prototypes
void Init_Conditions(void);

// Global Variables
extern char display_line[DISP_ROW_FOUR][DISP_COL_ELEVEN];
extern char *display[DISP_ROW_FOUR];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=DISP_ROW_ZERO;i<DISP_COL_ELEVEN;i++){
    display_line[DISP_ROW_ZERO][i] = RESET_STATE;
    display_line[DISP_ROW_ONE][i] = RESET_STATE;
    display_line[DISP_ROW_TWO][i] = RESET_STATE;
    display_line[DISP_ROW_THREE][i] = RESET_STATE;
  }
  display_line[DISP_ROW_ZERO][DISP_COL_TEN] = DISP_ROW_ZERO;
  display_line[DISP_ROW_ONE][DISP_COL_TEN] = DISP_ROW_ZERO;
  display_line[DISP_ROW_TWO][DISP_COL_TEN] = DISP_ROW_ZERO;
  display_line[DISP_ROW_THREE][DISP_COL_TEN] = DISP_ROW_ZERO;

  display[DISP_ROW_ZERO] = &display_line[DISP_ROW_ZERO][DISP_ROW_ZERO];
  display[DISP_ROW_ONE] = &display_line[DISP_ROW_ONE][DISP_ROW_ZERO];
  display[DISP_ROW_TWO] = &display_line[DISP_ROW_TWO][DISP_ROW_ZERO];
  display[DISP_ROW_THREE] = &display_line[DISP_ROW_THREE][DISP_ROW_ZERO];
  update_display = DISP_ROW_ZERO;
  update_display_count = DISP_ROW_ZERO;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}
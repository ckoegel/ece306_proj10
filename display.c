//------------------------------------------------------------------------------
//
//  Description: This file contains functions for making the car do a circle,
//               figure 8, and triangle
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
#include <string.h>

// Function Protoypes
void Clear_Disp(void);
void Disp_Wait(void);
void Disp_Intercept(void);
void Disp_Stopped(void);
void Disp_Turn(void);
void Disp_Time(void);
void Disp_Circle(void);
void Disp_Cal_1(void);
void Disp_Cal_2(void);
void Disp_Cal_3(void);
void Final_Text(void);
void Disp_L_Det(void);
void Disp_R_Det(void);
void Disp_TW_Det(void);


// Global Variables
extern char display_line[DISP_ROW_FOUR][DISP_COL_ELEVEN];
extern char *display[DISP_ROW_FOUR];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char thousands;
extern char hundreds;
extern char tens;
extern char ones;

void Clear_Disp(void) {
  strcpy(display_line[DISP_ROW_ZERO], "          ");
  update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
  strcpy(display_line[DISP_ROW_ONE], "          ");
  update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
  strcpy(display_line[DISP_ROW_TWO], "          ");
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
  strcpy(display_line[DISP_ROW_THREE], "          ");
  update_string(display_line[DISP_ROW_THREE], DISP_ROW_THREE);
}

void Disp_Wait(void) {
  strcpy(display_line[DISP_ROW_THREE], "S: WAITING");
}

void Disp_Intercept(void) {
  strcpy(display_line[DISP_ROW_THREE], "S:INTERCPT");
}

void Disp_Stopped(void) {
  strcpy(display_line[DISP_ROW_THREE], "S: STOPPED");
}

void Disp_Turn(void) {
  strcpy(display_line[DISP_ROW_THREE], "S: TURNING");
}

void Disp_Time(void) {
  display_line[DISP_ROW_THREE][DISP_COL_TWO] = thousands;
  display_line[DISP_ROW_THREE][DISP_COL_THREE] = hundreds;
  display_line[DISP_ROW_THREE][DISP_COL_FOUR] = tens;
  display_line[DISP_ROW_THREE][DISP_COL_FIVE] = '.';
  display_line[DISP_ROW_THREE][DISP_COL_SIX] = ones;
}

void Disp_Circle(void) {
  strcpy(display_line[DISP_ROW_THREE], "S:CIRCLING");
}

void Disp_Cal_1(void) {
  strcpy(display_line[DISP_ROW_TWO], "CAL. WHITE");
  strcpy(display_line[DISP_ROW_THREE], " PRESS S2 ");
}

void Disp_Cal_2(void) {
  strcpy(display_line[DISP_ROW_TWO], "CAL. BLACK");
  strcpy(display_line[DISP_ROW_THREE], " PRESS S2 ");
}

void Final_Text(void) {
  Clear_Disp();
  strcpy(display_line[DISP_ROW_ONE], "  -DONE-  ");
  update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
}

void Disp_L_Det(void) {
  display_line[DISP_ROW_ZERO][DISP_COL_TWO] = thousands;
  display_line[DISP_ROW_ZERO][DISP_COL_THREE] = hundreds;
  display_line[DISP_ROW_ZERO][DISP_COL_FOUR] = tens;
  display_line[DISP_ROW_ZERO][DISP_COL_FIVE] = ones;
  display_line[DISP_ROW_ZERO][DISP_COL_TEN] = RESET_STATE;
  update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
  display_changed = TRUE;
}

void Disp_R_Det(void) {
  display_line[DISP_ROW_ONE][DISP_COL_TWO] = thousands;
  display_line[DISP_ROW_ONE][DISP_COL_THREE] = hundreds;
  display_line[DISP_ROW_ONE][DISP_COL_FOUR] = tens;
  display_line[DISP_ROW_ONE][DISP_COL_FIVE] = ones;
  display_line[DISP_ROW_ONE][DISP_COL_TEN] = RESET_STATE;
  update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
  display_changed = TRUE;
}

void Disp_TW_Det(void) {
  display_line[DISP_ROW_TWO][DISP_COL_TWO] = thousands;
  display_line[DISP_ROW_TWO][DISP_COL_THREE] = hundreds;
  display_line[DISP_ROW_TWO][DISP_COL_FOUR] = tens;
  display_line[DISP_ROW_TWO][DISP_COL_FIVE] = ones;
  display_line[DISP_ROW_TWO][DISP_COL_TEN] = RESET_STATE;
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
  display_changed = TRUE;
}

void Disp_Baud_460(void) {
  strcpy(display_line[DISP_ROW_TWO], "BR: 460800");
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
  display_changed = TRUE;
}

void Disp_Baud_115(void) {
  strcpy(display_line[DISP_ROW_TWO], "BR: 115200");
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
  display_changed = TRUE;
}

void Disp_Baud_96(void) {
  strcpy(display_line[DISP_ROW_TWO], "BR: 9600  ");
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
  display_changed = TRUE;
}

void Disp_Msg_Rec(void) {
  strcpy(display_line[DISP_ROW_ZERO], " RECEIVED ");
  update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
  strcpy(display_line[DISP_ROW_ONE], "          ");
  update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
  display_changed = TRUE;
}

void Disp_Msg_Trans(void) {
  strcpy(display_line[DISP_ROW_ZERO], " TRANSMIT ");
  update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
  strcpy(display_line[DISP_ROW_THREE], "          ");
  update_string(display_line[DISP_ROW_THREE], DISP_ROW_THREE);
  display_changed = TRUE;
}





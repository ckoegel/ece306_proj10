//------------------------------------------------------------------------------
//
//  Description: This file contains the timer interrupt functionality
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
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch1_interrupt(void);

// Global Variables
volatile unsigned int B0_interrupt_count = RESET_STATE;
volatile unsigned short int display_change = RESET_STATE;
extern char display_line[DISP_ROW_FOUR][DISP_COL_ELEVEN];
extern short int SW1_Pressed;
short int SW1_Debounce;
extern short int SW2_Pressed;
short int SW2_Debounce;
unsigned int debounce_count_SW1;
unsigned int debounce_count_SW2;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
volatile short int R_Fwd_On = RESET_STATE;
volatile short int L_Fwd_On = RESET_STATE;
volatile short int R_Rev_On = RESET_STATE;
volatile short int L_Rev_On = RESET_STATE;
extern short int motors;
extern short int disp_text;
extern short int iot_emm;
short int begin_pause1 = RESET_STATE;
short int turn_seq = RESET_STATE;
extern short int begin_pause2;
extern short int step_count;
unsigned int timer_val = RESET_STATE;
short int black_line_check = RESET_STATE;
extern short int update_wheels;
extern short int begin_circle_count;
short int circle_time = RESET_STATE;
extern short int begin_turn_count;
extern short int turn_to_center;
extern short int end_in_center;
extern short int begin_center_count;
extern short int calib_step;
extern short int timer_allowed;
extern char test_command[];
extern short int UCA0_index;
extern short int UCA0_index2;
extern short int UCA1_index;
short int baud_set_115;
short int baud_set_460;
extern char send_command[];
extern short int baud_changed;
extern short int baud_set_96;
extern short int command_time;
short int startup_delay = RESET_STATE;
short int message_send = RESET_STATE;
short int drive_timer = RESET_STATE;
extern short int drive_fwd;
extern short int drive_rev;
extern short int drive_turn_R;
extern short int drive_turn_L;
extern short int stop_car;
extern short int driving_course;
extern short int begin_white_delay;
extern short int white_delay;
short int sw1_count = RESET_STATE;
char send_command2[LARGE_RING_SIZE];
short int bl_timer = RESET_STATE;
short int wh_tmr = RESET_STATE;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern short int black_thresh;
short int pause2 = RESET_STATE;
extern short int bl_travel;
extern short int bl_circle;

// TimerB0 0 Interrupt handler
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
    
  display_change++;
  startup_delay++;
  message_send++;
  
  if (drive_fwd || drive_rev || drive_turn_R || drive_turn_L) {
    drive_timer++;
  }
  
  if (drive_timer == command_time) {
    drive_timer = RESET_STATE;
    drive_fwd = RESET_STATE;
    drive_rev = RESET_STATE;
    drive_turn_R = RESET_STATE;
    drive_turn_L = RESET_STATE;
    stop_car = TRUE;
  }
  
  if (step_count > RESET_STATE) {
    bl_timer++;
    if ((step_count == TRUE) && (bl_timer == TB0CCR0_17)) {
      bl_timer = RESET_STATE;
      step_count = STEP_2;
      stop_car = TRUE;
    }
    if ((step_count == STEP_2) && (bl_timer == TB0CCR0_EIGHT)) {
      bl_timer = RESET_STATE;
      step_count = STEP_3;
      stop_car = TRUE;
    }
    if ((step_count == STEP_3) && (bl_timer == TB0CCR0_27)) {
      bl_timer = RESET_STATE;
      step_count = STEP_4;
      stop_car = TRUE;
    }
    if ((step_count == STEP_4) && (bl_timer == TB0CCR0_9)) {
      bl_timer = RESET_STATE;
      step_count = STEP_5;
      stop_car = TRUE;
    }
    if (((step_count == STEP_5) && (bl_timer == TB0CCR0_THIRTY)) || ((step_count == STEP_5) && ((ADC_Left_Detect > black_thresh) || (ADC_Right_Detect > black_thresh)))) {
      bl_timer = RESET_STATE;
      step_count = STEP_6;
      stop_car = TRUE;
    }
    if ((step_count == STEP_6) && begin_pause2) {
      pause2++;
      if (pause2 == TB0CCR0_TEN) {
        pause2 = RESET_STATE;
        bl_timer = RESET_STATE;
        step_count = STEP_7;
        stop_car = TRUE;
      }
    }
    if ((step_count == STEP_7) && (bl_timer == TB0CCR0_TWO)) {
      bl_timer = RESET_STATE;
      step_count = STEP_8;
      bl_travel = TRUE;
      stop_car = TRUE;
    }
    if ((step_count == STEP_8) && (bl_timer == TB0CCR0_THIRTY)) {
      bl_circle = TRUE;
    }
    if ((step_count == STEP_8) && (bl_timer == TB0CCR0_400)) {
      bl_timer = RESET_STATE;
      step_count = STEP_9;
      stop_car = TRUE;
    }
      if ((step_count == STEP_9) && (bl_timer == TB0CCR0_TWENTY)) {
      bl_timer = RESET_STATE;
      step_count = STEP_10;
      stop_car = TRUE;
    }
    
  }
  
  if (begin_white_delay) {
    wh_tmr++;
    if (wh_tmr == TB0CCR0_TEN) {
      wh_tmr = RESET_STATE;
      begin_white_delay = RESET_STATE;
      white_delay = TRUE;
    }
  }
  
  switch(display_change) {
    case TB0CCR0_TWO:
      if(timer_allowed) { timer_val += SHIFT_2;}
      if (timer_val > TIMER_MAX) { timer_val = RESET_STATE;}
      HEXtoBCD(timer_val);
      Disp_Time();
      update_display = TRUE;
      display_changed = TRUE;
      display_change = RESET_STATE;
      break;
    default: break;
  }
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
}


#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
  //----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,14)){
    case RESET_STATE: break;                      // No interrupt
    
    case 2:                             // CCR1 not used
      if (SW1_Debounce) {
        debounce_count_SW1++;
      }
      if (SW2_Debounce) {
        debounce_count_SW2++;
      }
      
      if (debounce_count_SW1 == TB0CCR1_EIGHT) {
        P4IE |= SW1;                            // Re-enable switch 1
        P4IFG &= ~SW1;                          // IFG SW1 cleared
        TB0CCTL1 &= ~CCIE;                      // Disable the switch debounce interrupt
        SW1_Debounce = RESET_STATE;             // Switch 1 is not being debounced
        SW1_Pressed = RESET_STATE;              // Switch 1 is not beging pressed
        debounce_count_SW1 = RESET_STATE;
      }
      if (debounce_count_SW2 == TB0CCR1_EIGHT) {
        P2IE |= SW2;                            // Re-enable switch 2
        P2IFG &= ~SW2;                          // IFG SW2 cleared
        TB0CCTL1 &= ~CCIE;                      // Disable the switch debounce interrupt
        SW2_Debounce = RESET_STATE;             // Switch 2 is not being debounced
        SW2_Pressed = RESET_STATE;              // Switch 2 is not beging pressed
        debounce_count_SW2 = RESET_STATE;
      }
      
      TB0CCR1 += TB0CCR1_INTERVAL;              // Add Offset to TBCCR1
      break;
      
    case 4:                                     // CCR2 not used
      TB0CCR2 += TB0CCR2_INTERVAL;              // Add Offset to TBCCR2
      break;
      
    case 14:                                    // overflow
      
      break;
      
    default: break;
  }
  //----------------------------------------------------------------------------
}

  // Switch 1 Interrupt Handler
#pragma vector = PORT4_VECTOR
__interrupt void switch1_interrupt(void) {

  if (P4IFG & SW1) {
    
    debounce_count_SW1 = RESET_STATE;   // Reset debounce count
    P4IFG &= ~SW1;                      // IFG SW1 cleared
    SW1_Debounce = TRUE;                // Switch 1 is being debounced
    SW1_Pressed = TRUE;                 // Swith 1 is beging pressed
    P4IE &= ~SW1;                       // Turn off switch 1
    TB0CCTL1 |= CCIE;                   // Enable the switch debounce interrupt
    
    if (sw1_count == TRUE) {
      strcpy(send_command,"");
      strcpy(send_command, "AT+NSTCP=42069,1");
      send_command[SMALL_RING_SIZE] = CARRAIGE_RET;
      UCA0_index = RESET_STATE;
      UCA0IE |= UCTXIE; // Enable RX interrupt
      UCA0TXBUF = send_command[RESET_STATE];
      sw1_count++;
      strcpy(display_line[DISP_ROW_THREE], "          ");
      update_string(display_line[DISP_ROW_THREE], DISP_ROW_THREE);
      strcpy(display_line[DISP_ROW_ZERO], "Waiting on");
      update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
      strcpy(display_line[DISP_ROW_ONE], "Input 192");
      update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
      strcpy(display_line[DISP_ROW_TWO], ".168.0.127");
      update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
      display_changed = TRUE;
      driving_course = TRUE;
    }
    /*if (sw1_count == TRUE) {
      strcpy(send_command,"");
      strcpy(send_command, "AT+NSTAT=?");
      send_command[DISP_COL_TEN] = CARRAIGE_RET;
      UCA0_index = RESET_STATE;
      UCA0IE |= UCTXIE; // Enable RX interrupt
      UCA0TXBUF = send_command[RESET_STATE];
      sw1_count++;
    }*/
    if (sw1_count == RESET_STATE) {
      strcpy(send_command, "AT+RESET=1");
      send_command[DISP_COL_TEN] = CARRAIGE_RET;
      UCA0_index = RESET_STATE;
      UCA0IE |= UCTXIE; // Enable RX interrupt
      UCA0TXBUF = send_command[RESET_STATE];
      sw1_count++;
    }
    
    P6OUT &= ~LCD_BACKLITE ; // LCD_BACKLITE off to indicate boot ISR working
  } 

}

  // Switch 2 Interrupt Handler
#pragma vector = PORT2_VECTOR
__interrupt void switch2_interrupt(void) {

  if (P2IFG & SW2) {
    
    debounce_count_SW2 = RESET_STATE;   // Reset debounce count
    P2IFG &= ~SW2;                      // IFG SW2 cleared
    SW2_Debounce = TRUE;                // Switch 2 is being debounced
    SW2_Pressed = TRUE;                 // Switch 2 is being pressed
    P2IE &= ~SW2;                       // Turn off switch 2
    TB0CCTL1 |= CCIE;                   // Enable the switch debounce interrupt
    calib_step++;
    /*if (P3OUT & IR_LED) {
      P3OUT &= ~IR_LED;
      iot_emm = RESET_STATE;
    } else {
      P3OUT |= IR_LED;
      iot_emm = TRUE;
    }*/
    if (UCA0BRW == BAUD_115200_BRW) {
      baud_set_460 = TRUE;
      baud_changed = TRUE;
      baud_set_115 = RESET_STATE;
      baud_set_96 = RESET_STATE;
    } else if (UCA0BRW == BAUD_460800_BRW) {
      baud_set_460 = RESET_STATE;
      baud_set_96 = RESET_STATE;
      baud_set_115 = TRUE;
      baud_changed = TRUE;
    }
    
    P6OUT &= ~LCD_BACKLITE ; // LCD_BACKLITE off to indicate boot ISR working
  } 

}


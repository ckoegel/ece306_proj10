//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Cameron Koegel
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

// Function Prototypes
void main(void);

// Global Variables
extern volatile char USB_Char_Rx[];
extern volatile char USB_Char_Tx[];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int B0_interrupt_count;
extern volatile unsigned int update_display_count;
extern volatile unsigned short int display_change;
extern unsigned int usb_rx_ring_rd;
extern unsigned int usb_tx_ring_rd;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb_Detect;
extern volatile char one_time;
extern char send_command2[];
extern char display_line[DISP_ROW_FOUR][DISP_COL_ELEVEN];
extern char *display[DISP_ROW_FOUR];
extern short int turn_seq;
extern short int bl_timer;
extern short int iot_comm2;
extern short int SW1_Pressed;
extern short int SW2_Pressed;
extern short int SW1_Debounce;
extern short int SW2_Debounce;
extern short int begin_pause1;
extern short int begin_pause2;
extern short int baud_set_115;
extern short int baud_set_460;
extern short int message_send;
extern short int startup_delay;
extern short int iot_comm2_complete;
unsigned char display_mode;
unsigned int myclock;
unsigned int loopCount;
unsigned int test_value;
unsigned int myclock_old;
unsigned int count2 = TRUE;
unsigned int countGO = TRUE;
unsigned int circleEnd = TRUE;
unsigned int circleText = TRUE;
unsigned int circleStart = TRUE;
unsigned int count1 = RESET_STATE;
char change;
char chosen_direction;
char test[DISP_COL_ELEVEN];
char ssid[DISP_COL_ELEVEN];
char command[SMALL_RING_SIZE];
char iot_command[LARGE_RING_SIZE];
char iot_command2[SMALL_RING_SIZE];
char send_command[LARGE_RING_SIZE];
char test_command[DISP_COL_TEN];
char process_buffer[LARGE_RING_SIZE];
char process_buffer2[LARGE_RING_SIZE];
char copy_message = RESET_STATE;
volatile char slow_input_down;
short int wait_for_pc;
short int iot_emm = TRUE;
short int iot_start = TRUE;
short int count = RESET_STATE;
short int one_time_ssid = TRUE;
short int update_wheels = TRUE;
short int port3Pin4 = USE_GPIO;
short int motors = RESET_STATE;
short int turn_to_center = TRUE;
short int stop_car = RESET_STATE;
short int off_side = RESET_STATE;
short int msg_trans = RESET_STATE;
short int bl_travel = RESET_STATE;
short int bl_circle = RESET_STATE;
short int white_val = RESET_STATE;
short int drive_fwd = RESET_STATE;
short int drive_rev = RESET_STATE;
short int ssid_check = RESET_STATE;
short int ssid_parse = RESET_STATE;
short int copy_index = RESET_STATE;
short int calib_step = RESET_STATE;
short int UCA0_index = RESET_STATE;
short int UCA1_index = RESET_STATE;
short int step_count = RESET_STATE;
short int disp_r_det = RESET_STATE;
short int disp_l_det = RESET_STATE;
short int UCA0_index2 = RESET_STATE;
short int ssid_check2 = RESET_STATE;
short int ssid_check3 = RESET_STATE;
short int ssid_check4 = RESET_STATE;
short int baud_set_96 = RESET_STATE;
short int disp_tw_det = RESET_STATE;
short int white_delay = RESET_STATE;
short int drive_turn_R = RESET_STATE;
short int drive_turn_L = RESET_STATE;
short int command_time = RESET_STATE;
short int begin_pause2 = RESET_STATE;
short int baud_changed = RESET_STATE;
short int timer_allowed = RESET_STATE;
short int end_in_center = RESET_STATE;
short int driving_course = RESET_STATE;
short int char_count_ssid = RESET_STATE;
short int command_complete = RESET_STATE;
short int look_iot_command = RESET_STATE;
short int look_for_command = RESET_STATE;
short int begin_turn_count = RESET_STATE;
short int password_correct = RESET_STATE;
short int clear_process_buf = RESET_STATE;
short int begin_white_delay = RESET_STATE;
short int clear_process_buf2 = RESET_STATE;
short int begin_center_count = RESET_STATE;
short int begin_circle_count = RESET_STATE;
short int black_thresh = BLK_THRESH_DEFAULT;
short int iot_command_complete = RESET_STATE;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                         // Initialize Ports
  Init_Clocks();                        // Initialize Clock System
  Init_Conditions();                    // Initialize Variables and Initial Conditions
  Init_Timers();                        // Initialize Timers
  Init_LCD();                           // Initialize LCD
  Init_LEDs();                          // Initialize LEDs
  Init_ADC();                           // Initialize ADC
  Init_Serial_UCA0();                   // Initialize Serial Communication for UART0
  Init_Serial_UCA1();                   // Initialize Serial Communication for UART1
  Clear_Disp();                         // Clear the Display 
  strcpy(test_command, " NCSU  #1 ");
  strcpy(test,"");
  /*strcpy(display_line[DISP_ROW_ZERO], " WAITING. ");
  update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
  strcpy(display_line[DISP_ROW_TWO], "BR: 115200");
  update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);*/
  display_changed = TRUE;
  enable_display_update();             // Enable the Display to Update
  int iot_com_count = RESET_STATE;
  int pc_command = RESET_STATE;
  int i = RESET_STATE;
  
  strcpy(ssid, "");
  strcpy(send_command2,"");

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {  
  // Can the Operating system run
    
    if (iot_start) {
      if (startup_delay == MS2500) {
        startup_delay = RESET_STATE;
        P5OUT |= IOT_RESET; // Set IOT_RESET inactive [High]
        iot_start = RESET_STATE;
      }
    }
    /*if (message_send == MS1000) {
      if (wait_for_pc) {
        UCA1_index = RESET_STATE;
        UCA1IE |= UCTXIE; // Enable RX interrupt
        UCA1TXBUF = send_command[RESET_STATE];
      }
      message_send = RESET_STATE;
    }*/
    if (!driving_course) {
      if (copy_message) {
        int i = RESET_STATE;
        while (ALWAYS) {
          if (USB_Char_Rx[copy_index] == CARRAIGE_RET) {
            while (i < DISP_COL_TEN) {
              display_line[DISP_ROW_THREE][i] = SPACE;
              send_command[i] = SPACE;
              i++;
            }
            break;
          }
          if (copy_index < SMALL_RING_SIZE) { 
            display_line[DISP_ROW_THREE][i] = USB_Char_Rx[copy_index];
            send_command[i] = USB_Char_Rx[copy_index];
            copy_index++;
          } else {
            copy_index = RESET_STATE;
            display_line[DISP_ROW_THREE][i] = USB_Char_Rx[copy_index];
            send_command[i] = USB_Char_Rx[copy_index];
            copy_index++;
          }
          i++;
        }
        //Disp_Msg_Rec();
        copy_index = usb_rx_ring_wr;
        send_command[DISP_COL_TEN] = RESET_STATE;
        display_line[DISP_ROW_THREE][DISP_COL_TEN] = RESET_STATE;
        update_string(display_line[DISP_ROW_THREE], DISP_ROW_THREE);
        display_changed = TRUE;
        copy_message = RESET_STATE;
      }
    }
    
    
    if (usb_rx_ring_rd != usb_rx_ring_wr) {
      if (USB_Char_Rx[usb_rx_ring_rd] == CARRAIGE_RET) {
        clear_process_buf = TRUE;
      }
      if ((char_count_ssid > TRUE) && (one_time_ssid)) {
        if (char_count_ssid < STEP_12) {
          display_line[DISP_ROW_ZERO][i] = USB_Char_Rx[usb_rx_ring_rd];
          i++;
          //ssid[char_count_ssid - STEP_2] = USB_Char_Rx[usb_rx_ring_rd];
        } else {
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          char_count_ssid = RESET_STATE;
          ssid_parse = RESET_STATE;
          one_time_ssid = RESET_STATE;
        }
      }
      if (ssid_parse) {
        ssid_check4 = RESET_STATE;
        ssid_check3 = RESET_STATE;
        ssid_check2 = RESET_STATE;
        ssid_check = RESET_STATE;
        char_count_ssid++;
      }
      if (ssid_check4) {
        if (USB_Char_Rx[usb_rx_ring_rd] == D) {
          ssid_parse = TRUE;
        } else {
          ssid_check4 = RESET_STATE;
          ssid_check3 = RESET_STATE;
          ssid_check2 = RESET_STATE;
          ssid_check = RESET_STATE;
        }
      }
      if (ssid_check3) {
        if (USB_Char_Rx[usb_rx_ring_rd] == I) {
          ssid_check4 = TRUE;
        } else {
          ssid_check3 = RESET_STATE;
          ssid_check2 = RESET_STATE;
          ssid_check = RESET_STATE;
        }
      }
      if (ssid_check2) {
        if (USB_Char_Rx[usb_rx_ring_rd] == S) {
          ssid_check3 = TRUE;
        } else {
          ssid_check2 = RESET_STATE;
          ssid_check = RESET_STATE;
        }
      }
      if (ssid_check) {
        if (USB_Char_Rx[usb_rx_ring_rd] == S) {
          ssid_check2 = TRUE;
        } else {
          ssid_check = RESET_STATE;
        }
      }
      if (USB_Char_Rx[usb_rx_ring_rd] == SPACE) {
        ssid_check = TRUE;
      }
      if (usb_rx_ring_rd < SMALL_RING_SIZE) {
        if (look_iot_command) {
          iot_command[iot_com_count] = USB_Char_Rx[usb_rx_ring_rd];
          iot_com_count++;
        }
        /*if (iot_comm2) {
          iot_command2[iot_com2_count] = USB_Char_Rx[usb_rx_ring_rd];
          iot_com2_count++;
        }*/
        process_buffer[count] = USB_Char_Rx[usb_rx_ring_rd];
        usb_rx_ring_rd++;
      } else {
        if (look_iot_command) {
          iot_command[iot_com_count] = USB_Char_Rx[usb_rx_ring_rd];
          iot_com_count++;
        }
        /*if (iot_comm2) {
          iot_command2[iot_com2_count] = USB_Char_Rx[usb_rx_ring_rd];
          iot_com2_count++;
        }*/
        usb_rx_ring_rd = RESET_STATE;
        process_buffer[count] = USB_Char_Rx[usb_rx_ring_rd];
      }
      count++;
    }
    
    if (clear_process_buf) {      
      clear_process_buf = RESET_STATE;
      count = RESET_STATE;
      for (int i = RESET_STATE; i < LARGE_RING_SIZE; i++) {
        process_buffer[i] = RESET_STATE;
      }
    }
    
    if (usb_tx_ring_rd != usb_tx_ring_wr) {
      if (USB_Char_Tx[usb_tx_ring_rd] == CARRAIGE_RET) {
        clear_process_buf2 = TRUE;
      }
      if (usb_tx_ring_rd < SMALL_RING_SIZE) {
        if (look_for_command) {
          command[pc_command] = USB_Char_Tx[usb_tx_ring_rd];
          pc_command++;
        }
        process_buffer2[count1] = USB_Char_Tx[usb_tx_ring_rd];
        usb_tx_ring_rd++;
      } else {
        if (look_for_command) {
          command[pc_command] = USB_Char_Tx[usb_tx_ring_rd];
          pc_command++;
        }
        usb_tx_ring_rd = RESET_STATE;
        process_buffer2[count1] = USB_Char_Tx[usb_tx_ring_rd];
      }
      count1++;
    }
    
    if (clear_process_buf2) {
      clear_process_buf2 = RESET_STATE;
      count1 = RESET_STATE;
      for (int i = RESET_STATE; i < LARGE_RING_SIZE; i++) {
        process_buffer2[i] = RESET_STATE;
      }
    }
    
    if (iot_command_complete) {
      if (iot_command[STEP_9] == CARET) {
        int j = RESET_STATE;
        for (int i = RESET_STATE; i < SMALL_RING_SIZE; i++) {
          if (iot_command[STEP_9 + i] != RESET_STATE) {
            iot_command2[j] = iot_command[STEP_9 + i];
            iot_command[STEP_9 + i] = RESET_STATE;
            j++;
          } 
        }
      }
      iot_com_count = RESET_STATE;
      iot_command_complete = RESET_STATE;
      command_time = RESET_STATE;
      if ((iot_command[TRUE] == SIX) && (iot_command[STEP_2] == NINE) && (iot_command[STEP_3] == SIX) && (iot_command[STEP_4] == NINE)) {
        password_correct = TRUE;
      }
      
      if (password_correct) {
        timer_allowed = TRUE;
        strcpy(display_line[DISP_ROW_ONE], iot_command);
        display_line[DISP_ROW_ONE][DISP_COL_NINE] = SPACE;
        display_line[DISP_ROW_ONE][DISP_COL_TEN] = RESET_STATE;
        update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
        display_changed = TRUE;
        command_time += iot_command[STEP_8] - ASCII_30;
        command_time += (iot_command[STEP_7] - ASCII_30) * STEP_10;
        command_time += (iot_command[STEP_6] - ASCII_30) * STEP_10 *STEP_10;
        switch (iot_command[STEP_5]) {
        case F:
          strcpy(display_line[DISP_ROW_ZERO], "          ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          RIGHT_FORWARD_SPEED = R_STRAIGHT;
          LEFT_FORWARD_SPEED = L_STRAIGHT;
          RIGHT_REVERSE_SPEED = WHEEL_OFF;
          LEFT_REVERSE_SPEED = WHEEL_OFF;
          drive_fwd = TRUE;
          drive_rev = RESET_STATE;
          drive_turn_R = RESET_STATE;
          drive_turn_L = RESET_STATE;
          break;
        case B:
          strcpy(display_line[DISP_ROW_ZERO], "          ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          RIGHT_FORWARD_SPEED = WHEEL_OFF;
          LEFT_FORWARD_SPEED = WHEEL_OFF;
          RIGHT_REVERSE_SPEED = R_STRAIGHT;
          LEFT_REVERSE_SPEED = L_STRAIGHT;
          drive_fwd = RESET_STATE;
          drive_rev = TRUE;
          drive_turn_R = RESET_STATE;
          drive_turn_L = RESET_STATE;
          break;
        case L:
          strcpy(display_line[DISP_ROW_ZERO], "          ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          RIGHT_FORWARD_SPEED = R_STRAIGHT;
          LEFT_FORWARD_SPEED = WHEEL_OFF;
          RIGHT_REVERSE_SPEED = WHEEL_OFF;
          LEFT_REVERSE_SPEED = L_STRAIGHT;
          drive_fwd = RESET_STATE;
          drive_rev = RESET_STATE;
          drive_turn_R = RESET_STATE;
          drive_turn_L = TRUE;
          break;
        case R:
          strcpy(display_line[DISP_ROW_ZERO], "          ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          RIGHT_REVERSE_SPEED = WHEEL_OFF;
          LEFT_REVERSE_SPEED = WHEEL_OFF;
          RIGHT_FORWARD_SPEED = LOFF_FIX_R;
          LEFT_FORWARD_SPEED = LOFF_FIX_L;
          drive_fwd = RESET_STATE;
          drive_rev = RESET_STATE;
          drive_turn_L = RESET_STATE;
          drive_turn_R = TRUE;
          break;
        case A:
          strcpy(display_line[DISP_ROW_ZERO], "Arrived   ");
          display_line[DISP_ROW_ZERO][DISP_COL_EIGHT] = iot_command[STEP_8];
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          drive_fwd = RESET_STATE;
          drive_rev = RESET_STATE;
          drive_turn_L = RESET_STATE;
          drive_turn_R = RESET_STATE;
          break;
        case G:
          strcpy(display_line[DISP_ROW_ZERO], " BL Start ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          drive_fwd = RESET_STATE;
          drive_rev = RESET_STATE;
          drive_turn_L = RESET_STATE;
          drive_turn_R = RESET_STATE;
          step_count = TRUE;
          break;
        case E:
          strcpy(display_line[DISP_ROW_ZERO], " BL Exit  ");
          update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
          strcpy(display_line[DISP_ROW_TWO], "          ");
          update_string(display_line[DISP_ROW_TWO], DISP_ROW_TWO);
          step_count = STEP_9;
          bl_timer = RESET_STATE;
        default: break;
        }
        
      } // ^6969F230^6969R400
    }
    
    switch(step_count) {
    case TRUE:
      RIGHT_FORWARD_SPEED = R_STRAIGHT;
      LEFT_FORWARD_SPEED = L_STRAIGHT;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      P3OUT |= IR_LED;
      break;
    case STEP_2:
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = LOFF_FIX_R;
      LEFT_FORWARD_SPEED = LOFF_FIX_L;
      break;
    case STEP_3:
      RIGHT_FORWARD_SPEED = R_STRAIGHT;
      LEFT_FORWARD_SPEED = L_STRAIGHT;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      break;
    case STEP_4:
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = LOFF_FIX_R;
      LEFT_FORWARD_SPEED = LOFF_FIX_L;
      break;
    case STEP_5:
      RIGHT_FORWARD_SPEED = R_STRAIGHT;
      LEFT_FORWARD_SPEED = L_STRAIGHT;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      begin_white_delay = TRUE;
      break;
    case STEP_6:
      begin_pause2 = TRUE;
      strcpy(display_line[DISP_ROW_ZERO], "Intercept ");
      update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
      RIGHT_FORWARD_SPEED = WHEEL_OFF;           // P6.0 Right Forward PWM OFF 
      LEFT_FORWARD_SPEED = WHEEL_OFF;            // P6.1 Left Forward PWM OFF
      RIGHT_REVERSE_SPEED = WHEEL_OFF;           // P6.0 Right Reverse PWM OFF 
      LEFT_REVERSE_SPEED = WHEEL_OFF;            // P6.1 Left Reverse PWM OFF
      break;
    case STEP_7:
      RIGHT_FORWARD_SPEED = R_STRAIGHT;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = L_STRAIGHT;
      break;
    case STEP_8:
      if (bl_travel) {
        strcpy(display_line[DISP_ROW_ZERO], "BL Travel ");
        update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
        bl_travel = RESET_STATE;
      }
      if (bl_circle) {
        strcpy(display_line[DISP_ROW_ZERO], "BL Circle ");
        update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
        bl_circle = RESET_STATE;
      }
      if ((ADC_Left_Detect > black_thresh) && (ADC_Right_Detect > black_thresh)) {
        RIGHT_FORWARD_SPEED = R_STRAIGHT;
        LEFT_FORWARD_SPEED = L_STRAIGHT;
      } else if ((ADC_Left_Detect > black_thresh) && (ADC_Right_Detect < black_thresh)) {
        RIGHT_FORWARD_SPEED = ROFF_FIX_R;
        LEFT_FORWARD_SPEED = ROFF_FIX_L;
        off_side = RIGHT;
      } else if ((ADC_Left_Detect < black_thresh) && (ADC_Right_Detect > black_thresh)) {
        RIGHT_FORWARD_SPEED = LOFF_FIX_R;
        LEFT_FORWARD_SPEED = LOFF_FIX_L;
        off_side = LEFT;
      } else {
          switch (off_side) {
          case LEFT:
            RIGHT_FORWARD_SPEED = LOFF_FIX_R;
            LEFT_FORWARD_SPEED = LOFF_FIX_L;
            break;
          case RIGHT:
            RIGHT_FORWARD_SPEED = ROFF_FIX_R;
            LEFT_FORWARD_SPEED = ROFF_FIX_L;
            break;
          default: break;
          }
      }
      break;
    case STEP_9:
      RIGHT_FORWARD_SPEED = R_STRAIGHT;
      LEFT_FORWARD_SPEED = L_STRAIGHT;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      break;
    case STEP_10:
      strcpy(display_line[DISP_ROW_ZERO], "BL Stop ");
      update_string(display_line[DISP_ROW_ZERO], DISP_ROW_ZERO);
      stop_car = TRUE;
      timer_allowed = RESET_STATE;
    default: break;
    }
    
    if (stop_car) {
      RIGHT_FORWARD_SPEED = WHEEL_OFF;           // P6.0 Right Forward PWM OFF 
      LEFT_FORWARD_SPEED = WHEEL_OFF;            // P6.1 Left Forward PWM OFF
      RIGHT_REVERSE_SPEED = WHEEL_OFF;           // P6.0 Right Reverse PWM OFF 
      LEFT_REVERSE_SPEED = WHEEL_OFF;            // P6.1 Left Reverse PWM OFF
      stop_car = RESET_STATE;
      if (iot_command2[RESET_STATE]) {
        iot_command_complete = TRUE;
        strcpy(iot_command,iot_command2);
        strcpy(iot_command2,"");
      }
    }
    
        
    if (command_complete) {
      command_complete = RESET_STATE;
      count1 = RESET_STATE;
      pc_command = RESET_STATE;
    
      switch(command[DISP_COL_ONE]) {
      case F:
        baud_set_115 = TRUE;
        baud_set_96 = RESET_STATE;
        baud_set_460 = RESET_STATE;
        baud_changed = TRUE;
        break;
      case S:
        baud_set_96 = TRUE;
        baud_set_115 = RESET_STATE;
        baud_set_460 = RESET_STATE;
        baud_changed = TRUE;
        break;
      default:
        break;
      }
    }
    
    if (msg_trans) {
      //Disp_Msg_Trans();
      //strcpy(display_line[DISP_ROW_ONE], send_command);
      //update_string(display_line[DISP_ROW_ONE], DISP_ROW_ONE);
      //display_changed = TRUE;
      msg_trans = RESET_STATE;
    }
    
    if (baud_set_460) {
      if(baud_changed) {
        UCA0BRW = BAUD_460800_BRW; // 460800 Baud 
        UCA0MCTLW = BAUD_460800_MCTLW; // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        baud_set_115 = RESET_STATE;
        baud_set_96 = RESET_STATE;
        Disp_Baud_460();
        baud_changed = RESET_STATE;
      }
    } else if (baud_set_115) {
      if(baud_changed) {
        UCA0BRW = BAUD_115200_BRW; // 115200 Baud 
        UCA0MCTLW = BAUD_115200_MCTLW; // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        baud_set_460 = RESET_STATE;
        baud_set_96 = RESET_STATE;
        Disp_Baud_115();
        baud_changed = RESET_STATE;
      }
    } else if (baud_set_96) {
      if(baud_changed) {
        UCA0BRW = BAUD_9600_BRW; // 9600 Baud 
        UCA0MCTLW = BAUD_9600_MCTLW; // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        baud_set_460 = RESET_STATE;
        baud_set_115 = RESET_STATE;
        Disp_Baud_96();
        baud_changed = RESET_STATE;
      }
    }
  Display_Process();
  }
//------------------------------------------------------------------------------
}





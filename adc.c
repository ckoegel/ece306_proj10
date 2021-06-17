//------------------------------------------------------------------------------
//
//  Description: This file contains the initializing fucntion for the ADC and the ISR for the ADC
//
//
//  Cameron Koegel
//  FEB 2020
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

// Function Prototypes
void Init_ADC(void);
void HEXtoBCD(int hexVal);

// Global Variables
unsigned int ADC_Channel = RESET_STATE;
unsigned int ADC_Left_Detect = RESET_STATE;
unsigned int ADC_Right_Detect = RESET_STATE;
unsigned int ADC_Thumb_Detect = RESET_STATE;
extern short int disp_r_det;
extern short int disp_l_det;
extern short int disp_tw_det;
char thousands;
char hundreds;
char tens;
char ones;

void Init_ADC(void) {
  //V_DETECT_L            (0x04) // Pin 2 A2
  //V_DETECT_R            (0x08) // Pin 3 A3
  //V_THUMB               (0x20) // Pin 5 A5
  
  //ADCCTL0 Register
  ADCCTL0 = RESET_STATE;              // Reset 
  ADCCTL0 |= ADCSHT_2;                // 16 ADC clocks
  ADCCTL0 |= ADCMSC;                  // MSC
  ADCCTL0 |= ADCON;                   // ADC On
  
  //ADCCTL1 Register
  ADCCTL2 = RESET_STATE;               // Reset 
  ADCCTL1 |= ADCSHS_0;                 // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP;                   // ADC sample-and-hold SAMPCON signal from sampling timer.   
  ADCCTL1 &= ~ADCISSH;                 // ADC invert signal sample-and-hold.   
  ADCCTL1 |= ADCDIV_0;                 // ADC clock divider - 000b = Divide by 1   
  ADCCTL1 |= ADCSSEL_0;                // ADC clock MODCLK   
  ADCCTL1 |= ADCCONSEQ_0;              // ADC conversion sequence 00b = Single-channel single-conversion 
  // ADCCTL1 & ADCBUSY  identifies a conversion is in process 

  // ADCCTL2 Register   
  ADCCTL2 = RESET_STATE;               // Reset   
  ADCCTL2 |= ADCPDIV0;                 // ADC pre-divider 00b = Pre-divide by 1   
  ADCCTL2 |= ADCRES_2;                 // ADC resolution 10b = 12 bit (14 clock cycle conversion time)   
  ADCCTL2 &= ~ADCDF;                   // ADC data read-back format 0b = Binary unsigned.   
  ADCCTL2 &= ~ADCSR;                   // ADC sampling rate 0b = ADC buffer supports up to 200 ksps 
  
  // ADCMCTL0 Register   
  ADCMCTL0 |= ADCSREF_0;               // VREF - 000b = {VR+ = AVCC and VR– = AVSS }   
  ADCMCTL0 |= ADCINCH_2;               // V_DETECT_L (0x04) Pin 2 A2
 
  ADCIE |= ADCIE0;                     // Enable ADC conv complete interrupt   
  ADCCTL0 |= ADCENC;                   // ADC enable conversion.   
  ADCCTL0 |= ADCSC;                    // ADC start conversion. 
}

#pragma vector=ADC_VECTOR 
__interrupt void ADC_ISR(void){   
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){     
    case ADCIV_NONE:       
      break;     
    case ADCIV_ADCOVIFG:   // When a conversion result is written to the ADCMEM0 before its previous conversion result was read.       
      break;     
    case ADCIV_ADCTOVIFG:   // ADC conversion-time overflow       
      break;     
    case ADCIV_ADCHIIFG:    // Window comparator interrupt flags       
      break;     
    case ADCIV_ADCLOIFG:    // Window comparator interrupt flag      
      break;     
    case ADCIV_ADCINIFG:    // Window comparator interrupt flag       
      break;     
    case ADCIV_ADCIFG:      // ADCMEM0 memory register with the conversion result       
       ADCCTL0 &= ~ADCENC;                         // Disable ENC bit.    
       switch (ADC_Channel++){       
         case CH_A2:                                            // Channel A2 Interrupt         
           ADCMCTL0 &= ~ADCINCH_2;                              // Disable Last channel A2         
           ADCMCTL0 |= ADCINCH_3;                               // Enable Next channel A3         
           ADC_Left_Detect = ADCMEM0;                           // Move result into Global         
           ADC_Left_Detect = ADC_Left_Detect >> SHIFT_2;        // Divide the result by 4 
           ADC_Left_Detect += CALIB_OFFSET;                     // Set L and R values equal
           break;       
         case CH_A3:                                            // Channel A3 Interrupt   
           ADCMCTL0 &= ~ADCINCH_3;                              // Disable Last channel A3
           ADCMCTL0 |= ADCINCH_5;                               // Enable Next channel A5
           ADC_Right_Detect = ADCMEM0;                          // Move result into Global
           ADC_Right_Detect = ADC_Right_Detect >> SHIFT_2;      // Divide the result by 4
           ADC_Right_Detect -= CALIB_OFFSET;                    // Set L and R values equal
           break;       
         case CH_A5:                                            // Channel A5 Interrupt
           ADCMCTL0 &= ~ADCINCH_5;                              // Disable Last channel A5
           ADCMCTL0 |= ADCINCH_2;                               // Enable Next channel A2
           ADC_Thumb_Detect = ADCMEM0;                          // Move result into Global
           ADC_Thumb_Detect = ADC_Thumb_Detect >> SHIFT_2;      // Divide the result by 4
           ADC_Channel = RESET_STATE;         
           break;       
         default:         
           break;     
       }     
       ADCCTL0 |= ADCENC;                // Enable Conversions     
       ADCCTL0 |= ADCSC;                 // Start next sample  
      break;     
    default:       
      break;   
  } 
}

void HEXtoBCD(int hexVal) {
  thousands = RESET_STATE;
  hundreds = RESET_STATE;
  tens = RESET_STATE;
  ones = RESET_STATE;
  
  while (hexVal >= THOUSAND) {
      hexVal -= THOUSAND;
      thousands++;
  }
  while (hexVal >= HUNDRED) {
      hexVal -= HUNDRED;
      hundreds++;
  }
  while (hexVal >= TEN) {
      hexVal -= TEN;
      tens++;
  }
  while (hexVal > RESET_STATE) {
      hexVal -= UNO;
      ones++;
  }
  
  thousands += ASCII_30;
  hundreds += ASCII_30;
  tens += ASCII_30;
  ones += ASCII_30;
}
 
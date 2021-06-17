//------------------------------------------------------------------------------
//
//  Description: This file contains the #defines for other files to remove magic numbers
//
//
//  Cameron Koegel
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MACROS========================================================================

#define ALWAYS                     (1)
#define TRUE                       (1)
#define RESET_STATE                (0)
#define SHIFT_2                    (2)

// Serial Comm
#define BEGINNING                  (0)
#define RX_IN                      (2)
#define TX_OUT                     (4)
#define SMALL_RING_SIZE           (16)
#define LARGE_RING_SIZE           (32)
#define BAUD_9600_BRW             (52)
#define BAUD_9600_MCTLW       (0x4911)
#define BAUD_115200_BRW            (4)
#define BAUD_115200_MCTLW     (0x5551)
#define BAUD_460800_BRW            (1)
#define BAUD_460800_MCTLW     (0x4A11)
#define LINE_FEED               (0x0A)
#define CARRAIGE_RET            (0x0D)
#define SPACE                   (0x20)
#define CARET                   (0x5E)
#define A                       (0x41)
#define B                       (0x42)
#define D                       (0x44)
#define E                       (0x45)
#define F                       (0x46)
#define G                       (0x47)
#define I                       (0x49)
#define L                       (0x4C)
#define R                       (0x52)
#define S                       (0x53)
#define T                       (0x54)
#define ESC                     (0x1B)
#define SIX                     (0x36)
#define NINE                    (0x39)

// Display
#define DISP_ROW_ZERO              (0)
#define DISP_ROW_ONE               (1) // Row 1
#define DISP_ROW_TWO               (2) // Row 2
#define DISP_ROW_THREE             (3) // Row 3
#define DISP_ROW_FOUR              (4) // Number of rows on LCD Display
#define DISP_COL_ZERO              (0) // Column 4
#define DISP_COL_ONE               (1) // Column 4
#define DISP_COL_TWO               (2) // Column 4
#define DISP_COL_THREE             (3) // Column 4
#define DISP_COL_FOUR              (4) // Column 4
#define DISP_COL_FIVE              (5) // Column 5
#define DISP_COL_SIX               (6) // Column 6
#define DISP_COL_SEVEN             (7) // Column 7
#define DISP_COL_EIGHT             (8) // Column 8
#define DISP_COL_NINE              (9) // Column 9
#define DISP_COL_TEN              (10) // Column 10
#define DISP_COL_ELEVEN           (11) // Number of columns on LCD Display
#define DISP_R_DET                 (2) // Correpsonds to Right Detector
#define DISP_L_DET                 (4) // Correpsonds to Left Detector
#define DISP_TW_DET                (6) // Correpsonds to ThumbWheel Detector
#define DISP_SW1                   (8) // Correpsonds to Switch 1
#define DISP_SW2                  (10) // Correpsonds to Switch 1
#define DISP_CLEAR                (12)

// Interrupts
#define TB0CCR0_INTERVAL       (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB0CCR1_INTERVAL       (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB0CCR2_INTERVAL       (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB0CCR0_ONE                (1) // Every interrupt
#define TB0CCR0_TWO                (2) // Every 2 interrupts
#define TB0CCR0_FOUR               (4) // Every 4 interrupts
#define TB0CCR0_FIVE               (5) // Every 5 interrupts
#define TB0CCR0_7                  (7) // Every 7 interrupts
#define TB0CCR0_EIGHT              (8) // Every 8 interrupts
#define TB0CCR0_9                  (9) // Every 9 interrupts
#define TB0CCR0_TEN               (10) // Every 10 interrupts (1 second)
#define TB0CCR0_FIFTEEN           (15) // Every 15 interrupts
#define TB0CCR0_17                (17) // Every 17 interrupts
#define TB0CCR0_TWENTY            (20) // Every 20 interrupts
#define TB0CCR0_25                (25) // Every 25 interrupts
#define TB0CCR0_27                (27) // Every 27 interrupts
#define TB0CCR0_THIRTY            (30) // Every 30 interrupts
#define TB0CCR0_FORTY             (40) // Every 40 interrupts
#define TB0CCR0_SIXTY             (60) // Every 60 interrupts
#define TB0CCR0_SEVENTY           (70) // Every 70 interrupts
#define TB0CCR0_EIGHTY            (80) // Every 80 interrupts
#define TB0CCR0_NINETY            (90) // Every 90 interrupts
#define TB0CCR0_120              (120) // Every 120 interrupts
#define TB0CCR0_140              (140) // Every 140 interrupts
#define TB0CCR0_170              (170) // Every 170 interrupts
#define TB0CCR0_190              (190) // Every 190 interrupts
#define TB0CCR0_220              (220) // Every 220 interrupts
#define TB0CCR0_400              (400) // Every 400 interrupts
#define TB0CCR1_EIGHT              (8) // Every 8 interrupts

// Motors
#define STEP_2                     (2) // Second stage of motors
#define STEP_3                     (3) // Third stage of motors
#define STEP_4                     (4) // Fourth stage of motors
#define STEP_5                     (5) // Fifth stage of motors
#define STEP_6                     (6) // Sixth stage of motors
#define STEP_7                     (7) // Seventh stage of motors
#define STEP_8                     (8) // Eighth stage of motors
#define STEP_9                     (9) // Ninth stage of motors
#define STEP_10                   (10) // Tenth stage of motors
#define STEP_11                   (11) // Eleventh stage of motors
#define STEP_12                   (12) // Twelfth stage of motors
#define STEP_13                   (13) // Thirteenth stage of motors

// Clocks
#define DELAY_CYCLES_THREE         (3) // 3 Cycle Clock Delay
#define MCLK_FREQ_MHZ              (8) // MCLK = 8MHz
#define TIMER_MAX               (9998) // Maximum Timer Value
#define MS2500                    (25) // 2.5 seconds
#define MS1000                    (10) // 1.0 seconds

// ADC
#define CH_A2                   (0x00) // Channel A2
#define CH_A3                   (0x01) // Channel A3
#define CH_A5                   (0x02) // Channel A5
#define THOUSAND                (1000) // HEX converter value 1000
#define HUNDRED                  (100) // HEX converter values 100
#define TEN                       (10) // HEX converter value 10
#define UNO                        (1) // HEX covnerter value 1
#define ASCII_30                (0x30) // ASCII conversion from BCD
#define CALIB_OFFSET              (30) // Value to make R and L detectors equal
#define BLK_THRESH_DEFAULT       (300) // Default ADC Threshold for black line

// PWM
#define RIGHT_FORWARD_SPEED  (TB3CCR1)
#define LEFT_FORWARD_SPEED   (TB3CCR2)
#define RIGHT_REVERSE_SPEED  (TB3CCR3)
#define LEFT_REVERSE_SPEED   (TB3CCR4)
#define WHEEL_OFF                  (0)
#define WHEEL_PERIOD           (50000)
#define R_STRAIGHT             (34000)
#define L_STRAIGHT             (35000)
#define R_TURN                 (25000)
#define L_TURN                 (25000)
#define ROFF_FIX_R             (44000)
#define ROFF_FIX_L              (4000)
#define LOFF_FIX_R              (4000)
#define LOFF_FIX_L             (48000)
#define LEFT                       (1)
#define RIGHT                      (2)

// Main/Shapes
#define TIME_250                 (250)
#define TIME_200                 (200)
#define TIME_150                 (150)
#define TIME_100                 (100)
#define TIME_50                   (50)

// Misc
#define OUTPUT                  (0xFF)
#define LOW                     (0x00)
#define GRN_LED                 (0x40) // GREEN LED 1
#define CLEAR_REGISTER        (0x0000)
#define ONES_WORD             (0xFFFF)
#define USE_GPIO                (0x00)
#define USE_SMCLK               (0x01)
#define HEX_8                   (0x08)

// PINS==========================================================================

// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define P2_0 (0x01) // 0
#define P2_1 (0x02) // 1
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define CHECK_BAT (0x02) // 1 CHECK_BAT
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define IR_LED (0x20) // 5 IR_LED
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7 P3_7

// Port 4 Pins
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// Port 5 Pins
#define IOT_RESET (0x01) // 0 IOT Reset
#define V_BAT (0x02) // 1 Battery Voltage
#define IOT_PROG_SEL (0x04) // 2 IOT Program Select
#define V_3_3 (0x08) // 3
#define IOT_PROG_MODE (0x10) // 4 IOT Program Mode

// Port 6 Pins
#define R_FORWARD (0x01)
#define L_FORWARD (0x02)
#define R_REVERSE (0x04)
#define L_REVERSE (0x08)
#define LCD_BACKLITE (0x10)
#define P6_5 (0x20)
#define GRN_LED (0x40)
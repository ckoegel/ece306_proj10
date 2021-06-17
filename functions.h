//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch1_interrupt(void);
__interrupt void switch2_interrupt(void);

// Analog to Digital Converter
void Init_ADC(void);
void HEXtoBCD(int hexVal);

// Clocks
void Init_Clocks(void);

// Serial
void out_character(char character);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

// LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(int pin4Function);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// Motors
void All_Wheels_Off(void);
void Drive_Fwd(void);
void Drive_Rev(void);
void CW_Spin(void);
void CCW_Spin(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Shapes
void Full_Circle(void);
void Full_Circle_Rev(void);
void Figure_8(void);
void Straight_Line(void);
void Turn_Sixty(void);
void Triangle(void);
void Stop_Wheels(void);
void Start_Wheels(void);
void Update_Time(void);

// Display
void Clear_Disp(void);
void Disp_Wait(void);
void Disp_Intercept(void);
void Disp_Stopped(void);
void Disp_Turn(void);
void Disp_Time(void);
void Disp_Circle(void);
void Disp_Cal_1(void);
void Disp_Cal_2(void);
void Final_Text(void);
void Disp_L_Det(void);
void Disp_R_Det(void);
void Disp_TW_Det(void);
void Disp_Baud_460(void);
void Disp_Baud_115(void);
void Disp_Baud_96(void);
void Disp_Msg_Rec(void);
void Disp_Msg_Trans(void);

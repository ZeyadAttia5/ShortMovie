#include "../../INCLUDE/MCAL/DIO/DIO_prv.h"
#include "../../INCLUDE/MCAL/DIO/DIO.h"
#include "../../INCLUDE/HAL/LCD/LCD.h"
#include "../../SERVICES/STD_TYPES.h"
/*
 * This project was created on October 20, 2022
 * This program contains the code for a short film on the LCD
 */



#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */


int main()
{

	u8 Character0[8] = { 0x00, 0x0E, 0x15, 0x1F, 0x04, 0x1F, 0x04, 0x0A };  //Stickman no Ground
	u8 Character1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F };	//Ground
	u8 Character2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };	//All-Light (Clear Block)
	u8 Character3[8] = { 0x0E, 0x15, 0x1F, 0x04, 0x1F, 0x04, 0x0A, 0x1F };	//Stickman on Ground

	u8 Character4[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00 };	//ramp
	u8 Character6[8] = { 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00 };	//ramp

	//Lower Part of Stickman
	u8 Character8[8] = { 0x15, 0x1F, 0x04, 0x1F, 0x04, 0x1F, 0x00, 0x00 };	//Stickman ground -2 pixels
	u8 Character10[8] = { 0x04, 0x04, 0x0A, 0x1F, 0x00, 0x00, 0x00, 0x00 };	//Stickman no ground -4 pixels

	//Upper Part of Stickman
	u8 Character12[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E };	//Stickman no ground -2 pixels
	u8 Character14[8] = { 0x00, 0x00, 0x00, 0x0E, 0x15, 0x1F, 0x04, 0x1F };	//Stickman no ground -4 pixels

	//hit the wall
	u8 HitWall[8] = { 0x0F, 0x15, 0x1F, 0x05, 0x1F, 0x05, 0x0B, 0x1F };		//Stickman no ground -4 pixels
	u8 HeadArmsSide[8] = { 0x00, 0x00, 0x00, 0x0C, 0x14, 0x1F, 0x15, 0x1F };//Stickman no ground -4 pixels
	u8 Legs[8] = { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x1F, 0x1F };		//Stickman no ground -4 pixels


	LCD_tLCD lcd;
	lcd.CfgPort = DIO_u8_PORTB;
	lcd.DataPort = DIO_u8_PORTA;
	lcd.ENPin = EN;
	lcd.RSPin = RS;
	lcd.RWPin = RW;
	LCD_vidInit(lcd);


	LCD_Custom_Char(0, Character0, lcd);  /* Build Character1 at position 0 */
	LCD_Custom_Char(1, Character1, lcd);  /* Build Character2 at position 1 */
	LCD_Custom_Char(2, Character2, lcd);  /* Build Character3 at position 2 */
	LCD_Custom_Char(3, Character3, lcd);  /* Build Character4 at position 3 */
	LCD_Custom_Char(4, Character4, lcd);  /* Build Character5 at position 4 */
	//LCD_Custom_Char(5, Character5);  /* Build Character6 at position 5 */
	LCD_Custom_Char(6, Character6, lcd);  /* Build Character7 at position 6 */
	//LCD_Custom_Char(7, Character7);  /* Build Character8 at position 7 */
	//LCD_Custom_Char(8, Character8);  /* Build Character9 at position 8 */

	LCD_vidSendCommand(0x80, lcd);		/*cursor at home position */
	/*LCD_String("Custom u8 LCD");
	LCD_Command(0xc0);*/


	// build ground on UpperFloor
	LCD_vidSendChar(3, lcd);
	for(u8 i=1;i<16;i++)
	{
		LCD_vidSendChar(1,lcd);
		//LCD_Char(' ')
	}
	_delay_ms(500);


	for(u8 k = 0; k<2; k++){
		//1st Iteration
		if(k == 0){
			//Move on the 1st row till the end
			for(u8 j = 0; j < 16; j++){
				LCD_vidMoveStickMan(0, j, j+1, Ground, lcd);
				_delay_ms(500);
			}

			//go down and move till the end
			LCD_vidMoveCursor(1, 0, lcd);
			LCD_vidSendChar(0, lcd);
			_delay_ms(500);

			for(u8 j = 0; j < 16; j++){
				LCD_vidMoveStickMan(1, j, j+1, No_Ground, lcd);;
				_delay_ms(500);
			}
			LCD_vidMoveCursor(0, 8, lcd);

			//LCD_Char(3);
			//_delay_ms(500);
		}

		if(k ==1){
			LCD_vidMoveCursor(0, 0, lcd);
			LCD_vidSendChar(3, lcd);
			_delay_ms(500);
			for(u8 j = 0; j < 8; j++){
				LCD_vidMoveStickMan(0, j, j+1, Ground, lcd);
				_delay_ms(500);
				if(j == 7){
					LCD_vidMoveCursor(0, 7, lcd);
					LCD_vidSendChar(1, lcd);
					LCD_vidSendChar(0, lcd);
					_delay_ms(500);
				}
			}
		}
	}
	LCD_vidMoveCursor(0, 8, lcd);
	LCD_vidSendChar(2, lcd);
	LCD_vidMoveCursor(1, 8, lcd);
	LCD_vidSendChar(0, lcd);
	_delay_ms(500);
	for(u8 i = 8; i > 0; i--){
		LCD_vidMoveStickMan(1, i, i-1, No_Ground, lcd);
		_delay_ms(500);
	}

	LCD_vidMoveCursor(1, 7, lcd);
	LCD_vidSendChar(4, lcd);
	//LCD_vidSendChar(5, lcd);
	LCD_vidSendChar(6, lcd);
	//LCD_vidSendChar(7, lcd);
	LCD_vidMoveCursor(0, 0, lcd);
	for(u8 i = 0; i < 8; i++)
		LCD_vidSendChar(2, lcd);
	for(u8 i = 0; i < 5; i++){
		LCD_vidMoveStickMan(LowerFloor, i, i+1, No_Ground, lcd);
		_delay_ms(500);
	}
	LCD_vidMoveCursor(LowerFloor, 5, lcd);
	LCD_vidSendChar(2, lcd);


	LCD_Custom_Char(0, Character8, lcd);  /* Build Character1 at position 0 */
	LCD_Custom_Char(3, Character12, lcd);  /* Build Character3 at position 2 */


/*
	LCD_vidMoveCursor(LowerFloor, 5, lcd);
	LCD_vidSendChar(0, lcd);
	LCD_vidMoveCursor(UpperFloor, 5, lcd);
	LCD_vidSendChar(4, lcd);
	_delay_ms(500);
*/

	LCD_vidMoveCursor(LowerFloor, 7, lcd);
	LCD_vidSendChar(0, lcd);
	LCD_vidMoveCursor(UpperFloor, 7, lcd);
	LCD_vidSendChar(3, lcd);
	_delay_ms(500);


	//Clear the split stickMan
	LCD_vidMoveCursor(LowerFloor, 7, lcd);
	LCD_vidSendChar(2, lcd);
	LCD_vidMoveCursor(UpperFloor, 7, lcd);
	LCD_vidSendChar(2, lcd);

	//move stickman one step up
	LCD_Custom_Char(0, Character10, lcd);  /* Build Character1 at position 0 */
	LCD_Custom_Char(3, Character14, lcd);  /* Build Character3 at position 2 */
	LCD_vidSendChar(2, lcd);
	LCD_vidMoveCursor(LowerFloor, 8, lcd);
	LCD_vidSendChar(0, lcd);
	LCD_vidMoveCursor(UpperFloor, 8, lcd);
	LCD_vidSendChar(3, lcd);
	_delay_ms(500);

	//clear
	LCD_vidMoveCursor(LowerFloor, 8, lcd);
	LCD_vidSendChar(2, lcd);
	LCD_vidMoveCursor(UpperFloor, 8, lcd);
	LCD_vidSendChar(2, lcd);

	LCD_Custom_Char(3, Character3, lcd);  /* Build Character1 at position 0 */
	LCD_Custom_Char(0, Character0, lcd);  /* Build Character3 at position 2 */
	LCD_vidMoveCursor(UpperFloor, 9, lcd);
	LCD_vidSendChar(3, lcd);
	for(u8 i = 8; i < 14; i++){
		LCD_vidMoveStickMan(UpperFloor, i, i+1, Ground, lcd);
		_delay_ms(500);
	}
	LCD_vidMoveCursor(UpperFloor, 14, lcd);
	LCD_vidSendChar(1, lcd);
	LCD_Custom_Char(0, HitWall, lcd);
	LCD_vidMoveCursor(UpperFloor, 15, lcd);
	LCD_vidSendChar(0, lcd);
	_delay_ms(500);

	LCD_Custom_Char(0, Legs, lcd);
	LCD_vidMoveCursor(UpperFloor, 15, lcd);
	LCD_vidSendChar(0, lcd);

	LCD_Custom_Char(3, HeadArmsSide, lcd);
	LCD_vidMoveCursor(UpperFloor, 14, lcd);
	LCD_vidSendChar(3, lcd);
	_delay_ms(1000);

	LCD_vidMoveCursor(LowerFloor, 3, lcd);
	LCD_vidSendString("Game Over", lcd);


	//LCD_vidSendChar(8, lcd);



}





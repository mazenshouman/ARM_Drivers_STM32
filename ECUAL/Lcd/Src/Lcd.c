/*
 *  File 	   : Lcd.c
 *  Created on : April 17, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Bit_Math.h"
#include "Dio.h"
#include "Dio_Lcfg.h"
#include "Lcd_Wrapper.h"
#include "Lcd_Cfg.h"
#include "Lcd.h"
#include "Lcd_Lcfg.h"

/*not complete yet i will continue coding for it later (i think i wont need it)*/
#ifdef LCD_ACTIVATE_STATES

typedef uint8 Lcd_FunctionStatesType;
#define LCD_NUMBER_OF_FUNCTIONS_WITH_STATE_COUNTER          (Lcd_FunctionStatesType)4


typedef uint8 Lcd_LocalStateCounterType;

/************************************************************************
 *              private Array used to save the lcd states in            *
 *                          case of realtime usage                     `*
 ************************************************************************/
Lcd_LocalStateCounterType garr_LcdStateCounter[LCD_NUMBER_OF_CONFIGURED_LCDS][LCD_NUMBER_OF_FUNCTIONS_WITH_STATE_COUNTER];

#endif


/************************************************************************
 *                               Macros And Types                       *
 ************************************************************************/
#define LCD_NUMBER_OF_DATA_LINES_MASK                           (0x30)
#define LCD_SHIFT_MASK                                          (0x05)

#define LCD_GET_LOWEST_BIT(VALUE)                               (VALUE&1)
#define LCD_GET_LOWER_NIBBLE(VALUE)                             (VALUE&0x0F)
#define LCD_MOVE_HIGH_NIBBLE_TO_LOW_NIBBLE(VALUE)               (VALUE>>=4)

#define LCD_NUMBER_OF_DISPLAY_LINES_MASK						(0x28)
#define LCD_DDRAM_FIRST_ADDRESS                                 (0)
#define LCD_DDRAM_FIRST_ROW_LAST_ADDRESS                        (39)
#define LCD_DDRAM_LAST_ADDRESS                                  (79)
#define LCD_NUMBER_OF_CHAR_IN_EACH_LINE                         (40)
#define LCD_SECOND_LINE_FIRST_ADDRESS                           (0x40)
#define LCD_CGRAM_FIRST_ADDRESS                                 (0)
#define LCD_CGRAM_LAST_ADDRESS                                  (63)

#define LCD_FONT_MASK                                           (0x24)
#define LCD_SIZE_CUST_CHAR_FONT_5_8                             8
#define LCD_SIZE_CUST_CHAR_FONT_5_10                            16
#define LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_8              8
#define LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_10             10
#define LCD_NUMBER_OF_BYTES_DDRAM_CUST_CHAR_FONT_5_10           2

/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Lcd_Init                                                                                                               *
 *  Param    : IN     : Name / none                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / none                                                                                                   *
 *                                                                                                                                    *
 *             Output : Name / none                                                                                                   *
 *                                                                                                                                    *
 *  Return   : none                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize The Lcd to be ready to take command and data from user and initialize local                   *
 *             structure for each lcd defined                                                                                         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Lcd_Init(void)
{
	/*
	 * we don't need to initialize the lcd as the internal reset circuit will do the job for us
	 * but we must make our configuration for it.
	 * if the hardware reset or software reset performed then there will be a problem as the internal circuit won't work
	 * at this moment we have to initialize lcd (same operations performed by the internal reset circuit)
	 * */

	Lcd_ConfigurationStrSizeType u8_localCounterForId=0;
	for(u8_localCounterForId=0 ; u8_localCounterForId<LCD_NUMBER_OF_CONFIGURED_LCDS ; ++u8_localCounterForId)
	{



		switch(gastr_LcdConfigArr[u8_localCounterForId].Lcd_FunctionSet & LCD_NUMBER_OF_DATA_LINES_MASK)
		{
			/*write value to the lcd*/
			case LCD_4_BIT_DATA_MODE:
				/*
				 * the first line is mandatory in case of internal reset not working
				 * and we need to initialize the lcd
				 * */

				/*
				 * send set 8 bit mode command high part of it twice as data sheet recommended
				 * */

				Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , 0x33);

				/*
				 * this line is mandatory in all cases without it the lcd won't work in 4 bit mode
				 * */
				/*
				 * then send one more 8 bit command high part after that the 4-bit mode
				 * */

				Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , 0x32);
				break;
			case LCD_8_BIT_DATA_MODE:
				/*
				 * send 8 bit mode at the start of the initialization
				 * */

				Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , 0x30);
				break;
		}
#if LCD_INTERAL_RESET_OPERATIONS
		/*
		 * write Clear display Command
		 * */

		Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , LCD_CLEAR_DISPLAY_COMMAND);

		/*
		 * display clear command needs 1.52 ms which stated in the datasheet
		 * but protues seems to need only 150 us at 8 MHZ clock and it works fine on hardware
		 * without delay :D
		 * */

		_delay_us(500);

#endif


		/*
		 * write Lcd_FunctionSet Command
		 * */

		Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , gastr_LcdConfigArr[u8_localCounterForId].Lcd_FunctionSet);

		/*
		 * write Lcd_DisplayControl Command
		 * */

		Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , gastr_LcdConfigArr[u8_localCounterForId].Lcd_DisplayControl);


		/*
		 * write Lcd_EntryMode Command
		 * */

		Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , gastr_LcdConfigArr[u8_localCounterForId].Lcd_EntryMode);

		/*
		 * write Lcd_CursorOrDiplayShift Command
		 * */
		if((gastr_LcdConfigArr[u8_localCounterForId].Lcd_EntryMode&LCD_SHIFT_MASK) == LCD_DISPLAY_SHIFT_ON)
		{
			Lcd_Write(u8_localCounterForId , LCD_WRITE_COMMAND , gastr_LcdConfigArr[u8_localCounterForId].Lcd_CursorOrDiplayShift);
		}

	}

}

/**************************************************************************************************************************************
 *  Function : Lcd_Write                                                                                                              *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                    : Name / Type                                                                                                   *
 *                      Type / Lcd_WriteType                                                                                          *
 *                      Desc / Selects between command and data                                                                       *
 *                    : Name / Value                                                                                                  *
 *                      Type / Lcd_ValueType                                                                                          *
 *                      Desc / wanted value to be written to the LCD                                                                  *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes the value wanted to be sent to the lcd. In case of command it must be ored together                *
 *             for specific functionality like entry mode set as if you don't ored it together it will override                       *
 *             the previous set value for this functionality OR data                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_Write(Lcd_IdType Lcd_Id ,Lcd_WriteType Type,Lcd_ValueType Value)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;
	Lcd_NumberOfDataPinsType u8_localCounterForPins=0;
	Lcd_ValueType            u8_localLowerValue=0;

	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS )
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*
		 * set value of R/W pin low to make it write to the lcd
		 * */

		Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_R_W] , STD_LOW);

		/*
		 * set value of RS pin depending on the value of the type (data or command)
		 * */

		switch(Type)
		{
			case LCD_WRITE_COMMAND:

				/*
				 * set RS pin Low for commands
				 * */

				Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_RS] , STD_LOW);
				break;
			case LCD_WRITE_DATA:

				/*
				 * set RS pin high for data
				 * */

				Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_RS] , STD_HIGH);
				break;
			default:
				returnState=LCD_WRONG_TYPE;
				break;
		}

		if(returnState==LCD_E_OK)
		{
			/*switch between the 4 data line and 8 data lines*/

			switch(gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_NUMBER_OF_DATA_LINES_MASK)
			{

				case LCD_4_BIT_DATA_MODE:

					/*
					 * save the lower part of the data
					 * */

					u8_localLowerValue=LCD_GET_LOWER_NIBBLE(Value);

					/*
					 * move the higher part of the data to the lower part
					 * */

					LCD_MOVE_HIGH_NIBBLE_TO_LOW_NIBBLE(Value);
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_ZERO ; u8_localCounterForPins<NUMBER_FOUR ; ++u8_localCounterForPins)
					{
						Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins] , LCD_GET_LOWEST_BIT(Value));
						Value>>=1;
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);

					/*
					 * the high part of the data has been latched
					 * */

					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_ZERO ; u8_localCounterForPins<NUMBER_FOUR ; ++u8_localCounterForPins)
					{
						Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins] , LCD_GET_LOWEST_BIT(u8_localLowerValue));
						u8_localLowerValue>>=1;
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);

					break;
				case LCD_8_BIT_DATA_MODE:
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_ZERO ; u8_localCounterForPins<NUMBER_EIGHT ; ++u8_localCounterForPins)
					{
						Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins] , LCD_GET_LOWEST_BIT(Value));
						Value>>=1;
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);

					break;
				default:
					break;
			}

		}
	}
	return returnState;
}

/**************************************************************************************************************************************
 *  Function : Lcd_Goto                                                                                                               *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / Row                                                                                                    *
 *                      Type / Lcd_RowValueType                                                                                       *
 *                      Desc / predefine macro for the row number                                                                     *
 *                      Name / Col                                                                                                    *
 *                      Type / Lcd_ColumnValueType                                                                                    *
 *                      Desc / value for the wanted column (range of values demonstrated in top of the type)                          *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes the wanted position to move the cursor to it. The position is taken in the form                    *
 *             of row number and column number                                                                                        *
 *  caution  : -if you will use single row in configuration the row value must                                                        *
 * 			    be LCD_FIRST_ROW only                                                                                                 *
 * 			   -in one row mode the column value ranges from 0:79                                                                     *
 * 			   -in two row mode the column value for the first or the second row ranges from 0:39                                     *
 * 			    (0->39 for the first row) and (0 ->39 for the second row).                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_Goto(Lcd_IdType Lcd_Id ,Lcd_RowValueType Row,Lcd_ColumnValueType Col)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;

	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS )
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*checking the value for single line*/
		if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_NUMBER_OF_DISPLAY_LINES_MASK) == LCD_ONE_DISPLAY_LINE) && ((Row!=LCD_FIRST_ROW)||(Col>LCD_DDRAM_LAST_ADDRESS)))
		{
			returnState=LCD_WRONG_POS;
		}

		/*checking the value for two lines (I divided the conditions for readability)
		 * and I didn't check for the row value in the second condition(trust in user)
		 * */
		else if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_NUMBER_OF_DISPLAY_LINES_MASK) == LCD_TWO_DISPLAY_LINE) && ((Col>LCD_DDRAM_FIRST_ROW_LAST_ADDRESS)))
		{
			returnState=LCD_WRONG_POS;
		}
		else
		{
			Lcd_Write(Lcd_Id , LCD_WRITE_COMMAND  , (LCD_DDRAM|Row|Col));
		}
	}
	return returnState;

}

/**************************************************************************************************************************************
 *  Function : Lcd_WriteString                                                                                                        *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / String                                                                                                 *
 *                      Type / const sint8                                                                                       ö      *
 *                      Desc / pointer to string which is sent from caller function                                                   *
 *                                                                                                                                    *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes string from the caller function and display it on the LCD                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_WriteString(Lcd_IdType Lcd_Id , const sint8* String)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;

	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS )
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		if(String==NULL)
		{
			returnState=LCD_NULL_POINTER;
		}
		else
		{
			while(*String)
			{
				Lcd_Write(Lcd_Id , LCD_WRITE_DATA , (uint8)(*String));
				String++;
			}
		}
	}

	return returnState;
}


/**************************************************************************************************************************************
 *  Function : Lcd_SetAddress                                                                                                         *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / type                                                                                                   *
 *                      Type / Lcd_DataOrCharacterMemorySelectType                                                                    *
 *                      Desc / predefine macro for selecting the memory wanted to set address for                                     *
 *                      Name / address                                                                                                *
 *                      Type / Lcd_ValueType                                                                                          *
 *                      Desc / value for the wanted address wanted to jump to                                                         *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes the wanted address wanted to jump to, either in DDRAM or CGRAM                                     *
 *  caution  : (For DDRAM)                                                                                                            *
 *             -the addres value must be in range (0 -> 79)                                                                           *
 *  		   -if you use single row in configuration the address value must can take any value in the                               *
 *  		    previous mentioned range                                                                                              *
 * 			   -in Two row mode the address for the first row will be (0->39) and for the second row(40 -> 79)                        *
 * 			   (For CGRAM)                                                                                                            *
 * 			   -the address must be in range (0 -> 63)                                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_SetAddress(Lcd_IdType Lcd_Id ,Lcd_DataOrCharacterMemorySelectType type,Lcd_ValueType address)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;

	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS )
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		if(type==LCD_DDRAM){
			/*checking if the address in the range or not*/
			if(address>LCD_DDRAM_LAST_ADDRESS)
			{
				returnState=LCD_ADDRESS_OUT_OF_RANGE;
			}
			else
			{
				/*if the lcd is configured as two line then we have to change the address for the second line if the address in it's range*/
				if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_NUMBER_OF_DISPLAY_LINES_MASK) == LCD_TWO_DISPLAY_LINE) && (address >39))
				{
					/*sub the address from number of characters in the first line to get the real position*/
					address-=LCD_NUMBER_OF_CHAR_IN_EACH_LINE;
					address|=(LCD_SECOND_LINE_FIRST_ADDRESS);
				}
				Lcd_Write(Lcd_Id , LCD_WRITE_COMMAND , LCD_SET_DDRAM_ADDRESS(address));
			}

		}
		else
		{	/*checking if the address in the range or not*/
			if(address>LCD_CGRAM_LAST_ADDRESS)
			{
				returnState=LCD_ADDRESS_OUT_OF_RANGE;
			}
			else
			{
				Lcd_Write(Lcd_Id , LCD_WRITE_COMMAND , LCD_SET_CGRAM_ADDRESS(address));
			}
		}
	}
	return returnState;
}


#ifdef LCD_ACTIVATE_CUSTOME_CHAR_MEMORY
/**************************************************************************************************************************************
 *  Function : Lcd_CreateCustomChar                                                                                                   *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / pos                                                                                                    *
 *                      Type / Lcd_CustCharPosType                                                                                    *
 *                      Desc / predefine macro for position of the char in the CGRAM                                                  *
 *                      Name / Char_Id                                                                                                *
 *                      Type / Lcd_CustCharIdType                                                                                     *
 *                      Desc / predefine macro for position of the char at pointer to array in the configuration Array                *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function create custom char from the predefine array of custom chars in the configuration array                   *
 *             by taking the id of the char in the 2d and the position of the custom char in the CGRAM                                *
 *             note that:                                                                                                             *
 *             -if the font configured as 5*8 you have max 8 positions  (0->7)                                                        *
 *             -if the font configured as 5*10 you have only 4 positions (0->3)                                                       *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_CreateCustomChar(Lcd_IdType Lcd_Id ,Lcd_CustCharPosType pos,Lcd_CustCharIdType Char_Id)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;
	uint8 Local_NumberOfBytes=1;
	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS)
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*check if char_id in range between first id and configured number of custom characters*/
		if(Char_Id >LCD_CUST_CHAR_7 || Char_Id >gastr_LcdConfigArr[Lcd_Id].Lcd_NumberOfCustomChar)
		{
			returnState=LCD_ID_OUTOFRANGE;
		}
		else
		{
			/*check if the postion in range depending on the font configuration value*/
			if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_FONT_MASK) == LCD_FONT_5_8))
			{
				if(pos>LCD_CUST_CHAR_POS_7)
				{
					returnState=LCD_POS_OUT_OR_RANGE;
				}
				else
				{
					pos*=LCD_SIZE_CUST_CHAR_FONT_5_8;
					Local_NumberOfBytes=LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_8;
				}
			}
			else
			{
				if(pos>LCD_CUST_CHAR_POS_3)
				{
					returnState=LCD_POS_OUT_OR_RANGE;
				}
				else
				{
					pos*=LCD_SIZE_CUST_CHAR_FONT_5_10;
					Local_NumberOfBytes=LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_10;
				}
			}
			if(returnState==LCD_E_OK)
			{
				/*change current address to the CGRAM address depending on position*/
				Lcd_SetAddress(Lcd_Id , LCD_CGRAM , pos);

				/*write custom char in CGRAM with for loop with loop depending on the font configuration*/
				for(pos=0 ; pos<Local_NumberOfBytes ; pos++)
				{
					Lcd_Write(Lcd_Id , LCD_WRITE_DATA , gastr_LcdConfigArr[Lcd_Id].Lcd_PtrArrCustomChar[Char_Id][pos]);
				}
				/*change address back to ddram address (temp return to address zero after each creation of custom char)
				 * (future enhancement)
				 * -read AC before jumping to CGRAM
				 * -then return to this address after creating the custom character
				 * */
				Lcd_SetAddress(Lcd_Id , LCD_DDRAM , LCD_DDRAM_FIRST_ADDRESS);
			}
		}
	}
	return returnState;
}

#else

/**************************************************************************************************************************************
 *  Function : Lcd_CreateCustomChar                                                                                                   *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / pos                                                                                                    *
 *                      Type / Lcd_CustCharPosType                                                                                    *
 *                      Desc / predefine macro for position of the char in the CGRAM                                                  *
 *                      Name / CustomChar                                                                                             *
 *                      Type / Lcd_CustCharType*                                                                                      *
 *                      Desc / address of the created array of values wanted to save in the CGRAM to create custom char               *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function create custom char from array passed to this function from the caller function                           *
 *             and save it in the position given in the CGRAM                                                                         *
 *             note that:                                                                                                             *
 *             -if the font configured as 5*8 you have max 8 positions                                                                *
 *             -if the font configured as 5*10 you have only 4 positions                                                              *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_CreateCustomChar(Lcd_IdType Lcd_Id ,Lcd_CustCharPosType pos,Lcd_CustCharType* CustomChar)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;
	uint8 Local_NumberOfBytes=1;
	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS)
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*check if the postion in range depending on the font configuration value*/
		if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_FONT_MASK) == LCD_FONT_5_8))
		{
			if(pos>LCD_CUST_CHAR_POS_7)
			{
				returnState=LCD_POS_OUT_OR_RANGE;
			}
			else
			{
				pos*=LCD_SIZE_CUST_CHAR_FONT_5_8;
				Local_NumberOfBytes=LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_8;
			}
		}
		else
		{
			if(pos>LCD_CUST_CHAR_POS_3)
			{
				returnState=LCD_POS_OUT_OR_RANGE;
			}
			else
			{
				pos*=LCD_SIZE_CUST_CHAR_FONT_5_10;
				Local_NumberOfBytes=LCD_MAX_NUMBER_OF_BYTES_CUST_CHAR_FONT_5_10;
			}
		}
		if(returnState==LCD_E_OK)
		{
			/*change current address to the CGRAM address depending on position*/
			Lcd_SetAddress(Lcd_Id , LCD_CGRAM , pos);

			/*write custom char in CGRAM with for loop with loop depending on the font configuration*/
			for(pos=0 ; pos<Local_NumberOfBytes ; pos++)
			{
				Lcd_Write(Lcd_Id , LCD_WRITE_DATA , CustomChar[pos]);
			}

			/*change address back to ddram address (temp return to address zero after each creation of custom char)
			 * (future enhancement)
			 * -read AC before jumping to CGRAM
			 * -then return to this address after creating the custom character
			 * */
			Lcd_SetAddress(Lcd_Id , LCD_DDRAM , LCD_DDRAM_FIRST_ADDRESS);

		}
	}
	return returnState;
}

#endif

/**************************************************************************************************************************************
 *  Function : Lcd_DisplayCustomChar                                                                                                  *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / pos                                                                                                    *
 *                      Type / Lcd_CustCharPosType                                                                                    *
 *                      Desc / predefined macro for location of the custom char in the DDRAM                                          *
 *                                                                                                                                    *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function the position of the custom char in DDRAM and display it                                                  *
 *             note that:                                                                                                             *
 *             -if the font configured as 5*8 you have max 8 positions                                                                *
 *             -if the font configured as 5*10 you have only 4 positions                                                              *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_DisplayCustomChar(Lcd_IdType Lcd_Id , Lcd_CustCharPosType pos)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;
	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS)
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*check if the postion in range depending on the font configuration value*/
		if(((gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_FONT_MASK) == LCD_FONT_5_8))
		{
			if(pos>LCD_CUST_CHAR_POS_7)
			{
				returnState=LCD_POS_OUT_OR_RANGE;
			}

		}
		else
		{
			if(pos>LCD_CUST_CHAR_POS_3)
			{
				returnState=LCD_POS_OUT_OR_RANGE;
			}
			else
			{
				pos*=LCD_NUMBER_OF_BYTES_DDRAM_CUST_CHAR_FONT_5_10;
			}
		}
		if(returnState==LCD_E_OK)
		{
			/*display custom char at pos in the DDRAM*/
			Lcd_Write(Lcd_Id , LCD_WRITE_DATA , pos);
		}
	}
	return returnState;
}

/**************************************************************************************************************************************
 *  Function : Lcd_Read                                                                                                               *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / Type                                                                                                   *
 *                      Type / Lcd_ReadType                                                                                           *
 *                      Desc / predefined macro selects between reading address or data                                               *
 *                                                                                                                                    *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function read the current data or address from the lcd (currently works only on eight bit mode)                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ValueType Lcd_Read(Lcd_IdType Lcd_Id , Lcd_ReadType Type)
{
	Lcd_ErrorStateType returnState=LCD_E_OK;
	Lcd_NumberOfDataPinsType u8_localCounterForPins=0;
	Lcd_ValueType            u8_returnValue=0;

	if(Lcd_Id > LCD_NUMBER_OF_CONFIGURED_LCDS )
	{
		returnState=LCD_ID_OUTOFRANGE;
	}
	else
	{
		/*
		 * set value of R/W pin Highh to make it Read From the lcd
		 * */

		Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_R_W] , STD_HIGH);

		/*
		 * set value of RS pin depending on the value of the type (address or data)
		 * */

		switch(Type)
		{
			case LCD_READ_ADDRESS:

				/*
				 * set RS pin Low for Address
				 * */

				Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_RS] , STD_LOW);
				break;
			case LCD_READ_DATA:

				/*
				 * set RS pin high for data
				 * */

				Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_RS] , STD_HIGH);
				break;
			default:
				returnState=LCD_WRONG_TYPE;
				break;
		}
		if(returnState==LCD_E_OK)
		{
			/*switch between the 4 data line and 8 data lines*/

			switch(gastr_LcdConfigArr[Lcd_Id].Lcd_FunctionSet & LCD_NUMBER_OF_DATA_LINES_MASK)
			{

			/*this part is not working has problems on it*/
#if 0
				case LCD_4_BIT_DATA_MODE:
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_FOUR ; u8_localCounterForPins<NUMBER_SEVEN ; ++u8_localCounterForPins)
					{
						SET_VALUE_FOR_BIT_IN_REG(u8_returnValue ,u8_localCounterForPins ,Lcd_ReadChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins]));
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);

					/*
					 * the high part of the data has been latched
					 * */

					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_FOUR ; u8_localCounterForPins<NUMBER_EIGHT ; ++u8_localCounterForPins)
					{
						SET_VALUE_FOR_BIT_IN_REG(u8_returnValue ,(u8_localCounterForPins-NUMBER_FOUR) ,Lcd_ReadChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins]));
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);

					break;
#endif
				case LCD_8_BIT_DATA_MODE:
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_HIGH);
					for(u8_localCounterForPins=NUMBER_ZERO ; u8_localCounterForPins<NUMBER_SEVEN ; ++u8_localCounterForPins)
					{
						SET_VALUE_FOR_BIT_IN_REG(u8_returnValue ,u8_localCounterForPins ,Lcd_ReadChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_DataPinsArr[u8_localCounterForPins]));
					}
					Lcd_WriteChannel(gastr_LcdConfigArr[Lcd_Id].Lcd_ControlPinsArr[LCD_E] , STD_LOW);
					break;
				default:
					break;
			}

		}
	}
	return u8_returnValue;
}




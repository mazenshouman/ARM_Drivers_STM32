/*
 *  File 	   : Lcd.h
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LCD_INC_LCD_H_
#define LCD_INC_LCD_H_

/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/

typedef uint8 Lcd_IdType;
#define LCD_ID0                                         (Lcd_IdType)0
#define LCD_ID1                                         (Lcd_IdType)1
#define LCD_ID2                                         (Lcd_IdType)2
#define LCD_ID3                                         (Lcd_IdType)3
#define LCD_ID4                                         (Lcd_IdType)4
#define LCD_ID5                                         (Lcd_IdType)5
#define LCD_ID6                                         (Lcd_IdType)6
#define LCD_ID7                                         (Lcd_IdType)7
#define LCD_ID8                                         (Lcd_IdType)8
#define LCD_ID9                                         (Lcd_IdType)9
#define LCD_ID10                                        (Lcd_IdType)10

/*
 * Error state macros
 * */
typedef uint8 Lcd_ErrorStateType;
#define LCD_E_OK                                        (Lcd_ErrorStateType)0
#define LCD_E_NOT_OK                                    (Lcd_ErrorStateType)1
#define LCD_ID_OUTOFRANGE                               (Lcd_ErrorStateType)2
#define LCD_ACTIVE_TYPE_IS_NOT_DEFINED                  (Lcd_ErrorStateType)3
#define LCD_NULL_POINTER                                (Lcd_ErrorStateType)4
#define LCD_UNDEFINED_STATE                             (Lcd_ErrorStateType)5
#define LCD_WRONG_TYPE                                  (Lcd_ErrorStateType)6
#define LCD_WRONG_POS                                   (Lcd_ErrorStateType)7
#define LCD_ADDRESS_OUT_OF_RANGE                        (Lcd_ErrorStateType)8
#define LCD_POS_OUT_OR_RANGE                            (Lcd_ErrorStateType)9


typedef uint8 Lcd_ValueType;

typedef uint8 Lcd_DataOrCharacterMemorySelectType;
#define LCD_CGRAM                                       (Lcd_DataOrCharacterMemorySelectType)64
#define LCD_DDRAM                                       (Lcd_DataOrCharacterMemorySelectType)128


#define LCD_CLEAR_DISPLAY_COMMAND                       (Lcd_ValueType)1

/*------------------------------------------------------------------------------------------------*/

/*
 * typedefs for goto function which takes row and columns
 * caution : -if you will use single row in configuration the row value must
 * 			  be LCD_FIRST_ROW only
 * 			 -in one row mode the column value ranges from 0:79
 * 			 -in two row mode the column value for the first or the second row ranges from 0:39
 * 			  (0->39 for the first row) and (0 ->39 for the second row).
 * */

typedef uint8 Lcd_RowValueType;
#define LCD_FIRST_ROW  									(Lcd_RowValueType)0
#define LCD_SECOND_ROW									(Lcd_RowValueType)64

typedef uint8 Lcd_ColumnValueType;

/*------------------------------------------------------------------------------------------------*/


/**************************
 *     Entry Mode Set     *
 * ************************/
typedef uint8 Lcd_EntryModeType;


#define LCD_DISPLAY_SHIFT_OFF                           (Lcd_EntryModeType)4
#define LCD_DISPLAY_SHIFT_ON                            (Lcd_EntryModeType)5

/*
 * Macros For AC Increment or Decrement on reading or writting to DDRAM
 * */

#define LCD_ADDRESS_DECREMENT                           (Lcd_EntryModeType)4
#define LCD_ADDRESS_INCREMENT                           (Lcd_EntryModeType)6

/**************************
 *Cursor or display shift *
 **************************/

typedef uint8 Lcd_CursorOrDiplayShiftType;

/*
 * macros for Direction of the shift
 * */

#define LCD_DISPLAY_OR_CURSOR_SHIFT_LEFT               (Lcd_CursorOrDiplayShiftType)16
#define LCD_DISPLAY_OR_CURSOR_SHIFT_RIGHT              (Lcd_CursorOrDiplayShiftType)20

/*
 * macros for Selecting Cursor of Display For Shift
 * */

#define LCD_CURSOR_SHIFT                               (Lcd_CursorOrDiplayShiftType)16
#define LCD_DISPLAY_SHIFT                              (Lcd_CursorOrDiplayShiftType)24

/**************************
 * Display On/Off Control *
 * ************************/

typedef uint8 Lcd_DisplayContorlType;

/*
 * macros for blinking
 * */

#define LCD_BLINKING_OFF                               (Lcd_DisplayContorlType)8
#define LCD_BLINKING_ON                                (Lcd_DisplayContorlType)9

/*
 * macros for cursor
 * */

#define LCD_CURSOR_OFF                                 (Lcd_DisplayContorlType)8
#define LCD_CURSOR_ON                                  (Lcd_DisplayContorlType)10

/*
 * macros for entire Display on/off
 * */

#define LCD_DISPLAY_OFF                                (Lcd_DisplayContorlType)8
#define LCD_DISPLAY_ON                                 (Lcd_DisplayContorlType)12


/***********************
 * function set macros *
 * *********************/

typedef uint8 Lcd_FunctionSetType;


/*
 * Macros for Font (each character size (8*5 or 10*5))
 * */


#define LCD_FONT_5_8                                  (Lcd_FunctionSetType)32
#define LCD_FONT_5_10                                 (Lcd_FunctionSetType)36

/*
 * macros for number of display lines
 * */

#define LCD_ONE_DISPLAY_LINE                         (Lcd_FunctionSetType)32
#define LCD_TWO_DISPLAY_LINE                         (Lcd_FunctionSetType)40

/*
 * macros for data pins (4 bit or 8 bit)
 * */

#define LCD_4_BIT_DATA_MODE                          (Lcd_FunctionSetType)32
#define LCD_8_BIT_DATA_MODE                          (Lcd_FunctionSetType)48

/*------------------------------------------------------------------------------------------------*/

typedef uint8 Lcd_WriteType;
#define LCD_WRITE_DATA                               (Lcd_WriteType)0
#define LCD_WRITE_COMMAND                            (Lcd_WriteType)1

/*------------------------------------------------------------------------------------------------*/

typedef uint8 Lcd_ReadType;
#define LCD_READ_ADDRESS                             (Lcd_ReadType)0
#define LCD_READ_DATA                                (Lcd_ReadType)1

/*------------------------------------------------------------------------------------------------*/
/*
 * macro like function
 * */

#define LCD_SET_CGRAM_ADDRESS(ADDRESS)               (uint8)(64|ADDRESS)
#define LCD_SET_DDRAM_ADDRESS(ADDRESS)               (uint8)(128|ADDRESS)

/*------------------------------------------------------------------------------------------------*/

/*Custom Char Macros*/
typedef const uint8 Lcd_CustCharType;
typedef uint8 Lcd_CustCharMaxNumberType;
#define LCD_MAX_NUMBER_OF_CUST_CHAR                  (Lcd_CustCharMaxNumberType)1
#define LCD_MAX_SIZE_OF_CUST_CHAR_ARR                10


/*Custom Char Pos in CGRAM*/
typedef uint8 Lcd_CustCharPosType;
#define LCD_CUST_CHAR_POS_0                          (Lcd_CustCharPosType)0
#define LCD_CUST_CHAR_POS_1                          (Lcd_CustCharPosType)1
#define LCD_CUST_CHAR_POS_2                          (Lcd_CustCharPosType)2
#define LCD_CUST_CHAR_POS_3                          (Lcd_CustCharPosType)3
#define LCD_CUST_CHAR_POS_4                          (Lcd_CustCharPosType)4
#define LCD_CUST_CHAR_POS_5                          (Lcd_CustCharPosType)5
#define LCD_CUST_CHAR_POS_6                          (Lcd_CustCharPosType)6
#define LCD_CUST_CHAR_POS_7                          (Lcd_CustCharPosType)7


#ifdef LCD_ACTIVATE_CUSTOME_CHAR_MEMORY
/*Custom Char Ids*/
typedef uint8 Lcd_CustCharIdType;
#define LCD_CUST_CHAR_0                              (Lcd_CustCharIdType)0
#define LCD_CUST_CHAR_1                              (Lcd_CustCharIdType)1
#define LCD_CUST_CHAR_2                              (Lcd_CustCharIdType)2
#define LCD_CUST_CHAR_3                              (Lcd_CustCharIdType)3
#define LCD_CUST_CHAR_4                              (Lcd_CustCharIdType)4
#define LCD_CUST_CHAR_5                              (Lcd_CustCharIdType)5
#define LCD_CUST_CHAR_6                              (Lcd_CustCharIdType)6
#define LCD_CUST_CHAR_7                              (Lcd_CustCharIdType)7

#endif


/*------------------------------------------------------------------------------------------------*/
/*old configuration*/
#if 0
/**************************
 *     Entry Mode Set     *
 * ************************/

/*
 * macros for Shift of the entire Address Space when Writing (display shift) when Writing to it
 * */

typedef uint8 Lcd_DisplayShiftOnWritingType;
#define LCD_DISPLAY_SHIFT_ON_WRITING_OFF                (Lcd_DisplayShiftOnWritingType)0
#define LCD_DISPLAY_SHIFT_ON_WRITING_ON                 (Lcd_DisplayShiftOnWritingType)1

/*
 * Macros For AC Increment or Decrement on reading or writting to DDRAM
 * */

typedef uint8 Lcd_AddressIncDecType;
#define LCD_ADDRESS_DECREMENT                           (Lcd_AddressIncDecType)0
#define LCD_ADDRESS_INCREMENT                           (Lcd_AddressIncDecType)2

/**************************
 *Cursor or display shift *
 * ************************/

/*
 * macros for Direction of the shift
 * */

typedef uint8 Lcd_DisplayOrCursorShiftDirectionType;
#define LCD_DISPLAY_OR_CURSOR_SHIFT_LEFT               (Lcd_DisplayOrCursorShiftDirectionType)0
#define LCD_DISPLAY_OR_CURSOR_SHIFT_RIGHT              (Lcd_DisplayOrCursorShiftDirectionType)4

/*
 * macros for Selecting Cursor of Display For Shift
 * */

typedef uint8 Lcd_DisplayOrCursorShiftType;
#define LCD_CURSOR_SHIFT                               (Lcd_DisplayOrCursorShiftType)0
#define LCD_DISPLAY_SHIFT                              (Lcd_DisplayOrCursorShiftType)8

/**************************
 * Display On/Off Control *
 * ************************/

/*
 * macros for blinking
 * */

typedef uint8 Lcd_BlinkingOnOffType;
#define LCD_BLINKING_OFF                               (Lcd_BlinkingOnOffType)0
#define LCD_BLINKING_ON                                (Lcd_BlinkingOnOffType)1

/*
 * macros for cursor
 * */

typedef uint8 Lcd_CursorOnOffType;
#define LCD_CURSOR_OFF                                 (Lcd_CursorOnOffType)0
#define LCD_CURSOR_ON                                  (Lcd_CursorOnOffType)2

/*
 * macros for entire Display on/off
 * */

typedef uint8 Lcd_DisplayOnOffType;
#define LCD_DISPLAY_OFF                                (Lcd_DisplayOnOffType)0
#define LCD_DISPLAY_ON                                 (Lcd_DisplayOnOffType)4

/***********************
 * function set macros *
 * *********************/

/*
 * Macros for Font (each character size (8*5 or 10*5))
 * */

typedef uint8 Lcd_FontSizeType;
#define LCD_FONT_5_8                                  (Lcd_FontSizeType)0
#define LCD_FONT_5_10                                 (Lcd_FontSizeType)4

/*
 * macros for number of display lines
 * */

typedef uint8 Lcd_NumbeOfDisplayLinesType;
#define LCD_ONE_DISPLAY_LINE                         (Lcd_NumbeOfDisplayLinesType)0
#define LCD_TWO_DISPLAY_LINE                         (Lcd_NumbeOfDisplayLinesType)8

/*
 * macros for data pins (4 bit or 8 bit)
 * */

#define LCD_4_BIT_DATA_MODE                          (Lcd_NumberOfDataPinsType)0
#define LCD_8_BIT_DATA_MODE                          (Lcd_NumberOfDataPinsType)16


/*
 * macro like function
 * */

#define LCD_FUNCTION_SET(COMMAND)                    (uint8)(32|COMMAND)
#define LCD_ENTRY_MODE_SET(COMMAND)                  (uint8)(4|COMMAND)
#define LCD_DISPLAY_CONTROL(COMMAND)                 (uint8)(8|COMMAND)
#define LCD_CURSOR_OR_DISPLAT_SHIFT(COMMAND)         (uint8)(16|COMMAND)
#define LCD_SET_CGRAM_ADDRESS(ADDRESS)               (uint8)(64|ADDRESS)
#define LCD_SET_DDRAM_ADDRESS(ADDRESS)               (uint8)(128|ADDRESS)

#endif

/************************************************************************/

/************************************************************************
 *                    Lcd functions' prototype                          *
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

void Lcd_Init(void);

/**************************************************************************************************************************************
 *  Function : Lcd_Write                                                                                                              *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / Type                                                                                                   *
 *                      Type / Lcd_CommandType                                                                                        *
 *                      Desc / wanted command to be send ORed together for specific command                                           *
 *                      Name / Value                                                                                                  *
 *                      Type / Lcd_ValueType                                                                                          *
 *                      Desc / wanted value to be written to the LCD                                                                  *
 *             Output:None                                                                                                            *
 *                                                                                                                                    *
 *  Return   : Lcd_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes the command wanted to be sent to the lcd ored together for specific functionality like             *
 *             entry mode set as if you don't ored it together it will override the previous set value for this functionality         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_Write(Lcd_IdType Lcd_Id ,Lcd_WriteType Type,Lcd_ValueType Value);

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

Lcd_ErrorStateType Lcd_Goto(Lcd_IdType Lcd_Id ,Lcd_RowValueType Row,Lcd_ColumnValueType Col);

/**************************************************************************************************************************************
 *  Function : Lcd_WriteString                                                                                                        *
 *  Param    : IN     : Name / Lcd_Id                                                                                                 *
 *                      Type / Lcd_IdType                                                                                             *
 *                      Desc / predefine macro for Lcd id                                                                             *
 *                      Name / String                                                                                                 *
 *                      Type / sint8*                                                                                       ö           *
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

Lcd_ErrorStateType Lcd_WriteString(Lcd_IdType Lcd_Id , const sint8* String);

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

Lcd_ErrorStateType Lcd_SetAddress(Lcd_IdType Lcd_Id ,Lcd_DataOrCharacterMemorySelectType type,Lcd_ValueType address);

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
 *             -if the font configured as 5*8 you have max 8 positions                                                                *
 *             -if the font configured as 5*10 you have only 4 positions                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Lcd_ErrorStateType Lcd_CreateCustomChar(Lcd_IdType Lcd_Id ,Lcd_CustCharPosType pos,Lcd_CustCharIdType Char_Id);

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

Lcd_ErrorStateType Lcd_CreateCustomChar(Lcd_IdType Lcd_Id ,Lcd_CustCharPosType pos,Lcd_CustCharType* CustomChar);

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

Lcd_ErrorStateType Lcd_DisplayCustomChar(Lcd_IdType Lcd_Id , Lcd_CustCharPosType pos);

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

Lcd_ValueType Lcd_Read(Lcd_IdType Lcd_Id , Lcd_ReadType Type);



#endif /* LCD_INC_LCD_H_ */


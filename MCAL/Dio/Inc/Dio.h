/*
 *  File 	   : Dio.h
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef DIO_INC_DIO_H_
#define DIO_INC_DIO_H_



/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

typedef uint8 Dio_ChannelType;
#define DIO_CHANNEL_A0              (Dio_ChannelType)0
#define DIO_CHANNEL_A1              (Dio_ChannelType)1
#define DIO_CHANNEL_A2              (Dio_ChannelType)2
#define DIO_CHANNEL_A3              (Dio_ChannelType)3
#define DIO_CHANNEL_A4              (Dio_ChannelType)4
#define DIO_CHANNEL_A5              (Dio_ChannelType)5
#define DIO_CHANNEL_A6              (Dio_ChannelType)6
#define DIO_CHANNEL_A7              (Dio_ChannelType)7
#define DIO_CHANNEL_A8              (Dio_ChannelType)8
#define DIO_CHANNEL_A9              (Dio_ChannelType)9
#define DIO_CHANNEL_A10             (Dio_ChannelType)10
#define DIO_CHANNEL_A11             (Dio_ChannelType)11
#define DIO_CHANNEL_A12             (Dio_ChannelType)12
#define DIO_CHANNEL_A13             (Dio_ChannelType)13
#define DIO_CHANNEL_A14             (Dio_ChannelType)14
#define DIO_CHANNEL_A15             (Dio_ChannelType)15


#define DIO_CHANNEL_B0              (Dio_ChannelType)16
#define DIO_CHANNEL_B1              (Dio_ChannelType)17
#define DIO_CHANNEL_B2              (Dio_ChannelType)18
#define DIO_CHANNEL_B3              (Dio_ChannelType)19
#define DIO_CHANNEL_B4              (Dio_ChannelType)20
#define DIO_CHANNEL_B5              (Dio_ChannelType)21
#define DIO_CHANNEL_B6              (Dio_ChannelType)22
#define DIO_CHANNEL_B7              (Dio_ChannelType)23
#define DIO_CHANNEL_B8              (Dio_ChannelType)24
#define DIO_CHANNEL_B9              (Dio_ChannelType)25
#define DIO_CHANNEL_B10             (Dio_ChannelType)26
#define DIO_CHANNEL_B11             (Dio_ChannelType)27
#define DIO_CHANNEL_B12             (Dio_ChannelType)28
#define DIO_CHANNEL_B13             (Dio_ChannelType)29
#define DIO_CHANNEL_B14             (Dio_ChannelType)30
#define DIO_CHANNEL_B15             (Dio_ChannelType)31


#define DIO_CHANNEL_C13             (Dio_ChannelType)45
#define DIO_CHANNEL_C14             (Dio_ChannelType)46
#define DIO_CHANNEL_C15             (Dio_ChannelType)47


typedef uint8 Dio_PortType;
#define DIO_PORTA                   (Dio_PortType)0
#define DIO_PORTB                   (Dio_PortType)1
#define DIO_PORTC                   (Dio_PortType)2


typedef uint8 MaskValue_t;
typedef struct{
	MaskValue_t                     mask;
	uint8                           offset;
	Dio_PortType                    port;
}Dio_ChannelGroupType;


/*uses the STD_LOW and STD_HIGH macros from STD_Types*/
typedef uint8 Dio_LevelType;


/*
 * takes the size of the largest reg in the system
 */
typedef uint32 Dio_PortLevelType;

/************************************************************************/

/************************************************************************
 *                    DIO functions' prototypes                         *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Dio_ReadChannel                                                                                                        *
 *  Param    : IN     : Name / ChannelId                                                                                              *
 *                      Type / Dio_ChannelType                                                                                        *
 *                      Desc / take channel ID which is predefine macro                                                               *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Dio_LevelType                                                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the level of passed channel ID                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/**************************************************************************************************************************************
 *  Function : Dio_WriteChannel                                                                                                       *
 *  Param    : IN     : Name / ChannelId                                                                                              *
 *                      Type / Dio_ChannelType                                                                                        *
 *                      Desc / take channel ID which is predefine macro                                                               *
 *                                                                                                                                    *
 *                      Name / Level                                                                                                  *
 *                      Type / Dio_LevelType                                                                                          *
 *                      Desc / take wanted value to write at the given channel                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Dio_LevelType                                                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function writes the level to the given channel ID                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level);

/**************************************************************************************************************************************
 *  Function : Dio_ReadPort                                                                                                           *
 *  Param    : IN     : Name / PortId                                                                                                 *
 *                      Type / Dio_PortType                                                                                           *
 *                      Desc / take Port ID which is predefine macro                                                                  *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the level of given port ID                                                                        *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/**************************************************************************************************************************************
 *  Function : Dio_WritePort                                                                                                          *
 *  Param    : IN     : Name / PortId                                                                                                 *
 *                      Type / Dio_PortType                                                                                           *
 *                      Desc / take PORT ID which is predefine macro                                                                  *
 *                                                                                                                                    *
 *                      Name / Level                                                                                                  *
 *                      Type / Dio_PortLevelType                                                                                      *
 *                      Desc / take wanted value to write at the given port                                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function writes the level to the given PORT ID                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level);

/**************************************************************************************************************************************
 *  Function : Dio_ReadChannelGroup                                                                                                   *
 *  Param    : IN     : Name / ChannelGroupIdPtr                                                                                      *
 *                      Type / const Dio_ChannelGroupType*                                                                            *
 *                      Desc / take structure which is defined type                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes structue contains the port number, the mask which specifies the wanted pin wanted to read          *
 *             its value and the offset which determines the location of the first pin the mask                                       *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

/**************************************************************************************************************************************
 *  Function : Dio_WriteChannelGroup                                                                                                  *
 *  Param    : IN     : Name / ChannelGroupIdPtr                                                                                      *
 *                      Type / const Dio_ChannelGroupType*                                                                            *
 *                      Desc / take Port ID which is predefine macro                                                                  *
 *                                                                                                                                    *
 *                      Name / Level                                                                                                  *
 *                      Type / Dio_PortLevelType                                                                                      *
 *                      Desc / take wanted value to write at the given port without shift                                             *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc    : This function takes structue contains the value wanted to be written on the specific register                           *
 *            on certain pin with offset value and number of pins define by the mask value each high value equals to pin              *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level);


/**************************************************************************************************************************************
 *  Function : Dio_FlipChannel                                                                                                        *
 *  Param    : IN     : Name / ChannelId                                                                                              *
 *                      Type / Dio_ChannelType                                                                                        *
 *                      Desc / take channel ID which is predefine macro                                                               *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Dio_LevelType                                                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function takes structue contains the port number, the mask which specifies the wanted pin wanted to read          *
 *             its value and the offset which determines the location of the first pin the mask                                       *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);


/************************************************************************/

#endif /* DIO_INC_DIO_H_ */

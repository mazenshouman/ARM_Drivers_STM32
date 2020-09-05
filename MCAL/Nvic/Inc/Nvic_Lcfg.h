
#ifndef NVIC_INC_NVIC_LCFG_H_
#define NVIC_INC_NVIC_LCFG_H_

/************************************************************************
 *                      Configuration Structure                         *
 ***********************************************************************/
typedef struct{
	Nvic_PeripheralId_t            PeripheralId;
	Nvic_PriorityValue_t           PriorityGroupNumber;
	Nvic_PriorityValue_t           PrioritySubgroupNumber;
}Nvic_ConfigType;

/************************************************************************
 *                      Externed Structure instance                     *
 ***********************************************************************/

extern Nvic_ConfigType gastr_NvicConfigArr[];


/************************************************************************/


#endif /* NVIC_INC_NVIC_LCFG_H_ */

#ifndef __HEAT_CONTROL_SYS_H__
#define __HEAT_CONTROL_SYS_H__

#include "stm32f10x.h"

#define HCS_IO_INPUT   volatile uint8_t
#define HCS_IO_OUTPUT  volatile uint8_t
#define HCS_VA_INPUT   volatile uint32_t
#define HCS_VA_OUTPUT  volatile uint32_t
	
typedef enum
{
	HCS_STATUS_STANDBY = 0,
	HCS_STATUS_STARTUP,
	HCS_STATUS_PREBLOW,
	HCS_STATUS_PREMATERIAL,
	HCS_STATUS_WARMEDUP,
	HCS_STATUS_FIREUP,
	HCS_STATUS_RUNNING,
	HCS_STATUS_FIREPROTECT,
	HCS_STATUS_POWEROFF,
}HCS_STATUS_enum;

typedef enum
{
	HCS_PARAM_GFQC = 0,   //�ķ�ǰ��
	HCS_PARAM_YFQC,       //����ǰ��
	HCS_PARAM_YLSJ,       //Ԥ��ʱ��
	HCS_PARAM_YRSJ,       //Ԥ��ʱ��
	HCS_PARAM_DHSJ,       //���ʱ��
	HCS_PARAM_JLSJ,       //����ʱ��
	HCS_PARAM_TLSJ,       //ͣ��ʱ��
	HCS_PARAM_GFHC,       //�ķ��
	HCS_PARAM_YFHC,       //�����
	HCS_PARAM_BHSL,       //��������
	HCS_PARAM_BHTL,       //����ͣ��
	HCS_PARAM_KJWD,       //�����¶�
	HCS_PARAM_TJWD,       //ͣ���¶�
	HCS_PARAM_BHWD,       //�����¶�
	HCS_PARAM_KBWD,       //�����¶�
	HCS_PARAM_TBWD,       //ͣ���¶�
	HCS_PARAM_DSKJ,       //��ʱ����
	HCS_PARAM_DSGJ,       //��ʱ�ػ�
	
	HCS_PARAM_DHYZ,       //�����ֵ
	HCS_PARAM_DHJG,       //�����
	HCS_PARAM_YFZH,       //�����ͺ�
	HCS_PARAM_GFZH,       //�ķ��ͺ�
	HCS_PARAM_DHYF,       //�������
	HCS_PARAM_DHGF,       //���ķ�
	HCS_PARAM_SLZH,       //�����ͺ�
	HCS_PARAM_BJWD,       //�����¶�
	HCS_PARAM_FDWD,       //�����¶�
	HCS_PARAM_ZCYF,       //��������
	HCS_PARAM_ZCGF,       //�����ķ�
	HCS_PARAM_BHYF,       //��������
	HCS_PARAM_BHGF,       //����ķ�
	
	HCS_PARAM_MAX,
}HCS_PARAM_enum;

typedef struct// HCS_TypeDef
{
	HCS_IO_INPUT WaterLow;
	HCS_IO_INPUT MaterialLow;
	HCS_IO_INPUT WaterHot;
	HCS_VA_INPUT WaterTemp;
	HCS_VA_INPUT StoveTemp;
	
	HCS_IO_OUTPUT WaterPump;
	HCS_IO_OUTPUT MaterialMachine;
	HCS_IO_OUTPUT FireUp;
	HCS_IO_OUTPUT AirBlower;
	HCS_IO_OUTPUT LeadFan;
	
	HCS_STATUS_enum Status;
	
	uint16_t TempBeforeFire;
	
	uint16_t Params[HCS_PARAM_MAX];
}HCS_TypeDef;

extern volatile HCS_TypeDef HCS_Struct;

extern void HCS_Init(void);

extern uint8_t HCS_SM_Standby(uint8_t param);
extern uint8_t HCS_SM_Startup(uint8_t param);
extern uint8_t HCS_SM_PreBlowing(uint8_t param);
extern uint8_t HCS_SM_WarmedUp(uint8_t param);
extern uint8_t HCS_SM_PreMaterial(uint8_t param);
extern uint8_t HCS_SM_FireUp(uint8_t param);
extern uint8_t HCS_SM_Running(uint8_t param);
extern uint8_t HCS_SM_FireProtection(uint8_t param);
extern uint8_t HCS_SM_Suspend(uint8_t param);
extern uint8_t HCS_SM_PowerOff(uint8_t param);



#endif


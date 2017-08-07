#include "stm32f10x.h"
#include "Task_KeyBoard.h"
#include "myButton.h"
#include "myLed.h"
#include "myBeep.h"
#include "HeatControlSys.h"

#include "Frames.h"

static uint32_t Is_Init=0;


void KB_PowerSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_STANDBY:
			case HCS_STATUS_STARTUP:
			case HCS_STATUS_PREBLOW:
			case HCS_STATUS_PREMATERIAL:
			case HCS_STATUS_WARMEDUP:
			case HCS_STATUS_FIREUP:
			case HCS_STATUS_RUNNING:
			case HCS_STATUS_FIREPROTECT:
				HCS_Struct.Status = HCS_STATUS_POWEROFF;
				//TODO:������Ϣ���ڽ���ػ�
				break;
			case HCS_STATUS_POWEROFF:
				HCS_Struct.Status = HCS_STATUS_STANDBY;
				//TODO:������Ϣ���ڽ��뿪����ʼ��
				break;
		}
	}
}

void KB_SysSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_STANDBY:
				HCS_Struct.Status = HCS_STATUS_STARTUP;
				//TODO:������Ϣ��������
				break;
			case HCS_STATUS_STARTUP:
			case HCS_STATUS_PREBLOW:
			case HCS_STATUS_PREMATERIAL:
			case HCS_STATUS_WARMEDUP:
			case HCS_STATUS_FIREUP:
			case HCS_STATUS_RUNNING:
			case HCS_STATUS_FIREPROTECT:
				//HCS_Struct.Status = HCS_STATUS_POWEROFF;
				//TODO:������Ϣ
				break;
			case HCS_STATUS_POWEROFF:
				//HCS_Struct.Status = HCS_STATUS_STANDBY;
				//TODO:������Ϣ
				break;
		}
	}
}

void KB_TestSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
	{
		MyBeep_Beep(1);
	}
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		MyBeep_Beep(0);
	}
}

void KB_SetSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		//���ý����л�
		if(BtnState == BUTTON_STATUS_RELEASE)
		{
			UI_Mode = !UI_Mode;
		}
	}
}

void KB_UpKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_DownKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_LeftKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_RightKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KeyBoard_Regs(void)
{
	MyButton_RegType btn;
	
	btn.ButtonIdleState = SET;
	
	btn.CallBackFunc = KB_PowerSwitch;
	btn.ButtonGPIO = GPIOB;
	btn.ButtonPin = GPIO_Pin_11;
	MyButton_Reg(0, &btn);
	
	btn.CallBackFunc = KB_SysSwitch;
	btn.ButtonGPIO = GPIOB;
	btn.ButtonPin = GPIO_Pin_10;
	MyButton_Reg(1, &btn);
	
	btn.CallBackFunc = KB_SetSwitch;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_5;
	MyButton_Reg(2, &btn);
	
	btn.CallBackFunc = KB_UpKey;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_4;
	MyButton_Reg(3, &btn);
	
	btn.CallBackFunc = KB_DownKey;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_3;
	MyButton_Reg(4, &btn);
	
	btn.CallBackFunc = KB_LeftKey;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_2;
	MyButton_Reg(5, &btn);
	
	btn.CallBackFunc = KB_RightKey;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_1;
	MyButton_Reg(6, &btn);
	
	btn.CallBackFunc = KB_TestSwitch;
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_0;
	MyButton_Reg(7, &btn);
}

void vTask_KeyBoard( void *pvParameters )
{
	MyButton_Init();
	KeyBoard_Regs();
	
	MyBeep_Init();
	
	Is_Init = KEYBOARD_INIT_DONE;
	xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	
	while(1)
	{
		MyButton_Process();
		vTaskDelay(50);
	}
}

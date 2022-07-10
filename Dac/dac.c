#include "dac.h"

/**
  * @brief  
  * @param  
  * @return 
  */
void Dac1_Init(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitType.DAC_Trigger=DAC_Trigger_None;
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	
	DAC_Init(DAC_Channel_1,&DAC_InitType);	
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); 
}

/**
  * @brief  
  * @param  
  * @return 
  */
void DacSetVol(uint8_t chan, float vol)
{
	if(chan == 1)
	{
		DAC_SetChannel1Data(DAC_Align_12b_R, vol * 4096.0 / 3.3);
	}
}





















































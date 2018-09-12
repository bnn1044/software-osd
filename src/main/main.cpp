#include "target.h"

/* Private variables ---------------------------------------------------------*/
LL_GPIO_InitTypeDef     GPIO_InitStructureE;
LL_GPIO_InitTypeDef			GPIO_InitStructureA;

LL_COMP_InitTypeDef			SyncComp;

static __IO uint32_t i;
static __IO uint32_t TimingDelay;
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);


int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f30x.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f30x.c file
	*/
	/* Setup SysTick Timer for 1 �sec interrupts  */
	SysTick_Config(SystemCoreClock / 1000);

	/* GPIOE Periph clock enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
	// RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	/* Configure PE14 and PE15 in output pushpull mode */

	GPIO_InitStructureE.Pin = LL_GPIO_PIN_15 | LL_GPIO_PIN_14 | LL_GPIO_PIN_13 | LL_GPIO_PIN_12 | LL_GPIO_PIN_11 | LL_GPIO_PIN_10 | LL_GPIO_PIN_9 | LL_GPIO_PIN_8;
	GPIO_InitStructureE.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStructureE.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStructureE.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructureE.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

	GPIO_InitStructureA.Pin = LL_GPIO_PIN_1;
	GPIO_InitStructureA.Mode = LL_GPIO_MODE_ANALOG;;
	GPIO_InitStructureA.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;


	SyncComp.PowerMode = LL_COMP_POWERMODE_HIGHSPEED;
	SyncComp.InputPlus = LL_COMP_INPUT_PLUS_IO1;
	SyncComp.InputMinus = LL_COMP_INPUT_MINUS_DAC1_CH1;
	SyncComp.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
	SyncComp.OutputSelection = LL_COMP_OUTPUT_NONE;
	SyncComp.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
	SyncComp.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;

	LL_GPIO_Init(GPIOE, &GPIO_InitStructureE);
	LL_GPIO_Init(GPIOA, &GPIO_InitStructureA);
	LL_COMP_Init(COMP1, &SyncComp);

	/* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory.
	You can monitor PE14 and PE15 on the scope to measure the output signal.
	If you need to fine tune this frequency, you can add more GPIO set/reset
	cycles to minimize more the infinite loop timing.
	This code needs to be compiled with high speed optimization option.  */

	while (1)
	{
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_15);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_14);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_13);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_12);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_11);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_10);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_9);
		Delay(50);
		LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_8);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_15);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_14);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_13);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_12);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_11);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_10);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_9);
		Delay(50);
		LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_8);
		Delay(50);
	}
}
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}
/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

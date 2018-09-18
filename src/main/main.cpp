#include "target.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_comp.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_spi.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_dac.h"
#include "stm32f3xx_ll_tim.h"

#define NTSCHSize   720
#define NTSCVSize   486
#define PALHSize    720
#define PALVSize    576

/* Private variables ---------------------------------------------------------*/
LL_GPIO_InitTypeDef     GPIO_InitStructureE;
LL_GPIO_InitTypeDef     GPIO_InitStructureA;
LL_COMP_InitTypeDef     SyncComp;
LL_EXTI_InitTypeDef     ComExti;
/* Counter Prescaler value */
uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/

void Delay(uint32_t nTime);
static void GPIO_Config(void);
static void Comp_Config(void);
static void Comp_Exti_config(void);
int main()
{
    /* Setup SysTick Timer for 1 ms interrupts  */
    SysTick_Config(SystemCoreClock / 1000);
	GPIO_Config();
	Comp_Config();
    Comp_Exti_config();
    while (1)
    {
       // LL_mDelay(100);
    }
}
void Delay(const uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0) {}
}
static void GPIO_Config(void){
   /* GPIOE Periph clock enable */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    // RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    /* Configure  output pushpull mode */
    GPIO_InitStructureE.Pin = LL_GPIO_PIN_15 | LL_GPIO_PIN_14 | LL_GPIO_PIN_13 | LL_GPIO_PIN_12 | LL_GPIO_PIN_11 | LL_GPIO_PIN_10 | LL_GPIO_PIN_9 | LL_GPIO_PIN_8;
    GPIO_InitStructureE.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStructureE.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStructureE.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureE.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOE, &GPIO_InitStructureE);
    /*Configure PA1 as input for the comparators*/
    GPIO_InitStructureA.Pin = LL_GPIO_PIN_1;
    GPIO_InitStructureA.Mode = LL_GPIO_MODE_ANALOG;    //The I/Os used as comparators inputs must be configured in analog mode in the GPIOs registers
    GPIO_InitStructureA.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    LL_GPIO_Init(GPIOA, &GPIO_InitStructureA);
}
static void Comp_Config(void){
	SyncComp.PowerMode = LL_COMP_POWERMODE_HIGHSPEED;
    SyncComp.InputPlus = LL_COMP_INPUT_PLUS_IO1;							//PA1 as none inverting input
    SyncComp.InputMinus = LL_COMP_INPUT_MINUS_1_4VREFINT;
    SyncComp.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
    SyncComp.OutputSelection = LL_COMP_OUTPUT_NONE;
    SyncComp.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
    SyncComp.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
    LL_COMP_Init(COMP1, &SyncComp);
    LL_COMP_Enable(COMP1);
}
static void Comp_Exti_config(void){
    ComExti.Line_0_31   = LL_EXTI_LINE_22;  /* connect to the comp1 output*/
    ComExti.Mode        = LL_EXTI_MODE_IT;
    ComExti.Trigger     = LL_EXTI_TRIGGER_RISING_FALLING;
    LL_EXTI_Init(&ComExti);
}

extern "C" void SysTick_Handler()
{
    if (TimingDelay != 0x00) {
        --TimingDelay;
    }
}
extern "C" void COMP1_2_3_IRQHandler(void)
{

}
/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  * ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "pir.h"
#include "stm8s_adc1.h"
#include "const.h"
#include "system_def.h"
#include "transport.h"
#include "gpio_util.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define F_CUT                   (IR_RECEIVER_SIGNAL_FREQ)
#define SAMPLE_RATE             1000    //1000 sample per second
#define F_CUT_HIGH_PASS         100
/* Private variables ---------------------------------------------------------*/
double RC;// = 1.0f/(F_CUT*2*3.1415);
double dt;// = 1.0/(SAMPLE_RATE);
double alpha;// = dt/(RC + dt);

double RC_h;// = 1.0/(SAMPLE_RATE);
double alpha_h;// = dt/(RC + dt);
/* Private function prototypes -----------------------------------------------*/
void process_ir_signal(void);
int16_t lowpass_filter(uint16_t v);
int16_t highpass_filter(uint16_t v);
/* Private functions ---------------------------------------------------------*/
void process_ir_signal(void)
{
    uint16_t v = ADC1_GetConversionValue()&0x03ff;
    //Low pass filter
    //v = highpass_filter(v);
    //v = lowpass_filter(v);
    //Trasmit value to the ...
    uint8_t data = 0xaa;
    Transport_TxPush(data);
    data = 0x55;
    Transport_TxPush(data);
    
    
    data = (v>>8)&0xff;
    Transport_TxPush(data);
    
    data = (v)&0xff;
    Transport_TxPush(data);
    
    if( v > 1000) {
      GPIO_Util_WriteLow(LED_PORT,LED_PIN);
    } else {
      GPIO_Util_WriteHigh(LED_PORT,LED_PIN);
    }
}

int16_t lowpass_filter(uint16_t v)
{
  static uint16_t filtered_value = 0;
  filtered_value = (uint16_t)(alpha*v + (1-alpha)*filtered_value);
  return filtered_value;
}

int16_t highpass_filter(uint16_t v)
{
  static int16_t previous_x=0, previous_y=0;
  previous_y = (int16_t)((previous_y + v - previous_x)*alpha);
  previous_x = v;
  return previous_y;
}
/* Public functions ----------------------------------------------------------*/
void PIR_Receiver_Init(void)
{
  //Init ADC
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
            IR_RECEIVER_ADC_CHANNEL,
            ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
            DISABLE,
            ADC1_ALIGN_LEFT,
            ADC1_SCHMITTTRIG_CHANNEL4,
            DISABLE);
  ADC1_StartConversion();
  uint16_t v = ADC1_GetConversionValue();
  
  //Init lowpass filter
  RC = 1.0f/(F_CUT*2*3.1415);
  dt = 1.0/(SAMPLE_RATE);
  alpha = dt/(RC + dt);
  
  RC_h = 1.0f/(F_CUT_HIGH_PASS*2*3.1415);
  alpha = dt/(RC_h + dt);
}

void PIR_Task(void *args)
{
  //Do the task here
  process_ir_signal();
}

/**
  * @}
  */



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
#include "ir_receiver.h"
#include "stm8s_adc1.h"
#include "const.h"
#include "system_def.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
//    typedef struct {
//      double everage_value;
//      uint16_t size;//Number of adc sample which is used to calcuate everage
//    } IR_Signal_Value_TypeDef;
typedef struct {
  IR_Signal_State_TypeDef state;
  uint32_t pulse_counter;//The time this state is exist
} IR_Signal_Value_TypeDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MAX_STABLE_PULSE         1000

//Macro for low pass filter
#define F_CUT                   (IR_RECEIVER_SIGNAL_FREQ)
#define SAMPLE_RATE             1000    //1000 sample per second

//For timeout service
//#define MAX_TIME_OUT_MS         300
//#define UPDATE_TIME_OUT(x)      (x++)
//#define RESET_TIME_OUT(x)       (x=0)
//#define IS_TIME_OUT(x)          (x==MAX_TIME_OUT_MS)
#define UPDATE_TIME(x)          (++x)

#define TIME_OUT_IN_MS          1000

/* Private variables ---------------------------------------------------------*/
//IR_Signal_Value_TypeDef ir_signal_value = {0.0f,0};
IR_Signal_Value_TypeDef signal_state = {IR_NOT_HIDDEN,0};

uint32_t detected_time_stamp = 0;
uint32_t timer_counter = 0;
// For LC Filter
double RC;// = 1.0f/(F_CUT*2*3.1415);
double dt;// = 1.0/(SAMPLE_RATE);
double alpha;// = dt/(RC + dt);


/* Private function prototypes -----------------------------------------------*/
void process_ir_signal(void);
//void calculate_everage(uint16_t v);
void make_decision(void);
uint16_t lowpass_filter(uint16_t v);
uint8_t detecting_pulse(uint16_t v); //YES - Has Pulse. No - No Pulse
/* Private functions ---------------------------------------------------------*/
void process_ir_signal(void)
{
  static uint16_t stable_marker = 0;
  if( stable_marker >= MAX_STABLE_PULSE )
  {
    uint16_t v = ADC1_GetConversionValue();
    //Low pass filter
    v = lowpass_filter(v);
    uint8_t has_pulse = detecting_pulse(v);
    
    if(has_pulse == YES) {
      if(timer_counter > detected_time_stamp){
        if(timer_counter > (detected_time_stamp + TIME_OUT_IN_MS)) {
          // Khong nhan duoc xung sau 1 khoang thoi gian TIME_OUT_IN_MS
          //Reset the counter
          signal_state.pulse_counter = 0;
        } else {
          // Nhan duoc xung nhip voi tan so xac dinh
          signal_state.pulse_counter += 1;
        }
      } else {
        //The timer counter overflow
        detected_time_stamp = timer_counter;
      }
    }   
    // making decision
    make_decision();
  } else {
    stable_marker++;
    detected_time_stamp = timer_counter;
  }
}
void calculate_everage(uint16_t v)
{
  (void)v;
//  if( ir_signal_value.size == 0) {
//    ir_signal_value.everage_value = v;
//    ir_signal_value.size = 1;
//  } else {
//    double size_inverse = 0;
//    if( ir_signal_value.size == U16_MAX) {
//      size_inverse = (1.0f/U16_MAX);
//    } else {
//      size_inverse = (1.0f/ir_signal_value.size);
//      ir_signal_value.size += 1;
//    }
//    ir_signal_value.everage_value=(ir_signal_value.everage_value+v*size_inverse)\
//                                  /(1+size_inverse);
//  }
}
void make_decision(void)
{
  
}

uint16_t lowpass_filter(uint16_t v)
{
  static uint16_t filtered_value = 0;
  filtered_value = (uint16_t)(alpha*v + (1-alpha)*filtered_value);
  return filtered_value;
}

uint8_t detecting_pulse(uint16_t v)
{
  static uint8_t  increase_counter =0;
  static uint8_t decrease_counter = 0;
  static uint16_t previous_v = 0;
  const uint8_t INCREASE =0, DECREASE =1;
  static uint8_t direction = 0;
  uint8_t is_has_pulse = NO;
  if( previous_v > v ) {
    increase_counter += 1;
    if( (direction == DECREASE) && (increase_counter >= 2)) {
      direction = INCREASE;
      is_has_pulse = YES;
      //Reset paramter
      decrease_counter = 0 ;
    }
  } else {
    decrease_counter +=1;
    if( (direction == INCREASE) && (decrease_counter >= 2)) {
      direction = DECREASE;
      is_has_pulse = YES;
      //Reset paramter
      increase_counter = 0 ;
    }
  }
  
  previous_v = v;
  
  return is_has_pulse;
}

/* Public functions ----------------------------------------------------------*/
void IR_Receiver_Init(void)
{
  //Init ADC
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
            ADC1_CHANNEL_2,
            ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
            DISABLE,
            ADC1_ALIGN_LEFT,
            ADC1_SCHMITTTRIG_CHANNEL2,
            DISABLE);
  ADC1_StartConversion();
  uint16_t v = ADC1_GetConversionValue();
  
  //Init lowpass filter
  RC = 1.0f/(F_CUT*2*3.1415);
  dt = 1.0/(SAMPLE_RATE);
  alpha = dt/(RC + dt);
}

void IR_Receiver_Task(void *args)
{
  /*This function will be call peridically with 1ms */
  /** This function will read adc value, calculate the everage values. 
    * Make the decision base on Received Signal 
    */
  UPDATE_TIME(timer_counter);
  process_ir_signal();
}

void IR_Receiver_GetState(void)
{
  
}

/**
  * @}
  */



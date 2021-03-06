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
#define F_CUT_HIGH_PASS         100

//For timeout service
//#define MAX_TIME_OUT_MS         300
//#define UPDATE_TIME_OUT(x)      (x++)
//#define RESET_TIME_OUT(x)       (x=0)
//#define IS_TIME_OUT(x)          (x==MAX_TIME_OUT_MS)
#define UPDATE_TIME(x)          (++x)

/* Private variables ---------------------------------------------------------*/
//IR_Signal_Value_TypeDef ir_signal_value = {0.0f,0};
IR_Signal_Value_TypeDef signal_state = {IR_HIDDEN,0};

uint32_t detected_time_stamp = 0;
uint32_t timer_counter = 0;
// For LC Filter
double RC;// = 1.0f/(F_CUT*2*3.1415);
double dt;// = 1.0/(SAMPLE_RATE);
double alpha;// = dt/(RC + dt);

double RC_h;// = 1.0/(SAMPLE_RATE);
double alpha_h;// = dt/(RC + dt);


/* Private function prototypes -----------------------------------------------*/
void process_ir_signal(void);
//void calculate_everage(uint16_t v);
void make_decision(void);
int16_t lowpass_filter(uint16_t v);
int16_t highpass_filter(uint16_t v);
uint8_t detecting_pulse(int16_t v); //YES - Has Pulse. No - No Pulse
/* Private functions ---------------------------------------------------------*/
void process_ir_signal(void)
{
  static uint16_t stable_marker = 0;
  if( stable_marker >= MAX_STABLE_PULSE )
  {
    uint16_t v = ADC1_GetConversionValue();
    //Low pass filter
    v = highpass_filter(v);
    v = lowpass_filter(v);
    uint8_t has_pulse = detecting_pulse(v);
    
    if(has_pulse == YES) {
      if(timer_counter > detected_time_stamp){
        if(timer_counter > (detected_time_stamp + TWO_PULSE_TIME_OUT_IN_MS)) {
          // Khong nhan duoc xung sau 1 khoang thoi gian TIME_OUT_IN_MS
          //Reset the counter
          signal_state.pulse_counter = 0;
        } else {
           //Nhan duoc xung nhip voi tan so xac dinh
          signal_state.pulse_counter += 1;
        }
      }
      detected_time_stamp = timer_counter;
    } else {
      if( timer_counter > (detected_time_stamp + TWO_PULSE_TIME_OUT_IN_MS) ){
        signal_state.pulse_counter = 0;
      }
    }   
    // making decision
    make_decision();
  } else {
    stable_marker++;
    detected_time_stamp = timer_counter;
  }
}

void make_decision(void)
{
  if( signal_state.pulse_counter < IR_RECEIVER_SHORT_PULSE_THRESHOLD_COUNTER){
    signal_state.state = IR_HIDDEN;
  }else  if( (signal_state.pulse_counter > IR_RECEIVER_SHORT_PULSE_THRESHOLD_COUNTER)\
    &&(signal_state.pulse_counter < IR_RECEIVER_SHORT_PULSE_PULSE_COUNTER)) 
  {
    signal_state.state = IR_SHORT_PULSE;
  } else {
    signal_state.state = IR_LONG_PULSE;
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

uint8_t detecting_pulse(int16_t v)
{
//  static uint8_t  increase_counter =0;
//  static uint8_t decrease_counter = 0;
  static uint16_t previous_v = 0;
  const uint8_t INCREASE =0, DECREASE =1;
  static uint8_t direction = 0;
  uint8_t is_has_pulse = NO;
  if( previous_v > (v+20) ) {
//    increase_counter += 1;
    if( (direction == INCREASE) ) {//&& (increase_counter >= 2)
      direction = DECREASE;
      is_has_pulse = YES;
      //Reset paramter
//      decrease_counter = 0 ;
    }
  } else if((previous_v +20) < v){
//    decrease_counter +=1;
    if((direction == DECREASE)) { // && (decrease_counter >= 2)
      direction = INCREASE;
      is_has_pulse = YES;
      //Reset paramter
//      increase_counter = 0 ;
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
            IR_RECEIVER_ADC_CHANNEL,
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
  
  RC_h = 1.0f/(F_CUT_HIGH_PASS*2*3.1415);
  alpha = dt/(RC_h + dt);
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

IR_Signal_State_TypeDef IR_Receiver_GetState(void)
{
  return signal_state.state; 
}

/**
  * @}
  */



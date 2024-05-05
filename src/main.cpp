#include <Arduino.h>
#include <DabbleESP32.h>
#include "driver/pcnt.h"

//hw_timer_t* timer = NULL;

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define motorAp 25
#define motorBp 13
#define pwmch_1 0
#define pwmch_2 1

/* #define PULSE_INPUT_PIN1 21
#define PULSE_CTRL_PIN1 4

#define PULSE_INPUT_PIN2 34
#define PULSE_CTRL_PIN2 23 */

/* int16_t count1 = 0; 
int16_t count2 = 0; 
int16_t difference = count1 + count2;

int16_t n = 0;//tuika */

const int motorA1 = 27;  
const int motorA2 = 26;  

const int STBY = 12; 

const int motorB1 = 32;  // IN1
const int motorB2 = 33;  // IN2



//A RIGHT B LEFT
//IN 1 LEFT IN 2 RIGHT

/*void IRAM_ATTR get_count(){
 //Dabble.processInput(); 
 pcnt_get_counter_value(PCNT_UNIT_0, &count1);
 pcnt_get_counter_value(PCNT_UNIT_1, &count2);
 //difference = count1 + count2;
 ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));
 
}*/
void setup() {
  // put your setup code here, to run once:
pinMode( motorA1, OUTPUT );
pinMode( motorA2, OUTPUT );
pinMode( motorAp, OUTPUT );
  
pinMode( STBY, OUTPUT );

pinMode( motorB1, OUTPUT );
pinMode( motorB2, OUTPUT );
pinMode( motorBp, OUTPUT );
   
ledcSetup (pwmch_1, 12800 , 8 );
ledcSetup (pwmch_2, 12800 , 8 );


ledcAttachPin ( motorAp, pwmch_1) ;
ledcAttachPin ( motorBp, pwmch_2) ;


digitalWrite( motorA1, LOW );
digitalWrite( motorA2, LOW );
//ledcWrite( pwmch_1 , 0 );

digitalWrite( motorB1, LOW );
digitalWrite( motorB2, LOW );
//ledcWrite( pwmch_2 , 0 );
  
digitalWrite( STBY, HIGH );

/* pcnt_config_t pcnt_config_A;//??????????(A?)   
        pcnt_config_A.pulse_gpio_num = PULSE_INPUT_PIN1;
        pcnt_config_A.ctrl_gpio_num = PULSE_CTRL_PIN1;
        pcnt_config_A.lctrl_mode = PCNT_MODE_REVERSE;
        pcnt_config_A.hctrl_mode = PCNT_MODE_KEEP;
        pcnt_config_A.channel = PCNT_CHANNEL_0;
        pcnt_config_A.unit = PCNT_UNIT_0;
        pcnt_config_A.pos_mode = PCNT_COUNT_INC;
        pcnt_config_A.neg_mode = PCNT_COUNT_DEC;
        
        

pcnt_config_t pcnt_config_B;//??????????(B?)   
        pcnt_config_B.pulse_gpio_num = PULSE_CTRL_PIN1;//?A???config????????????
        pcnt_config_B.ctrl_gpio_num = PULSE_INPUT_PIN1;//?A???config????????????
        pcnt_config_B.lctrl_mode = PCNT_MODE_KEEP;//?A???config????????????
        pcnt_config_B.hctrl_mode = PCNT_MODE_REVERSE;//?A???config????????????
        pcnt_config_B.channel = PCNT_CHANNEL_1;//??????1???
        pcnt_config_B.unit = PCNT_UNIT_0;//UNIT?A???????
        pcnt_config_B.pos_mode = PCNT_COUNT_INC;
        pcnt_config_B.neg_mode = PCNT_COUNT_DEC;
        

pcnt_unit_config(&pcnt_config_A);//???????A?
pcnt_unit_config(&pcnt_config_B);//???????B?
pcnt_counter_pause(PCNT_UNIT_0);//????????
pcnt_counter_clear(PCNT_UNIT_0);//???????
  
pcnt_counter_resume(PCNT_UNIT_0);//??????
  
pcnt_config_t pcnt_config_C;//??????????(C?)   
        pcnt_config_C.pulse_gpio_num = PULSE_INPUT_PIN2;
        pcnt_config_C.ctrl_gpio_num = PULSE_CTRL_PIN2;
        pcnt_config_C.lctrl_mode = PCNT_MODE_REVERSE;
        pcnt_config_C.hctrl_mode = PCNT_MODE_KEEP;
        pcnt_config_C.channel = PCNT_CHANNEL_0;
        pcnt_config_C.unit = PCNT_UNIT_1;
        pcnt_config_C.pos_mode = PCNT_COUNT_INC;
        pcnt_config_C.neg_mode = PCNT_COUNT_DEC;
        

pcnt_config_t pcnt_config_D;//??????????(D?)   
        pcnt_config_D.pulse_gpio_num = PULSE_CTRL_PIN2;//?C???config????????????
        pcnt_config_D.ctrl_gpio_num = PULSE_INPUT_PIN2;//?C???config????????????
        pcnt_config_D.lctrl_mode = PCNT_MODE_KEEP;//?C???config????????????
        pcnt_config_D.hctrl_mode = PCNT_MODE_REVERSE;//?C???config????????????
        pcnt_config_D.channel = PCNT_CHANNEL_1;//??????1???
        pcnt_config_D.unit = PCNT_UNIT_1;//UNIT?C???????
        pcnt_config_D.pos_mode = PCNT_COUNT_INC;
        pcnt_config_D.neg_mode = PCNT_COUNT_DEC;
        

pcnt_unit_config(&pcnt_config_C);//???????C?
pcnt_unit_config(&pcnt_config_D);//???????D?
pcnt_counter_pause(PCNT_UNIT_1);//????????
pcnt_counter_clear(PCNT_UNIT_1);//???????
  
pcnt_counter_resume(PCNT_UNIT_1);//??????   pcnt_config_C.ctrl_gpio_num = PULSE_CTRL_PIN1; */
  /* 
timer = timerBegin(0, 8000, true);
timerAttachInterrupt(timer, &get_count, true);
timerAlarmWrite(timer, 10000, true);
timerAlarmDisable(timer);1*/

Dabble.begin("Bluth");
Serial.begin(9600);
Serial.println( "Motor Standby" );

}



void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  
  if (GamePad.isUpPressed())
  { 
    /* pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_1);
    pcnt_get_counter_value(PCNT_UNIT_0, &count1);
    pcnt_get_counter_value(PCNT_UNIT_1, &count2);
    //difference = count1 + count2;
    //Serial.println("motorA forward"); */
    ledcWrite( pwmch_1 , 200);
    digitalWrite( motorA1, HIGH );
    digitalWrite( motorA2, LOW );
    //Serial.println("motorB forward");
    //ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));
    ledcWrite( pwmch_2 , 200);
    digitalWrite( motorB1, HIGH );
    digitalWrite( motorB2, LOW );
    // timerAlarmEnable(timer);
    // n = 1;
  }

  if (n == 1){
    pcnt_get_counter_value(PCNT_UNIT_0, &count1);
    pcnt_get_counter_value(PCNT_UNIT_1, &count2);
    difference = count1 + count2;
    ledcWrite( pwmch_2 , 210+(45*difference/10)/((1+(difference/10)^2)^(1/2)));
    delay(100);
  }
  if (GamePad.isDownPressed())
  {
    //timerAlarmDisable(timer);2
    n = 0;
    //Serial.println("motorA back");
    ledcWrite( pwmch_1 , 200 );
    digitalWrite( motorA1, LOW );
    digitalWrite( motorA2, HIGH );
    //Serial.println("motorB back");
    ledcWrite( pwmch_2 , 200 );
    digitalWrite( motorB1, LOW );
    digitalWrite( motorB2, HIGH );
  }
  if (GamePad.isCrossPressed())
  { 
    n = 0;
    //timerAlarmDisable(timer);3
    //Serial.println("motorA stop");
    digitalWrite( motorA1, LOW );
    digitalWrite( motorA2, LOW );
    ledcWrite( pwmch_1 , 0 );
    //Serial.println("motorB stop");
    digitalWrite( motorB1, LOW );
    digitalWrite( motorB2, LOW );
    ledcWrite( pwmch_2 , 0 );
    
    
  }
  if (GamePad.isCirclePressed())
  {
    //timerAlarmDisable(timer);4
    n = 0;
    //Serial.println("motorA back");
    ledcWrite( pwmch_1 , 200 );
    digitalWrite( motorA1, LOW );
    digitalWrite( motorA2, HIGH );
    //Serial.println("motorB forward");
    ledcWrite( pwmch_2 , 200 );
    digitalWrite( motorB1, HIGH );
    digitalWrite( motorB2, LOW );
  }

  if (GamePad.isSquarePressed())
  {
    //timerAlarmDisable(timer);5
    n = 0;
    //Serial.println("motorA forward");
    ledcWrite( pwmch_1 , 200 );
    digitalWrite( motorA1, HIGH );
    digitalWrite( motorA2, LOW );
    //rial.println("motorB back");
    ledcWrite( pwmch_2 , 200 );
    digitalWrite( motorB1, LOW );
    digitalWrite( motorB2, HIGH );
  }
  if (GamePad.isRightPressed())
  {
    //timerAlarmDisable(timer);6
    n = 0;
    //Serial.println("motorA slow");
    ledcWrite( pwmch_1 , 200 );
    digitalWrite( motorA1, HIGH );
    digitalWrite( motorA2, LOW );
    //Serial.println("motorB forward");
    ledcWrite( pwmch_2 , 256 );
    digitalWrite( motorB1, HIGH );
    digitalWrite( motorB2, LOW );
  }
  if (GamePad.isLeftPressed())
  { 
    //timerAlarmDisable(timer);7
    n = 0;
    //Serial.println("motorA forward");
    ledcWrite( pwmch_1 , 256 );
    digitalWrite( motorA1, HIGH );
    digitalWrite( motorA2, LOW );
    //Serial.println("motorB slow");
    ledcWrite( pwmch_2 , 200 );
    digitalWrite( motorB1, HIGH );
    digitalWrite( motorB2, LOW );
  }
  if (GamePad.isStartPressed())
  {
    pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_1);
  }
}
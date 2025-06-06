/*!
 * @file  i2c.ino
 * @brief Control the voice recognition module via I2C
 * @n  Get the recognized command ID and play the corresponding reply audio according to the ID;
 * @n  Get and set the wake-up state duration
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-04-02
 * @url  https://github.com/DFRobot/DFRobot_DF2301Q
 */
#include "DFRobot_DF2301Q.h"

#define Led1 D8
#define Led2 D9
#define Led3 D10
#define Led4 D11

//I2C communication
DFRobot_DF2301Q_I2C asr;

void setup() {
  Serial.begin(115200);

  pinMode(Led1, OUTPUT);    //Init LED pin to output mode
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  digitalWrite(Led1, LOW);  //Set LED pin to low 
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);

  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(800);
  }
  Serial.println("Begin ok!");

  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(10);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(10);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);

  // asr.playByCMDID(1);   // Wake-up command

  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID
}

void loop() {
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  switch (CMDID) {
    case 5:                                                  
      digitalWrite(Led1, HIGH);   //LOW SPEED
      digitalWrite(Led2, LOW); 
      digitalWrite(Led3, LOW);                            
      Serial.println("");  
      break;
    case 77:                                                  
      digitalWrite(Led1, HIGH);   //TURN FAN SPEED TO GEAR ONE
      digitalWrite(Led2, LOW); 
      digitalWrite(Led3, LOW);                            
      Serial.println("");  
      break;

    case 6:   
      digitalWrite(Led1, LOW);  
      digitalWrite(Led3, LOW);                                              
      digitalWrite(Led2, HIGH);   //MEDIUM SPEED                          
      Serial.println("");  
      break;

    case 78:                                                  
      digitalWrite(Led2, HIGH);   //TURN FAN SPEED TO GEAR ONE
      digitalWrite(Led1, LOW); 
      digitalWrite(Led3, LOW);                            
      Serial.println("");  
      break;

    case 7:                                                  
      digitalWrite(Led1, LOW);  
      digitalWrite(Led2, LOW);                                              
      digitalWrite(Led3, HIGH);       //HIGH SPEED
      Serial.println("");  
      break;
    case 79:                                                  
      digitalWrite(Led3, HIGH);   //TURN FAN SPEED TO GEAR THREE
      digitalWrite(Led1, LOW); 
      digitalWrite(Led2, LOW);                            
      Serial.println("");  
      break;
    case 76:                                                  
      digitalWrite(Led2, HIGH);   //TURN OFF THE FAN
      digitalWrite(Led1, LOW); 
      digitalWrite(Led3, LOW);                            
      Serial.println("");  
      break;
    case 103:                                                  
      digitalWrite(Led4, HIGH);   //TURN ON THE LIGHTS
      break;
    case 104:                                                  
      digitalWrite(Led4, LOW);   //TURN ON THE LIGHTS
      break;
    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}
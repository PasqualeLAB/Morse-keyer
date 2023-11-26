#include <cww_MorseTx.h>

#define KEY_PIN    2
#define SND_PIN    6
#define DIT_PIN    3
#define DAH_PIN    4
#define PIN_LED    7


#define SND_FREQ   800
#define CW_SPEED   15


cww_MorseTx morse(PIN_LED, CW_SPEED, SND_PIN, SND_FREQ,false);
char data[10];
int i = 0;
unsigned int StartTimeDot = 0,StartTimeDash = 0,StartKeyTime = 0;
unsigned long time = 0,key_time = 0;


void setup() 
{
  pinMode(KEY_PIN, INPUT_PULLUP);
  pinMode(DIT_PIN, INPUT_PULLUP);
  pinMode(DAH_PIN, INPUT_PULLUP);
  pinMode(SND_PIN, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println(morse.DecodeTimeout);
  Serial.println(morse.GetDotLen());
  Serial.println(morse.GetDashLen());
  //while(1);

  
  

}


void loop() 
{
  
    
    
    if(digitalRead(DIT_PIN) == 0)
    {
      
      if((StartTimeDot == 0) && (StartTimeDash == 0))
      {
        time = millis();
        StartTimeDot = 1;
      }
      morse.dot();
      if(i < 10)
      {
        data[i] = '.';
        
        i++;
      }
      else
        i = 0;
      
    }
      
    else if(digitalRead(DAH_PIN) == 0) 
    {
      
      if((StartTimeDot == 0) && (StartTimeDash == 0))
      {
        time = millis();
        StartTimeDash = 1;
      }
      morse.dash();
      if(i < 10)
      {
        data[i] = '_';
        
        i++;
      }
      else
        i = 0;
      
    }
      
    else if(digitalRead(KEY_PIN) == 0)
    {
      tone(SND_PIN,SND_FREQ);
      digitalWrite(PIN_LED, HIGH);
      
        
    }
    
      
    else
    {
      noTone(SND_PIN);  
      digitalWrite(PIN_LED, LOW);
      if((StartTimeDot != 0) || (StartTimeDash != 0))
      {
        if((millis() - time) >= morse.DecodeTimeout)
        {
          if(i < 10)
          {
            data[i] = ',';
            //Serial.print(data);
            Serial.print(decode(data));
            memset(data,0x00,sizeof(data));
            i=0;
          }
          else if(i == 9)
            i = 0;
           
        StartTimeDot = 0;
        StartTimeDash = 0;
         }
        
      }
      
      
    }
    
      

}


char decode(char* buffer)
{
  char letter = 0;
  
  if(!strcmp("._,",buffer))
    letter = 'a';
  else if(!strcmp("_...,",buffer))
    letter = 'b';  
  else if(!strcmp("_._.,",buffer))
    letter = 'c';  
  else if(!strcmp("_..,",buffer))
    letter = 'd';  
  else if(!strcmp(".,",buffer))
    letter = 'e';  
  else if(!strcmp(".._.,",buffer))
    letter = 'f';  
  else if(!strcmp("__.,",buffer))
    letter = 'g';  
  else if(!strcmp("....,",buffer))
    letter = 'h';  
  else if(!strcmp("..,",buffer))
    letter = 'i';  
  else if(!strcmp(".___,",buffer))
    letter = 'j';  
  else if(!strcmp("_._,",buffer))
    letter = 'k';
  else if(!strcmp("._..,",buffer))
    letter = 'l'; 
  else if(!strcmp("__,",buffer))
    letter = 'm'; 
  else if(!strcmp("_.,",buffer))
    letter = 'n'; 
  else if(!strcmp("___,",buffer))
    letter = 'o'; 
  else if(!strcmp(".__.,",buffer))
    letter = 'p'; 
  else if(!strcmp("__._,",buffer))
    letter = 'q'; 
  else if(!strcmp("._.,",buffer))
    letter = 'r';
  else if(!strcmp("...,",buffer))
    letter = 's';
  else if(!strcmp("_,",buffer))
    letter = 't';
  else if(!strcmp(".._,",buffer))
    letter = 'u';
  else if(!strcmp("..._,",buffer))
    letter = 'v';
  else if(!strcmp(".__,",buffer))
    letter = 'w';
  else if(!strcmp("_.._,",buffer))
    letter = 'x';
  else if(!strcmp("_.__,",buffer))
    letter = 'y';
  else if(!strcmp("__..,",buffer))
    letter = 'z'; 
  else
    letter = 0;                 


  return letter;
}

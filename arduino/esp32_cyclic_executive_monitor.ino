//Task1
#define led_1 4 
unsigned long startTime = 0; 
unsigned long endTime = 0; 
//-------------------------------------

//Task2
int highTime_1;    //integer for storing high time
int lowTime_1;     //integer for storing low time
float period_1;    // integer for storing period
float freq_1;      //storing frequency
int wave_1 = 14;
//-------------------------------------

//Task3
int highTime_2;    //integer for storing high time
int lowTime_2;     //integer for storing low time
float period_2;    // integer for storing period
float freq_2;      //storing frequency
int wave_2 = 25;
//-------------------------------------

//Task4
const int poten_pin = 15;
int poten_led = 2;
float avg;
float max_1;
float poten_value;
float func_val =0;
float p1 = 0;
float p2 = 0;
float p3 = 0;
float p4 = 0;
//-------------------------------------

//Task5
float freq_1_1;
float freq_2_1;
//-------------------------------------

//For Frame
#define frame_duration_ms 2 // 2ms
unsigned long framTime = 0;
unsigned long frameCounter = 0;
//-------------------------------------

void setup(void)
{
//Serial
  Serial.begin(9600);
//-------------------------------------

//Task1_Setup
pinMode(led_1, OUTPUT);
//-------------------------------------

//Task2_Setup
pinMode(wave_1, INPUT);
//-------------------------------------

//Task3_Setup
pinMode(wave_2, INPUT);
//-------------------------------------

//Task4_Setup
pinMode(poten_led, OUTPUT);
pinMode(15, INPUT);
  

}
//-------------------------------------

void frame()
{
  unsigned int slot = frameCounter % 10;
  
  switch (slot)
  {
    case 0 :                           break;
    case 1 :                           break;
    case 2 :                           break;
    case 3 :                           break;
    case 4 :                           break;
  }  
}
//-------------------------------------

void loop(void)
{
  JobTask1();
  JobTask2();
  JobTask3();
  JobTask4();
  JobTask5();
  unsigned long bT= micros();
  for (int i=0; i<1000; i++)
  {
    
  }
  
}
//--------------------------------------

void JobTask1(void)
{
  startTime = micros(); 
  digitalWrite(led_1, HIGH);  
  delayMicroseconds(200); 
  digitalWrite(led_1, LOW); 
  delayMicroseconds(50); 
  digitalWrite(led_1, HIGH);
  delayMicroseconds(30);
  endTime = micros();
  Serial.print("Time between turning LED on and off: ");
  Serial.print(endTime - startTime);
  Serial.println(" microseconds");  
}
//--------------------------------------

void JobTask2(void)
{
startTime = micros();  
highTime_1=pulseIn(wave_1,HIGH);  //read high time
lowTime_1=pulseIn(wave_1,LOW);    //read low time   
period_1 = highTime_1+lowTime_1; // Period = Ton + Toff  
freq_1=1000000/period_1;       //getting frequency with totalTime is in Micro seconds
endTime = micros();
Serial.print("Time between turning LED on and off_2: ");
Serial.print(endTime - startTime);
Serial.println(" microseconds");
delay(1000);
Serial.println(freq_1);



}
//--------------------------------------

void JobTask3(void)
{
startTime = micros();   
highTime_2=pulseIn(wave_2,HIGH);  //read high time
lowTime_2=pulseIn(wave_2,LOW);    //read low time   
period_2 = highTime_2+lowTime_2; // Period = Ton + Toff  
freq_2=1000000/period_2;       //getting frequency with totalTime is in Micro seconds
endTime = micros();
Serial.print("Time between turning LED on and off_3: ");
Serial.print(endTime - startTime);
Serial.println(" microseconds");
delay(1000);
Serial.println(freq_2); 
}
//--------------------------------------

void JobTask4(void)
{
  startTime = micros();
  poten_value = analogRead(poten_pin);
  func_val = (3.3*poten_value)/4095;
  p1 = p2;
  p2 = p3;
  p3 = p4;
  p4 = func_val;
  avg = (p1 + p2 + p3 + p4)/4;
  max_1 = 3.3/2;
  if (avg > max_1)  
    {digitalWrite(poten_led, HIGH);}
    else 
    {digitalWrite(poten_led, LOW);}
endTime = micros();
Serial.print("Time between turning LED on and off_4: ");
Serial.print(endTime - startTime);
Serial.println(" microseconds");  
}
//--------------------------------------

void JobTask5(void)
{
  startTime = micros();
  freq_1_1 = ((freq_1 - 333)*99)/(1000 - 333);
  freq_2_1 = ((freq_2 - 500)*99)/(1000 - 500);
  Serial.printf("%d, %d\n",freq_1_1, freq_2_1);
  endTime = micros();
  Serial.print("Time between turning LED on and off_5: ");
  Serial.print(endTime - startTime);
  Serial.println(" microseconds");  
}
//--------------------------------------

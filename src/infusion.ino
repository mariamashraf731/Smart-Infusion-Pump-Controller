#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 3, 9, 10, 11, 12); 

#define fsrpin A5
//Define variable to store sensor readings:
int fsrreading; //Variable to store FSR value
int yellow_fsr=8;

//Variable of thermistor

int ThermistorPin = A4;
int Vo;
float R1 = 10000;
float logR2, R2, T;
double Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int White_temp=4;


//Variable of relay

int IN2=6;

/*
YF‐ S201 Water Flow Sensor
Water Flow Sensor output processed to read in litres/hour
Adaptation Courtesy: www.hobbytronics.co.uk
*/
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
   flow_frequency++;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water Flow Meter");
  lcd.setCursor(0,1);
  lcd.print("****************");
  delay(2000);
  pinMode(yellow_fsr,OUTPUT);
  pinMode(fsrpin,INPUT);
  pinMode(White_temp,OUTPUT);
  
  pinMode(IN2,OUTPUT);      // Relay for pump
 
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  Serial.begin(9600);
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
}
void loop() {
 //FSR
  
  // Read the FSR pin and store the output as fsrreading:
  fsrreading = analogRead(fsrpin);
  // Print the fsrreading in the serial monitor:
  // Print the string "Analog reading = ".
  if (fsrreading>400) {digitalWrite(yellow_fsr,HIGH);
                       delay (2000);} 
  else {digitalWrite(yellow_fsr,LOW);}
  Serial.print("FSR reading = ");
  // Print the fsrreading:
  Serial.print(fsrreading);
  
   // thermistor
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = abs( T - 273.15);
  Tf = abs((Tc * 9.0)/ 5.0 + 32.0); 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");   
    if(Tc<35){                     //Indication of hypothermia
    digitalWrite(White_temp,HIGH); 
    }
  //flowmeter 
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
      lcd.print(l_hour, DEC); // Print litres/hour
      lcd.println(" L/hour"); 
   }

   digitalWrite (IN2,HIGH);
   delay(500);
   digitalWrite (IN2,LOW);
   delay(500);
   
}

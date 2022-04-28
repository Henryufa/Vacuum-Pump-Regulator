#include<LiquidCrystal.h>
//crystal pin setup
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
int brightness_pin = 6;
int brightness = 40;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//crystal reading initialization
int now;
int set;
int tol;

//potentiometer voltage variables
int p1Voltage = A1;
int p1Read;
float V1;

int p2Voltage = A2;
int p2Read;
float V2;



//vacuum sensor voltage variables
int vVoltage = A3;
int vRead;
float V3;

//power status variables
int relay_pin = 5;
int pump_status = 1;

void setup() {
  // put your setup code here, to run once:
  // turn on display components
  // set target value
  // display information on screen

  //(1) set pinMode for: screen(OUTPUT), regulator_19INPUT), vacuum_sensor(INPUT), power_distributor(OUTPUT)
  //(2) write to screen with arduino LCD Tutorial creat object, begin in setup, in loop lcd.print("Current:%d",Current), 
  // lcd.setCursor(2,1),lcd.print("min:%d max:%d",min, max) delay(500) lcd.clear()
  //(3) 
  pinMode(brightness_pin,OUTPUT);
  analogWrite(brightness_pin,brightness);
  pinMode(relay_pin,OUTPUT);

  Serial.begin(9600);
  
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  // if vacuum above max_vac turn pump off
  // if vacuum below min_vac turn pump on
  // update screen
  
//read and convert potentiometer values
p1Read=analogRead(p1Voltage);
V1 = (44.5/1023.)*p1Read-14.5;

p2Read=analogRead(p2Voltage);
V2 = (4.9/1023.)*p2Read+.1;

//read and convert vacuum sensor values
vRead=analogRead(vVoltage);
V3 = (44.5/1023.)*vRead-14.5;

//Serial.println(V2);
Serial.println(p1Voltage);

  set = V1;
  tol = V2;
  now = V3;
  
//display current, minimum, and maximum pressure
  lcd.setCursor(0,0);
  lcd.print("Pressure:");
  lcd.print(now);
  lcd.setCursor(0,2);
  lcd.print("set:");
  lcd.print(set);
  lcd.print(" +-:");
  lcd.print(tol);
  if(pump_status == 0){
    lcd.print("  off");
  }
    if(pump_status == 1){
    lcd.print("   on");
  }
  digitalWrite(relay_pin,pump_status);

//if vacuum is to high turn pump off
  if(now > set+tol){
    pump_status = 1;
  }
//if vacuum is too low turn pump on
  if(now < set-tol){
    pump_status = 0;
  }
  
  delay(500);
  lcd.clear(); 

  
  }

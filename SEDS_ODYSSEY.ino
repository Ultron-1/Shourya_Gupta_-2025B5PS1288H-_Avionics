//Shourya Gupta - 2025B5PS1288H
//https://www.tinkercad.com/things/91d3bJKi8Zg-athena/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fall
#include <LiquidCrystal.h>
int buttonoldval=1, buttonnewval , button=2,redled=3,buzzer=4,photosensor=A2,voltagevalue,trig=5,echo=6,RS=7,E=8,DB4=9,DB5=10;
int DB6=11,DB7=12,dt=50,anchor=0,count=0,storm=0,charybids=0,timetaken,dt1=10,sailing=1,wrecked=0;
long timer1=0,timer2=0,speedofsound=34300;
long conversionfactor=2000000;
float actualvoltage,distance;
LiquidCrystal lcd(RS,E,DB4,DB5,DB6,DB7);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  pinMode(button,INPUT);
  digitalWrite(button,HIGH);  //this is done so i dont have to use a pull up resistor, it saves a resistor lol 
  pinMode(redled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(photosensor, INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,LOW);              //code snippet for HC-SR04 sensor
  delayMicroseconds(dt1);
  digitalWrite(trig,HIGH);
    delayMicroseconds(dt1);
    digitalWrite(trig, LOW);
    timetaken=pulseIn(echo,HIGH);       //it measures the time it takes for the ultra sonic wave to leave the sensor and return back, so we need to divide by 2 to measure the distance.
    distance=(speedofsound*timetaken)/conversionfactor;
buttonnewval=digitalRead(button);
if(buttonnewval==0 && buttonoldval==1 && sailing==1 && wrecked==0)      //we need to make sure that it doesnt work when the ship is already down so i used wrecked==0, that is ship is down 
{           //if else for putting anchor and sailing condition
  anchor=1;       //this signifies the anchor is down and records the state of the ship 
  sailing=0;       // this if statement make sure if ship is saling then on pressing the button anchor is down 
}
else if(buttonnewval==0 && buttonoldval==1 && sailing==0 && wrecked==0)  //this else make sures on pressing the button ship starts sailing given that it is not wrecked
{
  anchor=0;               //saves the state of the ship
  sailing=1;
}
buttonoldval=buttonnewval;        //i did this to make sure that when the button is pressed it does not take multiple inputs bcz in that millisecond it can have a lot of zero and might enter the if statement again and mess with the state of the ship, so when once the button 
                                      //is pressed if we keep on holding it, state will not change once we firrst release it and then again presss it
if(wrecked==1 && anchor==0 && sailing==0)   //i put wrecked in the top hierarchy of this if else statement and this entire if else statement is for lcd printing only
                                            //i recorded differnt states and then used them for lcd 
{
  lcd.setCursor(0,0);
  lcd.print("WRECKED.        ");      //have given space to remove any earlier text, using  lcd.clear was causing lot of flicker
}

else if(wrecked==0 && storm==1)
{
  lcd.setCursor(0,0);
  lcd.print("STORM!!        ");
}
else if(wrecked==0 && charybids==1)
{
  lcd.setCursor(0,0);
  lcd.print("CHARYBIDS!!         ");
}
else if(anchor==1 && sailing==0 && wrecked==0 )
{
    lcd.setCursor(0,0);
  lcd.print("ANCHOR DOWN.      ");

}
 else if(sailing==1 && anchor==0 && wrecked==0)
{
    lcd.setCursor(0,0);
  lcd.print("SAILING.         ");
}
voltagevalue=analogRead(photosensor);
if(voltagevalue <=479 && anchor==0)  //my photosensor went from 28 to 958, so i took 479 as middle ground ,, then if anchor is down no need to enter here
{
  if(storm==0)
  {
    timer1=millis();   //millis always run from the start, so i need to timer1=millis only when the storm starts , so i used this if statement otherwise it would have entered this if statement
                       //multiple times ,and timer will always be equal to the millis , so later on i can not use it to find whether the time is greater than 5 sec or less
  }
  storm=1;
  
}
else if(distance<=100 && anchor==0)
{
  if(charybids==0)
  {
     timer2=millis();
  }
  charybids=1;
}

if(storm==1 && wrecked==0)             //now here is the if else for what to when specific states are activated and assign states for lcd to shhow
{
  digitalWrite(redled,HIGH);
  if(anchor==0 && millis()-timer1<=5000 && voltagevalue >479)         //condition if storm goes within 5s, so i used voltage above 479
  {
  storm=0;
sailing=1;
wrecked=0;
digitalWrite(redled,LOW);
}
else if(anchor==0 && millis()-timer1 > 5000 )    //timer goes greater than 5s, ship goes wrecked
{
  sailing=0;
  wrecked=1;
  storm=0;
  digitalWrite(redled,LOW);
}
else if(anchor==1 && millis()-timer1 <=5000)    //if anchor goes within 5s , ship is safe 
{
  sailing=0;
  wrecked=0;
  storm=0;
  digitalWrite(redled,LOW);
}

}
else if(charybids==1 && wrecked==0)  //this is for charybids, same thing as storm 
{
digitalWrite(buzzer,HIGH);

  if(anchor==1 && millis()-timer2<=5000)
  {
    charybids=0;
    sailing=0;
    wrecked=0;
    digitalWrite(buzzer,LOW);
  
  }
  else if(anchor==0 && millis()-timer2<=5000 && distance >100)
  {
    charybids=0;
    sailing=1;
    wrecked=0;
    digitalWrite(buzzer,LOW);
  }
  else if( anchor==0 && millis()-timer2 >5000)
  {
    sailing=0;
    wrecked=1;
    charybids=0;
    digitalWrite(buzzer, LOW);
  }
}


}

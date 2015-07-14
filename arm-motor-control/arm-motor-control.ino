////////////////////////////////////////////////
// TINAH Template Program - UBC Engineering Physics 253
// (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
/////////////////////////////////////////////////


#include <phys253.h>          
#include <LiquidCrystal.h>    

void setup()
{  
  #include <phys253setup.txt>
  Serial.begin(9600) ;
  
}


// GLOBAL VARIABLES


void loop()
{
  int knob = 0;
  int knob_pin = 7;
  int threshold = 255;
  // Set the screen to be ready to print
  LCD.clear();  LCD.home();
  LCD.setCursor(0,0); LCD.print("Press Start");
  LCD.setCursor(0,1);
  knob = (analogRead(knob_pin) - 511.5)/2.0;
  LCD.print(knob);
  
  // only runs when the start button is pressed
  while(startbutton()){
      knob = (analogRead(knob_pin) - 511.5)/2.0;
      if( knob > threshold){knob = threshold;}
      if( knob < -threshold){knob = -threshold;}
      motor.speed(3,knob);
      // display on TINAH
      LCD.clear();  LCD.home();
      LCD.setCursor(0,0); LCD.print("Speed: ");
      LCD.setCursor(0,1);
      LCD.print(knob);
      delay(100);
  }
  
  while(stopbutton()){
    
  }

  motor.speed(3,0);
  delay(100);
}


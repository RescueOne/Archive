////////////////////////////////////////////////
// TINAH Menu Program - UBC Engineering Physics 253
// (fogelman, 2015 Jan 2)
/////////////////////////////////////////////////

#include <avr/EEPROM.h>
#include <phys253.h>          
#include <LiquidCrystal.h>    

//void loop()
//{
//  int pinNumber = 0;
//  int variable = LOW;
//  LCD.clear();  LCD.home() ;
//  LCD.setCursor(0,0); LCD.print("Switch Test");
//  LCD.setCursor(0,1);
//  variable = digitalRead(pinNumber);
//  if(variable == HIGH){
//    LCD.print("1");
//  } else {
//    LCD.print("1");
//  }
//
//}
 
class MenuItem
{
public:
	String    Name;
	uint16_t  Value;
	uint16_t* EEPROMAddress;
	static uint16_t MenuItemCount;
	MenuItem(String name)
	{
		MenuItemCount++;
		EEPROMAddress = (uint16_t*)(2 * MenuItemCount);
		Name 		  = name;
		Value         = eeprom_read_word(EEPROMAddress);
	}
	void Save()
	{
		eeprom_write_word(EEPROMAddress, Value);
	}
};
 
uint16_t MenuItem::MenuItemCount = 0;
/* Add the menu items here */
MenuItem Speed            = MenuItem("Speed");
MenuItem ProportionalGain = MenuItem("P-gain");
MenuItem DerivativeGain   = MenuItem("D-gain");
MenuItem IntegralGain     = MenuItem("I-gain");
MenuItem menuItems[]      = {Speed, ProportionalGain, DerivativeGain};

void setup()
{  
  #include <phys253setup.txt>
  Serial.begin(9600);
  LCD.clear();
  LCD.home();
  
}

void loop()
{
	LCD.clear(); LCD.home()
	LCD.print("Start + stop = menu");
	LCD.setCursor(0, 1);
	LCD.print("Start = run code");
	delay(100);
 
	if (startbutton() && stopbutton())
	{
		delay(100);
		if (startbutton())
		{
			Menu();
		}
	}
        if (startbutton())
        {
          LCD.clear(); LCD.home();
	  LCD.print("Press stop to exit!");
          while(!stopbutton())
          {
            // PID CODE HERE 
          }
        }
}
 
void Menu()
{
	LCD.clear(); LCD.home();
	LCD.print("Entering menu");
	delay(500);
 
	while (true)
	{
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * (MenuItem::MenuItemCount) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(menuItems[menuIndex].Name); LCD.print(" "); LCD.print(menuItems[menuIndex].Value);
		LCD.setCursor(0, 1);
		LCD.print("Set to "); LCD.print(knob(7)); LCD.print("?");
		delay(100);
 
		/* Press start button to save the new value */
		if (startbutton())
		{
			delay(100);
			if (startbutton())
			{
				menuItems[menuIndex].Value = knob(7);
				menuItems[menuIndex].Save();
				delay(250);
			}
		}
 
		/* Press stop button to exit menu */
		if (stopbutton())
		{
			delay(100);
			if (stopbutton())
			{
				LCD.clear(); LCD.home();
				LCD.print("Leaving menu");
				delay(500);
				return;
			}
		}
	}
}


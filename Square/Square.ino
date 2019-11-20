#include <Wire.h>
#include <Adafruit_MCP23017.h>
#define I2CADDR 0 
Adafruit_MCP23017 mcp_2;

#define MAXLEDS 5
int states[MAXLEDS][MAXLEDS] = {
    { 1, 1, 1 , 1 , 1 },
    { 1, 0, 0 , 0 , 1 },
    { 1, 0, 0 , 0 , 1 },
    { 1, 0, 0 , 0 , 1 },
    { 1, 1, 1 , 1 , 1 }
    
};
int Led_Row_Pins[] = { 0 , 1 , 2 , 3 , 4 } ;             //   Anode pins are shorted in row_wise_manner
int Led_Column_Pins[] = { 5 , 6  , 7 , 8 , 9 } ;          //   Column Pins are shorted in column_wise_manner   
int Loop_Count = 5 ;
int i = 0 ;
int j = 0 ;
int state = 1 ;

void setup() {
   Serial.begin(9600);
  Serial.println("Program Started" );
  
  
  //Begin I2C Devices
  Wire.begin();
  Wire.beginTransmission(32);
  if (Wire.endTransmission() == 0) Serial.println("I2C Device Connected successfully with address 0x20");
  else Serial.println("I2C Device  Not Connected with address 0x20");
  mcp_2.begin();
 
  
  for( i = 0 ; i < Loop_Count ; i++ ){     // Anode Pins are connected in row_wise manner and are made LOW so that they dont conduct       
    mcp_2.pinMode(Led_Row_Pins[i],OUTPUT);
    mcp_2.digitalWrite(Led_Row_Pins[i],LOW);
    mcp_2.pinMode(Led_Column_Pins[i],OUTPUT);    // Cathode Pins are connected in column_wise manner and are made HIGH so that they dont conduct
    mcp_2.digitalWrite(Led_Column_Pins[i],HIGH); 
  }
}


void switch_leds(int row) {
    int i;

    /* switch off all rows */
    for(i = 0; i < MAXLEDS; i++) {
        mcp_2.digitalWrite(Led_Row_Pins[i], 0);
    }

    /* switch columns according to current row */
    for(i = 0; i < MAXLEDS; i++) {
        mcp_2.digitalWrite(Led_Column_Pins[i], !states[row][i]);
    }

    /* switch on current row */
    mcp_2.digitalWrite(Led_Row_Pins[row], 1);

}

void loop() { 
    static int row = 0;
    /* switch on LEDs in a single row */
    switch_leds(row);
    /* next row */
    row++; row %= MAXLEDS;
    /* The processing delay between calls to loop() is added to this delay. */
    
}

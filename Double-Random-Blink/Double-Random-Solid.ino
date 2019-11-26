/* Keypad is connected to MCP - 1 with address 0*24  and Led - Matrix is connected to MCP - 2 with address 0*20 */
#include <Wire.h>
#include <Keypad_MC17.h>
#include <Keypad.h>        
#include <Adafruit_MCP23017.h>
Adafruit_MCP23017 mcp_1;
Adafruit_MCP23017 mcp_2;
#define I2CADDR 0x24

const byte ROWS = 5; //four rows
const byte COLS = 5; //five columns

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','4','5'},
  {'6','7','8','9','A'},
  {'B','C','D','E','F'},
  {'G','H','I','J','K'},
  {'L','M','N','O','P'}
};

byte rowPins[ROWS] = {4 , 3 , 2 , 1 , 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9 , 8 , 7 , 6 , 5}; //connect to the column pinouts of the keypad
int Led_Rows[] = { 0 , 1 , 2 , 3 , 4 } ; //   Anode pins are shorted in row_wise_manner
int Led_Columns[] = { 5 , 6  , 7 , 8 , 9 } ;//   Column Pins are shorted in column_wise_manner   
int Loop_Count = 5 ;
int first_key_pressed = 0;
int second_key_pressed = 0;
char first_in_position = '1';
char second_in_position = '5';
int Wait_Time = 500 ; 
int i = 0 ;
int j = 0 ;
int x = 0 ;
int y = 0 ; 
int c = 0 ;

//initialize an instance of class NewKeypad
Keypad_MC17 customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

void Led_Glow( int a , int b ){
  mcp_2.digitalWrite(Led_Rows[a],HIGH);
  mcp_2.digitalWrite(Led_Columns[b],LOW); 
}

void Led_Dim( int a ,int b ){
  mcp_2.digitalWrite(Led_Rows[a],HIGH);
  mcp_2.digitalWrite(Led_Columns[b],HIGH);
} 

void restore( ){
  for(int i=0;i<5;i++){
    mcp_2.digitalWrite(Led_Rows[i],LOW);
    mcp_2.digitalWrite(Led_Columns[i],HIGH);
  }
}

void check_for_position (char c)
{
  if (first_in_position == c)
  {
    first_key_pressed = 1;
  }
  else if (second_in_position == c)
  {
    second_key_pressed = 1;
  }
}

void set_next_expected_leds()
{
    first_key_pressed = 0;
    second_key_pressed = 0;
  if (first_in_position == '1') 
  {
    first_in_position = 'L';
    second_in_position = 'P';
    restore();
    Led_Glow(4,0);
    delay(Wait_Time);
    Led_Glow(4,4);
    delay(Wait_Time);
  } else if (first_in_position == 'L')
  {
    first_in_position = 'B';
    second_in_position = 'D';
    restore();
    Led_Glow(2, 0);
    delay(Wait_Time);
    Led_Glow(2 , 2);
    delay(Wait_Time);
  }else if (first_in_position == 'B')
  {
    first_in_position = 'N';
    second_in_position = 'P';
    restore();
    Led_Glow(4,2);
    delay(Wait_Time);
    Led_Glow(4,4);
    delay(Wait_Time);
  }else if (first_in_position == 'N') 
  {
    first_in_position = '3';
    second_in_position = '5';
    restore();
    Led_Glow(0,2);
    delay(Wait_Time);
    Led_Glow(0,4);
    delay(Wait_Time);
  }
}
  


void setup(){
  Serial.begin(9600);
  Wire.begin( );
  customKeypad.begin( );        

  Serial.println("Program Started" );
    
  //Begin I2C Devices
  Wire.beginTransmission(36);
  if (Wire.endTransmission() == 0) Serial.println("I2C Device Found at address 0x24 for Keypad - Matrix MCP - 1 ");
  else Serial.println("I2C 0x24 not Connected for Keypad - Matrix MCP - 1");
  mcp_1.begin();
 
  Wire.beginTransmission(32);
  if (Wire.endTransmission() == 0) Serial.println("I2C Device Found at address 0x20 for Led - Matrix MCP - 2");
  else Serial.println("I2C 0x20 not Connected for Led - Matrix MCP - 2  ");
  mcp_2.begin();
  
   
  for(int i=0;i<5;i++){
   mcp_2.pinMode(Led_Rows[i], OUTPUT);
   mcp_2.digitalWrite(Led_Rows[i],LOW);
   mcp_2.pinMode(Led_Columns[i], OUTPUT);
   mcp_2.digitalWrite(Led_Columns[i],HIGH);
  }

  Led_Glow(0,0);
  delay(Wait_Time);
  Led_Glow(0,4);
  delay(Wait_Time);
    
 }


void loop(){
  char customKey = customKeypad.getKey();
  if( customKey == first_in_position || customKey == second_in_position){
   switch (customKey)
   {
    case '1':
      check_for_position('1');
      Led_Dim(0,0);
      delay(Wait_Time);
      break;

    case '3':
      check_for_position('3');
      Led_Dim(0, 2);
      delay(Wait_Time);
      break;

    case '5':
      check_for_position('5');
      Led_Dim(0,4);
      delay(Wait_Time);
      break;

    case 'F':
      check_for_position('F');
      Led_Dim(4,4);
      delay(Wait_Time);
      break;

    case 'D':
      check_for_position('D');
      Led_Dim(2,2);
      delay(Wait_Time);
      break;

    case 'B':
      check_for_position('B');
      Led_Dim(2,0);
      delay(Wait_Time);
      break;

    case 'L':
      check_for_position('L');
      Led_Dim(4,0);
      delay(Wait_Time);
      break;

    case 'N':
      check_for_position('N');
      Led_Dim(4,2);
      delay(Wait_Time);
      break;

    case 'P':
      check_for_position('P');
      Led_Dim(4,4);
      delay(Wait_Time);
      break;
    }
  }
   if(first_key_pressed == 1 && second_key_pressed == 1) 
   {
      set_next_expected_leds();
   }
}

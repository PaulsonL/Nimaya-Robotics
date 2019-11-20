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
int i = 0 ;
int j = 0 ; 
int c = 0 ;
int Wait_Time_Clap = 300;
int Wait_Time = 1000 ;
int expected = '1';


//initialize an instance of class NewKeypad
Keypad_MC17 customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

void Led_Glow( int a , int b ){
  mcp_2.digitalWrite(Led_Rows[a],HIGH);
  mcp_2.digitalWrite(Led_Columns[b],LOW); 
}

void Led_Dim( int a ,int b ){
  mcp_2.digitalWrite(Led_Rows[a],LOW);
  mcp_2.digitalWrite(Led_Columns[b],HIGH);
}

void All_On(){
 for( int i = 0  ; i < Loop_Count  ; i++ ){
    mcp_2.digitalWrite(Led_Rows[i],HIGH);
    while( j < Loop_Count ){
    mcp_2.digitalWrite(Led_Columns[j],LOW);
    j++ ;
    }
  }
  j = 0 ;
}

void All_Off(){
  for( int  i = 0 ; i < Loop_Count ; i++ ){
    mcp_2.digitalWrite(Led_Rows[i],LOW);
    mcp_2.digitalWrite(Led_Columns[i],HIGH);
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
  Led_Dim(0,0);

}
  
void loop(){
  char customKey = customKeypad.getKey();
  if( customKey == expected )
  {
    switch(customKey)
    {
    case '1' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();    
    Led_Glow(0,2);
    delay(Wait_Time);
    Led_Dim(0,2);
    expected = '3' ;
    break;

    case '3' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(0,4);
    delay(Wait_Time);
    Led_Dim(0,4);
    expected = '5' ;
    break;
   

    case '5' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(2,0);
    delay(Wait_Time);
    Led_Dim(2,0);
    expected = 'B' ;
    break;
    
    case 'B' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(2,2);
    delay(Wait_Time);
    Led_Dim(2,2);
    expected = 'D' ;
    break;
  
    case 'D' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(2,4);
    delay(Wait_Time);
    Led_Dim(2,4);
    expected = 'F' ;
    break;
   
    case 'F' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(4,0);
    delay(Wait_Time);
    Led_Dim(4,0);
    expected = 'L' ;
    break;
    
    case 'L' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(4,2);
    delay(Wait_Time);
    Led_Dim(4,2);
    expected = 'N' ;
    break;
    
    case 'N' :
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    Led_Glow(4,4);
    delay(Wait_Time);
    Led_Dim(4,4);
    expected = 'P' ;
    break;
      
    case 'P' :
    if( c == 0 ){
    All_On();
    delay(Wait_Time_Clap);
    All_Off();
    c++;
    }
    break; 
      
    }
}
}  

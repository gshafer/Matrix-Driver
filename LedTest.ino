/*
  Reading a serial ASCII-encoded string.
 
 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints,
 
 This example code is in the public domain.
 */

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> //  Hardware-specific library


#define CLK 8
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

#define DEBUG 1

int tempNum = 0;
int hourNum = 0;
int minNum = 0;
int sign = 0;
int tsxNum = 0;
int tsxSign = 0;
int portDay = 0;
int portDaySign = 0;
int displayOffFlag = 1;
int djiaDay = 0;
int djiaDaySign = 0;

//Display text
int display(String titleText , String stringOne, int sign) {
matrix.begin();
matrix.fillScreen(0);
delay(10);
matrix.setCursor(1, 1);
matrix.setTextColor(matrix.Color333(7,7,7));
matrix.println(titleText);
matrix.setCursor(1, 9);   // next line
if(sign == 1)
{
matrix.setTextColor(matrix.Color333(7,0,0));
}
else
{
matrix.setTextColor(matrix.Color333(0,7,0));
}
matrix.println(stringOne);
}

void setup()
{
  Serial.begin(19200);
  if(displayOffFlag == 0)
  {
  display("Start", "Up", 0);
  }
  else
  {
  display(" ", " ", 0);
  }
  delay(5000);
  
}

void loop() {
  // if there's any serial available, read it:
  
//Modify temperature string to show time bu adding colon and leading 0 if required
  String tempNumString = String(tempNum);
  String timeNumString = String(hourNum) + ":" + String(minNum);
  if (minNum < 10){
    timeNumString = String(hourNum) + ":0" + String(minNum);
  }
  else {
    timeNumString = String(hourNum) + ":" + String(minNum);
  }

//Modify temperature sting to add - or + and degree C
  if (sign == 1){
    tempNumString = "-" + String(tempNum) + "C";
  }
  else {
    tempNumString = "+" + String(tempNum) + "C";
  }

//Reconstruct TSX number to get 1 decimal place
  float tsxNumFloat = tsxNum / 10.0;
  //Serial.print(tsxNumFloat);
  String tsxNumString = String(tsxNumFloat);
  int length = tsxNumString.length() - 1;
  //Serial.print(length);
  tsxNumString.remove(length);
  //Serial.print(tsxNumString);

//Modify TSX string to add + or - and % sign
if (tsxSign == 1){
    tsxNumString = "-" + tsxNumString + "%";
  }
  else {
    tsxNumString = "+" + tsxNumString + "%";
  }

  //Reconstruct portfolio day number to get 1 decimal place
  float portDayFloat = portDay / 10.0;
  //Serial.print(portDayFloat);
  String portDayString = String(portDayFloat);
  int portDaylength = portDayString.length() - 1;
  //Serial.print(portDaylength);
  portDayString.remove(portDaylength);
  //Serial.print(portDayString);

//Modify portfolio day string to add + or - and % sign
if (portDaySign == 1){
    portDayString = "-" + portDayString + "%";
  }
  else {
    portDayString = "+" + portDayString + "%";
  }

  //Reconstruct djia day number to get 1 decimal place
  float djiaDayFloat = djiaDay / 10.0;
  //Serial.print(djiaDayFloat);
  String djiaDayString = String(djiaDayFloat);
  int djiaDaylength = djiaDayString.length() - 1;
  //Serial.print(djiaDaylength);
  djiaDayString.remove(djiaDaylength);
  //Serial.print(djiaDayString);

//Modify portfolio djia string to add + or - and % sign
if (djiaDaySign == 1){
    djiaDayString = "-" + djiaDayString + "%";
  }
  else {
    djiaDayString = "+" + djiaDayString + "%";
  }
  
// Display all of the info for 5 seconds each if the Display Off Flag is not set. Display only time in the evening.
      if(displayOffFlag == 0)
      {
      display("Time",timeNumString,0);
      delay(5000);
      display("Temp",tempNumString,sign);
      delay(5000);
      display("TSX",tsxNumString,tsxSign);
      delay(5000);
      display("SSX",portDayString,portDaySign);
      delay(5000);
      display("DJIA",djiaDayString,djiaDaySign);
      delay(5000);
      }
      else if (displayOffFlag == 1)
      {
      matrix.fillScreen(0);
      delay(30000);
      }
      else if (displayOffFlag == 2)
      {
      display("Time",timeNumString,0);
      delay(60000);
      }
      else if (displayOffFlag == 3)
      {
      display("Time",timeNumString,0);
      delay(10000);
      display("Temp",tempNumString,sign);
      delay(10000);
      }
      else
      {
      Serial.println("Error in Display Flag");  
      }
  
  // look for the next valid integer in the incoming serial stream
  while (Serial.available() > 0) {
    tempNum = Serial.parseInt(); // Get Temperature Value
    hourNum = Serial.parseInt(); //Get the Hour Value
    minNum = Serial.parseInt();  //Get the minute Value
    sign = Serial.parseInt();    //Get the teperture sign value
    tsxNum = Serial.parseInt();  //Get the TSX % change
    tsxSign = Serial.parseInt(); //Get the sign of the TSX change
    portDay = Serial.parseInt(); //Get the portfolio daily change
    portDaySign = Serial.parseInt(); //Get the sign of the portfolio day change
    displayOffFlag = Serial.parseInt(); //Get the display off flag
    djiaDay = Serial.parseInt(); //Get the DJIA daily change
    djiaDaySign = Serial.parseInt(); //Get the sign of the DJIA day change

    
    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '*') {
      // print the values received:
      #ifdef DEBUG
      Serial.print("Temp=");
      Serial.println(tempNum);
      Serial.print("Hours=");
      Serial.println(hourNum);
      Serial.print("Minutes=");
      Serial.println(minNum);
      Serial.print("Temp Sign=");
      Serial.println(sign);
      Serial.print("TSX=");
      Serial.println(tsxNum);
      Serial.print("TSX Sign=");
      Serial.println(tsxSign);
      Serial.print("Port=");
      Serial.println(portDay);
      Serial.print("Port Sign=");
      Serial.println(portDaySign);
      Serial.print("DJIA=");
      Serial.println(djiaDay);
      Serial.print("DJIA Sign=");
      Serial.println(djiaDaySign);
      Serial.print("Display Off Flag=");
      
      Serial.println(displayOffFlag);
      #endif
    }
  }
}


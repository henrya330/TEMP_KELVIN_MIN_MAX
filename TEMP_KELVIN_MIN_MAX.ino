
//www.elegoo.com
//2016.12.9
#include <LiquidCrystal.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>

int itempC, itempF,tempReading,tempPin,iMin,iMax = 0;
float tempC, tempF = 0;
double tempK = 0;
 
//                BS E  D4 D5  D6  D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
  initialize();
}
void loop()
{
  int delayTimer = 4000;
  GetTemperaturesValues();
  TruncateValues();
  setMinMaxValues();
  DisplayMinMax();
  delay(delayTimer);
  DisplayResults();
  delay(delayTimer);
}

void GetTemperaturesValues(){
  tempReading = analogRead(tempPin);
  tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
}

void TruncateValues(){
  //The LCD display is limited so need to drop decimal places.
  itempC = round(tempC);
  itempF = round(tempF);
}

void setMinMaxValues()
{
  iMin = (iMin >= itempF)? itempF:iMin;

  // if (iMin >= itempF)
  // {
  //   iMin = itempF;
  // }

  if (iMax <= itempF)
  {
    iMax = itempF;
  } 
   
}

void initialize()
{
  GetTemperaturesValues();
  TruncateValues();

  iMin = itempF;
  iMax = itempF;
}

void DisplayMinMax(){
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Temperature:");

  lcd.setCursorAndPrint(0,1,"Min")
  lcd.setCursorAndPrint(9,1,"Max");
  lcd.setCursorAndPrint(13,0, " ");
  lcd.setCursorAndPrint(13,0, itempF);
  lcd.setCursorAndPrint(5,1, " ");
  lcd.setCursorAndPrint(4,1, iMin);
  lcd.setCursorAndPrint(13,1, "   ");
  lcd.setCursorAndPrint(13,1, iMax);
}

void DisplayResults(){
  lcd.clear();
  lcd.setCursorAndPrint(0,0, String("F") + char(223) + String(itempF));
  lcd.setCursorAndPrint(8,0, String("C") + char(223) + String(itempC));
  lcd.setCursorAndPrint(0,1, String("Kelvin  ") + String(tempK));
  lcd.setCursor(10, 1);
}

void setCursorAndPrint(int num1, int num2, string string){
  lcd.setCursor(num1, num2);
  lcd.print(string);
}
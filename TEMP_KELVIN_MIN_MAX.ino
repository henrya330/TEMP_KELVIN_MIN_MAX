
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
  GetTemperaturesValues();
  TruncateValues();
  setMinMaxValues();
  DisplayMinMax();
  ScreenDelay();
  DisplayResults();
  ScreenDelay();
}

void ScreenDelay(){
  delay(4000); 
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

  int iNew = 0;

  if (iMin >= itempF)
  {
    iMin = itempF;
  }

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
  lcd.setCursor(0,1);
  lcd.print("Min");
  lcd.setCursor(9,1);
  lcd.print("Max");

  lcd.setCursor(13, 0);
  lcd.print ("   ");
  lcd.setCursor(13, 0);
  lcd.print(itempF);
  lcd.setCursor(5, 1);
  lcd.print ("   ");  
  lcd.setCursor(4, 1);
  lcd.print(iMin);
  lcd.setCursor(13, 1);
  lcd.print ("   ");
  lcd.setCursor(13, 1);
  lcd.print(iMax);
}

void DisplayResults(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("F") + char(223) + String(itempF));

  lcd.setCursor(8, 0);
  lcd.print(String("C") + char(223) + String(itempC));

  lcd.setCursor(0, 1);
  lcd.print(String("Kelvin  ") + String(tempK)); 
  lcd.setCursor(10, 1);
}
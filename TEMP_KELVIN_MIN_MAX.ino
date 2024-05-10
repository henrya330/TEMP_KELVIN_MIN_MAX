
#include <LiquidCrystal.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
//#include <string.h>

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

void DisplayMinMaxOld(){
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print("Min");
  lcd.setCursor(9,1);
  lcd.print("Max");



  lcd.setCursor(13, 0);
  lcd.print ("   ");
  
  //DisplayPrint(13,0,String(itempF));


  lcd.setCursor(13, 0);
  lcd.print(itempF);


  lcd.setCursor(5, 1);
  lcd.print ("   ");  
  lcd.setCursor(4, 1);
  lcd.print(iMin);
  lcd.setCursor(13, 1);
  lcd.print ("   ");
  lcd.setCursor(13, 1);
  lcd.print(String(iMax));
}

void DisplayMinMax() {
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Temperature:");

  const String values[3] = {
    String(itempF),
    String(iMin),
    String(iMax)
  };

  const int positions[3][2] = {
    {13, 0},
    {4, 1},
    {13, 1}
  };

  for (int i = 0; i < 3; i++) {
    DisplayPrint(values[i], positions[i][0], positions[i][1]);
  }

  lcd.setCursor(0, 1);
  lcd.print("Min");
  lcd.setCursor(9, 1);
  lcd.print("Max");
} 

void DisplayPrint(String string, int x, int y ){
  lcd.setCursor(x, y);
  lcd.print(string);
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
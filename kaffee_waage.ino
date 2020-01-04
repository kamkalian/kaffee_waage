#include <HX711.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

HX711 scale;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


void setup() {
  //Serial.begin(9600);

  scale.begin(2, 3);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  /* ----------------------
   *  Kalibrierung starten
     ----------------------*/
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Kalibrierung...");
  display.display();
  
  scale.set_scale();
  scale.tare();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Gewicht!");
  display.display();

  delay(3000);
  
  long cal_val = scale.get_units(50) / 140;

  scale.set_scale(cal_val);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Fertig!");
  display.display();
  delay(1000);
  
}

double sum_weight;
int c;

void loop() {
  long scale_val = scale.read();
  //Serial.println(scale_val);
  double weight_val = mapfloat(scale_val, start_val+(tara_val-start_val), val_140+(tara_val-start_val), 0, 140);

  sum_weight += weight_val;cd DDDd

  if(c>9){  

    double avg_weight = sum_weight / 10;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(avg_weight, 1);
    display.display();

    sum_weight = 0;
    c = 0;

  }

  c++;

String floatAlignRight ( float num )
{
  int    space  = 0;
  String spaces = "";
 
  //how large is this number?
  //always assumes value has 2 digits after the decimal point.
  if ( num < 10.0 ) space = 5; //10.0=4chars. 12+4=16, etc
  else if ( num > 9.0 && 100.0 > num ) space = 4;
  else if ( num > 99.0 && 1000.0 > num ) space = 3;
  else if ( num > 999.00 ) space = 2;
 
  //add the correct amount of spaces infront of our value
  for ( uint8_t s=0; s<space; s++ ) spaces += F(" ");
 
  //return value (or your code here)
  return spaces + String ( num );
}

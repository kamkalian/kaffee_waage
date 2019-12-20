//#include <Q2HX711.h>
#include <HX711.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Q2HX711 hx711(2, 3);
HX711 scale;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

long start_val;
long tara_val;
long val_500 = 8379053;
long val_140 = -162080;




float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}


void setup() {
  //Serial.begin(9600);

  scale.begin(2, 3);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  start_val = scale.read();
  tara_val = scale.read();
  
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

}
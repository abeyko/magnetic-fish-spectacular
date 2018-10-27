// 10/27/2018 - Magnetic Fish Spectacular!
// https://github.com/abeyko/magnetic-fish-spectacular
// https://devpost.com/software/magnetic-fish-spectacular

// https://www.pjrc.com/teensy/td_libs_SSD1306.html
// Pins for OLED 
// SDA  18
// SCL  19
// VCC  5V
// GND  GND

#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h by defining SSD1306_LCDHEIGHT as 64");
#endif
int theScore = 0;
int theTime = 120;// 120; // 2 minutes
int currentFish = 0; // no fish + 27 fish
String fishName = "No Fish Detected...";
String fishNames[28] = {"No fish detected...", "Lord Scenturio","Clide","Henry","Gus","Peter","Rufus","Margaret","Portia","Ariel", "Elsa", "Dory", "Buffy", "Sushi", "Bubbles", "Casper", "Shadow", "Nemo", "Gilligan", "N Chips", "Bubba", "Cosmo", "Stewy", "Gunther", "Sponge Bob", "Patrick", "Chumley", "Watermelloon"};
void setup() {
  Serial.begin(9600);
  delay(200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
}

void loop() {
  fishScore(fishNames[currentFish],theScore);
  delay(1000);
  //placeholder for catching a fish
  if(theTime % 4 == 1) {
    theScore = (theScore + 4) - (theTime % 5);
    currentFish++;
  }
  theTime--;
  // time is up, so reset...
  if(theTime < 0) {
    theScore = 0;
    theTime = 120; //120; // two minutes
    // invert the display
    display.invertDisplay(true);
    delay(1000); 
    display.invertDisplay(false);
    delay(1000); 
    //
  }
}

void fishScore(String name, int theScore) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("Score: ");
  display.println(theScore);

  display.setTextSize(1);
  display.println();
  display.setTextColor(BLACK, WHITE); // 'inverted' 
  display.setTextSize(1);
  display.print(" Fish:  ");
  display.print(name);
  display.println(" ");

  display.setTextColor(WHITE);
  display.print("     Time: ");
  display.println(theTime);
  
  display.display();
  
}

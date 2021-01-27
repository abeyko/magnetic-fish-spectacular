#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=255,182
AudioFilterBiquad        biquad1;        //xy=394,182
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=535,319
AudioPlaySdWav           playFlashWav;
AudioFilterStateVariable filter1;        //xy=558,189
AudioAnalyzePeak         peak1;          //xy=559,255
AudioMixer4              mixer1;         //xy=710,196
AudioOutputAnalog        dac1;           //xy=844,196
AudioConnection          patchCord1(adc1, biquad1);
AudioConnection          patchCord2(biquad1, 0, filter1, 0);
AudioConnection          patchCord3(biquad1, peak1);
AudioConnection          patchCord4(playFlashRaw1, 0, mixer1, 2);
AudioConnection          patchCord5(filter1, 0, mixer1, 0);
AudioConnection          patchCord6(filter1, 2, mixer1, 1);
AudioConnection          patchCord7(mixer1, dac1);
// GUItool: end automatically generated code

// Parameters
const bool DEBUG = false;
const bool BEGIN_CLICK = true;  // Play click on voice start
const bool END_SOUND = true;    // Play click/burst on voice end
const bool FEEDBACK_SUPPRESSION = false;  // Enables input filter
const unsigned int LOWPASS_CUTOFF = 2200; // Hz
const unsigned int CROSSOVER_FREQ = 2000; // Filter center freq
const float BASS_GAIN_ON = 0.01;
const float BASS_GAIN_OFF = 0.0;
const float TREBLE_GAIN_ON = 0.25;    // Voice output volume
const float TREBLE_GAIN_OFF = 0.0;
const float SFX_GAIN = 0.95;           // Sound clip volume
const float SQUELCH_CUTOFF = 0.10;    // Voice threshold
const int HYSTERESIS_TIME_ON = 20;    // Milliseconds
const int HYSTERESIS_TIME_OFF = 400;  // Milliseconds

// Pins
const int FLASH_CS = 6;               // Serial flash chip select
const int AMP_ENABLE = 5;             // Amplifier enable pin

// On/Off state machine states
typedef enum volState {
  QUIET,
  QUIET_TO_LOUD,
  LOUD,
  LOUD_TO_QUIET,
} VolState;

// Global variables
elapsedMillis fps; // Sample peak only if we have available cycles
VolState state = QUIET;

long timeout = 0;     // This timeout allows us to put a newline between all the scans

boolean playSplash = false;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  // Initialize amplifier
  AudioMemory(20);
  dac1.analogReference(EXTERNAL); // much louder!
  delay(50);                      // time for DAC voltage stable
  pinMode(AMP_ENABLE, OUTPUT);

  // wait up to 10 seconds for Arduino Serial Monitor
  unsigned long startMillis = millis();
  if ( DEBUG ) {
    while ( !Serial && ( millis() - startMillis < 10000 ) );
  }

  // Adjust gain into the mixer
  mixer1.gain(0, BASS_GAIN_OFF);
  mixer1.gain(1, TREBLE_GAIN_OFF);
  mixer1.gain(2, SFX_GAIN);

  // Initialize serial flash
  if ( !SerialFlash.begin(FLASH_CS) ) {
    if ( DEBUG ) {
      Serial.println( "Unable to access SPI Flash chip" );
    }
  }

  // Use the time since boot as a seed (I know, not great, but
  // the audio toolbox took away my analogRead)
  int seed = micros() % 32767;
  if ( DEBUG ) {
    Serial.print("Seed: ");
    Serial.println(seed);
  }
  randomSeed(seed);

  Serial.println("Finished init");
  digitalWrite(AMP_ENABLE, HIGH);  
}

void loop() {  
  while (Serial1.available()) {                 // Do this whenever this is data coming in the serial port, pins 0&1
    int dataFromLine = Serial1.read();          // Put that data in an integer so we can work with it
    if (dataFromLine < 10){                     // If the data is under ten, print a zero so we get leading zeroes on our data
      Serial.print("0");
    }
    Serial.print(dataFromLine);                 // Print the received data to our USB serial port
    timeout = (millis() + 5);                   // Wait five milliseconds for any new data
  }
  if ((millis() > timeout) && timeout != 0){      // If no new data arrives, print a single newline
    Serial.println("");
    playFile("splash.wav");
    while (Serial1.available()) {
      Serial1.read();
    }
    timeout = 0;
    Serial.println("clear");
  }
}

// Play a sound clip from serial flash
void playFile( const char* filename) {

  if ( DEBUG ) {
    Serial.print("Playing file: ");
    Serial.print(filename);
  }

  // Start playing the file
    playFlashRaw1.play(filename);


  // A brief delay for the library read info
  delay(5);

  // Wait for the file to finish playing
  while ( playFlashRaw1.isPlaying() || playFlashWav.isPlaying());

  if ( DEBUG ) {
    Serial.println("...done");
  }
}

/** 
 *  You caught...!
 *  
 *Lord Scenturio: -10 points
 *0254504848515356575654535603
 *Clide: 7 points
 *0254504848515657566667556903
 *Henry: 7 points
 *0254504848515653566848685003
 *Gus: 7 points
 *0254504848515668485052656903
 *Peter: 7 points
 *0254504848515668485165664803
 *Rufus: 7 points
 *0254504848515657575450654903
 *Margaret: 7 points
 *0254504848515653566848685003
 *
 *16 decoy fish, each worth 1 point
 *2 octopuses, each worth 10 points
 *2 starfish, each worth 5 points
 *
 **/
 

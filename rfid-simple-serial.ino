// This code was cobbled together in a hurry. But it does the job.
// DON'T FORGET TO UNPLUG THE DATA LINES FROM PINS 0 AND 1 WHEN UPLOADING
// When connected, it will spit out the serial number and some otehr data as soon as
// a tag is scanned.

long timeout = 0;     // This timeout allows us to put a newline between all the scans

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {                     // Do this whenever this is data coming in the serial port, pins 0&1
    int dataFromLine = Serial.read();           // Put that data in an integer so we can work with it
    if (dataFromLine < 10){                     // If the data is under ten, print a zero so we get leading zeroes on our data
      Serial.print("0");
    }
    Serial.print(dataFromLine);                 // Print the received data to our USB serial port
    timeout = (millis() + 5);                   // Wait five milliseconds for any new data
  }
  if ((millis() > timeout) && timeout != 0){    // If no new data arrives, print a single newline
    Serial.println("");
    timeout = 0;
  }
}

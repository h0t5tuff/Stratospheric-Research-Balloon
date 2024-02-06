#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SPI.h>
#include <SD.h>

File myFile;


/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

#define backgroundField 506L // Analog output with no applied field, calibrate this
#define conversionFactor 1563L  // For SS495B: 3.125mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1563mG


float calibrate(float val, float min, float max){
    float reference_high = -9.80665;
    float reference_low = 9.80665;
    float reference_range = reference_high - reference_low;
    float raw_range = max - min; 
    float calibrated = (((val - min) * reference_range) / raw_range) + reference_low;
    return calibrated;
}

void measure_magnetic_field(File file)
{
// measure magnetic field
  int raw = analogRead(0);   // Range : 0..1024

//  Uncomment this to get a raw reading for calibration of no-field point
  Serial.print("Raw reading: ");
  Serial.println(raw);

  long calibrated = raw - backgroundField;                 // adjust relative to no applied field 
  long b_field = calibrated * conversionFactor / 1000;   // adjust scale to Gauss

  file.println(b_field);
}



void setup(void) 
{

  Serial.begin(9600);
  Serial.println("Adafruit accelerometer library basic test!");
   /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }

  myFile = SD.open("data.csv", FILE_WRITE);

  if (myFile) {
      myFile.println("time (ms),x (m/s^2),y (m/s^2),z (m/s^2),B (Guass)");
      myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
}


void loop(void) 
{

  

  myFile = SD.open("data.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
  /* Get a new sensor event */ 
    sensors_event_t event; 
    accel.getEvent(&event);
 
    /* Display the results (acceleration is measured in m/s^2) */

    
    myFile.print(millis()); myFile.print(",");
    myFile.print(calibrate(event.acceleration.x, -10.12, 10.47)); myFile.print(",");
    myFile.print(calibrate(event.acceleration.y, -10.16, 10.32)); myFile.print(",");
    myFile.print(calibrate(event.acceleration.z, -10.98, 8.90));  myFile.print(",");
    
    measure_magnetic_field(myFile);
       
    delay(1000);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  
}

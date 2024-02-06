#define backgroundField 506L    // Analog output with no applied field, calibrate this

// This is used to convert the analog voltage reading to milliGauss
// #define conversionFactor 3756L  // For A1302: 1.3mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 3756mG
#define conversionFactor 1563L  // For SS495B: 3.125mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1563mG

void setup() 
{
  Serial.begin(9600);
}

void DoMeasurement()
{
// measure magnetic field
  int raw = analogRead(0);   // Range : 0..1024

//  Uncomment this to get a raw reading for calibration of no-field point
  Serial.print("Raw reading: ");
  Serial.println(raw);

  long calibrated = raw - backgroundField;                 // adjust relative to no applied field 
  long b_field = calibrated * conversionFactor / 1000;   // adjust scale to Gauss

  Serial.print(b_field);
  Serial.println(" Gauss ");

}

void loop() 
{
    delay(1000);
    DoMeasurement();
}

// variable name A0 as our input  
int analogInput = 0;

// declare variables
float v_out = 0.00;
float v_in = 0.00;
float R1 = 10000.0;
float R2 = 1000.0;

// initialize the value we will read in on pin A0
int val = 0;

void setup() {
  // put your setup code here, to run once:

  // define A0 for input
  pinMode(analogInput, INPUT); 

  // speed of serial communication 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // get the bit value input from pin A0
  val = analogRead(analogInput);

  // convert the bit value to decimal value (10 bits)
  v_out = ( val * 5.00)/1024.00;

  // calculate the source voltage based on the input to arduino
  v_in = v_out/ (R2/(R1 + R2));

  // write the results to screen (serial monitor)
  Serial.print("\t Source Voltage: ");
  Serial.println(v_in);

  //wait 5 seconds to update 
  delay(3000);
}

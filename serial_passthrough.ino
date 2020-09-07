void setup() {
  // Open Seriall communications and wait for port to open:
  Serial1.begin(115200);
  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for Seriall port to connect. Needed for native  port only
  }


  Serial.println("Goodnight moon!");


}

void loop() { // run over and over
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}



// void setup() {
//   Serial.begin(115200);
  
//   // Define the LED pin as Output
//   pinMode (13, OUTPUT);
  
//   Serial.println("Arduino UART Receiver");
//   Serial.println("-----------------------------");
    
// }


// void loop() {

//   digitalWrite(13, LOW); 
//   //wait until something is received
//   while(! Serial.available());
//   digitalWrite(13, HIGH); 
//   //read the data
//   char in_read=Serial.read();
//   //print the data
//   Serial.print(in_read);

// }

#include <SoftwareSerial.h>

// Create a SoftwareSerial object on pins 2 (RX) and 3 (TX)
SoftwareSerial mySerial(2, 3); // RX = D2, TX = D3

void setup() {
  mySerial.begin(115200); // UART to STM32
  Serial.begin(115200);   // USB Serial to Serial Monitor
  
  pinMode(13, OUTPUT);

  Serial.println("Arduino UART Receiver on D2");
  Serial.println("-----------------------------");
}

void loop() {
  digitalWrite(13, LOW);

  // Wait until something is received from STM32
  if (mySerial.available()) {
    digitalWrite(13, HIGH);
    
    // Read one byte
    char in_read = mySerial.read();
    
    // Send it to the PC Serial Monitor
    Serial.print(in_read);
  }
}


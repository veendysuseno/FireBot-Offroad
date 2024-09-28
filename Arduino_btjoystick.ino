#include <Servo.h> 

Servo myservo;
int pos = 0;      // Servo position
int i = 140;      // Initial servo position for proper operation

#define semprotan 9 // Define spray pin

char val; // Variable to read data from Bluetooth

// Motor pin allocations
int M11 = 5; 
int M12 = 3;
int M21 = 11;                     
int M22 = 6; 

// Servo angles for opening and closing
int maxclose = 140;
int maxopen = 70;

void setup(){
  Serial.begin(9600); // Activate serial monitor in Arduino GUI
  
  // Motor pin setup
  pinMode(M11, OUTPUT); 
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT); 

  // Spray pin setup
  pinMode(semprotan, OUTPUT);
  digitalWrite(semprotan, HIGH); // Default spray off

  myservo.attach(10); // Attach servo to pin 10
  myservo.write(i);   // Set initial position of the servo
}

void loop(){
  if (Serial.available()){
    val = Serial.read(); // Read data from Bluetooth
  }

  Serial.println(val); // Print the value to serial monitor for debugging

  // Servo control based on Bluetooth input
  if (val == '7'){
    CLOSE();
  } else if (val == '8'){
    OPEN();
  }

  // Motor control
  if (val == '4'){
    FW();
  } else if (val == '2'){
    RR();
  } else if (val == '1'){
    RL();
  } else if (val == '3'){
    BW();
  } else if (val == '5'){
    ROT();
  } else if (val == '6'){
    MX();
  } else if (val == 'A'){
    digitalWrite(semprotan, LOW); // Activate spray
  } else if (val == '9'){
    digitalWrite(semprotan, HIGH); // Deactivate spray
  } else {
    STOP(); // Stop all motors if no valid input
  }
}

// Rotate Right    
void RR(){
    analogWrite(M11, 200);
    analogWrite(M12, 0);    // Motor 1 backward
    
    analogWrite(M21, 0);
    analogWrite(M22, 200);  // Motor 2 forward   
}

// Rotate Left
void RL(){
    analogWrite(M11, 0); 
    analogWrite(M12, 200);  // Motor 1 forward
    
    analogWrite(M21, 200); 
    analogWrite(M22, 0);    // Motor 2 backward
}

// Forward
void FW(){
    analogWrite(M11, 0);
    analogWrite(M12, 200);  // Motor 1 forward
    
    analogWrite(M21, 0); 
    analogWrite(M22, 200);  // Motor 2 forward
}   

// Max Speed
void MX(){
    analogWrite(M11, 255);
    analogWrite(M12, 0);    // Motor 1 forward
    
    analogWrite(M21, 255); 
    analogWrite(M22, 0);    // Motor 2 forward
}

// Backward
void BW(){
    analogWrite(M11, 200);
    analogWrite(M12, 0);    // Motor 1 backward
    
    analogWrite(M21, 200); 
    analogWrite(M22, 0);    // Motor 2 backward
}
  
// Fast Rotate
void ROT(){
    analogWrite(M11, 255);
    analogWrite(M12, 0);    // Motor 1 forward
    
    analogWrite(M21, 0); 
    analogWrite(M22, 255);  // Motor 2 backward
}

// Stop all motors
void STOP(){
    analogWrite(M11, 0);
    analogWrite(M12, 0);    // Stop Motor 1
    
    analogWrite(M21, 0); 
    analogWrite(M22, 0);    // Stop Motor 2
}

// Open the servo
void OPEN(){
  if (i > maxopen){
    i -= 1;
    myservo.write(i); // Move the servo
    delay(15);        // Give time for the servo to move
  }
}

// Close the servo
void CLOSE(){
  if (i < maxclose){
    i += 1;
    myservo.write(i); // Move the servo
    delay(15);        // Give time for the servo to move
  }
}
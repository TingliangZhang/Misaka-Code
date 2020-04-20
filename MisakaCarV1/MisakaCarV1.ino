/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Using DRV8825
// D6-D12 PWM Pin
// D6 : the Step input to the driver. Low to high transition means to step  
// D7 : the Direction input the driver. High means forward.

// Unit : Step or Step per second
// If one step is 1.8 degree, one round is 360/1.8 = 200 step. 


// Define stepper motor connections and steps per revolution:

#define stepPin1 6
#define dirPin1 7
#define stepPin2 8
#define dirPin2 9
#define stepPin3 10
#define dirPin3 11

// Clock Error
#define TimeScale 16

#define stepsPerRevolution 200

float speedabs = 0;
float MicrosecondsDelay = 0;

float SetSpeed(int dirPin, int stepPin, float stepperspeed)
{
  if (stepperspeed >= 0)
  {
    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);
    speedabs = stepperspeed;
  }
  else
  {
    // Set the spinning direction clockwise:
    digitalWrite(dirPin, LOW);
    speedabs = - stepperspeed;   
  }
  return speedabs;
}


void Run()
{
  //Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) 
  {
    // These four lines result in 1 step:
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500/TimeScale);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500/TimeScale);
  }
}


void setup() {
  // Declare pins as output:
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
}

void loop() {
  SetSpeed(dirPin1, stepPin1, 100);
  SetSpeed(dirPin2, stepPin2, 100);
  SetSpeed(dirPin3, stepPin3, 100);

  Run();
}

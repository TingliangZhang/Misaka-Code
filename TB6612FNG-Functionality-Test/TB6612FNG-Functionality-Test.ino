
                        //define the two direction logic pins and the speed / PWMA and PWMB pin
const int PWMA = 3;     // Front Motor (A)
const int AIN1 = 5;
const int AIN2 = 7;
                        // Rear  Motor (B)
const int PWMB = 2;
const int BIN1 = 4;
const int BIN2 = 6;

const int STBY = 9;

void setup()
{
                        // Motor A : set all pins as output
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

                        // Motor B : set all pins as output
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
}

void loop()
{
  digitalWrite(STBY, HIGH);
                        //drive forward at full speed by pulling AIN1/BIN1 High
                        //and AIN2/BIN2 low, while writing a full 255 to PWMA/PWMB to
                        //control speed
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 255);

                        //wait 1 second
  delay(1000);

                        //Brake the motorS by pulling both direction pins to
                        //the same state (in this case LOW). PWMA/PWMB doesn't matter
                        //in a brake situation, but set as 0.
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);

                        //wait 1 second
  delay(1000);

                        //change direction to reverse by flipping the states
                        //of the direction pins from their forward state at lower speed
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 150);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 150);

                        //wait 1 second
  delay(1000);

                        //Brake again
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);

                        //wait 1 second
  delay(1000);
}

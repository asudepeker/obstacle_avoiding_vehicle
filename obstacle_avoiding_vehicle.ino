// Define ultrasonic sensor pins
#define r_echoPin 12
#define r_trigPin 13
#define f_echoPin 11
#define f_trigPin 10

// Define motor control pins
#define MotorR1 5
#define MotorR2 4
#define MotorRE 3
#define MotorL1 7
#define MotorL2 6
#define MotorLE 9

float distance_r = 0;
float distance_f = 0;

void setup() 
{ // Set ultrasonic sensor pins
  pinMode(r_echoPin, INPUT);
  pinMode(r_trigPin, OUTPUT);
  pinMode(f_echoPin, INPUT);
  pinMode(f_trigPin, OUTPUT);

  // Set motor pins as output
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() 
{
  distance_f = measure_distance(f_trigPin, f_echoPin);

  if (distance_f > 30 || distance_f == 0) 
  {
    forward();
  } 
  else if (distance_f < 10) 
  {
    backward();
    delay(200);
  } 
  else 
  {
    stop();
    comparison();
    delay(100);
  }
}

float measure_distance(int trigPin, int echoPin) 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  return duration / 29.1 / 2.0;
}

void forward() 
{
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 250);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 250);
}

void turnRight() 
{
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 500);
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 500);
}

void turnLeft() 
{
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 500);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 500);
}

void backward() 
{
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 200);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 200);
}

void stop() 
{
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}

void comparison() 
{
  distance_r = measure_distance(r_trigPin, r_echoPin);

  if (distance_r > 30) 
  {
    turnRight();
    delay(300);
  } 
  else 
  {
    turnLeft();
    delay(300);
  }
}
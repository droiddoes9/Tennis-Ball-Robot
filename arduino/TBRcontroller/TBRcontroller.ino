const int xPin = A0;
const int yPin = A1;
const byte switchPin = 2;
const int right = 9;
const int left = 3;
const int collector = 7;

double maxPower = .4;
double leftPower = 0;
double rightPower = 0;
volatile bool collectOn = false;

volatile int counter = 0;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double updateJoy(int pin){
  if(superMap(analogRead(pin),0,1024,1,-1)>-.03&&superMap(analogRead(pin),0,1024,1,-1)<.03){
    return 0.0;
  }
  else{
    return superMap(analogRead(pin),0,1024,-(maxPower),maxPower);
  }
}
void updatePowers(){
  //LEFT
  double leftAxes = updateJoy(yPin) + updateJoy(xPin)/1.5; //1.35
  
  if (leftAxes>=maxPower) //left
    leftPower = maxPower;
    
  else if (leftAxes<=-maxPower) //left
    leftPower = -maxPower;
    
  else
    leftPower = leftAxes;
  
  //RIGHT
  double rightAxes = updateJoy(yPin) - updateJoy(xPin)/1.5; //.45
  
  if (rightAxes>=maxPower) //right
    rightPower = maxPower;

  else if (rightAxes<=-maxPower)//right
    rightPower = -maxPower;
    
  else
    rightPower = rightAxes;
    
  rightPower = ((rightPower+1)/2)*255;
  leftPower = ((leftPower+1)/2)*255;
}
void collectorTrigger(){
  if (collectOn){
    digitalWrite(collector, LOW);
    collectOn = false;
    maxPower = .4;
    //Serial.print("WORKSON");
  }
  else{
    digitalWrite(collector, HIGH);
    collectOn = true;
    maxPower = .25;
    //Serial.print("WORKSOFF");
  }
  
  while(digitalRead(switchPin) == LOW){}
}

void setup() {
  // put your setup code here, to run once:
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
pinMode(switchPin, INPUT_PULLUP);
pinMode(left, OUTPUT);
pinMode(right, OUTPUT);
pinMode(collector, OUTPUT);
attachInterrupt(digitalPinToInterrupt(2),&collectorTrigger,FALLING);

//Serial.begin(115200);

}

void loop() {
  updatePowers();
  analogWrite(right, (int)rightPower);
  analogWrite(left, (int)leftPower);
  
  
}

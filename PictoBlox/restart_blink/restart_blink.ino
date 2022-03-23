//Gloabl Variables are declared here
#define SWICH_PIN 8
#define BREATH_LED 11
bool status=false;    //start or stop
float breath_speed=0.001;  //second
//User Defined Functions
void check_status(){
  if(digitalRead(SWICH_PIN)==LOW){
    status=(!status);
    delay(300);
  }
  if(!status)    analogWrite(BREATH_LED, 0);
  digitalWrite(LED_BUILTIN, status);
}
void setup() {
  //put your setup code here, to run once:
  pinMode(SWICH_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BREATH_LED, OUTPUT);
  check_status();
}

void loop() {
  //put your main code here, to run repeatedly:
  for(int i = 0; i < 256 && status; i++) {
    analogWrite(BREATH_LED, i);
    check_status();
    delay(breath_speed * 1000);
  }
  for(int i = 255; i >= 0 && status; i--) {
    analogWrite(BREATH_LED, i);
    check_status();
    delay(breath_speed * 1000);
  }
  check_status();
}

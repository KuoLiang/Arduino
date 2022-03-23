//Gloabl Variables are declared here
#define SWICH_PIN 8
#define BREATH_LED 11
bool status=false;    //start or stop
//User Defined Functions
void check_status(){
  if(digitalRead(SWICH_PIN)==LOW){
    status=(!status);
    delay(300);
  }
  if(!status){
    analogWrite(BREATH_LED, 0);
//    break;
  }
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
  digitalWrite(LED_BUILTIN, status);
  for(int i = 0; i < 256 && status; i++) {
    analogWrite(BREATH_LED, i);
    check_status();

    delay(0.01 * 1000);
  }
  digitalWrite(LED_BUILTIN, status);
  for(int i = 256; i > 0 && status; i--) {
    analogWrite(BREATH_LED, i);
    check_status();
    if(!status){
      analogWrite(BREATH_LED, 0);
      break;
    }
    delay(0.01 * 1000);
  }
  check_status();
}

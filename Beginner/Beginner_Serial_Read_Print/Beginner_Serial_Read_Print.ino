void setup() {
  // put your setup code here, to run once:
char c=NULL;
//Serial.begin(115200);
Serial.begin(9600);

Serial.write("hello1");
Serial.println("hello2");
Serial.print("hello3");

pinMode(2, OUTPUT);    // sets the digital pin 2 as output
pinMode(13, OUTPUT);    // sets the digital pin 13 as output
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char x = Serial.read();
    //int x = Serial.read();
    Serial.print(x); 
  }
  //Serial.print("test");
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,false);
  delay(1000);

  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,false);
  delay(1000);
}

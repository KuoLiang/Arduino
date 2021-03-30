void setup() {
  // put your setup code here, to run once:
char c=NULL;
Serial.begin(115200);
//Serial.begin(9600);

Serial.write("hello1");
Serial.println("hello2");
Serial.print("hello3");
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
}

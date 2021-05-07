#define outputA 2 
#define outputB 3 
#define SW 4
int counter = 0; 
int a_Now; 
int a_Last; 

void setup() { 
  pinMode (outputA,INPUT); 
  pinMode (outputB,INPUT); 
  pinMode (SW,INPUT_PULLUP); 
  Serial.begin (9600); 
  
  a_Last = a_Now = digitalRead(outputA); //初始
} 


void loop() { 
    a_Now = digitalRead(outputA); //
    if (digitalRead(SW)==LOW)
    {
      Serial.println("Reset");
      counter=0;
      delay(300);
    }
    if (a_Now != a_Last)//A 改變，可能順也可能逆 //A 改變，可能順也可能逆 
    { 
    
      if (digitalRead(outputB) != a_Now) { //如果 AB不同則順；AB相同則逆
        counter ++; //計數器+1，但會有兩次
      } 
      else {
        counter --; //計數器-1，但會有兩次，但會有兩次
      }
      Serial.print("Position: "); // Position: 
      Serial.print(counter); //跳兩次的值
      Serial.print("/");
      Serial.println(counter/2);//真正的值
    }
    
    a_Last = a_Now; //
}

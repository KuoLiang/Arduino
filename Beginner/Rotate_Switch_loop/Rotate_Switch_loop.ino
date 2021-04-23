

#define outputA 2 //pin 2
#define outputB 3 //pin 3
#define click_sw 4 // pin 4
int counter = 0; 
int aState; 
int aLastState; 

void setup() 
{ 
  pinMode (outputA,INPUT); 
  pinMode (outputB,INPUT); 
  pinMode (click_sw,INPUT_PULLUP); 
  Serial.begin (9600); 

aLastState = digitalRead(outputA); 
} 


void loop() 
{ 

  if(!digitalRead(click_sw))
  {
    
    Serial.println("RESET");
    counter=0;
    delay(300);
  }
  
  
  aState = digitalRead(outputA); //將outputA的讀取值 設給 aState
  
  if (aState != aLastState){ //條件判斷，當aState 不等於 aLastState時發生 

    if (digitalRead(outputB) != aState) 
      { //條件判斷，當outputB讀取值 不等於 aState時發生
        counter ++; //計數器+1
      } 
    else 
      {
        counter --; //計數器-1
      }
  Serial.print("Position: "); //透過serial印出字串 Position: 
  Serial.println(counter); //透過serial印出 counter 值
  
  }
  
  aLastState = aState; //將aState 最後的值 設給 aLastState
}

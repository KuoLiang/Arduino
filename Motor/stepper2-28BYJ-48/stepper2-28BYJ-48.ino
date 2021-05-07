#include <Unistep2.h>

Unistep2 stepper(8, 9, 10, 11, 4096, 1000);// IN1, IN2, IN3, IN4, 總step數, 每步的延遲(in micros)

void setup()
{

}

void loop()
{

  stepper.run();  //步進機啟動

  if ( stepper.stepsToGo() == 0 )
  {
    delay(500);
    stepper.move(4096);    //正轉一圈
    //stepper.move(-4096/2);  //負數就是反轉，反轉一圈
  }

}

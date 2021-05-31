float mydelay(int x)
{
  float delay_time;
  delay_time=float(x)/6;
  Serial.println(delay_time);
  return delay_time;

  //return 1;
}

void run_7sec()
{
    digitalWrite(stop_LED,LOW);
    for(int i=0;i<6;i++)
    {
      for(int j=0;j<6;j++)
      {
        digitalWrite(LED[j],LOW); //clear all
      }
      digitalWrite(LED[i],HIGH);
      //Serial.println(LED[i]);
      delay(mydelay(i)*500);
    }
    digitalWrite(stop_LED,HIGH);

}

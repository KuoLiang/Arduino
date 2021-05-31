
BLYNK_WRITE(V7) //start 
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  start=pinValue;
}
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[0]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[0]=pinValue;
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[1]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[1]=pinValue;
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[2]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[2]=pinValue;
}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[3]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[3]=pinValue;
}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[4]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[4]=pinValue;
}
BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[5]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[5]=pinValue;
}

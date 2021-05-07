// 動手做6-1：連接 LED 七段顯示器與Arduino板
// 詳細的程式說明，請參閱6-5頁。

byte index = 0;
/*const byte LEDs[10] = {
    B1111110,
    B0110000,
    B1101101,
    B1111001,
    B0110011,
    B1011011,
    B1011111,
    B1110000,
    B1111111,
    B1111011};
    //以上共陰
*/const byte LEDs[10] = {
    B0000001,
    B1001111,
    B0010010,
    B0000110,
    B1001100,
    B0100100,
    B0100000,
    B0001111,
    B0000000,
    B0000100};
    //以上共陽
    
void setup()
{
 DDRD= B11111111;
}
void loop()
{
    
  PORTD = LEDs[index];
  index++;
  if (index == 10)
  {
    index = 0;
  }
  delay(1000);
}

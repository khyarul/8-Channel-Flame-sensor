/*Sentinel Array Flame Sensor 8 Channel 
 *Programmed by Khyarul Arham - SENTINEL
 *This program is to read digital output of flame sensor
 *The digital output is need to be converted by comparator before it send to the microcontroller, 
 *the comparator IC much slower than the multiplexer IC, so it needs some delay to do that
 *Therefore delay AFTER switch the channel and BEFORE read is very necessary...!
*/
#define S0 13
#define S1 A0
#define S2 A1
#define DOUT A2

bool bit_flame[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte array_flame = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  pinMode(DOUT, INPUT);
}

void loop()
{
  for (byte index = 0; index <= 7; index++) {
    mux_flame(index);       //switch channel
    delayMicroseconds(20);  //give time for comparator to convert before arduino read it, 
    bit_flame[index] = digitalRead(DOUT);  //then read
  }
  //array_flame = bit_flame[0] * 1 + bit_flame[1] * 2 + bit_flame[2] * 4 + bit_flame[3] * 8 + bit_flame[4] * 16 + bit_flame[5] * 32 + bit_flame[6] * 64;  //make into 1 variable
  //Serial.println(array_flame, BIN);   //print array in bit
  Serial.println(bit_flame[7]);
  Serial.print(bit_flame[6]); Serial.print(bit_flame[5]); Serial.print(bit_flame[4]); Serial.print(bit_flame[3]); Serial.print(bit_flame[2]); Serial.print(bit_flame[1]); Serial.println(bit_flame[0]);
  //delay(100);
}

void switch_flame(bool c, bool b, bool a) {
  digitalWrite(S0, a);
  digitalWrite(S1, b);
  digitalWrite(S2, c);
}

void mux_flame(byte switching) {
  switch (switching) {
    case 0:
      switch_flame(0, 0, 0);
      break;
    case 1:
      switch_flame(0, 0, 1);
      break;
    case 2:
      switch_flame(0, 1, 0);
      break;
    case 3:
      switch_flame(0, 1, 1);
      break;
    case 4:
      switch_flame(1, 0, 0);
      break;
    case 5:
      switch_flame(1, 0, 1);
      break;
    case 6:
      switch_flame(1, 1, 0);
      break;
    case 7:
      switch_flame(1, 1, 1);
      break;
  }
}

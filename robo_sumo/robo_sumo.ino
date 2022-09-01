#include <Ultrasonic.h> //https://github.com/ErickSimoes/Ultrasonic

#define M1A 2
#define M2A 3
#define M1B 4
#define M2B 5

#define BRS 8  // back right sensor
#define BLS 9  // back left sensor
#define FRS 10 // front right sensor
#define FLS 11 // front left sensor

const int arena = 60;

void go_forward();
void go_backward();
void turn(int direcao);

bool identify_enemy();
bool identify_edge();

Ultrasonic ultrasonic(7, 6);

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

}

void go_forward()
{
  digitalWrite(M1A, 1);
  digitalWrite(M2A, 0);

  digitalWrite(M1B, 0);
  digitalWrite(M2B, 1);
}

void go_backward()
{
  digitalWrite(M1A, 0);
  digitalWrite(M2A, 1);

  digitalWrite(M1B, 1);
  digitalWrite(M2B, 0);
}

void turn(int direcao)
{
  if (direcao == 0)
  {
    digitalWrite(M1A, 1);
    digitalWrite(M2A, 0);

    digitalWrite(M1B, 1);
    digitalWrite(M2B, 0);
  }
  else
  {
    digitalWrite(M1A, 0);
    digitalWrite(M2A, 1);

    digitalWrite(M1B, 0);
    digitalWrite(M2B, 1);
  }
}

bool identify_enemy()
{
  if (ultrasonic.read(CM) <= arena)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool identity_edge()
{
  bool brs = !digitalRead(BRS);
  bool bls = !digitalRead(BLS);
  bool frs = !digitalRead(FRS);
  bool fls = !digitalRead(FLS);
  return brs || bls || frs || fls;
}

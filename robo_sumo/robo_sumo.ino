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
void turn(char direcao);

void attack();
void look_for_enemy();

bool identify_enemy();

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
  if(!identify_enemy())
  {
    look_for_enemy();
  }
  else
  {
    attack();
  }
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

void turn(char direcao)
{
  if (direcao == 'r')
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

void attack()
{
  bool frs = !digitalRead(FRS);
  bool fls = !digitalRead(FLS);
  if (!frs && !fls)
  {
    go_forward();
  }
}

bool left_turn = false;
bool right_turn = false;

unsigned int turn_time = 0;
bool may_have_enemy = true;
int tolerance_time = 6000;

void look_for_enemy()
{
  bool brs = !digitalRead(BRS);
  bool bls = !digitalRead(BLS);
  bool frs = !digitalRead(FRS);
  bool fls = !digitalRead(FLS);

  // evitar cair
  if (brs && bls) // ambos traseiros
  {
    go_forward();
  }

  if (frs && fls) // ambos dianteiros
  {
    go_backward();
  }

  if (may_have_enemy)
  {
    //busca de fato
    if (!left_turn && !right_turn)
    {
      turn_time = millis();
    }
    
    if (!bls && !fls && !left_turn)
    {
      turn('l');
    }
    else
    {
      left_turn = true;
      turn_time = millis();
    }
    
    if (!brs && !frs && !right_turn && left_turn)
    {
      turn('r');
    }
    else
    {
      right_turn = true;
    }
    
    if (left_turn && right_turn)
    {
      turn('l');
      delay(turn_time/2);
      go_forward();
      delay(500);
      left_turn = false;
      right_turn = false;
    }

    if (turn_time >= tolerance_time)
    {
      may_have_enemy = false;
    }
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

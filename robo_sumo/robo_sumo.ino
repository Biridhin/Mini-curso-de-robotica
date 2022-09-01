#define M1A 2
#define M2A 3
#define M1B 4
#define M2B 5

void go_forward();
void go_backward();
void turn(int direcao);

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

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

#include <Ultrasonic.h> //https://github.com/ErickSimoes/Ultrasonic

// Motor
#define M1A 2
#define M2A 3
#define M1B 4
#define M2B 5

// Sensor de linha
#define BR A0
#define BL A1
#define FL A2
#define FR A3

// Ultrassom
#define trigger 7
#define echo 6

Ultrasonic ultrasonic(trigger, echo);
const int field_of_view = 30;

//==================================================================
class Sensor
{
  private:
    int base_value;
    int pin;
    int tolerance;
  public:
    Sensor(int pin, int tolerance)
    {
      this->base_value = analogRead(pin);
      this->pin = pin;
      this->tolerance = tolerance;
    }

    bool find_line()
    {
      int current_value = analogRead(pin);
      if (abs(base_value - current_value) >= tolerance)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
};


void go_direction(char direcao);
void attack();
void look_for_enemy();

bool identify_enemy();

void debug_line_sensor();
void debug_ultrasonic_sensor();

//==================================================================
void setup()
{
  pinMode(M1A, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2B, OUTPUT);

  pinMode(BR, INPUT);
  pinMode(BL, INPUT);
  pinMode(FR, INPUT);
  pinMode(FL, INPUT);

  Serial.begin(9600);
}

Sensor BRS(BR, 50);
Sensor BLS(BL, 50);
Sensor FRS(FR, 50);
Sensor FLS(FL, 50);

//==================================================================
void loop()
{
  if (identify_enemy())
  {
    attack();
  }
  else
  {
    look_for_enemy();
  }

  //debug_line_sensor();
  //debug_ultrasonic_sensor();
}

//==================================================================
bool identify_enemy()
{
  if (ultrasonic.read(CM) <= field_of_view)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//==================================================================
void attack()
{
  if (!FRS.find_line() and !FLS.find_line())
  {
    go_direction('f');
  }
  else
  {
    go_direction('p');
  }
}

//==================================================================
bool left_turn = false;
bool right_turn = false;
unsigned int turn_time = 0;
void look_for_enemy()
{
  if (!BRS.find_line() and !FLS.find_line() and !left_turn)
  {
    go_direction('l');
  }
  else if (!left_turn)
  {
    go_direction('p');
    left_turn = true;
    turn_time = millis();
  }
  
  if (!BLS.find_line() and !FRS.find_line() and left_turn and !right_turn)
  {
    go_direction('r');
  }
  else if (!right_turn)
  {
    go_direction('p');
    right_turn = true;
    
  }

  if (left_turn and right_turn)
  {
    go_direction('l');
    delay((millis() - turn_time));
    go_direction('p');
    delay(50);
    go_direction('f');
    delay(500);
    go_direction('p');
    left_turn = false;
    right_turn = false;
  }
}

//==================================================================
void go_direction(char direcao)
{
  if (direcao == 'f')
  {
    digitalWrite(M1A, 0);
    digitalWrite(M2A, 1);

    digitalWrite(M1B, 0);
    digitalWrite(M2B, 1);
  }
  else if (direcao == 'b')
  {
    digitalWrite(M1A, 1);
    digitalWrite(M2A, 0);

    digitalWrite(M1B, 1);
    digitalWrite(M2B, 0);
  }
  else if (direcao == 'r')
  {
    digitalWrite(M1A, 1);
    digitalWrite(M2A, 0);

    digitalWrite(M1B, 0);
    digitalWrite(M2B, 1);
  }
  else if (direcao == 'l')
  {
    digitalWrite(M1A, 0);
    digitalWrite(M2A, 1);

    digitalWrite(M1B, 1);
    digitalWrite(M2B, 0);
  }
  else if (direcao == 'p')
  {
    digitalWrite(M1A, 0);
    digitalWrite(M2A, 0);

    digitalWrite(M1B, 0);
    digitalWrite(M2B, 0);
  }
}

//==================================================================
void debug_line_sensor()
{
  Serial.print("BR: ");
  Serial.print(analogRead(BR));
  Serial.print("  BL: ");
  Serial.print(analogRead(BL));
  Serial.print("  FR: ");
  Serial.print(analogRead(FR));
  Serial.print("  FL: ");
  Serial.println(analogRead(FL));
  delay(500);
}

//==================================================================
void debug_ultrasonic_sensor()
{
  Serial.print("Distância(CM): ");
  Serial.print(ultrasonic.read(CM));
  Serial.print(" cm  ");
  Serial.print("Identified enemy: ");
  Serial.println(identify_enemy());
  delay(500);
}

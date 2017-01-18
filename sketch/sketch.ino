#include <Ultrasonic.h>
#include <Servo.h>
// Сервомотор
Servo servomotor;
Ultrasonic sonar(5, 6);

int motor_L1, motor_L2, input_L;
int motor_R1, motor_R2, input_R;

void setup()
{
  Serial.begin(9600);
  servomotor.attach(9);
  setup_motor_system(3, 4, 11, 7, 8, 10);
  setspeed(0, 0);
}

void loop()
{
  servomotor.write(50);   // Поворот головы до 50 градусов
  delay(500);
  // Расстояние 1 до препятствия в см
  double obstacle1 = sonar.Ranging(CM);
  // Serial.print("Distance 1 = ");
  // Serial.print(obstacle1);
  // Serial.println(" cm");
  if(obstacle1 > 60) // Проверка если Расстояние 1 больше 60 см, то
  {
    setspeed(255, 255);
    forward();
    delay(500);
  } else { // иначе
      _stop();
      delay(2000);
      servomotor.write(150); // Поворот головы до 150 градусов
      delay(500);
      // Расстояние 2 до препятствия в см
      double obstacle2 = sonar.Ranging(CM);
      forward_left();
      delay(500);
  }
}

void setup_motor_system(int L1, int L2, int iL, int R1, int R2, int iR)
{
  motor_L1=L1;
  motor_L2=L2;
  input_L=iL;
  motor_R1=R1;
  motor_R2=R2;
  input_R=iR;
  pinMode(motor_L1, OUTPUT);
  pinMode(motor_L2, OUTPUT);
  pinMode(input_L, OUTPUT);
  pinMode(motor_R1, OUTPUT);
  pinMode(motor_R2, OUTPUT);
  pinMode(input_R, OUTPUT);
}

// Установить скорость колес
void setspeed(int LeftSpeed ,int RightSpeed)  
{
  analogWrite(input_R, RightSpeed);
  analogWrite(input_L, LeftSpeed);
}
  
// Вперед  
void forward()
{
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_L2, HIGH); 
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, LOW); 
}

// Вправо
 void forward_right()
 {
 digitalWrite(motor_L1, LOW);
 digitalWrite(motor_L2, LOW);
 digitalWrite(motor_R1, HIGH);
 digitalWrite(motor_R2, LOW);
 }

 // Влево
 void forward_left()
 {
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
 }

 // Назад
 void backward()
 {
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
 }

 // Стоп
 void _stop ()
 {
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, LOW); 
 }

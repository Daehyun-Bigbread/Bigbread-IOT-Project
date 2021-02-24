// Ultrasonic sensors (초음파)
#define trigPin 3
#define echoPin 4

// Bluetooth
#include <SoftwareSerial.h>
SoftwareSerial mySerial(1, 0); // HC-06 TX=1번핀 , RX=0번핀 연결

// MOTOR
#define motor1EnablePin  7
#define motor1_1        6
#define motor1_2        5
int pwmA;

//Servo Motor
#include <Servo.h>
Servo sv1; //Servo 라이브러리의 sv 객체 선언
Servo sv2;

// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sound
const int SOUND_SENSOR_PIN = A1;
int Sound_sensorValue;

// DHT
#include <DHT.h>
#define DHTTYPE DHT11 // DHT11
#define DHTPIN 13
DHT dht(DHTPIN, DHTTYPE);

// Buzzer
int buzzer = 2;
int freq = 440;     // 부저 음 주파수(Hz)
int duration = 500;  // 부저 음 지속 시간(msec)

// LED
int vResistor = A0;  // A0 핀에 가변저항 연결
int pins_LED[] = {12, 11, 10, 9, 8}; // LED 연결 핀

void setup()
{
  Serial.begin(9600);
// Ultrasonic sensors
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 

  
// LCD
  lcd.init(); // I2C LCD의 초기화
  lcd.backlight(); // I2C LCD 백라이트 ON

// Bluetooth
  mySerial.begin(9600); // 통신 속도 9600bps로 블루투스 시리얼 통신 시작

// DHT
  dht.begin();  

//Servo Motor
  sv1.attach(8); //서보모터(8번핀) 연결

// Buzzer
  pinMode(buzzer, OUTPUT);

// MOTOR
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  analogWrite(motor1EnablePin, 0);

// Power
  pinMode(A0, INPUT);

  //Servo Motor
  int x = analogRead(A2); //A2 입력값 x에 저장
  int y = analogRead(A3); //A3 입력값 y에 저장

  int angle1 = map(x, 0, 1023, 0, 120);
  sv1.write(angle1); //서보모터 8번에 angle1만큼 값 출력

  delay(15);

// LED
    pinMode(vResistor, INPUT);
    for (int i = 0; i < 5; i++)
    {
      pinMode(pins_LED[i], OUTPUT);
      digitalWrite(pins_LED[i], LOW);
    }
}

// Ultrasonic sensors (초음파)
long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}

void loop()
{
// Ultrasonic sensors (초음파)
  long duration, cm;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
  
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
    Serial.print(cm); 
    delay(500);   

  char buf[20];
  snprintf(buf, sizeof(buf), "Distance %4d cm", cm);
  lcd.setCursor(0, 0);
  lcd.println(buf);
  delay(500);

  // DHT
  float tem = dht.readTemperature();

   // 온도와 습도 값을 LCD 모듈에 출력
  lcd.setCursor(0,1);  lcd.print("Temp : "); lcd.setCursor(7,1);  lcd.print(tem,1);   lcd.print(" C"); 

  //Sound
  Sound_sensorValue = analogRead(SOUND_SENSOR_PIN);
  delay(20);

  //Bluetooth
   if (mySerial.available()){
   Serial.write(mySerial.read());
 }
  // Serial 핀에 입력이 들어오면, 바이트단위로 읽어서 블루투스로 출력
 if (Serial.available()){
   mySerial.write(Serial.read());
 }

  // MOTOR
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  analogWrite(motor1EnablePin, 128);

    // Motor Power Control
  pwmA = analogRead(A0)/5;
  analogWrite(motor1EnablePin, pwmA);
  delay(20);


  // LED
      int adc = analogRead(vResistor); // 가변저항 값 읽기
//  int count_led = map(adc, 0, 1023, 0, 4); // LED 개수 결정
    int count_led = adc / 160;    // LED (0~4)  개수 결정
    for (int i = 0; i < 5; i++) { // LED 점멸
        if (i < count_led)
             digitalWrite(pins_LED[i], HIGH);
        else
             digitalWrite(pins_LED[i], LOW);
    }
        delay(10);               // 0.1 초(100ms) 대기

    if(cm < 20)
    {  
    tone(buzzer, freq, duration);

      digitalWrite(motor1_1, LOW);
      digitalWrite(motor1_2, LOW);

      for(int i=0; i<3; i++);
     {
       digitalWrite(buzzer, HIGH); // Buzzer on
       delay(10);     
       digitalWrite(buzzer, LOW); // Buzzer on
       delay(10);
     }
    lcd.clear( );          // LCD화면 지우기  
  }    
  else if(Sound_sensorValue < 20 || Sound_sensorValue > 800)
  {
      digitalWrite(motor1_1, LOW);
      digitalWrite(motor1_2, LOW);
  }
}

#include <DHT.h>
#define DHTPIN 2 // 습도센서 Signal 선 연결
#define DHTTYPE DHT11 // 습도센서 종류: DHT22
#define LEDPIN 7
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2); // LCD주소: 0x27 또는 0x3F
float hum; // 습도값 저장 변수
float temp; // 온도값 저장 변수

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(LEDPIN, OUTPUT);
}
void loop() {
  hum = dht.readHumidity();//온도값 읽기
  temp= dht.readTemperature();//습도값 읽기

  Serial.print("HUMIDITY: "); // "HUMIDITY:" 출력
  Serial.print(hum,0);// 습도 값 소수점 이하 자리 없음
  Serial.print(" %, TEMPERATURE: "); //"%"(습도단위) "TEMPERATURE:" 출력
  Serial.print(temp, 1);//온도값은 소수점 이하 1자리까지 표시
  Serial.println(" C"); //"C" 온도 단위 표시

  lcd.setCursor(0,0); // LCD Cursor 원점
  lcd.print("TEMP:"); // LCD에 "temp" 표시
  lcd.print(temp,1); // 온도값 LCD로 출력
  lcd.print(" C"); // 온도 단위 표시
  lcd.setCursor(0,1); //LCD 커서 줄바꿈
  lcd.print("HUMIDITY:"); //LCD 2번째 줄에 "humidity:" 출력
  lcd.print(hum); //습도값 LCD에 출력
  lcd.print(" % "); //습도 단위 출력
  lcd.println();
  delay(2000); // 샘플링 간격 2초

  if (hum >= 75){
      digitalWrite(LEDPIN, HIGH);
  }
  else (hum < 75){
      digitalWrite(LEDPIN, HIGH);
  }

}
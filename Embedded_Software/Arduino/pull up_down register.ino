const int ledPin = 9;      // LED가 연결된 핀 (PWM 핀)
const int switch1Pin = 2;  // 풀다운 저항을 연결한 택트 스위치 핀
const int switch2Pin = 3;  // 풀업 저항을 연결한 택트 스위치 핀

int brightness = 128;      // LED 밝기 초기값 (0 ~ 255)
int step = 1;              // 밝기 증가 또는 감소 폭

void setup() {
  pinMode(ledPin, OUTPUT);           // LED 핀을 출력으로 설정
  pinMode(switch1Pin, INPUT);        // 풀다운 저항 스위치 핀을 입력으로 설정
  pinMode(switch2Pin, INPUT_PULLUP); // 풀업 저항 스위치 핀을 내부 풀업 저항으로 설정
  
  Serial.begin(9600);                // 시리얼 통신 시작
  analogWrite(ledPin, brightness);   // LED 초기 밝기 설정
  Serial.println("LED Brightness: " + String(brightness));  // 초기 밝기 출력
}

void loop() {
  // 풀다운 저항 스위치가 눌리면 밝기 증가
  if (digitalRead(switch1Pin) == HIGH) {
    brightness += step;
    if (brightness > 255) brightness = 255;  // 최대값 255로 제한
    analogWrite(ledPin, brightness);
    Serial.println("LED Brightness: " + String(brightness)); // 현재 밝기 출력
    delay(200);  // 빠른 입력 방지
  }

  // 풀업 저항 스위치가 눌리면 밝기 감소
  if (digitalRead(switch2Pin) == LOW) {
    brightness -= step;
    if (brightness < 0) brightness = 0;      // 최소값 0으로 제한
    analogWrite(ledPin, brightness);
    Serial.println("LED Brightness: " + String(brightness)); // 현재 밝기 출력
    delay(200);  // 빠른 입력 방지
  }
}
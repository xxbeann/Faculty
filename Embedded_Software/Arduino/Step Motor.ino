#include <Stepper.h>

const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup(){
  myStepper.setSpeed(10);
  // 모터 속도 설정, 모터가 도는 RPM
  // 전력에 따라 스피트를 조절
}

void loop() {
  myStepper.step(1024); //2바퀴 돌릴거면 4096
  delay(1000);
  myStepper.step(-stepsPerRevolution); // - 붙으면 반대로 돌림
  delay(1000);
}
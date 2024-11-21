int button = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_data = digitalRead(button);
  Serial.println(button_data);
}
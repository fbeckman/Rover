void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(5);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
String input;
String old_input;
void loop() {
  input = Serial.readString();
  if (input != old_input) {
    Serial.println(input);
    if (input == "LEDON")
      digitalWrite(LED_BUILTIN, HIGH);
    if (input == "LEDOFF")
      digitalWrite(LED_BUILTIN, LOW);
    old_input = input;
  }
}

char inp;
int ledpin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  Serial.print("hello python dweeb");
  Serial.print("\n");
}

void loop() {
  while (Serial.available()>0) {
    inp = Serial.read();
    Serial.print("you entered " + String(inp));
    Serial.print("\n");
    
    if (inp=='1'){
      digitalWrite(ledpin,HIGH);
      Serial.print("led on ho gya hai");
      Serial.print("\n");
    }
    
    else if (inp=='0'){
      digitalWrite(ledpin,LOW);
      Serial.print("led off ho gya hai");
      Serial.print("\n");
    } 
    delay(100);
  }
}

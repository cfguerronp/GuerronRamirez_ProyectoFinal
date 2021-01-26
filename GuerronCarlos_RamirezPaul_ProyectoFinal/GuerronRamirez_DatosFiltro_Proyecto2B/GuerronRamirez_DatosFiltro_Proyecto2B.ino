/*
 *    Programa Recoleccion de datos
 * Proyecto Segundo Bimestre
 * Integrantes: Carlos Guerron. Paul Ramirez
 * 
 */
int mq135=0;
int mq7=0;
int aireLimpio=8;
int aireConta=9;

void setup() {
  pinMode(aireLimpio, OUTPUT);
  pinMode(aireConta, OUTPUT);
  Serial.begin(9600);
  Serial.println("Recoleccion de datos");
  digitalWrite(aireLimpio, LOW);
  digitalWrite(aireConta, LOW);
  
}

void loop() {
  delay(500);
  mq135=analogRead(A0);
  mq7=analogRead(A1);
  Serial.println(String(mq135)+String(", ")+String(mq7));
  delay(500);
  if(mq135>60 && mq135<200){
    digitalWrite(aireLimpio, HIGH);
    digitalWrite(aireConta, LOW);
    }
   if(mq135>200){
    digitalWrite(aireLimpio, LOW);
    digitalWrite(aireConta, HIGH);
    }
    if(mq7>130 && mq7<300){
    digitalWrite(aireLimpio, HIGH);
    digitalWrite(aireConta, LOW);
    }
    if(mq135>300){
    digitalWrite(aireLimpio, LOW);
    digitalWrite(aireConta, HIGH);
    }
}

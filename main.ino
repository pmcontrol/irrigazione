int res = 13;

int b = A1;

const int A = 9;
const int B = 10;
const int C = 11;
const int D = 12;

int t = A0; // pin potenziometro per regolare tempo

int l1 = 5; // pin led zona1
int l2 = 6; // pin led zona2
int l3 = 7; // pin led zona3
//int l4 = 6 // pin led zona4
//int l5 = 7 // pin led zona5
//int 16 = 8 // pin led zona6
//int l7 = 9 // pin led zona7

int lc = 8; // pin led controllo tempo > 0

unsigned long tempo; // tempo analogRead(t)enziometro (di base = 0)
unsigned long tempo_att = 0; // tempo durata azione (di base = 0)

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  pinMode(res, INPUT);
  //pinMode(z4, INPUT);
  //pinMode(z5, INPUT);
  //pinMode(z6, INPUT);
  //pinMode(z7, INPUT);

  pinMode(b, INPUT);

  pinMode(l1, OUTPUT); // l + numero : led zona => informazione esce (OUTPUT)
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  //pinMode(l4, OUTPUT);
  //pinMode(l5, OUTPUT);
  //pinMode(l6, OUTPUT);
  //pinMode(l7, OUTPUT);
  
  pinMode(lc, OUTPUT); // accesa = tempo scelto; spenta = tempo non scelto

}

void loop() {
  // put your main code here, to run repeatedly

  Serial.print("Val pot : ");
  Serial.println(analogRead(t));
  Serial.print("tempo : ");
  Serial.println(tempo);
  Serial.print("b : ");
  Serial.println(digitalRead(res));
  Serial.println("###");

  delay(2000);

  if (analogRead(t) < 1){
    tempo = 0;
    Serial.println("0 minuti");
  }

  if ( analogRead(t) > 1 && analogRead(t) <325 ){ //posizione 5 min analogRead(t)enziometro

    tempo = 30000; // 30 secondi
    Serial.println("30 secondi"); 
    
  }

  if ( analogRead(t) > 325 && analogRead(t) < 650 ){  //posizione 10 min analogRead(t)enziometro

    tempo = 60000; // 1 minuto
    Serial.println("1 minuto");
    
  }

  if ( analogRead(t) > 650 && analogRead(t) < 975 ){  //posizione 15 min analogRead(t)enziometro

    tempo = 90000; // 1 minuto 30 secondi
    Serial.println("1,5 minuti");
    
  }

  if ( analogRead(t) > 975 ){  //posizione 20 min analogRead(t)enziometro

    tempo = 120000; // 2 minuti
    Serial.println("2 minuti");
    
  }

  if (tempo < 30000){
    digitalWrite(lc, LOW);
  }else{
    digitalWrite(lc, HIGH);
    if (analogRead(b)>0 && analogRead(b)<10){
      
      digitalWrite(l1, HIGH);
      
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 
      
      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(res) == LOW){
          tempo = 0;
        }
      }
      
      digitalWrite(l1, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
    }
    
    if (analogRead(b)>510 && analogRead(b)<520){

      if (digitalRead(res) == LOW){
        tempo = 0;
      }
      
      digitalWrite(l2, HIGH);

      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 

      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(res) == LOW){
          tempo = 0;
        }
      }
      
      delay(tempo);
      digitalWrite(l2, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
    }
    
    if (analogRead(b)>680 && analogRead(b)<690){
      
      digitalWrite(l3, HIGH);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 

      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(res) == LOW){
          tempo = 0;
        }
      }
      
      delay(tempo);
      digitalWrite(l3, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
    }
    
  }
}
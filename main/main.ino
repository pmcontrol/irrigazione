// programma irrigazione S. Marco


int reset = 13; // pin reset tempo
int tastiera1 = A1;  // tastiera zone (

const int A = 9;  // uscita binaria per elettrovalvole
const int B = 10; // uscita binaria per elettrovalvole
const int C = 11; // uscita binaria per elettrovalvole
const int D = 12; // uscita binaria per elettrovalvole

int potenziometro_tempo = A0; // pin potenziometro per regolare tempo

int l1 = 5; // pin led zona1
int l2 = 6; // pin led zona2
int l3 = 7; // pin led zona3
//int l4 = 6 // pin led zona4
//int l5 = 7 // pin led zona5
//int 16 = 8 // pin led zona6
//int l7 = 9 // pin led zona7

int led_timer = 8; // pin led controllo tempo > 0

unsigned long tempo; // tempo analogRead(potenziometro_tempo)enziometro (di base = 0)
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
  pinMode(reset, INPUT);
  //pinMode(z4, INPUT);
  //pinMode(z5, INPUT);
  //pinMode(z6, INPUT);
  //pinMode(z7, INPUT);

  pinMode(tastiera1, INPUT);

  pinMode(l1, OUTPUT); // l + numero : led zona => informazione esce (OUTPUT)
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  //pinMode(l4, OUTPUT);
  //pinMode(l5, OUTPUT);
  //pinMode(l6, OUTPUT);
  //pinMode(l7, OUTPUT);
  
  pinMode(led_timer, OUTPUT); // accesa = tempo scelto; spenta = tempo non scelto

}

void loop() {
  // put your main code here, to run repeatedly

  Serial.print("Val pot : ");
  Serial.println(analogRead(potenziometro_tempo));
  Serial.print("tempo : ");
  Serial.println(tempo);
  Serial.print("tastiera1 : ");
  Serial.println(digitalRead(reset));
  Serial.println("###");

  delay(2000);

  if (analogRead(potenziometro_tempo) < 1){
    tempo = 0;
    Serial.println("0 minuti");
  }

  if ( analogRead(potenziometro_tempo) > 1 && analogRead(potenziometro_tempo) <325 ){ //posizione 5 min analogRead(potenziometro_tempo)enziometro

    tempo = 30000; // 30 secondi
    Serial.println("30 secondi"); 
    
  }

  if ( analogRead(potenziometro_tempo) > 325 && analogRead(potenziometro_tempo) < 650 ){  //posizione 10 min analogRead(potenziometro_tempo)enziometro

    tempo = 60000; // 1 minuto
    Serial.println("1 minuto");
    
  }

  if ( analogRead(potenziometro_tempo) > 650 && analogRead(potenziometro_tempo) < 975 ){  //posizione 15 min analogRead(potenziometro_tempo)enziometro

    tempo = 90000; // 1 minuto 30 secondi
    Serial.println("1,5 minuti");
    
  }

  if ( analogRead(potenziometro_tempo) > 975 ){  //posizione 20 min analogRead(potenziometro_tempo)enziometro

    tempo = 120000; // 2 minuti
    Serial.println("2 minuti");
    
  }

  if (tempo < 30000){
    digitalWrite(led_timer, LOW);
  }else{
    digitalWrite(led_timer, HIGH);
    if (analogRead(tastiera1)>0 && analogRead(tastiera1)<10){
      
      digitalWrite(l1, HIGH);
      
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 
      
      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(reset) == LOW){
          tempo = 0;
        }
      }
      
      digitalWrite(l1, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
    }
    
    if (analogRead(tastiera1)>510 && analogRead(tastiera1)<520){

      if (digitalRead(reset) == LOW){
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

        if (digitalRead(reset) == LOW){
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
    
    if (analogRead(tastiera1)>680 && analogRead(tastiera1)<690){
      
      digitalWrite(l3, HIGH);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 

      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(reset) == LOW){
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

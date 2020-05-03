// programma irrigazione S. Marco


// Ingressi
int potenziometro_tempo = A0; // pin potenziometro per regolare tempo
int tastiera1 = A1;  // tastiera zone 1, 2, 3;
int tastiera2 = A2;  // tastiera zone 4, 5, 6, 7;
int reset = 13; // pin reset tempo


const int A = 9;  // uscita binaria per elettrovalvole (b0)
const int B = 10; // uscita binaria per elettrovalvole (b1)
const int C = 11; // uscita binaria per elettrovalvole (b2)
const int D = 12; // uscita binaria per elettrovalvole (b3)
const int POZZO = 8;  // uscita comando pozzo


int led1 = 5; // pin led zona1
int led2 = 6; // pin led zona2
int led3 = 7; // pin led zona3
//int led4 = 6; // pin led zona4
//int led5 = 7; // pin led zona5
//int 16 = 8; // pin led zona6
//int led7 = 9; // pin led zona7

int led_timer = 8; // pin led controllo tempo > 0

unsigned long tempo; // tempo analogRead(potenziometro_tempo)enziometro (di base = 0)
unsigned long tempo_att = 0; // tempo durata azione (di base = 0)

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(reset, INPUT);
  pinMode(tastiera1, INPUT);
  pinMode(tastiera2, INPUT); 
  //pinMode(z4, INPUT);
  //pinMode(z5, INPUT);
  //pinMode(z6, INPUT);
  //pinMode(z7, INPUT);
   
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  
  pinMode(led_timer, OUTPUT); // accesa = tempo scelto; spenta = tempo non scelto


  pinMode(led1, OUTPUT); // l + numero : led zona => informazione esce (OUTPUT)
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  //pinMode(led4, OUTPUT);
  //pinMode(led5, OUTPUT);
  //pinMode(led6, OUTPUT);
  //pinMode(led7, OUTPUT);

  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
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
    digitalWrite(led_timer, LOW);  // led timer OFF
      
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH); 

    digitalWrite(POZZO, LOW)
    
  }else{
    digitalWrite(led_timer, HIGH);
    if (analogRead(tastiera1)>0 && analogRead(tastiera1)<10){
      
      digitalWrite(led1, HIGH);
      
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 

      digitalWrite(POZZO, HIGH)
          
      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(reset) == LOW){
          tempo = 0;
        }
      }
      
      digitalWrite(led1, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);

      digitalWrite(POZZO, HIGH)
      
    }
    
    if (analogRead(tastiera1)>510 && analogRead(tastiera1)<520){

      if (digitalRead(reset) == LOW){
        tempo = 0;
      }
      
      digitalWrite(led2, HIGH);

      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW); 

      digitalWrite(POZZO, HIGH)

      while(tempo > 0){
        delay(1);
        tempo--;

        if (digitalRead(reset) == LOW){
          tempo = 0;
        }
      }
      
      delay(tempo);
      digitalWrite(led2, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);

      digitalWrite(POZZO, HIGH)
      
    }
    
    if (analogRead(tastiera1)>680 && analogRead(tastiera1)<690){
      
      digitalWrite(led3, HIGH);

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
      digitalWrite(led3, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
    }    
  }
}
// prova

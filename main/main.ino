// programma irrigazione S. Marco
// Modulo trasmettitore


//  composizione byte da trasmettere/ricevere
//
// b7...b4 -- bits linea
// 0001 - linea 1
// 0011 - linea 2
// 0100 - linea 3
// 0101 - linea 4
// 0110 - linea 5
// 0111 - linea 6
// 1000 - linea 7
// b3...b0 -- bits tempo
// 0001 - 30'
// 0011 - 60'
// 0100 - 90'
// 0101 - 120'
// 0110 - 240'
// 0111 - 360'
//
// definizioni linee di irrigazioni  
#define LINEA1 0b0001
#define LINEA2 0b0011
#define LINEA3 0b0100
#define LINEA4 0b0101
#define LINEA5 0b0110
#define LINEA6 0b0111
#define LINEA7 0b1000

// definizioni tempi di irrigazioni  
#define T30  0b0001
#define T60  0b0011
#define T90  0b0100
#define T120 0b0101
#define T240 0b0110
#define T260 0b0111

// deinizioni DISPLAY
#define DISPLAY_0 0
#define DISPLAY_1 1
#define DISPLAY_2 2
#define DISPLAY_3 3
#define DISPLAY_4 4
#define DISPLAY_5 5
#define DISPLAY_6 6
#define DISPLAY_7 7
#define DISPLAY_8 8
#define DISPLAY_9 9

#define B0 11 // bit0 uscita BCD->7segm
#define B1 10 // bit1 ucita BCD->7segm
#define B2 9  // bit2 uscita BCD->7segm
#define B3 8  // bit3 uscita BCD->7segm

#define ARDUINO_UNO

#if defined(ARDUINO_UNO)

// Ingressi
int reset = 13; // pin reset tempo
int potenziometro_tempo = A0; // pin potenziometro per regolare tempo
int tasto1 = 0;
int tasto2 = 1;
int tasto3 = 2;
int tasto4 = 3;
int tasto5 = 4;
int tasto6 = 5;
int tasto7 = 6;

// Uscite
  int ledRun = 7; // pin indicazione led, contatto pozzo
  int rf_out = 12; // uscita comando per modulo RF

// Variabili
  unsigned long tempo; // tempo analogRead(potenziometro_tempo)enziometro (di base = 0)
  unsigned long tempo_att = 0; // tempo durata azione (di base = 0)
  int display_num=0;
  int linea_out=0;
  int tempo_out=0;
    
void setup() {
   // put your setup code here, to run once:

  Serial.begin(9600);

//
// definizione ingressi
//
  pinMode(reset, INPUT);
  pinMode(tasto1, INPUT);
  pinMode(tasto2, INPUT); 
  pinMode(tasto3, INPUT);
  pinMode(tasto4, INPUT);
  pinMode(tasto5, INPUT);
  pinMode(tasto6, INPUT);  
  pinMode(tasto7, INPUT);   

//
// definizione uscite
//
  pinMode(ledRun, OUTPUT);
  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(rf_out, OUTPUT);
  
};

void loop() {

  Serial.print("Val pot : ");
  Serial.println(analogRead(potenziometro_tempo));
  Serial.print("tempo : ");
  Serial.println(tempo);
  Serial.print("tastiera1 : ");
  Serial.println(digitalRead(reset));
  Serial.println("###");
  
  delay(2000);

//
// lettura potenziometro tempo
//
  if (analogRead(potenziometro_tempo) < 1){
  tempo = 0;
  Serial.println("0 minuti");
  }
  if ( analogRead(potenziometro_tempo) > 1 && analogRead(potenziometro_tempo) <325 ){ //posizione 5 min analogRead(potenziometro_tempo)
    tempo = 30000; // 30 secondi
    Serial.println("30 secondi"); 
  }
  if ( analogRead(potenziometro_tempo) > 325 && analogRead(potenziometro_tempo) < 650 ){  //posizione 10 min analogRead(potenziometro_tempo)
    tempo = 60000; // 1 minuto
    Serial.println("1 minuto");
  }
  if ( analogRead(potenziometro_tempo) > 650 && analogRead(potenziometro_tempo) < 975 ){  //posizione 15 min analogRead(potenziometro_tempo)
    tempo = 90000; // 1 minuto 30 secondi
    Serial.println("1,5 minuti");
  }
  if ( analogRead(potenziometro_tempo) > 975 ){  //posizione 20 min analogRead(potenziometro_tempo)
    tempo = 120000; // 2 minuti
    Serial.println("2 minuti");  
  }
  
// 
// Lettura tasti
//
  if (digitalRead(tasto1) == HIGH) {
    display_num = 1; 
    linea_out=1;   
    linea_out=1;   

  } 
  else if (digitalRead(tasto2) == HIGH) {
    display_num = 2;
    linea_out=1;   
    
  }   
  else if (digitalRead(tasto3) == HIGH) {
    display_num = 3;
    linea_out=1;   
   
  }   
  else if (digitalRead(tasto4) == HIGH) {
    display_num = 4;
    linea_out=1;   
    
  }   
  else if (digitalRead(tasto5) == HIGH) {
    display_num = 5;
    linea_out=1;   
    
  } 
  else if (digitalRead(tasto6) == HIGH) {
    display_num = 6;
    linea_out=1;   
    
  } 
  else if (digitalRead(tasto7) == HIGH) {
    display_num = 7;
    linea_out=1;   
    
  } else {
    display_num = 0;
    linea_out=0;
    tempo_out=0;   
  }


//
// parametro_tempo
//

  switch (tempo) {
    case T30 :
      tempo_out=0b0001;
    break;
    case T60 : 
      tempo_out=0b0011;
    break;
    case T90 : 
      tempo_out=0b0100;
    break;
    case T120 :
      tempo_out=0b0101;
    break;
    case T240 :
      tempo_out=0b0110;
    break;
    case T260 :    
      tempo_out=0b0111;
    break;
  }

//
// scrittura comando rf_out
//
  digitalWrite(rf_out,linea_out | tempo_out);
  
//
// uscita display
//
  switch (display_num) {
    case DISPLAY_0:
      digitalWrite(B0, LOW);
      digitalWrite(B1, LOW);
      digitalWrite(B2, LOW);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_1:
      digitalWrite(B0, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, LOW);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_2:
      digitalWrite(B0, LOW);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_3:
      digitalWrite(B0, HIGH);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_4:
      digitalWrite(B0, LOW);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_5:
      digitalWrite(B0, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_6:
      digitalWrite(B0, LOW);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, HIGH);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_7:
      digitalWrite(B0, HIGH);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, HIGH);
      digitalWrite(B3, LOW);
    break;
    case DISPLAY_8:
      digitalWrite(B0, LOW);
      digitalWrite(B1, LOW);
      digitalWrite(B2, LOW);
      digitalWrite(B3, HIGH);
    break;
    case DISPLAY_9:
      digitalWrite(B0, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, LOW);
      digitalWrite(B3, HIGH);
    break;
  }
}


#elif defined(ARDUINO_NANO)
//
// Ingressi
//
  int reset = 13; // pin reset tempo
  int tastiera1 = A1;  // tastiera zone 1, 2, 3;
  int tastiera2 = A2;  // tastiera zone 4, 5, 6, 7;
  int potenziometro_tempo = A0; // pin potenziometro per regolare tempo

//
// Uscite
//
  int ledRun = 7; // pin indicazione led, contatto pozzo

  int led_timer = 7; // pin indicazione led, contatto pozzo
  
  const int A = 9;  // uscita binaria per elettrovalvole (b0)
  const int B = 10; // uscita binaria per elettrovalvole (b1)
  const int C = 11; // uscita binaria per elettrovalvole (b2)
  const int D = 12; // uscita binaria per elettrovalvole (b3)

  int led1 = 5; // pin led zona1
  int led2 = 6; // pin led zona2
  int led3 = 7; // pin led zona3

  
  unsigned long tempo; // tempo analogRead(potenziometro_tempo)enziometro (di base = 0)
  unsigned long tempo_att = 0; // tempo durata azione (di base = 0)

  void setup() {
//
// put your setup code here, to run once:
//
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
      digitalWrite(led_timer, LOW);
    }else{
    digitalWrite(led_timer, HIGH);
    if (analogRead(tastiera1)>0 && analogRead(tastiera1)<10){
      
      digitalWrite(led1, HIGH);
      
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
      
      digitalWrite(led1, LOW);

      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      
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

#else
  #error Unsupported board selection.
#endif



  

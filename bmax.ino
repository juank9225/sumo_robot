//este codigo es exclusivo para el sumo robot veronica la cal fue creada por:
//juan carlos salcedo,luis miguel yances,silvio angel,carlos cardales ,jorge coronado
//.................................................................
//sensor linea blanca  ...................................................
int pinSensorLuz1 = 2;
int valorSensorLuz1 = 0;
int valorSensorLuz1anterior = -1;
//...................
int pinSensorLuz2 = 4;
int valorSensorLuz2 = 0;
int valorSensorLuz2anterior = -1;
//.................................................................
//sensor de sonido HY-SRF05
#define MEDIA_VELOCIDAD_SONIDO 0.017175 // Mitad de la velocidad del sonido a 20 °C expresada en cm/µs
#define PIN_TRIGGER 7
#define PIN_ECHO 10
#define ESPERA_ENTRE_LECTURAS 1000 // tiempo entre lecturas consecutivas en milisegundos
#define TIMEOUT_PULSO 25000 // la espera máxima de es 30 ms o 30000 µs
//creando variables para el sensor HY-SRF05
float distancia;
unsigned long tiempo;
unsigned long cronometro;
unsigned long reloj=0;
//.................................................................
//creando variables para los motores:
int inicio =0;
//crear variable rando giro
int girarinicio;
//.......................
void setup() {
  //detectar linea blaca 
    pinMode(pinSensorLuz1,INPUT);
    pinMode(pinSensorLuz2,INPUT);
    Serial.begin(9600);
  //.........................................
  //declarar las variables para el sensor HY-SRF05
   Serial.begin(9600);
  pinMode(PIN_ECHO,INPUT);
  pinMode(PIN_TRIGGER,OUTPUT);
  digitalWrite(PIN_TRIGGER,LOW); // Para «limpiar» el pulso del pin trigger del módulo
  delayMicroseconds(2);
  //..............................................
  //para controlar los dos motores
  //canal A
  pinMode (3,OUTPUT);//COMO SALIDA(derecha A)
  pinMode (9,OUTPUT);//freno (IZQUIERDA A)
  pinMode (12,OUTPUT);//direccion (VELOCIDAD)
  //canal B 
  pinMode (8,OUTPUT);//COMO SALIDA(DERECHA B)
  pinMode (11,OUTPUT);//freno(IZQUIERDA B)
  pinMode (13,OUTPUT);//direccion (VELOCIDAD)
  //...............................
}

//esta es la funcion que se repita ciclicamente .....
void loop() {
Serial.println(girarinicio);
  iniciar();
  lineadetector2();
  lineadetector1();
  detectearDistancia();
  detectearDistancia();
  if((valorSensorLuz1==1 && valorSensorLuz2==1)&&(distancia>25.00 || distancia==0.00)){
      buscar();
      frenar();
      }
  if(distancia<=25.00 && distancia >0.00){
     motorderecho(); 
      }
  //................................................................................  
  if(valorSensorLuz1==0 || valorSensorLuz2==0){
      motorreversa();
      frenar();
      }
  lineadetector2();
  lineadetector1();
  detectearDistancia();
  detectearDistancia();
}
//final de la funcion que se repite ciclicamente..........
//.....................................................
//iniciar al modo duelo veronica.......

void buscar(){
   girarinicio =random(1,3);//minimo 1 y maximo 2 por lo tanto colocar (1,3)
   if(girarinicio==1){ 
    girarizquierda();
     frenar();}
   if(girarinicio==2){ 
      girarderecha();
      frenar();}
      }
  
void iniciar(){
  if(inicio ==0){
    delay(4888);//tiempo de espera para funcionar en milecimas
    inicio=1;//cambiamos el valor de inicio para que solo haga esto una vez
    }  
  }
//fin de la funcion inicio.............

void motorderecho(void){
  digitalWrite (12,HIGH);//voltaje alto que avance M A
  digitalWrite (9,LOW);// M A (desabilita el freno)
  analogWrite (3,100);//da la velocidad del arduino MA(max 250)
  digitalWrite (13,LOW);//voltaje alto que avance M B
  digitalWrite (8,LOW);// M B(desabilita el freno)
  analogWrite (11,100);//da la velocidad del arduino M B(max 250)
  //tiempo de espera
  delay(50);
  }
  //..........

  void frenar (void){
  digitalWrite (9,HIGH);
  digitalWrite (8,HIGH);
  delay(50);
  }
  void motorreversa(void){
 digitalWrite (12,LOW);//voltaje alto que avance M A
  digitalWrite (9,LOW);// M A (desabilita el freno)
  analogWrite (3,250);//da la velocidad del arduino MA (max 250)
  digitalWrite (13,HIGH);//voltaje alto que avance M B
  digitalWrite (8,LOW);// M B(desabilita el freno)
  analogWrite (11,250);//da la velocidad del arduino M B (max 250)
  //tiempo de espera
  delay(500);
  }
  void girarderecha(void){
  digitalWrite (12,LOW);//voltaje alto que avance M A
  digitalWrite (13,LOW);//voltaje alto que avance M B
  digitalWrite (9,LOW);// M A (desabilita el freno)
  digitalWrite (8,LOW);// M B(desabilita el freno)
  analogWrite (3,200);//da la velocidad del arduino MA(max 250)
  analogWrite (11,200);//da la velocidad del arduino M B (250)
  //tiempo de espera
  delay(500);
  }
    void girarizquierda(void){
  digitalWrite (12,HIGH);//voltaje alto que avance M A
  digitalWrite (13,HIGH);//voltaje alto que avance M B
  digitalWrite (9,LOW);// M A (desabilita el freno)
  digitalWrite (8,LOW);// M B(desabilita el freno)
  analogWrite (3,200);//da la velocidad del arduino MA(max 250)
  analogWrite (11,200);//da la velocidad del arduino M B (250)
  //tiempo de espera
  delay(500);
  }
  void detectearDistancia(){
      cronometro=millis()-reloj;
  if(cronometro>ESPERA_ENTRE_LECTURAS)
  {
    digitalWrite(PIN_TRIGGER,HIGH); // Un pulso a nivel alto…
    delayMicroseconds(10); // …durante 10 µs y
    digitalWrite(PIN_TRIGGER,LOW); // …volver al nivel bajo
    tiempo=pulseIn(PIN_ECHO,HIGH,TIMEOUT_PULSO); // Medir el tiempo que tarda en llegar un pulso
    distancia=MEDIA_VELOCIDAD_SONIDO*tiempo;
    Serial.print(distancia);
    Serial.println(" cm");
    reloj=millis();
  }
    }
//sensor de linea 1    
void lineadetector1() {
  valorSensorLuz1 = digitalRead(pinSensorLuz1);
     Serial.print( "valorSensorLuz1 = " );
    Serial.println( valorSensorLuz1 ); 
  if( valorSensorLuz1 != valorSensorLuz1anterior ) {
    Serial.print( "valorSensorLuz1 = " );
    Serial.println( valorSensorLuz1 ); 
  }
  valorSensorLuz1anterior = valorSensorLuz1;
  delay(50);
}
//sensor de linea 2
void lineadetector2() {
  valorSensorLuz2 = digitalRead(pinSensorLuz2);
     Serial.print( "valorSensorLuz2 = " );
    Serial.println( valorSensorLuz2 ); 
  if( valorSensorLuz2 != valorSensorLuz2anterior ) {
    Serial.print( "valorSensorLuz2 = " );
    Serial.println( valorSensorLuz2 ); 
  }
  valorSensorLuz2anterior = valorSensorLuz2;
  delay(50);
}       
  

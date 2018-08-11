//HEADER - Definicoes
#include "Ultrasonic.h"
#define echoPin 10    //Sensor ultrassonico
#define trigPin 9     //Sensor ultrasonico

int inPin = 2;        //Pino de entrada no sensor
int valor = 0;        //Inteiro que armazena o valor lido
int Motor_E1 = 8;     //Sentido horário
int Motor_E2 = 7;     //Sentido anti-horário
int Motor_D1 = 3;     //Sentido horário
int Motor_D2 = 4;     //Sentido anti-horário
int Motor_EV = 6;     //Velocidade esquerda
int Motor_DV = 5;     //Velocidade direita
int velEsquerda = 51; //Velocidade padrão lado esquerdo
int velDireita = 51;  //Velocidade padrão lado direito
Ultrasonic ultrasonic(9,10); //iniciando a função e passando os pinos

void setup() { 
    pinMode(Motor_EV, OUTPUT);
    pinMode(Motor_DV, OUTPUT);

    pinMode(Motor_E1, OUTPUT);
    pinMode(Motor_E2, OUTPUT);
    pinMode(Motor_D2, OUTPUT);
    pinMode(Motor_D1, OUTPUT);

    pinMode(inPin, INPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int distancia = 0;
    valor = digitalRead(inPin);
    if (valor == LOW) {
        while(1) {
          seguirLinha();
            distancia = distanciaObjeto(); //Le a distancia do objeto
            if (distancia <= 12) {
                parar(200);
                re();
                delay(300);
                parar(200);
                desviarObjeto();
            }
            else {
                seguirLinha();
            }
            delayMicroseconds(1);
        }
    }
  
}

void emFrente() {
  //Seguir em frente
    analogWrite(Motor_EV, velEsquerda);
    analogWrite(Motor_DV, velDireita);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH);
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH);
}

void parar(int espera){
  //Frear o carro
    digitalWrite(Motor_E1, HIGH);
    digitalWrite(Motor_E2, HIGH); 
    digitalWrite(Motor_D1, HIGH);
    digitalWrite(Motor_D2, HIGH);     
    delay(espera);
    analogWrite (Motor_EV, 0);      
    analogWrite (Motor_DV, 0); 
}

void girarDireita() {
  //Virar para direita
    analogWrite (Motor_EV, velEsquerda);      
    analogWrite (Motor_DV, velDireita);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH); 
    digitalWrite(Motor_D1, HIGH);
    digitalWrite(Motor_D2, LOW);    
}

void girarEsquerda() {
  //Virar para esquerda
    analogWrite (Motor_EV, velEsquerda);      
    analogWrite (Motor_DV, velDireita);
    digitalWrite(Motor_E1, HIGH);
    digitalWrite(Motor_E2, LOW);  
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH);     
}

void re() {
  //Dar ré
    analogWrite(Motor_EV, velEsquerda);
    analogWrite(Motor_DV, velDireita);
    digitalWrite(Motor_E1, HIGH);
    digitalWrite(Motor_E2, LOW);
    digitalWrite(Motor_D1, HIGH);
    digitalWrite(Motor_D2, LOW);   
  
}

void irDireita(){
    analogWrite (Motor_EV, velEsquerda);      
    analogWrite (Motor_DV, velDireita);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH); 
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, LOW); 
}

void irEsquerda(){
    analogWrite (Motor_EV, velEsquerda);      
    analogWrite (Motor_DV, velDireita);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, LOW); 
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH); 
}


void seguirLinha () {
    valor = digitalRead(inPin);

    if(valor == LOW) {
      while(valor == LOW) {
        irDireita();
        delay(1);
        valor = digitalRead(inPin);
      }
      parar(5);
    }
    
    if(valor == HIGH) {
      while(valor == HIGH) {
        irEsquerda();
        delay(1);
        valor = digitalRead(inPin);
      }
      parar(5);
    }

    if(valor == LOW) {
      while(valor == LOW) {
        irEsquerda();
        delay(1);
        valor = digitalRead(inPin);
      }
      parar(5);
    }

    if(valor == HIGH) {
      while(valor == HIGH) {
        irDireita();
        delay(1);
        valor = digitalRead(inPin);
      }
      parar(5);
    }
//Valor = HIGH --- BRANCO
//Valor = LOW ---- PRETO
}


//Funcao para ler a distancia do objeto
int distanciaObjeto() {
    //seta o pino 9 com um pulso baixo "LOW" ou desligado ou ainda 0
    digitalWrite(trigPin, LOW);
    // delay de 2 microssegundos
    delayMicroseconds(2);
    //seta o pino 9 com pulso alto "HIGH" ou ligado ou ainda 1
    digitalWrite(trigPin, HIGH);
    //delay de 10 microssegundos
    delayMicroseconds(10);
    //seta o pino 9 com pulso baixo novamente
    digitalWrite(trigPin, LOW);
    // função Ranging, faz a conversão do tempo de
    //resposta do echo em centimetros, e armazena
    //na variavel distancia
    int distancia = (ultrasonic.Ranging(CM));
    Serial.print(distancia);

    return distancia;
}

//Funcao para desviar do objeto
void desviarObjeto () {
    girarDireita();
    delay(250);      //Tempo para ele virar a direita
    parar(80);
    emFrente();
    delay(800);      //Tempo para ir um pouco em frente

    parar(200);

    girarEsquerda();
    delay(650);      //Tempo para virar a esquerda
    parar(80);

   int line = 1;
    while(line){     //Laço para fazer o carrinho voltar a linha
      if(digitalRead(inPin) == LOW){
        girarDireita();
        delay(250);
        line = 0;
      }
      else{         
        emFrente();
        delay(1);
      }
      
  }
}


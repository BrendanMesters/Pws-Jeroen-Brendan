//als je iets terug wilt zien van je programma gebruik je Serial.println('Hier is je bericht');
//Berekeningen worden in CM gemaakt

//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#include <AccelStepper.h>

// Some of the 'weird' variables.
  const float Pi = 3.14;
  int error = false;

// Afstandscencor pin definement
  const int trigPinLinks = A4;
  const int echoPinLinks = A5;
  const int trigPinVoor = 12;
  const int echoPinVoor = 13;
  const int trigPinRechts = 2;
  const int echoPinRechts = 3;

// const int's van de auto
  const float bandRadius = 6.5*Pi; // omtrek van de band ;
  const int afstandWielDraaipunt = 17/2; // afstand van het wiel tot het draaipunt van de auto
  const int volledigeRotatieafstandWiel = 2*Pi*afstandWielDraaipunt; //De afstand die beide wielen afleggwen voor een voledig rondje om de AUTO zijn as;
  const int stappenPerRotatie = 4096; // aantal stappen in halfstep dat nodig is om een volledig rondje te maken (nog aanpassen als het 4096 is);
  const int gradenNaarStappen = stappenPerRotatie/360; //het omrekenen van graden naar stappen, dus 180graden*gradenNaarStappen=2048 als stappenPerRotatie 4096 is;
  const int stappenNaarGraden = 360/stappenPerRotatie; // het omrekenen van stappen naar graden, gebruiken voor doorgeven aan pi hoeveel stappen er zijn gezet

AccelStepper stepper1(AccelStepper::HALF4WIRE, A0, A2, A1, A3); // motor links
AccelStepper stepper2(AccelStepper::HALF4WIRE, 6, 8, 7, 9);     // motor rechts

// temp variables
  int inputR = 10; //this is a temporary testing variable resembles the pi's input for rotation(in degrees).
  int input = 10; //this is a temporary testing variable resembles the pi's input going forward(in cm).



void setup() {  
  //setup stepper
    Serial.begin(9600);
    stepper1.setMaxSpeed(5000); // motor links max stappen per sec
    stepper2.setMaxSpeed(5000); // motor rechts max stappen per sec

  //setup afsandsensoren
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
    pinMode(trigPinLinks, OUTPUT); // Sets the trigPinLinks as an Output
    pinMode(echoPinLinks, INPUT); // Sets the echoPinLinks as an Input
    pinMode(trigPinVoor, OUTPUT); // Sets the trigPinVoor as an Output
    pinMode(echoPinVoor, INPUT); // Sets the echoPinVoor as an Input
    pinMode(trigPinRechts, OUTPUT); // Sets the trigPinRechts as an Output
    pinMode(echoPinRechts, INPUT); // Sets the echoPinRechts as an Input
}



void loop() {
  drive(input); // de afstandsensoren moeten nog in drive en rotate
  rotate(inputR); // de anti bots moet in bijde functies zelf verwerkt worden
}


void drive (int cm){
  if(error) return;

    stepper1.move( round(cm / bandRadius * stappenPerRotatie) ); // het draaien van de linker stappenmotor 
    stepper2.move( round(cm / bandRadius * stappenPerRotatie) ); // het draaien van de rechter stappenmotor
    //calling run for both steppers to make them actualy run.
    int i = 10;
    while(stepper1.isRunning() || stepper2.isRunning()){
      stepper1.run();
      stepper2.run();
      if(i % 10 == 0){
        obstakelOntwijking();
        Serial.println(i);
      }
      i++;
    }
      //check cencoren
     // (inconcoren) als fout run switch case
   // }
  //  if() fout{        moet nog test
   //     run error;
   //   }
}



// rotate functie opzet;
void rotate(int graden){
  if(error) return; //Breaks out of roation if there is an error
  // voer de draai alleen uit als de afstandsensoren iets zien dat verder weg is dan test afstand
 
    stepper1.move( round(inputR * gradenNaarStappen) ); // het draaien van de linker stappenmotor tijdens het draaien
    stepper2.move( round(inputR * -gradenNaarStappen) ); // het draaien van de rechter stappenmotor tijdens het draaien
    //calling run for both steppers to make them actualy run.
    int i = 0;
    while(stepper1.isRunning() || stepper2.isRunning()){
      stepper1.run();
      stepper2.run();
      if(i % 10 == 0){
        obstakelOntwijking();
        Serial.println(i);
      }
      i++;
    }
    //  if() fout{        moet nog test
   //     run error;
   //   }
  }


void obstakelOntwijking(){
 
  // als de afstand kleiner is dan 2 cm dan moet het stoppen dat moet ik nog testen
  //hier moet ik er voor zorgen dat de loop stopt en dat hij een ander pad gaat kiezen 
  //Run the code that gets you unstuck, when you are free you'll break
  //switchKey is a variable that is used to easily get the case function to know if eighter the front, the left or the right,
  // or a combination of these three is to close to a surface, we use the numbers 2, 3 and 4 because anny addition,
  // of these three numbers makes a unique number
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  // Clears the trigPinLinks
  digitalWrite(trigPinLinks, LOW);
  delayMicroseconds(2);
  // Sets the trigPinLinks on HIGH state for 10 micro seconds
  digitalWrite(trigPinLinks, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLinks, LOW);
  // Reads the echoPinLinks, returns the sound wave travel time in microseconds
  long durationLinks = pulseIn(echoPinLinks, HIGH);
  // Calculating the distance
  int distanceLinks= durationLinks*0.034/2; 
  if(distanceLinks <= 5){
    obstakelOntwijking();
  }
    
  // Clears the trigPinVoor
  digitalWrite(trigPinVoor, LOW);
  delayMicroseconds(2);
  // Sets the trigPinVoor on HIGH state for 10 micro seconds
  digitalWrite(trigPinVoor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinVoor, LOW);
  // Reads the echoPinVoor, returns the sound wave travel time in microseconds
  long durationVoor = pulseIn(echoPinVoor, HIGH);
  // Calculating the distance
  int distanceVoor= durationVoor*0.034/2; 
  if(distanceVoor <= 5){
    obstakelOntwijking();
  }
    
  // Clears the trigPinRechts
  digitalWrite(trigPinRechts, LOW);
  delayMicroseconds(2);
  // Sets the trigPinRechts on HIGH state for 10 micro seconds
  digitalWrite(trigPinRechts, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRechts, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long durationRechts = pulseIn(echoPinRechts, HIGH);
  // Calculating the distance
  int distanceRechts= durationRechts*0.034/2; 
  if(distanceRechts <= 5){
    obstakelOntwijking();
  }
  
  int switchKey = 0; // moet nog alle cases nagaan test
      
  if(distanceVoor <= 5){switchKey += 2;}
  if(distanceLinks <= 5){switchKey += 3;}
  if(distanceRechts <= 5){switchKey += 4;}
      
  switch (switchKey){  
    case 0:
      return;  
    case 2: // voor
      //  rand() % 2;  random 0 of 1
          if (rand() % 2 == 0){
            stepper1.move(90 * gradenNaarStappen); // beweging motor links
            stepper2.move(90 * -gradenNaarStappen); // beweging motor rechts
            while(stepper1.isRunning() || stepper2.isRunning()){
              stepper1.run();
              stepper2.run();
            }
          }
    else{
            stepper1.move(90 * -gradenNaarStappen); // beweging motor links
            stepper2.move(90 * gradenNaarStappen); // beweging motor rechts
            while(stepper1.isRunning() || stepper2.isRunning()){
              stepper1.run();
              stepper2.run();
            }
          }
          break;
          
    case 3: // links
        // zolang de afstand van links kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit rijden 
          while ((distanceLinks <=5) && (distanceVoor > 5)){ 
            stepper1.move( bandRadius *  stappenPerRotatie);
            stepper2.move( bandRadius *  stappenPerRotatie);
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run();
                stepper2.run();
             }
          }
          break;
        
    case 4: // rechts
        // zolang de afstand van rechts kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit rijden 
          while ((distanceRechts <=5) && (distanceVoor > 5)){ 
            stepper1.move( bandRadius *  stappenPerRotatie);
            stepper2.move( bandRadius *  stappenPerRotatie);
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run();
                stepper2.run();
             }
          }
          break;
        
    case 5: // voor & links dus naar rechts draaien
          stepper1.move(90 * gradenNaarStappen); // beweging motor links
          stepper2.move(90 * -gradenNaarStappen); // beweging motor rechts
            while(stepper1.isRunning() || stepper2.isRunning()){
              stepper1.run();
              stepper2.run();
            }
          break;
        
     case 6: // voor & rechts
          stepper1.move(90 * -gradenNaarStappen); // beweging motor links
          stepper2.move(90 * gradenNaarStappen); // beweging motor rechts
            while(stepper1.isRunning() || stepper2.isRunning()){
              stepper1.run();
              stepper2.run();
            }
          break;
        
     case 7: // links & rechts
         // zolang de afstand van rechts en links kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit of achteruit rijden 
        while ((distanceRechts <=5) && (distanceLinks <= 5) && (distanceVoor > 5)){ 
             // ga naar achter of naar voren bij if naar achteren
             if (rand() % 2 == 0){
              stepper1.move( bandRadius *  -stappenPerRotatie);
              stepper2.move( bandRadius *  -stappenPerRotatie);
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run();
                stepper2.run();
              }
             }

                         // ga naar voren
            else {
              stepper1.move( bandRadius *  stappenPerRotatie);
              stepper2.move( bandRadius *  stappenPerRotatie);
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run();
                stepper2.run();
              }
            }
        }
          break;
        
        case 9: // voor & links & rechts
        // ga naar achter zolang de afstand van alle 3 kleiner is dan 5 cm
        while ((distanceRechts <=5) && (distanceLinks <= 5) && (distanceVoor <= 5)){ 
              stepper1.move( bandRadius *  -stappenPerRotatie);
              stepper2.move( bandRadius *  -stappenPerRotatie);
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run();
                stepper2.run();
              }

        }
          break;
        
        default: // glitch
          break;
      }

}


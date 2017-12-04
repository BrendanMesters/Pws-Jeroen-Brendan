//als je iets terug wilt zien van je programma gebruik je Serial.println('Hier is je bericht');
//Berekeningen worden in CM gemaakt
// mijn mac kan nu ook veranderingen aan brengen??
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#include <AccelStepper.h>



#define WITH_ERRORS

#ifdef WITH_ERRORS
#define ERRORPRINT(v) { Serial.print("* "); Serial.println(v); }
#else
#define ERRORPRINT(v)
#endif



// Some of the 'weird' variables.
  const float Pi = 3.14;
  int error = false;
  int distanceLinks;
  int distanceVoor;
  int distanceRechts;


// Afstandscencor pin definement
  const int trigPinLinks = A4;
  const int echoPinLinks = A5;
  const int trigPinVoor = 12;
  const int echoPinVoor = 13;
  const int trigPinRechts = 2;
  const int echoPinRechts = 3;

// de ir sensor zijn setup
//collects data from an analog sensor
// y= 11181x^-1,143 de functie moet nog worden aangepast
int sensorpin = 0;                 // analog pin used to connect the sharp sensor
float val = 0;                 // variable to store the values from sensor(initially zero)
float afstand = 0;




// const int's van de auto
  const float bandRadius = 6.5*Pi; // omtrek van de band ;
  const int afstandWielDraaipunt = 17/2; // afstand van het wiel tot het draaipunt van de auto
  const int volledigeRotatieafstandWiel = 2*Pi*afstandWielDraaipunt; //De afstand die beide wielen afleggwen voor een voledig rondje om de AUTO zijn as;
  const int stappenPerRotatie = 4047; // aantal stappen in halfstep dat nodig is om een volledig rondje te maken (nog aanpassen als het niet 4096 is);
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
  irSensor();
  drive(input); // de afstandsensoren moeten nog in drive en rotate
  rotate(inputR); // de anti bots moet in bijde functies zelf verwerkt worden
}
void sensor(){
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
  distanceLinks = durationLinks*0.034/2; 
 
    
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
  distanceVoor = durationVoor*0.034/2; 
 
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
  distanceRechts = durationRechts*0.034/2; 
  
  
}


void irSensor()
{
  if (val = 0){
  val = analogRead(sensorpin);       // reads the value of the sharp sensor
  Serial.println(val);            // prints the value of the sensor to the serial monitor 
  if(val != 0){ 
    afstand = (11181*pow(val,-1.143));
    Serial.print("dit is de afstand");
    Serial.println(val);
  }          
  }
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
        Serial.print("i  ");
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
    int i = 10;
    while(stepper1.isRunning() || stepper2.isRunning()){
      stepper1.run();
      stepper2.run();
      if(i % 10 == 0){
        obstakelOntwijking();
        Serial.print("i is");
        Serial.println(i);
      }
      i++;
    }
    //  if() fout{        moet nog test
   //     run error;
   //   }
  }



  
void alsIsRunning(){
  while(stepper1.isRunning() || stepper2.isRunning()){
       stepper1.run(); // deze kan goed worden aangeroepen om code te besparen
       stepper2.run();
  }
}




void obstakelOntwijking(){
 
  // als de afstand kleiner is dan 2 cm dan moet het stoppen dat moet ik nog testen
  //hier moet ik er voor zorgen dat de loop stopt en dat hij een ander pad gaat kiezen 
  //Run the code that gets you unstuck, when you are free you'll break
  //switchKey is a variable that is used to easily get the case function to know if eighter the front, the left or the right,
  // or a combination of these three is to close to a surface, we use the numbers 2, 3 and 4 because anny addition,
  // of these three numbers makes a unique number
  int punt1L;
  int punt1R;
  int switchKey = 0; // moet nog alle cases nagaan test
  sensor();   
  if(distanceVoor <= 5){switchKey += 2;}
  if(distanceLinks <= (5 / cos(30/ 180 * Pi))){switchKey += 3;  punt1L = stepper1.currentPosition();}
  if(distanceRechts <= (5 / cos(30/ 180 * Pi))){switchKey += 4; punt1R = stepper1.currentPosition();}
  Serial.print("switchKey is ");
  Serial.println(switchKey);   
  Serial.print("voor is ");
  Serial.println(distanceVoor);
  Serial.print("links is ");
  Serial.println(distanceLinks);
  Serial.print("rechts is ");
  Serial.println(distanceRechts); 
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
              sensor();
              if (distanceVoor <= 2){//dit werkt blijkbaar ook nog niet zoals ik dacht moet nog naar gekeken worden.?????? test
                Serial.print("voor is");
                Serial.println(distanceVoor);
                stepper1.move( 1 *  -stappenPerRotatie);
                stepper2.move( 1 *  -stappenPerRotatie);
                alsIsRunning();
                sensor();
                Serial.print("voor is bij case 2 na sensor");
                Serial.println(distanceVoor);
              }             
            }
           }
    else{
            stepper1.move(90 * -gradenNaarStappen); // beweging motor links
            stepper2.move(90 * gradenNaarStappen); // beweging motor rechts
            while(stepper1.isRunning() || stepper2.isRunning()){
              stepper1.run();
              stepper2.run();
              sensor();
              if (distanceVoor <= 2){
                Serial.print("voor is");
                Serial.println(distanceVoor);
                stepper1.move( 1 *  -stappenPerRotatie);
                stepper2.move( 1 *  -stappenPerRotatie);
                alsIsRunning();
                sensor();
                Serial.print("voor is bij case 2 na sensor");
                Serial.println(distanceVoor);
              }
            }
          }
          break;

    case 3: // links ??????? test
        // zolang de afstand van links kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit rijden
        // currentPosition() geeft de huidige positie van de stappenmotor in stappen
          while ((distanceLinks <= (5/cos(30/ 180 * Pi))) && (distanceVoor > 5)){ 
            
            stepper1.move( 1 *  stappenPerRotatie);
            stepper2.move( 1 *  stappenPerRotatie);
            Serial.println("Ik ben hier!");
            while ((stepper1.isRunning()) || (stepper2.isRunning())){
              sensor();
              Serial.print("while is ");
              Serial.println((distanceLinks <= (5/cos(30/ 180 * Pi))) && (distanceVoor > 5));
              Serial.print("while #2 is ");
              Serial.println(5/cos(30/ 180 * Pi));
              Serial.print("while #1 is ");
              Serial.println((distanceLinks <= (5/cos(30/ 180 * Pi))));
              Serial.print("case 3 voor is ");
              Serial.println(distanceVoor);
              Serial.print("case 3 links is ");
              Serial.println(distanceLinks);
              Serial.print("case 3 rechts is ");
              Serial.println(distanceRechts); 
              stepper1.run();
              stepper2.run();
              if(distanceLinks <= (3/cos(30/ 180 * Pi))){
                Serial.println ("hij doet while van case 3 het if deel voor als de afstand kleiner is dan 3");
                int punt2L = stepper1.currentPosition();
                int afgelegdeAfstand = (punt2L - punt1L) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                int teDraaienHoek = 1 / (tan((afgelegdeAfstand/2)/ 180 * Pi)); // bereken de te draaien hoek
                // nu parralel krijgen en er voor zorgen dat hij niet nog maar 3 cm van de muur af is en er geen obstakelOntwijking meer in werking kan gaan
                stepper1.move((teDraaienHoek + 90) * gradenNaarStappen); //motor links; deel van het parralel krijgen en meer dan 3cm van de muur af
                stepper2.move((teDraaienHoek + 90) * -gradenNaarStappen); //motor rechts
                alsIsRunning();
                 stepper1.move( round(3 / bandRadius * stappenPerRotatie) ); // het draaien van de linker stappenmotor; 3cm van de muur af rijden
                 stepper2.move( round(3 / bandRadius * stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                 //hierna moet hij nog wat doen om niet steed 3/cos( 30 / 180 * Pi) cm dicht bij de muur te zijn
                 alsIsRunning();
                stepper1.move(90 * -gradenNaarStappen); //motor links; paralel krijgen
                stepper2.move(90 * gradenNaarStappen); //motor rechts
                alsIsRunning();
                sensor();
            }
          }
        }
        
    break ;
        
    case 4: // rechts
        // zolang de afstand van rechts kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit rijden 
          while((distanceRechts <= (5/cos(30/ 180 * Pi))) && (distanceVoor > 5)){ 
            stepper1.move( 1 *  stappenPerRotatie);
            stepper2.move( 1 *  stappenPerRotatie);
            while ((stepper1.isRunning()) || (stepper2.isRunning())){
              sensor();
              Serial.print("case 4 voor is ");
              Serial.println(distanceVoor);
              Serial.print("case 4 links is ");
              Serial.println(distanceLinks);
              Serial.print("case 4 rechts is ");
              Serial.println(distanceRechts); 
              stepper1.run();
              stepper2.run();
              if(distanceRechts <= (3/cos(30/ 180 * Pi))){
                Serial.println ("hij doet while van case 4 het if deel voor als de afstand kleiner is dan 3");
                int punt2R = stepper1.currentPosition();
                int afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                int teDraaienHoek = 1 / (tan((afgelegdeAfstand/2)/ 180 * Pi)); // bereken de te draaien hoek
                // nu parralel krijgen en er voor zorgen dat hij niet nog maar 3 cm van de muur af is en er geen obstakelOntwijking meer in werking kan gaan
                stepper1.move((teDraaienHoek + 90) * -gradenNaarStappen); //motor links; deel van het parralel krijgen en meer dan 3cm van de muur af
                stepper2.move((teDraaienHoek + 90) * gradenNaarStappen); //motor rechts
                alsIsRunning();
                stepper1.move( round(3 / bandRadius * stappenPerRotatie) ); // het draaien van de linker stappenmotor; 3cm van de muur af rijden
                stepper2.move( round(3 / bandRadius * stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                //hierna moet hij nog wat doen om niet steed 3/cos( 30 / 180 * Pi) cm dicht bij de muur te zijn
                alsIsRunning();
                stepper1.move(90 * gradenNaarStappen); //motor links; paralel krijgen
                stepper2.move(90 * -gradenNaarStappen); //motor rechts
                alsIsRunning();
                sensor();
            }
          }
        }
   break;
        
    case 5: // voor & links dus naar rechts draaien
          stepper1.move(90 * gradenNaarStappen); // beweging motor links
          stepper2.move(90 * -gradenNaarStappen); // beweging motor rechts
            alsIsRunning();
            sensor();
          break;
        
     case 6: // voor & rechts
          stepper1.move(90 * -gradenNaarStappen); // beweging motor links
          stepper2.move(90 * gradenNaarStappen); // beweging motor rechts
            alsIsRunning();
            sensor();
          break;
        
     case 7: // links & rechts
         // zolang de afstand van rechts en links kleiner is dan 5 en hij voor ook niet gaat botsen moet hij vooruit of achteruit rijden 
         //deze moet ik nog nakijken op sensor(); en formules
         int switchKeyCase7;
         int punt2L;
         int punt2R;
         switchKeyCase7 = 0;
         punt2L = 0;
         punt2R = 0;
  
         if((distanceLinks > (3/cos(30/ 180 * Pi))) && (distanceRechts > (3/cos(30/ 180 * Pi)))) {switchKeyCase7 += 3;}
         if(distanceLinks <=(3/cos(30/ 180 * Pi))) {switchKeyCase7 += 4;}
         if(distanceRechts <=(3/cos(30/ 180 * Pi))) {switchKeyCase7 += 5;}
          switch(switchKeyCase7){
            case 3: // nog groter dan 3 maar kleiner dan 5
              stepper1.move( 1 *  stappenPerRotatie); // beweging motor links
              stepper2.move( 1 *  stappenPerRotatie); // beweging motor rechts
              while(stepper1.isRunning() || stepper2.isRunning()){
                stepper1.run(); 
                stepper2.run();
                sensor();
                Serial.print("case 7 voor is ");
                Serial.println(distanceVoor);
                Serial.print("case 7 links is ");
                Serial.println(distanceLinks);
                Serial.print("case 7 rechts is ");
                Serial.println(distanceRechts); 
                if (distanceLinks <= 3){
                  // de positie van de motor om de hoek te berekenen
                  punt2L = stepper1.currentPosition();
                  break;
                }
                else if(distanceRechts <= 3){ // is de else hier nodig???
                  // de positie van de motor om de hoek te berekenen
                  punt2R = stepper1.currentPosition();
                  break;
                }
              }
            break;
            
            case 4: // links kleiner dan 3
                if((distanceLinks + distanceRechts) > 7){
                 int afgelegdeAfstand;
                 int teDraaienHoek;
                 afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                 teDraaienHoek = 1 / (tan((afgelegdeAfstand/2)/ 180 * Pi)); // bereken de te draaien hoek
                 // nu parralel krijgen en er voor zorgen dat hij niet nog maar 3 cm van de muur af is en er geen obstakelOntwijking meer in werking kan gaan
                 stepper1.move((teDraaienHoek + 90) * gradenNaarStappen); //motor links; deel van het parralel krijgen en meer dan 3cm van de muur af
                 stepper2.move((teDraaienHoek + 90) * -gradenNaarStappen); //motor rechts
                 alsIsRunning();
                 float tussenDeMuren; // een var om uit te rekenen hoeveel hij moet rijden om in het midden te rijden moet toegepast in wat er onder staat
                 tussenDeMuren = distanceLinks + distanceRechts;       
                 stepper1.move( round( (tussenDeMuren / 2 - 3/cos( 30 / 180 * Pi)) / bandRadius * stappenPerRotatie) ); // het draaien van de linker stappenmotor; naar het midden van de twee muren test
                 stepper2.move( round( (tussenDeMuren / 2 - 3/cos( 30 / 180 * Pi)) / bandRadius * stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                 alsIsRunning();
                 stepper1.move(90 * -gradenNaarStappen); //motor links; paralel krijgen
                 stepper2.move(90 * gradenNaarStappen); //motor rechts
                 alsIsRunning();
                }
                else{
                  int afgelegdeAfstand;
                  afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                  stepper1.move( round( (afgelegdeAfstand + 3 ) / bandRadius * -stappenPerRotatie) ); // het draaien van de linker stappenmotor; achteruit als hij in een trechter zit
                  stepper2.move( round( (afgelegdeAfstand + 3 ) / bandRadius * -stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                  alsIsRunning();
                  if (rand() % 2 == 0){
                    //draai naar links
                    stepper1.move(90 * -gradenNaarStappen); //motor links; 
                    stepper2.move(90 * gradenNaarStappen); //motor rechts
                    alsIsRunning();
                  }
                  else{
                   stepper1.move(90 * gradenNaarStappen); //motor links; 
                   stepper2.move(90 * -gradenNaarStappen); //motor rechts
                   alsIsRunning();
                  }
                // ga achteruit rijden weg van de trechter
                }
            break;
            
            case 5: // rechts kleiner dan 3
                if((distanceLinks + distanceRechts) > 7){
                 int afgelegdeAfstand;
                 int teDraaienHoek;
                 afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                 teDraaienHoek = 1 / (tan((afgelegdeAfstand/2)/ 180 * Pi)); // bereken de te draaien hoek
                 // nu parralel krijgen en er voor zorgen dat hij niet nog maar 3 cm van de muur af is en er geen obstakelOntwijking meer in werking kan gaan
                 stepper1.move((teDraaienHoek + 90) * -gradenNaarStappen); //motor links; deel van het parralel krijgen en meer dan 3cm van de muur af
                 stepper2.move((teDraaienHoek + 90) * gradenNaarStappen); //motor rechts
                 alsIsRunning();
                 float tussenDeMuren; // een var om uit te rekenen hoeveel hij moet rijden om in het midden te rijden moet toegepast in wat er onder staat
                 tussenDeMuren = distanceLinks + distanceRechts;       
                 stepper1.move( round( (tussenDeMuren / 2 - 3/cos( 30 / 180 * Pi)) / bandRadius * stappenPerRotatie) ); // het draaien van de linker stappenmotor; naar het midden van de twee muren test
                 stepper2.move( round( (tussenDeMuren / 2 - 3/cos( 30 / 180 * Pi)) / bandRadius * stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                 alsIsRunning();
                 stepper1.move(90 * gradenNaarStappen); //motor links; paralel krijgen
                 stepper2.move(90 * -gradenNaarStappen); //motor rechts
                 alsIsRunning();
                }
                else{
                  int afgelegdeAfstand;
                  afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                  stepper1.move( round( (afgelegdeAfstand + 3 ) / bandRadius * -stappenPerRotatie) ); // het draaien van de linker stappenmotor; achteruit als hij in een trechter zit 
                  stepper2.move( round( (afgelegdeAfstand + 3 ) / bandRadius * -stappenPerRotatie) ); // het draaien van de rechter stappenmotor
                  alsIsRunning();
                  if (rand() % 2 == 0){
                    //draai naar links
                    stepper1.move(90 * -gradenNaarStappen); //motor links; 
                    stepper2.move(90 * gradenNaarStappen); //motor rechts
                    alsIsRunning();
                  }
                  else{
                   stepper1.move(90 * gradenNaarStappen); //motor links; 
                   stepper2.move(90 * -gradenNaarStappen); //motor rechts
                   alsIsRunning();
                  }
                // ga achteruit rijden weg van de trechter
                }
            break;

            case 9: // links en rechts kleiner dan 3
            // moet nog verzinnen hoe ver hij naar achter moet rijden.
                int afgelegdeAfstand;
                afgelegdeAfstand = (punt2R - punt1R) / stappenPerRotatie * bandRadius; // uitrekenen hoeveel afstand er is afgelegd sind switchKey = 3 tot distanceLinks <= (3/cos( 30 / 180 * Pi)  
                stepper1.move( (afgelegdeAfstand + 1) *  -stappenPerRotatie); // beweging motor links
                stepper2.move( (afgelegdeAfstand + 1) *  -stappenPerRotatie); // beweging motor rechts
                if (rand() % 2 == 0){
                    //draai naar links
                    stepper1.move(90 * -gradenNaarStappen); //motor links; 
                    stepper2.move(90 * gradenNaarStappen); //motor rechts
                    alsIsRunning();
                  }
                  else{
                   stepper1.move(90 * gradenNaarStappen); //motor links; 
                   stepper2.move(90 * -gradenNaarStappen); //motor rechts
                   alsIsRunning();
                  }
            break;

            default: // glitch
            break;


                   
          }
            
        
        while ((distanceRechts <=5) && (distanceLinks <= 5) && (distanceVoor > 5)){ 
             // ga naar achter of naar voren bij if naar achteren
             if (rand() % 2 == 0){
              stepper1.move( 1 *  -stappenPerRotatie);
              stepper2.move( 1 *  -stappenPerRotatie);
              alsIsRunning();
             }

                         // ga naar voren
            else {
              stepper1.move( 1 *  stappenPerRotatie);
              stepper2.move( 1 *  stappenPerRotatie);
              alsIsRunning();
            }
        }
          break;
        
        case 9: // voor & links & rechts
        // ga naar achter zolang de afstand van alle 3 kleiner is dan 5 cm
        while ((distanceRechts <=5) && (distanceLinks <= 5) && (distanceVoor <= 5)){ 
              stepper1.move( 1 *  -stappenPerRotatie);
              stepper2.move( 1 *  -stappenPerRotatie);
              alsIsRunning();
              sensor();

        }
          break;
        
        default: // glitch
          break;
      }

  }


// Brendan zijn code beneden

void mainComunication() {  //Used to talk with an other devise
  while(!Serial.available()){}  //Waits for a message
  error = false;

  String str = Serial.readString();
  str.trim();  //Takes away junk such as \n or \r\n
  while (str.length() > 0) {
    char chr = str.charAt(0);  //Saves the first character of the string in chr.
    str.remove(0, 1);  //Removes the first character from str.
    procesCommand(chr, str);
    if (error) return;
  }
}



float stringToVariable(String &str) {
  float returnVal;  //Make a return value variable
  boolean decimalPoint = false;
  int decimalPlace = 1;
  if (str.length() == 0) {
    error = true;
    ERRORPRINT("No variables for rotation command.");
    return -1;
  }
  
  
  while (str.length() > 0) {  //A weird way to convert our string into an interger we want
    
    if (str.charAt(0) == '.') {  //Tests for decimal points, one means do a diferent 'algorithm' a second one means an error
      if (decimalPoint == false) {  //if this is the first decimal point decimalPoint becomes true, else there is something wrong cause 2 points
        decimalPoint = true;
      }
      else {
        error = true;
        ERRORPRINT("Second decimal point.");
        return -1;
      } 
    }

    
    if ( !( (str.charAt(0) > '0' && str.charAt(0) < '9') || str.charAt(0) == '.'  ) ) {  //Gives an error if the character isn't valid(between 0 and 9 or a decimal point)
      error = true;
      ERRORPRINT("Invalid character in float");
      return -1;
    }
    
    if (decimalPoint == false) {  //Checks if a decimal point has been found and acts acordingly
      returnVal = returnVal*10 + int(str.charAt(0))-int('0');  //A simple way to convert our string to an interger
    } else {
      if (str.charAt(0) != '.') {
        returnVal = returnVal + ( int(str.charAt(0))-int('0') )/pow(10, decimalPlace); //Devides the new character by 10 to the power n where n is grows the more it is called
        decimalPlace += 1;
      }
    }
    
    str.remove(0,1);
    
  }
  
  return returnVal;
}



void procesCommand(char chr, String &str) {  //Check what command he has to execute and does it.
  float var;
  if(str != ""){
    var = stringToVariable(str);
  }
  
  switch(chr){
    case 'D':  //Drive
      drive(var); 
      break;
      
    case 'R':  //Rotate
      rotate(var);
      break;
      
    case 'T':  //Test
      
      break;
      
    default:
      error = true;
      ERRORPRINT("Unknown command.");
      return;
  }
  str.remove(0);
}

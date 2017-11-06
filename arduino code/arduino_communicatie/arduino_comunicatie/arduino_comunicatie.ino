//Let the arduino send back the axact amounth of degrees he has turned so the py can 
//adjust acordingly.
// !!! voor getallen gebruiken we punten, geen comma's
// add error in str to float for empty string


boolean error;
int test;

#define WITH_ERRORS

#ifdef WITH_ERRORS
#define ERRORPRINT(v) { Serial.print("* "); Serial.println(v); }
#else
#define ERRORPRINT(v)
#endif

void setup() {
  //Put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A1, OUTPUT);
  
}

void loop() {
  mainComunication();
  if (error) { 
    Serial.println("RR");
    return;
  }
  // Do more things
  //
  // Tell host everything was okay
  Serial.println("OK");
}

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

void procesCommand(char chr, String &str) {  //Check what command he has to execute and does it.
  //str is the variable
  switch(chr){
    case 'M':  //Move
      Serial.println(str); 
      break;
      
    case 'R':  //Rotate
      float var;
      var = stringToVariable(str);
 //     var = str.toFloat();
      if (error) return;
      Serial.println(var);
      break;
      
    case 'K':  //Test
      if (test == 0){
        digitalWrite(A1, HIGH);
        test = 1;
      } else{
        digitalWrite(A1, LOW);
        test = 0;
      }
      break;
      
    default:
      error = true;
      ERRORPRINT("Unknown command.");
      return;
  }
  str.remove(0);
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

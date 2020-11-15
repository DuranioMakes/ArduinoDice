

//Duranio LED dice roll program, 8-28-20

//Initialize DieOne and DieTwo, long type numbers for random number storage
long DieOne;
long DieTwo;

//DieRand variable for storage of the random number for Die One or Die Two
long DieRand;

// "Display" is used to keep track of which LED die to display, Die 1 or Die 2
// Display == 1 will display DieOne while DieTwo is OFF
// Display == 2 will display DieTwo, DieOne is OFF
int Display;

//Assign ports 2 and 3 as die select lines 1 and 2
//Pins 2 and 3 are attached to N-FET transitors, ZVN4206A, to turn ON either DieOne or DieTwo
//Transistor One                //Transistor Two
//Gate = Pin 2                  //Gate = Pin 3
//Source = GND                  //Source = GND
//Drain = DieOne LED Cathodes   //Drain = DieTwo LED Cathodes
int Select1 = 2; //DieOne select line
int Select2 = 3; //DieTwo select line

//Assign LEDs to port pins 4 thru 10
int LED4 = 4; //LED anode assigned to pin 4
int LED5 = 5;
int LED6 = 6;
int LED7 = 7;
int LED8 = 8;
int LED9 = 9;
int LED10 = 10; //LED anode assigned to pin 10

int BUTTON = 12; //Assign button to pin 12, this pin has a 10K pull-down

//Now setup the Arduino pins and seed the random number generator
void setup() {
  //Set pin 12 as an input
  pinMode(BUTTON, INPUT);

  //Set Die Select lines as outputs
  pinMode(Select1, OUTPUT);
  pinMode(Select2, OUTPUT);

  //Set all LED pins to outputs
  pinMode(LED4, OUTPUT); //sets pin 4 as an output
  pinMode(LED5, OUTPUT); 
  pinMode(LED6, OUTPUT); 
  pinMode(LED7, OUTPUT); 
  pinMode(LED8, OUTPUT); 
  pinMode(LED9, OUTPUT); 
  pinMode(LED10, OUTPUT); //sets pin 10 as an output

  //With nothing connected to the 10 bit analog input, read the noise on the input for the pseudo-random number gerneration 
  randomSeed(analogRead(0));

  //Set both select lines LOW, then set the initial Display state to 1
  digitalWrite(Select1,LOW); //Turn OFF Die One
  digitalWrite(Select2,LOW); //and turn OFF Die Two
  Display = 1; //Initial state of DieOne is ON
}

void loop() {
  //Read the state of the button. If it is HIGH, then "roll the dice" and store
  //the number for Die One and Die Two
  
  if (digitalRead(BUTTON) == HIGH){
    // Die One
    DieOne = random(1,7); //Generate a random number between 1 and 6 and store in DieOne
        
    // Die Two
    DieTwo = random(1,7); //Generate a random number for DieTwo between 1 and 6
  }

  //Display DieOne
  if (Display == 1){
    //Copy the random number in DieOne and place it in DieRand
    DieRand = DieOne;  
    digitalWrite(Select1,HIGH); //Turn ON Die One
    digitalWrite(Select2,LOW); //Turn OFF Die Two

    //Use the "DisplayDie()" function to light the proper number of LEDs based on the random number
    DisplayDie();
    delay(5); //Display LEDs on DieOne for 5 milliseconds
    
    //Use the "AllOff()" function to set all LED pins LOW to prevent DieOne data from bleeding over into DieTwo and vice-versa
    AllOff();
    
    //Prepare to display DieTwo
    Display = 2;
  }

  //Display DieTwo
  if (Display == 2){
    //Now copy the random number in DieTwo and place it in DieRand
    DieRand = DieTwo;  
    digitalWrite(Select1,LOW); //Turn OFF Die One
    digitalWrite(Select2,HIGH); //Turn ON Die Two
    
    //Now use the "DisplayDie()" function to light the LEDs for DieTwo
    DisplayDie();
    delay(5); //Display LEDs on DieTwo for 5 milliseconds
    
    //Use the "AllOff()" function to set all LED pins LOW to prevent DieTwo data from bleeding over into DieOne and vice-versa
    AllOff();

    //Prepare to display DieOne again
    Display = 1;
  }
}


// Display functions for DieOne and DieTwo
// Two Sets of seven LEDs are positioned as shown below
// Top view of LEDs arranged for each die

//       DieOne                   DieTwo
// LED4   LED6    LED9      LED4   LED6    LED9
//        LED7                     LED7                    
// LED5   LED8    LED10     LED5   LED8    LED10

void DisplayDie(){
  if (DieRand == 1){
    //one();
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, HIGH);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, LOW);
    digitalWrite(LED10, LOW);
  }
  
  if (DieRand == 2){
    //two();
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, LOW);
    digitalWrite(LED10, HIGH);
  }
  
  if (DieRand == 3){
    //three();
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, HIGH);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, HIGH);
    digitalWrite(LED10, LOW);
  }

  if (DieRand == 4){
    //four();
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, HIGH);
    digitalWrite(LED10, HIGH);
  }

  if (DieRand == 5){
    //five();
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, HIGH);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, HIGH);
    digitalWrite(LED10, HIGH);
  }

  if (DieRand == 6){
    //six();
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, HIGH);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, HIGH);
    digitalWrite(LED9, HIGH);
    digitalWrite(LED10, HIGH);
  } 
}

//Function used to place all lines low to prevent DieOne from "bleeding over" to DieTwo and vice-versa
void AllOff(){
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
  digitalWrite(LED10, LOW);
}



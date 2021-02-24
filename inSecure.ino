

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


//forward :20DF00FF
//backward: 20DF807F
//right :20DF40BF
//left: 20DFC03F


// mirror motor up:    20DF48B7  unit 0.1 sec
// mirror motor down : 20DFA857  unit 0.2 sec



// gun fire     on :   20DF28D7
//   gun          off : 20DFE817




int RECV_PIN =2;

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  
  irrecv.enableIRIn();

}

void loop() {
  if(irrecv.decode(&results)){
    Serial.println(results.value,HEX);

    
    if(results.value == 0x20DF28D7){
      //gun firing 
      digitalWrite(5,HIGH);
      delay(100); 
      
    }
    if(results.value == 0x20DFE817){
      //gun firing 
      digitalWrite(5,LOW);      
    }

    if(results.value == 0x20DF48B7){
      // motor up
      digitalWrite(7,1);
      digitalWrite(8,1);
      analogWrite(9,255);
      digitalWrite(10,0);
      delay(2800);
      digitalWrite(7,0);
      digitalWrite(8,0);
      analogWrite(9,0);
      digitalWrite(10,0);
     
    }
    
    if(results.value == 0x20DFA857){
      // motor down
      digitalWrite(7,1);
      digitalWrite(8,1);
      analogWrite(9,0);
      digitalWrite(10,1);
      delay(3000);
      digitalWrite(7,0);
      digitalWrite(8,0);
      analogWrite(9,0);
      digitalWrite(10,0);
     
    }

    if(results.value == 0x20DF00FF){
      // forward

      digitalWrite(A0,1);
      digitalWrite(A1,1);
      digitalWrite(A4,1);
      digitalWrite(A5,1);
      
      digitalWrite(A2,1);
      digitalWrite(A3,0);
      digitalWrite(11,0);
      digitalWrite(12,1);
      delay(500);
      digitalWrite(A0,0);
      digitalWrite(A1,0);
      digitalWrite(A4,0);
      digitalWrite(A5,0);
      
      digitalWrite(A2,0);
      digitalWrite(A3,0);
      digitalWrite(11,0);
      digitalWrite(12,0);
      
    }


    if(results.value == 0x20DF807F){
      // backward

      digitalWrite(A0,1);
      digitalWrite(A1,1);
      digitalWrite(A4,1);
      digitalWrite(A5,1);
      
      digitalWrite(A2,0);
      digitalWrite(A3,1);
      digitalWrite(11,1);
      digitalWrite(12,0);
      delay(500);
      digitalWrite(A0,0);
      digitalWrite(A1,0);
      digitalWrite(A4,0);
      digitalWrite(A5,0);
      
      digitalWrite(A2,0);
      digitalWrite(A3,0);
      digitalWrite(11,0);
      digitalWrite(12,0);
      
    }

     if(results.value == 0x20DF40BF){
      // right

      digitalWrite(A0,1);
      digitalWrite(A1,1);
      digitalWrite(A4,1);
      digitalWrite(A5,1);
      
      digitalWrite(A2,1);
      digitalWrite(A3,0);
      digitalWrite(11,1);
      digitalWrite(12,0);
      delay(500);
      digitalWrite(A0,0);
      digitalWrite(A1,0);
      digitalWrite(A4,0);
      digitalWrite(A5,0);
      
      digitalWrite(A2,0);
      digitalWrite(A3,0);
      digitalWrite(11,0);
      digitalWrite(12,0);
      
    }

    if(results.value == 0x20DFC03F){
      // left

      digitalWrite(A0,1);
      digitalWrite(A1,1);
      digitalWrite(A4,1);
      digitalWrite(A5,1);
      
      digitalWrite(A2,0);
      digitalWrite(A3,1);
      digitalWrite(11,0);
      digitalWrite(12,1);
      delay(500);
      digitalWrite(A0,0);
      digitalWrite(A1,0);
      digitalWrite(A4,0);
      digitalWrite(A5,0);
      
      digitalWrite(A2,0);
      digitalWrite(A3,0);
      digitalWrite(11,0);
      digitalWrite(12,0);
      
    }
    
  
    irrecv.resume();
  }
  delay(100);

}

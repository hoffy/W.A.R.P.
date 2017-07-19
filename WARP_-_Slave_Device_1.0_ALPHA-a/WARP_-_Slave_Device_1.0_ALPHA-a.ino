/*
 |________________________________________________________________________________________________________________________|
 |----------------------------------- Workshop Automation & Reporting Protocol (WARP) ------------------------------------|
 |                                                 VERSION - SLAVE DEVICE - ALPHA a                                                     |
 |________________________________________________________________________________________________________________________|
 |                                                                                                                        |
 |     This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.   |
 |                  To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.              |
 |________________________________________________________________________________________________________________________|
 |                                                                                                                        |
 | Master Device Code is Coded for the Arduino Mega 2560 Microcontroller and compatible devices                           |                                            
 |________________________________________________________________________________________________________________________|
 | Code Authored by: S. D. "Hoffy" Hofmeister      7/14/2017                                                              |
 |________________________________________________________________________________________________________________________|
 |                                      Code Purpose, Narrative, or Instruction                                           |
 |________________________________________________________________________________________________________________________|
 | Future Upgrades & Additions Planned                                                                                    |                                   
 |                                                                                                                        |
 |________________________________________________________________________________________________________________________|
 | Revision History:                                                                                                      |
 | _______________________________________________________________________________________________________________________|
 |                                                                                                                        |
 |                                                                                                                        |
 |                                                                                                                        |
 |                                                                                                                        |
 |                                                                                                                        |
 |                                                                                                                        |
 |________________________________________________________________________________________________________________________}                                                           

 BEGIN CODE
*/
//------------- BEGIN Define Constants & Globals -------------------------------------------------------------------------

String Data_Type;
String Num_Outputs = "16";  
/* Data_Type defines the Packet Type Identifier.  
 *  
 *  A "S" packet or "Switching" packet is initiated via a local physical switch, reactive action to a workshop sensor or via the "Web GUI" 
 * This will allow for processing of data packets of various formats to allow for cross compatible control and packet
 * length processing.  Essentially, Multiple Masters should be able to control and know the status of the connected 
 * devices.
 * 
 * A "A" packet or "Acknowledge" packet is initiated as a status update to the Master and other interested devices reporting the from who, 
 * which switch, and the state.
 */

const int ID = 1;  // This Devices ID
//--- Integer Definitions-------------------------------------------------------------------------------------------------

int FROM_ID;       // Who is the Message Coming From
int TO_ID;         // Who are we sending to?
int Switch;        // Which Local Switch are we needing to address?
int State;        // Are we turning it on or off?
int Sw_Status;
//------------------------------------------------------------------------------------------------------------------------

//--- String Definitions -------------------------------------------------------------------------------------------------
String Version = "VERSION - SLAVE DEVICE - ALPHA a";
String Incoming_Data; // IN_ID, ID, Switch, Status
String Data_Out[8]; // ID,OUT_TO_ID,Switch,Status 

//------------- END Define Constants & Globals ---------------------------------------------------------------------------



//--------------------- BEGIN Configure RS485 BUS ------------------------------------------------------------------------

#include <Auto485.h>
#define DE_PIN 2
#define RE_PIN 3
Auto485 bus(DE_PIN, RE_PIN); // new Auto485 wrapper using DE_PIN & RE_PIN to toggle read/write mode on the MAX485

//--------------------- END Configure RS485 BUS --------------------------------------------------------------------------

//--------------------- BEGIN Pin Assignment and Labeling ------------------------------------------------------------------------

int pin1 = 4;
int pin2 = 5;
int pin3 = 6;
int pin4 = 7;
int pin5 = 8;
int pin6 = 9;
int pin7 = 10;
int pin8 = 11;
int pin9 = 12;
int pin10 = 13;
int pin11 = 14;
int pin12 = 15;
int pin13 = 16;
int pin14 = 17;
int pin15 = 18;
int pin16 = 19;

String pin1_Label =  "RP1 -  OFFLINE";
String pin2_Label =  "RP2 -  OFFLINE";
String pin3_Label =  "RP3 -  OFFLINE";
String pin4_Label =  "RP4 -  OFFLINE";
String pin5_Label =  "RP5 -  OFFLINE";
String pin6_Label =  "RP6 -  OFFLINE";
String pin7_Label =  "RP7 -  OFFLINE";
String pin8_Label =  "RP8 -  OFFLINE";
String pin9_Label =  "RP9 -  OFFLINE";
String pin10_Label = "RP10 - OFFLINE";
String pin11_Label = "RP11 - OFFLINE";
String pin12_Label = "RP12 - OFFLINE";
String pin13_Label = "RP13 - OFFLINE";
String pin14_Label = "RP14 - OFFLINE";
String pin15_Label = "RP15 - OFFLINE";
String pin16_Label = "RP16 - OFFLINE";
//----- BEGIN Setup ------------------------------------------------------------------------------------------------------

void setup() {
  bus.begin(9600); // RS485 Bus at 9600bps
  Serial.begin(9600);

pinMode(pin1, OUTPUT);
pinMode(pin2, OUTPUT);
pinMode(pin3, OUTPUT);
pinMode(pin4, OUTPUT);
pinMode(pin5, OUTPUT);
pinMode(pin6, OUTPUT);
pinMode(pin7, OUTPUT);
pinMode(pin8, OUTPUT);
pinMode(pin9, OUTPUT);
pinMode(pin10, OUTPUT);
pinMode(pin11, OUTPUT);
pinMode(pin12, OUTPUT);
pinMode(pin13, OUTPUT);
pinMode(pin14, OUTPUT);
pinMode(pin15, OUTPUT);
pinMode(pin16, OUTPUT);
//----------------------------------------------------------------------------------
  
  Serial.println(F("       _____________________________________________________"));
  Serial.println(F("       |  Workshop Automation & Reporting Protocol (WARP)  |"));
  Serial.print(F("       |        "));        
  Serial.print(Version);        
  Serial.println(F("          |"));
  Serial.println(F("       |___________________________________________________|"));
  Serial.println(F("       |    Author: S.D. 'Hoffy' Hofmeister  7/14/2017     |"));
  Serial.println(F("       |                                                   |"));
  Serial.println(F("       |___________________________________________________|"));
  Serial.println(F("       |          This work is licensed under the          |"));
  Serial.println(F("       |                 Creative Commons                  |")); 
  Serial.println(F("       |     Attribution-NonCommercial-ShareAlike 4.0      |"));
  Serial.println(F("       |              International License.               |"));
  Serial.println(F("       |          To view a copy of this license,          |"));
  Serial.println(F("       |                      visit                        |"));
  Serial.println(F("       | http://creativecommons.org/licenses/by-nc-sa/4.0/.|"));
  Serial.println(F("       |___________________________________________________|"));
  Serial.println(F("       |                                                   |"));
  Serial.println(F("       |          Serial Debug Terminal Display            |"));
  Serial.println(F("       |___________________________________________________|"));  
  Serial.println(F(""));
Serial.println(F("             Encrypted Certificate of Authenticity               "));
Serial.println(F("                          Short Form                             "));
Serial.println(F("========== Encrypted with Encrypt Easy Text Encryption =========="));
Serial.println(F("vCeOQ3BY/GaeRiURNmrtTgRiDIGAXJhfnzojHWToj7SfIn4Xc/Ii9rPTTQTpKfu/M"));
Serial.println(F("VM1WDQOsS74/ZjayCMEKUx6AnbouYd9sgYWCUKhWZjd6gFRFWKOPn/iHgHV+mWYdq"));
Serial.println(F("hsoNRJIDqvSsSkHWHmROlL7AgODkFAnZ8sLnxSvEyDCew45j7ilsKsLJGm7Ny2Bt7"));
Serial.println(F("YEjEM0V+5ZREHi0FAOyfHUAoPD7pop7sVXdMAkVHEpt5pDuY9hHZME45tUwzG7Bzm"));
Serial.println(F("IKaEU179CHpT7HfspMK1Kr/QrToYj7XVoQGOj/z5yLK8u90o1VzcS3YS5s2cYUb+2"));
Serial.println(F("xuXiBEAIZZ6gd70Ca0cmLZHdmy8F7kIliL+5aZIxW/23lzPexW1NqcOejuGj/Kzxk"));
Serial.println(F("OW2Czu0gM7QtSg0YUmcrAwrSVrV/u9YNgfKEaAKn4R9mTseTb7jgIhbgQcG1yHUix"));
Serial.println(F("SIpAfF0D48yIewmnP+Mj+k7BA4eCXgvdrDw/GZVJBoCfT4bWqMH//cRAdNT0NrRH/"));
Serial.println(F("dd+Yr5Z6TyhcL54NemBLtaydSRFD9FDZdqC3GNG7Z6r8LAQp3ryc5Bu12WD+XmAOo"));
Serial.println(F("CDfoN855gYQj7fuRFbk5wsEceLI++Ukz0aLFMLUfNVBUOnVhUqm89CTAjI5HyrXMc"));
Serial.println(F("X7knANXFjJuiEUDsQdWFTkZecL8CzKIaK0pJ5XLNjaL3h4+oA/VruO8NDuKhGRlZl"));
Serial.println(F("aRNj1WHLBosP32PZcnLYIjSY1nOdoLZX6YsVrVNX618QAdD4r8IGe5jE7ss0J7Wid"));
Serial.println(F("dqbWytbiLEx5UWPClMJBuvZ8DutPVVgciPARhi+Orx/1CE3uk/NqM+mSeIfsVHb7X"));
Serial.println(F("afzvPoCRlGqTfKjaK1G8qfU+MksmsEylVBzC70Qt13nSIBxKcLIkzjJz804JVgrRV"));
Serial.println(F("mKZ5yNdNI9DVqawRlv0MLHCiwXdWfEfr2iV8asyxpxsLAwwh3LBIJO24pSFA+DZ7P"));
Serial.println(F("aFRp3cHZWMaMBvEjGmgj8enROhIw===                                  "));
Serial.println(F("=========== More info at http://www.encrypt-easy.com ============"));
Serial.println(F(""));
Serial.println(F(""));
Serial.println(F(""));
Serial.println(F(""));
Serial.println(F(""));
Serial.print(F("This Devices Unique Bus ID is: "));
Serial.println(ID);   
Serial.println(F(""));
delay(1000);
Serial.flush();
delay(1000);
Serial.println(F("Sending Boot Identification Packet to Master Device"));
delay(1000);
bus.print("B");
bus.print(" ");
bus.print(ID);
bus.print(" ");
bus.print(Num_Outputs);
bus.print(" ");
bus.println("E");
delay(1000);
Serial.flush();
delay(1000);
Serial.println(F("Boot Complete"));
}

//----- END Setup --------------------------------------------------------------------------------------------------------



//----- BEGIN Loop -------------------------------------------------------------------------------------------------------
void loop()
{
    if (bus.available() > 0) 
    {
      
      char c = bus.read();

        if(c == "E")
        {
          parse_Incoming_Data(Incoming_Data);  
          Incoming_Data = "";  
        }
        
        else 
        {
         Incoming_Data += c;
        }
    }
delay(1000);

    
}
//----- END Loop ---------------------------------------------------------------------------------------------------------


//---------FUNCTION :: BEGIN Process Incoming Data Reports From RS485 Bus ------------------------------------------------
void parse_Incoming_Data(String INData)
{
   String DATA_TYPE;
   String FROM_ID_INBOUND;
   String TO_ID_INBOUND;
   String SWITCH_INBOUND;
   String STATE_INBOUND;
   String EOT_CHAR;
    // Inbound Packet Consists of:  ( DATA_TYPE, IN_ID, ID, Switch, Status )

   DATA_TYPE = getStringPartByNr(INData, ' ', 0);
   FROM_ID_INBOUND = getStringPartByNr(INData, ' ', 1);
   TO_ID_INBOUND = getStringPartByNr(INData, ' ', 2);
   SWITCH_INBOUND = getStringPartByNr(INData, ' ', 3);  
   STATE_INBOUND = getStringPartByNr(INData, ' ', 4);
   EOT_CHAR = getStringPartByNr(INData, ' ', 5); 
    
    if (DATA_TYPE == "A")
    {
      FROM_ID = FROM_ID_INBOUND.toInt();
      TO_ID = TO_ID_INBOUND.toInt();

          if (TO_ID == ID) 
          {
            Switch = SWITCH_INBOUND.toInt();
            State = STATE_INBOUND.toInt();

              if (State == 0) 
              {
                digitalWrite(Switch, LOW);
                bus.print("Switch # ");
                bus.print(Switch);
                bus.print("Set To State LOW or OFF");
                Send_Outgoing_Data();
              }
                
              }

              if (State == 1) 
              {
                digitalWrite(Switch, HIGH);
                bus.print("Switch # ");
                bus.print(Switch);
                bus.print("Set To State HIGH or ON");
                Send_Outgoing_Data();
                
              }
        
    
    
  
    else if (DATA_TYPE != Data_Type)
    {
     Error_Handler(1);
    }

}
}
//---------FUNCTION :: END Process Incoming Data Reports From RS485 Bus --------------------------------------------------

// OUTSOURCED FUNCTION https://github.com/BenTommyE/Arduino_getStringPartByNr
String getStringPartByNr(String data, char separator, int index)
{
    // spliting a string and return the part nr index
    // split by separator
    
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text
    
    for(int i = 0; i<data.length()-1; i++) {    //Walk through the text one letter at a time
      
      if(data[i]==separator) {
        //Count the number of times separator character appears in the text
        stringData++;
        
      }else if(stringData==index) {
        //get the text when separator is the rignt one
        dataPart.concat(data[i]);
        
      }else if(stringData>index) {
        //return text and stop if the next separator appears - to save CPU-time
        return dataPart;
        break;
        
      }

    }
    //return text if this is the last part
    return dataPart;
}

//---------FUNCTION :: BEGIN Process Outgoing Data Reports To RS485 Bus ------------------------------------------------

void Send_Outgoing_Data()
{
   Data_Type = "A";
   
   TO_ID = FROM_ID;

   //if (TO_ID == ID) {
   // TO_ID = "0";
   //}
   
   int SWITCH_OUTBOUND;
   SWITCH_OUTBOUND = Switch;
   String SWITCH_CONVERTED;
   SWITCH_CONVERTED = SWITCH_OUTBOUND;   
       
   int STATE_OUTBOUND;
   STATE_OUTBOUND = digitalRead(SWITCH_OUTBOUND);
        

bus.print(Data_Type);
bus.print(" ");
bus.print(ID);
bus.print(" ");
bus.print(TO_ID);
bus.print(" ");
bus.print(SWITCH_OUTBOUND);
bus.print(" ");
bus.print(STATE_OUTBOUND);
bus.print(" ");
bus.println("E");




}
//---------FUNCTION :: END Process Outgoing Data Reports To RS485 Bus --------------------------------------------------




//---------FUNCTION :: BEGIN Error Handling ------------------------------------------------

void Error_Handler(int ERR)  
{  
 switch (ERR) {
/* ERROR CLASS 1: RS485 Communications Error
 *    ERROR #1-001 - Packet Identification Error - Non-Critical
 *    ERROR #1-002 - Packet Parsing Error - Critical
 */
        
  case 1:
    Serial.println(F("ERROR #1-001 - Packet Identification Error - Non-Critical"));
    Serial.println(F("Incoming Data did not begin with the correct packet identifier"));
    break;
  
  case 2:
    Serial.println(F("ERROR #1-002 - Packet Parsing Error - Critical"));
    Serial.println(F("The Data Packet properly identified but did not parse properly during processing"));
    break;
  
  default: 
    Serial.println(F("Undefined Error:: The specific problem could not be identified, but and error has been indicated"));
  break;
}

}
//---------FUNCTION :: END Error Handling --------------------------------------------------




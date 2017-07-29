


/*
 |________________________________________________________________________________________________________________________|
 |----------------------------------- Workshop Automation & Reporting Protocol (WARP) ------------------------------------|
 |                                      VERSION - MASTER DEVICE ALPHA d (UNSTABLE)                                        |
 |________________________________________________________________________________________________________________________|
 |                                                                                                                        |
 |            W.A.R.P - Workshop Automation & Reporting Protocol by Steven D. Hofmeister "Hoffy" is licensed              |
 |                      under a Creative Commons Attribution-ShareAlike 4.0 International License.                        |
 |                  Permissions beyond the scope of this license may be available at hoffysworld.com.                     |
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
 | 1.0  - 7/14/17 - Initial Coding                                                                                        |
 | 1.0a - 7/15/17 - Clarified variable names to avoid reader confusion between local device and remote device actions     |
 | 1.0b - 7/15/17 - Added Code to reject any data without the correct data type identifier                                |                                                        |
 |  "       "     - Error Handling Function Added                                                                         |
 |  "       "     - Created Serial Terminal Identification Header in Setup Function                                       |
 | 1.0c - 7/16/17 - Developed, Debugged, & Tested Local Switch Control Section of Web GUI                                 |
 |  "        "     - Updated Error Handling to address the new packet data types                                                                                                              |
 |________________________________________________________________________________________________________________________}                                                           | 

 BEGIN CODE
*/

//------------- BEGIN External Library Includes -------------------------------------------------------------------------
#include <Auto485.h>
#include <SPI.h>
#include <Ethernet.h>
//------------- END External Library Includes -------------------------------------------------------------------------


//------------- BEGIN Define Constants & Globals -------------------------------------------------------------------------

String Data_Type;  
/* Data_Type defines the Packet Type Identifier.  
 *  
 *  A "S" packet or "Switching" packet is initiated via a local physical switch, reactive action to a workshop sensor or via the "Web GUI" 
 * This will allow for processing of data packets of various formats to allow for cross compatible control and packet
 * length processing.  Essentially, Multiple Masters should be able to control and know the status of the connected 
 * devices.
 * 
 * A "A" packet or "Acknowledge" packet is initiated as a status update to the Master and other interested devices reporting the from who, 
 * which switch, and the state.
 * 
 * A "B" packet or "Boot" packet will send an initial Identifiying packet from a remote device to the master in order to automatically populate
 * the Web GUI with available remote devices and switches
 * 
 * 
 * 
 * 
 * 
 */

const int ID = 0;  // This Devices ID
const int bSize = 20;
//--- Integer Definitions-------------------------------------------------------------------------------------------------
int FROM_ID;       // Who is the Message Coming From
int TO_ID;         // Who are we sending to?
int Switch;        // Which Local Switch are we needing to address?
int Status;        // Are we turning it on or off?
int REMOTE_SWITCH; // Which Remote Switch are we needing to address?
int REMOTE_STATE;  // Are we turning the remote switch on or off?
int Rem_Dev1[4];
int Rem_Dev2[4];
int Rem_Dev3[4];
int Rem_Dev4[4];
int Rem_Dev5[4];
int Rem_Dev6[4];
int Rem_Dev7[4];
int Rem_Dev8[4];
int Rem_Dev9[4];
int Rem_Dev10[4];
int Rem_Dev11[4];
int Rem_Dev12[4];
int Rem_Dev13[4];
int Rem_Dev14[4];
int Rem_Dev15[4];
int Rem_Dev16[4];
int Rem_Dev17[4];
int Rem_Dev18[4];
int Rem_Dev19[4];
int Rem_Dev20[4];
int Rem_Dev21[4];
int Rem_Dev22[4];
int Rem_Dev23[4];
int Rem_Dev24[4];
int Rem_Dev25[4];
int Rem_Dev26[4];
int Rem_Dev27[4];
int Rem_Dev28[4];
int Rem_Dev29[4];
int Rem_Dev30[4];
int Rem_Dev31[4];
int Rem_Dev32[4];

//------------------------------------------------------------------------------------------------------------------------

//--- byte Definitions----------------------------------------------------------------------------------------------------
byte mac[] = { 0x00, 0x08, 0xDC, 0xAB, 0xCD, 0xEF };// Physical MAC address
byte ip[] = { 192, 168, 1, 233 };// Fixed IP address
//------------------------------------------------------------------------------------------------------------------------

//--- String Definitions -------------------------------------------------------------------------------------------------
String Version = "VERSION - MASTER DEVICE ALPHA d (UNSTABLE)";
String LS1_Label  = "OFFLINE";
String LS2_Label  = "OFFLINE";
String LS3_Label  = "OFFLINE";
String LS4_Label  = "OFFLINE";
String LS5_Label  = "OFFLINE";
String LS6_Label  = "OFFLINE";
String LS7_Label  = "OFFLINE";
String LS8_Label  = "OFFLINE";
String LS9_Label  = "OFFLINE";
String LS10_Label = "OFFLINE";
String LS11_Label = "OFFLINE";
String LS12_Label = "OFFLINE";
String LS13_Label = "OFFLINE";
String LS14_Label = "OFFLINE";
String LS15_Label = "OFFLINE";
String LS16_Label = "OFFLINE";
String LS17_Label = "OFFLINE";
String LS18_Label = "OFFLINE";
String LS19_Label = "OFFLINE";
String LS20_Label = "OFFLINE";
String LS21_Label = "OFFLINE";
String LS22_Label = "OFFLINE";
String LS23_Label = "OFFLINE";
String LS24_Label = "OFFLINE";

String RS1_1_Label = "REMOTE OFFLINE";

String REMOTE_SWITCH_STATE; // Is The remote Switch on or off?  HIGH or LOW
String Incoming_Data; // IN_ID, ID, Switch, Status, EOT
String Data_Out[6]; // DATA_TYPE, ID, TO_ID, Switch, Status, EOT
String HTTP_req; // HTML Data 
//------------- END Define Constants & Globals ---------------------------------------------------------------------------

//------------- BEGIN Pin Assignments ------------------------------------------------------------------------------------
int pin1 =  26;
int pin2 =  27;
int pin3 =  28;
int pin4 =  29;
int pin5 =  30;
int pin6 =  31;
int pin7 =  32;
int pin8 =  33;
int pin9 =  34;
int pin10 = 35;
int pin11 = 36;
int pin12 = 37;
int pin13 = 38;
int pin14 = 39;
int pin15 = 40;
int pin16 = 41;
int pin17 = 42;
int pin18 = 43;
int pin19 = 44;
int pin20 = 45;
int pin21 = 46;
int pin22 = 47;
int pin23 = 48;
int pin24 = 49;

//------------- END Pin Assignments ------------------------------------------------------------------------------------


//--------------------- BEGIN Configure RS485 BUS ------------------------------------------------------------------------
#define DE_PIN 2
#define RE_PIN 3
Auto485 bus(DE_PIN, RE_PIN, Serial1); // new Auto485 wrapper using DE_PIN & RE_PIN to toggle read/write mode on the MAX485

//--------------------- END Configure RS485 BUS --------------------------------------------------------------------------

//--------------------- BEGIN Configure HTTP Server ------------------------------------------------------------------------
EthernetServer server(6161);// Server port--------------------

//--------------------- END Configure HTTP Server --------------------------------------------------------------------------


//----- BEGIN Setup ------------------------------------------------------------------------------------------------------

void setup() {
Serial.begin(9600);  // Initialize Debug Terminal  
   
    
  // --------------------------------- START Pin Mode Setup -----------------------------------
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
    pinMode(pin17, OUTPUT);
    pinMode(pin18, OUTPUT);
    pinMode(pin19, OUTPUT);
    pinMode(pin20, OUTPUT);
    pinMode(pin21, OUTPUT);
    pinMode(pin22, OUTPUT);
    pinMode(pin23, OUTPUT);
    pinMode(pin24, OUTPUT);
  // --------------------------------- END Pin Mode Setup -----------------------------------
  
  // --------------------------------- BEGIN Serial Debug Terminal Identification Header ------
    Serial.println("       _____________________________________________________");
    Serial.println("       |  Workshop Automation & Reporting Protocol (WARP)  |");
    Serial.print("       |        ");        
    Serial.print(Version);        
    Serial.println("          |");
    Serial.println("       |___________________________________________________|");
    Serial.println("       |    Author: S.D. 'Hoffy' Hofmeister  7/14/2017     |");
    Serial.println("       |                                                   |");
    Serial.println("       |___________________________________________________|");
    Serial.println("       |          This work is licensed under the          |");
    Serial.println("       |                 Creative Commons                  |"); 
    Serial.println("       |     Attribution-NonCommercial-ShareAlike 4.0      |");
    Serial.println("       |              International License.               |");
    Serial.println("       |          To view a copy of this license,          |");
    Serial.println("       |                      visit                        |");
    Serial.println("       | http://creativecommons.org/licenses/by-nc-sa/4.0/.|");
    Serial.println("       |___________________________________________________|");
    Serial.println("       |                                                   |");
    Serial.println("       |          Serial Debug Terminal Display            |");
    Serial.println("       |___________________________________________________|");  
    Serial.println("");
    Serial.println("             Encrypted Certificate of Authenticity               ");
    Serial.println("                          Short Form                             ");
    Serial.println("========== Encrypted with Encrypt Easy Text Encryption ==========");
    Serial.println("vCeOQ3BY/GaeRiURNmrtTgRiDIGAXJhfnzojHWToj7SfIn4Xc/Ii9rPTTQTpKfu/M");
    Serial.println("VM1WDQOsS74/ZjayCMEKUx6AnbouYd9sgYWCUKhWZjd6gFRFWKOPn/iHgHV+mWYdq");
    Serial.println("hsoNRJIDqvSsSkHWHmROlL7AgODkFAnZ8sLnxSvEyDCew45j7ilsKsLJGm7Ny2Bt7");
    Serial.println("YEjEM0V+5ZREHi0FAOyfHUAoPD7pop7sVXdMAkVHEpt5pDuY9hHZME45tUwzG7Bzm");
    Serial.println("IKaEU179CHpT7HfspMK1Kr/QrToYgGe6lqS1zMy0mLGPE29KdkKpy7xESWHeSQY/R");
    Serial.println("fP0aqACQZeWkb4etCmIUpewcNfwfPZc5YUcE95FoZK+4EOeYLg0rQuZ2h4gWKpcpS");
    Serial.println("03DuIxCHIpmLteTvaEuN6eggePAwq1++c8TZ5xjDDCeib2nAqR3lOnat7S/VDGeGg");
    Serial.println("/VecuXBIpWGF0qj1eRyuBfXWAqGdoVPid5hkN/+98064Q/ZY2Rds3RLagzTOg4Sfi");
    Serial.println("L6owXhA27SKsuN3TEb/vrafuSeAkNmp9hHgoufmHoZ1kRp4AYJKYQ3XaD7hukXkFo");
    Serial.println("a1LeVCndjkK7JWzHLOX7okgVdIe12ICXjElzDrXUy24msLlOj2+mkLdz+Oy2oo59v");
    Serial.println("grrdBakzlwkJhzqH4AHOEtIvZoojOACmokwpWjBij86AwuxiPzdyLR++HBambw+Pn");
    Serial.println("0vhNHG/y1JCJXPZqO9QSBBYcCaQZRj+WUgnOU2MKrtZizc1U+ejaCKCdP3UR3QxJn");
    Serial.println("5gr3dFFe1rvMAXTb9olykt2ufYPqVh0c8iwKOdcChjGAo7Jz7cPPWdxG8uLw2fRgO");
    Serial.println("i1Nr9rfKxzS1krAGUkfW8KrNdrFSBVlsuRp5zmdWbX6tqKsQtjCaAGED5d67/qCyd");
    Serial.println("+Fbj/E/N36W8FhSDy4wqjTCzk7wnAgE8iw9CHNs3kqr8BJdVNTBKV3Roet2aIyALV");
    Serial.println("1eSEMIFGYPDzxokLet4gAOysQyq4===                                  ");
    Serial.println("=========== More info at http://www.encrypt-easy.com ============");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
     // --------------------------------- END Serial Debug Terminal Identification Header ------     
    // ---------------------------------- BEGIN Initialize Communication Buses ----------------
    delay(300);// Delay for Ethernet shield initialization (Arduino has 65mS Power Up delay and W5100 reset logic has 280mS)
    Ethernet.begin(mac, ip);// Start Ethernetbus.begin(9600); // RS485 Bus at 9600bps
    server.begin(); // Initialize HTTP Server
    Serial.println(F("Starting HTTP Server"));
    for (int i=0; i <= 10; i++){
      Serial.print(".");
      delay(500);
    }
    Serial.println("");
    Serial.println(F("HTTP Server Online"));
    Serial.println("");
    
    bus.begin(9600); // Initialize RS-485 Bus
    Serial.println(F("Starting RS-485 Bus Communication"));
    for (int i=0; i <= 10; i++){
      Serial.print(".");
      delay(500);
    }
    Serial.println("");
    Serial.println(F("RS-485 Bus Online"));
    Serial.print("This MASTER Device is Identifying as Device ID: ");
    Serial.print(ID);   
    Serial.println("");
    Serial.println("Boot Complete");
  // ---------------------------------- END Initialize Communication Buses ------------------ 
   
   }  
//----- END Setup --------------------------------------------------------------------------------------------------------

//----- BEGIN Loop -------------------------------------------------------------------------------------------------------
void loop()
{
EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println(F("HTTP/1.1 200 OK"));
                    client.println(F("Content-Type: text/html"));
                    client.println(F("Connection: keep-alive"));
                    client.println();
                    // AJAX request for switch state
                    if (HTTP_req.indexOf("ajax_switch") > -1) {
                        // read switch state and analog input
                        GetAjaxData(client);
                    }
                    else {  // HTTP request for web page
                        // send web page - contains JavaScript with AJAX calls
                        client.println(F("<!DOCTYPE html>"));
                        client.println(F("<html>"));
                        client.println(F("<head>"));
                        client.println(F("<title>W.A.R.P. Web Control Panel</title>"));
                        client.println(F("<script>"));
                        client.println(F("function GetSwitchAnalogData() {"));
                        client.println(F("nocache = \"&nocache=\" + Math.random() * 1000000;"));
                        client.println(F("var request = new XMLHttpRequest();"));
                        client.println(F("request.onreadystatechange = function() {"));
                        client.println(F("if (this.readyState == 4) {"));
                        client.println(F("if (this.status == 200) {"));
                        client.println(F("if (this.responseText != null) {"));
                        client.println(F("document.getElementById('sw_an_data')\.innerHTML = this.responseText;"));
                        client.println(F("}}}}"));
                        client.println(F("request.open(\"GET\", \"ajax_switch\" + nocache, true);"));
                        client.println(F("request.send(null);"));
                        client.println(F("setTimeout('GetSwitchAnalogData()', 1000);"));
                        client.println(F("}"));
                        client.println(F("</script>"));
                        client.println(F("<style type='text/css'>"));
                        client.println(F(".tg  {border-collapse:collapse;border-spacing:0;}"));
                        client.println(F(".tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}"));
                        client.println(F(".tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}"));
                        client.println(F(".tg .tg-3ojx{font-weight:bold;background-color:#333333;color:#ffffff;vertical-align:top}"));
                        client.println(F("@media screen and (max-width: 767px) {.tg {width: auto !important;}.tg col {width: auto !important;}.tg-wrap {overflow-x: auto;-webkit-overflow-scrolling: touch;}}</style>"));
                        client.println(F("</head>"));
                        client.println(F("<body bgcolor='#000000' onload=\"GetSwitchAnalogData()\">"));
                        client.println(F("<h1 style='color:white'>W.A.R.P. Web Control Panel</h1>"));
                        client.println(F("<h3 style='color:white'>Workshop Automation & Reporting Protocol</h3>"));
                        client.print(F("<h4 style='color:grey'>"));
                        client.println(Version);
                        client.println(F("</h4>"));
                        client.println(F("<div id=\"sw_an_data\">"));
                        client.println(F("</div>"));
                        client.println(F("</body>"));
                        client.println(F("</html>"));
                    }
                    // display received HTTP request on serial port
                    //Serial.print(HTTP_req);
                    HTTP_req = "";            // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)

HTTP_req = "";// Clearing string for next read


while(bus.available()) {

Incoming_Data= bus.readString();// read the incoming data as string
Process_Incoming_Data(Incoming_Data);

}

}

//----- END Loop ---------------------------------------------------------------------------------------------------------

// send the state of the switch to the web browser
void GetAjaxData(EthernetClient cl)
{

cl.println(F("<div class='tg-wrap'>"));

cl.println(F("<table class='tg'>"));
cl.println(F("<tr>"));
cl.println(F("<th class='tg-3ojx' colspan='8'>Local Switches</th>"));
cl.println(F("</tr>"));

cl.println(F("<tr>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin1)) {
        cl.println(F("<center><a href='/?LS1_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS1_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS1_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS1_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin2)) {
        cl.println(F("<center><a href='/?LS2_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS2_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS2_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS2_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));


cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin3)) {
        cl.println(F("<center><a href='/?LS3_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS3_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS3_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS3_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin4)) {
        cl.println(F("<center><a href='/?LS4_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS4_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS4_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS4_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin5)) {
        cl.println(F("<center><a href='/?LS5_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS5_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS5_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS5_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin6)) {
        cl.println(F("<center><a href='/?LS6_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS6_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS6_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS6_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin7)) {
        cl.println(F("<center><a href='/?LS7_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS7_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS7_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS7_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin8)) {
        cl.println(F("<center><a href='/?LS8_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS8_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS8_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS8_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("</tr>"));

cl.println(F("</tr>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin9)) {
        cl.println(F("<center><a href='/?LS9_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS9_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS9_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS9_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin10)) {
        cl.println(F("<center><a href='/?LS10_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS10_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS10_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS10_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin11)) {
        cl.println(F("<center><a href='/?LS11_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS11_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS11_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS11_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin12)) {
        cl.println(F("<center><a href='/?LS12_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS12_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS12_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS12_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin13)) {
        cl.println(F("<center><a href='/?LS13_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS13_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS13_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS13_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin14)) {
        cl.println(F("<center><a href='/?LS14_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS14_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS14_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS14_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin15)) {
        cl.println(F("<center><a href='/?LS15_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS15_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS15_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS15_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));;

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin16)) {
        cl.println(F("<center><a href='/?LS16_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS16_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS16_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS16_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("</tr>"));

cl.println(F("<tr>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin17)) {
        cl.println(F("<center><a href='/?LS17_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS17_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS17_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS17_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin18)) {
        cl.println(F("<center><a href='/?LS18_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS18_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS18_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS18_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin19)) {
        cl.println(F("<center><a href='/?LS19_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS19_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS19_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS19_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin20)) {
        cl.println(F("<center><a href='/?LS20_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS20_Label);
        cl.println(F("</p></center>"));
        }
    else {
        cl.println(F("<center><a href='/?LS20_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS20_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin21)) {
        cl.println(F("<center><a href='/?LS21_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS21_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS21_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS21_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin22)) {
        cl.println(F("<center><a href='/?LS22_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS22_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS22_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS22_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin23)) {
        cl.println(F("<center><a href='/?LS23_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS23_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS23_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS23_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("<td class='tg-3ojx'>"));
if (digitalRead(pin24)) {
        cl.println(F("<center><a href='/?LS24_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(LS24_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?LS24_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(LS24_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("</tr>"));

cl.println(F("</table>"));


<<<<<<< HEAD


// Remote Devices GUI Population 
if (Rem_Dev1[0] == 1) {                          
=======
if (Rem_Dev1[0] == 1) {                          //ISSUE  MASTER DEVICE : Line 788 - Device ID not being assigned or properly detected by GUI #1
>>>>>>> parent of 7124d60... Fixed MASTER DEVICE : Line 788 - Device ID not being assigned or properly detected by GUI #1
cl.println(F("<table class='tg'>"));
cl.println(F("<tr>"));
cl.println("<th class='tg-3ojx' colspan='8'> Device # ");
cl.print(Rem_Dev1[0]);
cl.print("</th>");
cl.println(F("</tr>"));

cl.println(F("<tr>"));

cl.println(F("<td class='tg-3ojx'>"));
if (FROM_ID == Rem_Dev1[0] && Rem_Dev1[1]> 0 && REMOTE_SWITCH == Rem_Dev1[1] && REMOTE_STATE == 1) {
        cl.println(F("<center><a href='/?RS1-1_off'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-green.png' height='30' size='30' alt='Switch ON'</a></center>"));
        cl.println(F("<center><p style='color:green'>"));
        cl.print(RS1_1_Label);
        cl.println(F("</p></center>"));
    }
    else {
        cl.println(F("<center><a href='/?RS1-1_on'><img src='http://hoffysworld.creativevisionmedia.net/wp-content/uploads/sites/3/2017/07/Bullet-red.png' height='30' size='30' alt='Switch OFF'</a></center>"));
        cl.println(F("<center><p style='color:red'>"));
        cl.print(RS1_1_Label);
        cl.println(F("</p></center>"));
    }
cl.println(F("</td>"));

cl.println(F("</tr>"));
cl.println(F("</table>"));
}

cl.println(F("</div>"));


    if(HTTP_req.indexOf("/?LS1_on") > 0)digitalWrite(pin1, HIGH);
    if(HTTP_req.indexOf("/?LS1_off") > 0) digitalWrite(pin1, LOW);

    if(HTTP_req.indexOf("/?LS2_on") > 0)digitalWrite(pin2, HIGH);
    if(HTTP_req.indexOf("/?LS2_off") > 0) digitalWrite(pin2, LOW);
    
    if(HTTP_req.indexOf("/?LS3_on") > 0)digitalWrite(pin3, HIGH);
    if(HTTP_req.indexOf("/?LS3_off") > 0) digitalWrite(pin3, LOW);

    if(HTTP_req.indexOf("/?LS4_on") > 0)digitalWrite(pin4, HIGH);
    if(HTTP_req.indexOf("/?LS4_off") > 0) digitalWrite(pin4, LOW);

    if(HTTP_req.indexOf("/?LS5_on") > 0)digitalWrite(pin5, HIGH);
    if(HTTP_req.indexOf("/?LS5_off") > 0) digitalWrite(pin5, LOW);

    if(HTTP_req.indexOf("/?LS6_on") > 0)digitalWrite(pin6, HIGH);
    if(HTTP_req.indexOf("/?LS6_off") > 0) digitalWrite(pin6, LOW);

    if(HTTP_req.indexOf("/?LS7_on") > 0)digitalWrite(pin7, HIGH);
    if(HTTP_req.indexOf("/?LS7_off") > 0) digitalWrite(pin7, LOW);

    if(HTTP_req.indexOf("/?LS8_on") > 0)digitalWrite(pin8, HIGH);
    if(HTTP_req.indexOf("/?LS8_off") > 0) digitalWrite(pin8, LOW);

    if(HTTP_req.indexOf("/?LS9_on") > 0)digitalWrite(pin9, HIGH);
    if(HTTP_req.indexOf("/?LS9_off") > 0) digitalWrite(pin9, LOW);

    if(HTTP_req.indexOf("/?LS10_on") > 0)digitalWrite(pin10, HIGH);
    if(HTTP_req.indexOf("/?LS10_off") > 0) digitalWrite(pin10, LOW);

    if(HTTP_req.indexOf("/?LS11_on") > 0)digitalWrite(pin11, HIGH);
    if(HTTP_req.indexOf("/?LS11_off") > 0) digitalWrite(pin11, LOW);

    if(HTTP_req.indexOf("/?LS12_on") > 0)digitalWrite(pin12, HIGH);
    if(HTTP_req.indexOf("/?LS12_off") > 0) digitalWrite(pin12, LOW);

    if(HTTP_req.indexOf("/?LS13_on") > 0)digitalWrite(pin13, HIGH);
    if(HTTP_req.indexOf("/?LS13_off") > 0) digitalWrite(pin13, LOW);

    if(HTTP_req.indexOf("/?LS14_on") > 0)digitalWrite(pin14, HIGH);
    if(HTTP_req.indexOf("/?LS14_off") > 0) digitalWrite(pin14, LOW);

    if(HTTP_req.indexOf("/?LS15_on") > 0)digitalWrite(pin15, HIGH);
    if(HTTP_req.indexOf("/?LS15_off") > 0) digitalWrite(pin15, LOW);

    if(HTTP_req.indexOf("/?LS16_on") > 0)digitalWrite(pin16, HIGH);
    if(HTTP_req.indexOf("/?LS16_off") > 0) digitalWrite(pin16, LOW);

    if(HTTP_req.indexOf("/?LS17_on") > 0)digitalWrite(pin17, HIGH);
    if(HTTP_req.indexOf("/?LS17_off") > 0) digitalWrite(pin17, LOW);

    if(HTTP_req.indexOf("/?LS18_on") > 0)digitalWrite(pin18, HIGH);
    if(HTTP_req.indexOf("/?LS18_off") > 0) digitalWrite(pin18, LOW);

    if(HTTP_req.indexOf("/?LS19_on") > 0)digitalWrite(pin19, HIGH);
    if(HTTP_req.indexOf("/?LS19_off") > 0) digitalWrite(pin19, LOW);

    if(HTTP_req.indexOf("/?LS20_on") > 0)digitalWrite(pin20, HIGH);
    if(HTTP_req.indexOf("/?LS20_off") > 0) digitalWrite(pin20, LOW);

    if(HTTP_req.indexOf("/?LS21_on") > 0)digitalWrite(pin21, HIGH);
    if(HTTP_req.indexOf("/?LS21_off") > 0) digitalWrite(pin21, LOW);

    if(HTTP_req.indexOf("/?LS22_on") > 0)digitalWrite(pin22, HIGH);
    if(HTTP_req.indexOf("/?LS22_off") > 0) digitalWrite(pin22, LOW);

    if(HTTP_req.indexOf("/?LS23_on") > 0)digitalWrite(pin23, HIGH);
    if(HTTP_req.indexOf("/?LS23_off") > 0) digitalWrite(pin23, LOW);

    if(HTTP_req.indexOf("/?LS24_on") > 0)digitalWrite(pin24, HIGH);
    if(HTTP_req.indexOf("/?LS24_off") > 0) digitalWrite(pin24, LOW);

    //Remote Switch Actions
    
    if(HTTP_req.indexOf("/?RS1-1_on") > 0)
  {
   // DATA_TYPE, ID, TO_ID, Switch, Status, EOT
    bus.print("A");
    bus.print(" ");
    bus.print(ID);
    bus.print(" ");
    bus.print(Rem_Dev1[0]);
    bus.print(" ");
    bus.print("1");
    bus.print(" ");
    bus.print("1");
    bus.print(" ");
    bus.println("E");
    
  }
    
    if(HTTP_req.indexOf("/?RS1-1_off") > 0) 
    {
    bus.print("A");
    bus.print(" ");
    bus.print(ID);
    bus.print(" ");
    bus.print(Rem_Dev1[0]);
    bus.print(" ");
    bus.print("1");
    bus.print(" ");
    bus.print("0");
    bus.print(" ");
    bus.println("E");

}
    


delay(150);
}

    



//---------FUNCTION :: BEGIN Process Incoming Data Reports From RS485 Bus ------------------------------------------------

void Process_Incoming_Data(String INData)

{
   String DATA_TYPE;
   String FROM_ID_INBOUND;
   String TO_ID_INBOUND;
   String REMOTE_SWITCH_INBOUND;
   String REMOTE_STATUS_INBOUND;
   String EOT_CHAR;
    // Inbound Packet Consists of:  ( DATA_TYPE, IN_ID, ID, Switch, Status )

   DATA_TYPE = getStringPartByNr(INData, ' ', 0);
   
   
    if (DATA_TYPE == "S")
    {
     FROM_ID_INBOUND = getStringPartByNr(INData, ' ', 1);
     TO_ID_INBOUND = getStringPartByNr(INData, ' ', 2);
     REMOTE_SWITCH_INBOUND = getStringPartByNr(INData, ' ', 3);  
     REMOTE_STATUS_INBOUND = getStringPartByNr(INData, ' ', 4);
     EOT_CHAR = getStringPartByNr(INData, ' ', 5); 
      
      FROM_ID = FROM_ID_INBOUND.toInt();
      TO_ID = TO_ID_INBOUND.toInt();

          if (TO_ID == ID) 
          {
            REMOTE_SWITCH = REMOTE_SWITCH_INBOUND.toInt();
            REMOTE_STATE = REMOTE_STATUS_INBOUND.toInt();

              if (REMOTE_STATE == 0) 
              {
                
              }

              if (REMOTE_STATE == 1) 
              {
                
              }
        }
    
    }
  
    if (DATA_TYPE == "B"){

String Device = getStringPartByNr(INData, ' ', 1);

String Num_Outputs = getStringPartByNr(INData, ' ', 2);
int OUTPUT_COUNT = Num_Outputs.toInt();
int Device_ID = Device.toInt();

Serial.print("Receiving Boot Packet From Device#: ");
Serial.print(Device_ID);
Serial.println("");
//if (Device_ID > 0 && Device_ID <= 32)
    //{
        // 1 to 32

        switch (Device_ID)
        {
            case 1:
                Rem_Dev1[0] = Device_ID;
<<<<<<< HEAD
                for (int i=1; i <= OUTPUT_COUNT; i++){
=======
                Serial.println("I am assigning value to device array");
                Serial.print("The Rem_Dev1[0] Value has been set to:");
                Serial.print(Rem_Dev1[0]);
                for (int i=0; i <= OUTPUT_COUNT; i++){
>>>>>>> parent of 7124d60... Fixed MASTER DEVICE : Line 788 - Device ID not being assigned or properly detected by GUI #1
                Rem_Dev1[i] = i;
                                
                }
                break;
            
            case 2:
                Rem_Dev2[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev2[i] = i;
                                
                }
                break;
                
            case 3:
                Rem_Dev3[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev3[i] = i;
                                
                }
                break;
            
            case 4:
                Rem_Dev4[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev4[i] = i;
                                
                }
                break;
            
            case 5:
                Rem_Dev5[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev5[i] = i;
                                
                }
                break;         
                       
            case 6:
                Rem_Dev6[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev6[i] = i;
                int L = i+2;
                
                
                }
                break;           
                
            case 7:
                Rem_Dev7[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev7[i] = i;
                                
                }
                break;
        
           case 8:
                Rem_Dev8[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev8[i] = i;
                                
                }
                break;
        
          case 9:
                Rem_Dev9[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev9[i] = i;
                
                
                }
                break;
        
          case 10:
                Rem_Dev10[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev10[i] = i;
                
                }
                break;


          case 11:
                Rem_Dev11[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev11[i] = i;
                
                }
                break;

          
          case 12:
                Rem_Dev12[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev12[i] = i;
                
                }
                break;

          case 13:
                Rem_Dev13[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev13[i] = i;
                
                }
                break;
          
         case 14:
                Rem_Dev14[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev14[i] = i;
                
                }
                break;
        
        
        case 15:
                Rem_Dev15[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev15[i] = i;
                
                }
                break;
        
        case 16:
                Rem_Dev16[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev16[i] = i;
                
                }
                break;
        
        case 17:
                Rem_Dev17[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev17[i] = i;
                
                }
                break;

        case 18:
                Rem_Dev18[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev18[i] = i;
                
                }
                break;

        case 19:
                Rem_Dev19[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev19[i] = i;
                
                }
                break;

        case 20:
                Rem_Dev20[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev20[i] = i;
                
                }
                break;

        case 21:
                Rem_Dev21[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev21[i] = i;
                
                }
                break;

        case 22:
                Rem_Dev22[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev22[i] = i;
                
                }
                break;

        case 23:
                Rem_Dev23[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev23[i] = i;
                
                }
                break;

        case 24:
                Rem_Dev24[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev24[i] = i;
                
                }
                break;

        case 25:
                Rem_Dev25[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev25[i] = i;
                
                }
                break;

        case 26:
                Rem_Dev26[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev26[i] = i;
                
                }
                break;

        case 27:
                Rem_Dev27[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev27[i] = i;
               
                }
                break;

        case 28:
                Rem_Dev28[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev28[i] = i;
                
                }
                break;

        case 29:
                Rem_Dev29[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev29[i] = i;
                }
                break;

        case 30:
                Rem_Dev30[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev30[i] = i;
                }
                break;

        case 31:
                Rem_Dev31[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev31[i] = i;
                }
                break;

        case 32:
                Rem_Dev32[0] = Device_ID;
                for (int i=0; i <= OUTPUT_COUNT; i++){
                Rem_Dev32[i] = i;
                }
                break;
        
    //}

delay(10);
}
  
delay(10);



}


   else if (DATA_TYPE != "A" || "B" || "S")
    {
              
     Error_Handler(1);
    }

}
//---------FUNCTION :: END Process Incoming Data Reports From RS485 Bus --------------------------------------------------
  

//---------FUNCTION :: END Parse Incoming Data Reports From RS485 Bus --------------------------------------------------
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
//---------FUNCTION :: END Parse Incoming Data Reports From RS485 Bus --------------------------------------------------



void Error_Handler(int ERR)  
{  
 switch (ERR) {
/* ERROR CLASS 1: RS485 Communications Error
 *    ERROR #1-001 - Packet Identification Error - Non-Critical
 *    ERROR #1-002 - Packet Parsing Error - Critical
 */
        
  case 1:
    Serial.println("ERROR #1-001 - Packet Identification Error - Non-Critical");
    Serial.println("Incoming Data did not begin with the correct packet identifier");
    Serial.println("");
    break;
  
  case 2:
    Serial.println("ERROR #1-002 - Packet Parsing Error - Critical");
    Serial.println("The Data Packet properly identified but did not parse properly during processing");
    Serial.println("");
    break;
  
  default: 
    Serial.println("Undefined Error:: The specific problem could not be identified, but and error has been indicated");
    
    
  break;
}
return;
}




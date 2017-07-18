W.A.R.P. - Workshop Automation & Reporting Protocol

Narrative::
------------------------------------------------------------------------------------------------------------------------------------
W.A.R.P. is being developed for the proprietary use in my basement workshop.  It is not being developed for use anywhere else,
however you are welcome to custom fit it to your application under the terms of the license below and the LICENSE file
found in the repository at https://github.com/hoffy/WARP./
  
W.A.R.P. is an RS485 Half Duplex Based Home Automation Protocol or Network.  
Using a three wire TRANSMIT, RECEIVE, Common Ground BUS.  The Arduino's will use Serial Communication via the auto485 library
developed by madleech.  Serial Communication is transceived to the BUS via MAX485 8 Pin DIP IC's as notated below.  The BUS will
consist of standard CAT 5/6 Cable as used for Ethernet networking, but only three (3) wires will be employed at this time.

A BUS Schematic will be provided once developed.
  
W.A.R.P. will utilize an Arduino Mega 2560 Microcontroller as the "MASTER" unit equipped with a Seeed Studios Ethershield Ver. 1.0.

W.A.R.P. will utilize Arduino Pro Mini Microcontrollers as the "SLAVE" Units.

License::
------------------------------------------------------------------------------------------------------------------------------------
                  W.A.R.P - Workshop Automation & Reporting Protocol by Steven D. Hofmeister "Hoffy" is licensed 
                            under a Creative Commons Attribution-ShareAlike 4.0 International License.        
                         Permissions beyond the scope of this license may be available at hoffysworld.com.
                         
          Credit for components, libraries, and functions produced by other authors are notated further down in this document

------------------------------------------------------------------------------------------------------------------------------------

Purpose::
-------------------------------------------------------------------------------------------------------------------------------------
W.A.R.P.'s purpose is to provide a network based GUI to control various componments around the workshop.  S
ometimes, I will retire upstairs and forget to turn something off.  W.A.R.P. will allow for me to not only have local control via 
manual switch, but also the ability to override that switch via the GUI remotely.

Example:  Main Workshop Lights are left on.  Even though the manaual light swtich is turned on, I will be able to tell those lights 
to turn off through the GUI.  Once returning to the Workhop, by turning the manual Switch OFF and then ON again will reactivate the
lights locally.

The Main Workshop Light Outlet Box will be fitted with a 110VAC to 12VDC voltage converter, An Arduino Pro Mini with a digitally
controlled relay and the additional hardware for the RS485 BUS.  The light switch cover will be adapted to contain a Status LED and
device reset switch.

Similar device configurations will be deployed as well.

Eventually, analog data reporting will be phased into the protocol, allowing for various readings to be reported back to the GUI
or for data logging to a MYSQL Database.
-------------------------------------------------------------------------------------------------------------------------------------

Hardware Requirements::
------------------------------------------------------------------------------------------------------------------------------------
  Seeed Studios Ethershield Ver. 1.0 or later or compatible Wiznet 5100 Shield/Hardware 
  - http://wiki.seeedstudio.com/wiki/Ethernet_Shield_V1.0

  MAX485 Transceiver IC 
  - https://datasheets.maximintegrated.com/en/ds/MAX1487-MAX491.pdf

Required Arduino IDE Libraries:: 
-------------------------------------------------------------------------------------------------------------------------------------
  #include <Auto485.h> - https://github.com/madleech/Auto485
  
  #include <SPI.h> - Arduino IDE Native Library
  
  #include <Ethernet.h> - Arduino IDE Native Library


Provided Functions:: 
-------------------------------------------------------------------------------------------------------------------------------------

  Function inside code: getStringPartByNr 

    Arduino_getStringPartByNr

    Arduino function that return a stringpart from a string - determine by a number

    Inspired by split feature in several programming languages.
    https://github.com/BenTommyE/Arduino_getStringPartByNr


-------------------------------------------------------------------------------------------------------------------------------------

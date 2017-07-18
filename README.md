W.A.R.P. - Workshop Automation & Reporting Protocol

Narrative::
------------------------------------------------------------------------------------------------------------------------------------

W.A.R.P. is being developed for the proprietary use in my basement workshop.  It is not being developed for use anywhere else,
however you are welcome to custom fit it to your application under the terms of the license below and the LICENSE file
found in the repository at https://github.com/hoffy/WARP./
  
W.A.R.P. is an RS485 Half Duplex Based Home Automation Protocol or Network.  
Using a three wire TRANSMIT, RECEIVE, Common Ground BUS.
  
W.A.R.P. will utilize an Arduino Mega 2560 as the master unit
-------------------------------------------------------------------------------------------------------------------------------------

License::
------------------------------------------------------------------------------------------------------------------------------------
                  W.A.R.P - Workshop Automation & Reporting Protocol by Steven D. Hofmeister "Hoffy" is licensed 
                            under a Creative Commons Attribution-ShareAlike 4.0 International License.        
                         Permissions beyond the scope of this license may be available at hoffysworld.com.
                         
          Credit for components, libraries, and functions produced by other authors are notated further down in this document

------------------------------------------------------------------------------------------------------------------------------------

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

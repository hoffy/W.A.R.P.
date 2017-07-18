W.A.R.P. - Workshop Automation & Reporting Protocol

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

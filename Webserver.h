/****************************************************************************************************

RepRapFirmware - Webserver

This class serves web pages to the attached network.  These pages form the user's interface with the
RepRap machine.  It interprests returned values from those pages and uses them to Generate G Codes,
which it sends to the RepRap.  It also collects values from the RepRap like temperature and uses
those to construct the web pages.

It implements very very restricted PHP.  It can do:

   <?php print(myStringFunction()); ?>
   <?php if(myBooleanFunction()) print(myOtherStringFunction()); ?>
   <?php if(myOtherBooleanFunction()) echo 'Some arbitrarily long string of HTML including newlines up to this quote:'; ?>

Note that by printing a function that returns "" you can just call 
that function in this C++ code with no effect on the loaded web page.

-----------------------------------------------------------------------------------------------------

Version 0.1

13 February 2013

Adrian Bowyer
RepRap Professional Ltd
http://reprappro.com

Licence: GPL

****************************************************************************************************/

#ifndef WEBSERVER_H
#define WEBSERVER_H

#define CLIENT_CLOSE_DELAY 1000 // Microseconds to wait after serving a page

#define PASSWORD_PAGE "passwd.php"
#define STRING_LENGTH 1000
#define PHP_TAG_LENGTH 200
#define PHP_IF 1
#define PHP_ECHO 2
#define PHP_PRINT 3
#define NO_PHP 99
#define IGNORE_FILE_EXTENSIONS { "php", "htm", "png", "prf" } // User won't want to print or delete these
#define IGNORE_LENGTH 4

class Webserver
{   
  public:
  
    Webserver(Platform* p);
    boolean Available();
    byte Read();
    void spin();
    
  private:
  
    void ParseClientLine();
    void IncomingByte(unsigned char b);
    void SendFile(char* nameOfFileToSend);
    void WriteByte();
    boolean StringEndsWith(char* string, char* ending);
    boolean StringStartsWith(char* string, char* starting);
    void ParseQualifier();
    void CheckPassword();
    boolean LoadGcodeBuffer(char* gc, boolean convertWeb);
    void CloseClient();
    void initialisePHP();
    char PHPParse(char* phpString);
    boolean printHeadString();
    boolean printLinkTable();
    char* getGCodeTable();
    boolean callPHPBoolean(char* phpRecord);
    char* callPHPString(char* phpRecord);  
    void ProcessPHPByte(char b);
    void WritePHPByte();
    char* prependRoot(char* fileName);
    
    Platform* platform;
    unsigned long lastTime;
    int fileBeingSent;
    boolean writing;
    boolean inPHPFile;
    boolean clientLineIsBlank;
    unsigned long clientCloseTime;
    boolean needToCloseClient;
    char scratchString[STRING_LENGTH];
    char clientLine[STRING_LENGTH];
    char clientRequest[STRING_LENGTH];
    char clientQualifier[STRING_LENGTH];
    char gcodeBuffer[GCODE_LENGTH];
    boolean gcodeAvailable;
    int gcodePointer;
    int clientLinePointer;
    boolean gotPassword;
    char* password;
    char* myName;
    char phpTag[PHP_TAG_LENGTH];
    char phpRecord[PHP_TAG_LENGTH];
    int inPHPString;
    int phpPointer;
    boolean phpEchoing;
    boolean phpIfing;
    boolean phpPrinting;
    boolean eatInput;
    boolean recordInput;
    boolean ifWasTrue;
    boolean sendTable;
    char eatInputChar;
    int phpRecordPointer;
    boolean ifwasTrue;
    char* ignoreExtensions[IGNORE_LENGTH];
};


#endif


#pragma once
#ifndef _ERRORS_H
#define _ERRORS_H


/*


NAME
     Errors - Keeps tracks of the errors encountered and displays them.

DESCRIPTION
     
     Errors class - Class to manage error reporting. Note: all members are 
     static so we can access them anywhere.

*/



#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
   static  void InitErrorReporting();

    // Records an error message.
   static void RecordError( string  a_emsg );

    // Displays the collected error message.
    static  void DisplayErrors( );

    static bool NoErrors(); // Returns if the errors are recorded or not
 
    static void PrintCurrentError();// To print the latest error encountered

private:
    
};
#endif
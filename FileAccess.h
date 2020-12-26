
#ifndef _FILEACCESS_H  // This is the way that multiple inclusions are defended against often used in UNIX
#define _FILEACCESS_H // We use pramas in Visual Studio.  See other include files

/**/
/*
FileAccess Class
NAME
     FileAccess - Provides ability to read source code.
DESCRIPTION
     FileAccess class - File access to source file which is passed
     through command line argument. Allows to open and read the 
     file line by line.
AUTHOR
     Bishal Thapa
DATE
    4/30/2020
*/
/**/
#include <fstream>
#include <stdlib.h>
#include <string>


/*


NAME
     FileAccess - Provides Access to the source file

DESCRIPTION

     FileAccesss class - Class to manage file Access. It reads source 
     code from the file line by line and reports error if encountered.

*/



class FileAccess {

public:

    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file.
    bool GetNextLine( string &a_buff );

    // Put the file pointer back to the beginning of the file.
    void rewind( );

private:

    ifstream m_sfile;		// Source file object.
};
#endif


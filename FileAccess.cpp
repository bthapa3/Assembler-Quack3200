//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"


/*


NAME
    FileAccess - constructor for the file access class.
SYNOPSIS

    FileAccess::FileAccess( int argc, char *argv[] );
    argc  --> total number of arguments received through the command line.
    *argv[] --> a pointer for the arguments list recieved through command line.

DESCRIPTION

    It is the constructor for the file access class.It opens the file and if 
    unsuccesful reports an error.


*/


// Don't forget to comment the function headers.
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
}


/*


NAME
    ~FileAccess - Desstructor for the file access class.
SYNOPSIS

    FileAccess::~FileAccess();
    

DESCRIPTION

    When an object goes out of scope it closes the file.

*/

FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}


/*


NAME
    GetNextLine - provides a line of source code at a time.

SYNOPSIS

   bool FileAccess::GetNextLine( string &a_buff );
   a_buff--> string parameter passed by reference to write a line of source code.

DESCRIPTION

   This function reads the file and writes a line of source code into the referenced.
   string variable.

RETURNS
    
    Returns true if line is succesfully written, false if end of file is reached.



*/

bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
}




/*
NAME

    rewind - starts reading the file from the begining.

SYNOPSIS

    void FileAccess::rewind( )

DESCRIPTION

    This function cleans all file flags to go back to the beginning of the file
    by moving the file access pointer.



*/

void FileAccess::rewind( )
{
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}
    

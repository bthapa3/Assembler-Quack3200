#include "stdafx.h"
#include "Errors.h"

#pragma once
static vector <string> m_ErrorMsgs; // vector to push back errors
bool errorinlastline=false; //Keeps track of last instruction errors.

/*


NAME

    InitErrorReporting -clears the errors previously recorded

SYNOPSIS

    void  Errors::InitErrorReporting()

DESCRIPTION

    Initializes the Errors by clearing the error items existing in the vector.


*/

void  Errors::InitErrorReporting()
{
    errorinlastline = false;
}


/*


NAME

    RecordError - Records the errors encountered

SYNOPSIS
    void Errors::RecordError(string  a_emsg)
    a_emsg--> It is a string parameter that passes the information about the error.

DESCRIPTION

    This function records the errors by pusing them to a vector of strings. Ignored if
    same error is encountered more than once.


*/


void Errors::RecordError(string  a_emsg)
{   
    std::vector<string>::iterator it = std::find(m_ErrorMsgs.begin(), m_ErrorMsgs.end(), a_emsg);
    if (it == m_ErrorMsgs.end())
    {
        m_ErrorMsgs.push_back(a_emsg);
        
    }
    errorinlastline = true;
    
}


/*

  NAME

      Errors::DisplayErrors - Displays the errors recorded

  SYNOPSIS
    void Errors::DisplayErrors()

  DESCRIPTION

      This function displays the errors recorded in the vector.


  */
void Errors::DisplayErrors()
{
    cout << "          Final Errors list:           " << endl;
    for (std::vector<string>::iterator it = m_ErrorMsgs.begin(); it != m_ErrorMsgs.end(); ++it)
    {
        std::cout   << *it;
        std::cout << '\n';
    }
};


/*

  NAME

      Errors::DisplayErrors - Displays the errors recorded

  SYNOPSIS
    void Errors::DisplayErrors()

  DESCRIPTION

      This function displays the error recorded from the last line.
      If last line of sourcecode doesnot have errors it doesnot
      display anything.


  */
void Errors::PrintCurrentError()
{
    if (errorinlastline == true)
    {
        cout << m_ErrorMsgs.back()<<endl;
        errorinlastline = false;
    }

}


/*


NAME

    NoErrors - tells if the errors were encountered.
  
SYNOPSIS
      
    bool  Errors::NoErrors()

DESCRIPTION

    This function checks if the error has been pushed at least once.

RETURNS
    
    It returns a boolean value true if the vector is empty, false otherwise.

*/
 
bool  Errors::NoErrors()
{
    return m_ErrorMsgs.empty();
}

 
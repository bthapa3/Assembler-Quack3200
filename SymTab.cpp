//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"


/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );
    a_symbol--> symbol to insert in the symbol table.
    a_loc-->location to record for the symbol.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/


void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/*
NAME

    DisplaySymbolTable - Displays symbols and locations recorded in the symbol table

SYNOPSIS

    void SymbolTable::DisplaySymbolTable()

DESCRIPTION

    This function will go through the symbol table and display symbols and
    their location. It also works on recording the error if the label has invalid 
    location or if the label is multiply defined.
*/

void SymbolTable::DisplaySymbolTable() 
{
    int numberofsymbols = 0; // to count the total number of symbols
    cout << "Symbol#      Symbol  " << "           " << "Location" << endl;
    for (map<string, int>::iterator st = m_symbolTable.begin();st != m_symbolTable.end();st++) 
    {
        cout << numberofsymbols++<< "             "<<setw(20) << left << st->first << setw(10) << left << st->second << endl;
        if (!isalpha(st->first[0]) || st->first.size()>10)
        {
            Errors::RecordError("Error! Invalid Label Format");
        }
        
        if (st->second == -999)
        {
            Errors::RecordError("Error! Multiply defined label found");
            
        }
    }
    cout << "______________________________________________" << endl;
    Errors::PrintCurrentError();
    Errors::InitErrorReporting();

}

/*
NAME

    LookupSymbol- Finds the location of the symbol.

SYNOPSIS

    bool SymbolTable::LookupSymbol(string a_symbol, int& a_loc) 
    a_symbol--> symbol stored on the symbol table
    a_loc--> location of the symbol.

DESCRIPTION

    This function will find the location of the symbol "a_symbol"
    and store it on integer variable "a_loc" which is passed by reference.
    It will also return boolean value true if symbol is found. If not
    found it will record error and return false.

*/


bool SymbolTable::LookupSymbol(string a_symbol, int& a_loc) 
{
    for (map<string, int>::iterator st = m_symbolTable.begin();st != m_symbolTable.end();st++)
    {   

        
        if (st->first == a_symbol)
        {
            if (st->second == -999)
            {
                Errors::RecordError("Error! Multiply defined label found");
                a_loc = 0;
                return false;
            }  
            else
            {
                a_loc = st->second;
                return true;
            }
        }
    }
    Errors::RecordError("Error! Undefined label found:" + a_symbol);
    return false;
}
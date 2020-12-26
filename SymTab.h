

#pragma once
#include "Errors.h"

/*


NAME
     SymbolTable - Manages the symbol and their location

DESCRIPTION

     SymbolTable class - It works with storing the labels and and their location 
     found in the source code into the map. It can also print SymbolTable and 
     look up the existence and the location of the symbol in the symbol table.

*/

class SymbolTable {

public:
  
    // Get rid of constructor and destructor if you don't need them.
    SymbolTable( ) {};
    ~SymbolTable( ) {};
    
    const int multiplyDefinedSymbol = -999;

    // Add a new symbol to the symbol table.
    void AddSymbol( string &a_symbol, int a_loc );

    // Display the symbol table.
    void DisplaySymbolTable();

    // Lookup a symbol in the symbol table.
    bool LookupSymbol(string a_symbol, int& a_loc);

private:

    // This is the actual symbol table.  The symbol is the key to the map.
    map<string, int> m_symbolTable;
};

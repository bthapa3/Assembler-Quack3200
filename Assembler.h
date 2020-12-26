//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once



/*

NAME
     Assembler - Translates the source code into Quack 3200
     machine level code and emulates it.
DESCRIPTION
    It contains all the necessary elements for translating machine 
    code, detecting/displaying errors and running translated machine
    code in emulator.

*/



#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    Assembler( int argc, char *argv[] );
    ~Assembler( );

    // Pass I - establish the locations of the symbols
    void PassI( );

    // Pass II - generate a translation
    void PassII( );

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }
    
    // Run emulator on the translation.
    void RunProgramInEmulator();

    //Display information on the screen
    void DisplaytoScreen(int a_loc, int a_machinecode, string a_line);
private:

    SymbolTable m_symtab;  //Symbol Table object
    FileAccess m_facc;	    // File Access object
    Instruction m_inst;	    // Instruction object
    Emulator m_emul;  // Emulator object
 
};


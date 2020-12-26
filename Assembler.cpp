//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/*
NAME

    Assembler - The constructor for the Assembler class.

SYNOPSIS

    Assembler::Assembler( int argc, char *argv[] );
    argc  --> total number of arguments received through the command line.
    *argv[] --> a pointer for the arguments list recieved through command line.
   

DESCRIPTION
    This is the constructor for the Assembler class. It receives
    the arguments argc and *argv[] from the commandline and 
    passes them to the file access class constructor. 

*/

 
Assembler::Assembler( int argc, char *argv[] )

// Destructor currently does nothing.  You might need to add something as you develope this project.
    : m_facc(argc, argv)
{
    // Nothing else to do here at this point.
}
//Destructor for the Assembler
Assembler::~Assembler( )
{
}


/*
NAME

     PassI  - The first pass of the Assembler.

SYNOPSIS

    void  Assembler::PassI();

DESCRIPTION

    Pass I establishes the location of the labels and also 
    establishes the symbol table.


*/



void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction( line);
        
        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
	    }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {

           m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
      
    }
} 


/*

NAME

    PassII  - The second pass of the Assembler.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    Pass II goes thorugh the source code again and works mainly to
    translate to generate machine code. In addition, Pass II checks
    for any possible errors and prints and records them. Pass II
    also prints the location, generated machine code and orignal
    instruction on the screen. Finally, Pass II inserts location 
    and the generated machine code to the memory of the emulator class.
     
*/


void Assembler::PassII() {
    m_facc.rewind();
    int loc = 0;
    cout << "Location" << "     " << "Contents"  << "               " << "Original Statement" << endl;
    for (; ; )
    {
        // Read the next line from the source file.
        string line;
        int changedmachinecode=0; // To change the symbolic instruction from  a line to  machinecode
        if (!m_facc.GetNextLine(line)) {
            Errors::RecordError("Error! Missing End statement");  // No endline error reported by Pass II.
            return;
        }
        
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        if (st == Instruction::ST_End)
        {
            DisplaytoScreen(-1, 0, line); // -1 refers no location and 0 refers no machine code
            bool commentorempty = true;;
            while (m_facc.GetNextLine(line) && commentorempty == true)
            {
                if (m_inst.ParseInstruction(line) == Instruction::ST_AssemblerInstr ||
                    m_inst.ParseInstruction(line) == Instruction::ST_MachineLanguage)
                {
                    Errors::RecordError("Error! More instruction found after Endline!-Location:"+to_string(loc));
                    commentorempty = false;
                }
            }
            // If no more instructions return or else continue producing machine code
            if (commentorempty)  return;
        }

        if (st != Instruction::ST_Comment && st != Instruction::ST_End)
        {
            changedmachinecode = m_inst.TranslatetoMachineCode(m_symtab);
            // Print location, machine code and original instruction.
            DisplaytoScreen(loc, changedmachinecode, line);
            if (changedmachinecode != 0)  m_emul.insertMemory(loc, changedmachinecode);
                
        }
        // In case of Comment instruction only print instruction line
        else { DisplaytoScreen(-1, 0, line); }
        
        // Compute the location of the next instruction.
       loc = m_inst.LocationNextInstruction(loc); 
       if (loc<0 || loc >99999)
       {
           Errors::RecordError("Invalid Memory location used");
           return;
       }
       
    }
} 


/*

NAME

    DisplaytoScreen - Display information on the screen.

SYNOPSIS

   void Assembler::DisplaytoScreen(int loc, int machinecode,string line )'
   a_loc--> location of the machine code
   a_machinecode--> translated machine code
   a_line--> original source code instruction

DESCRIPTION

    This funtion initially display the symbol table on the screen.
    It also display location, changed machine code and the
    original statement in the screen. If any error is occured in any
    line of the code it also displays the errors.


*/
void Assembler::DisplaytoScreen(int a_loc, int a_machinecode,string a_line )
{
    if(a_machinecode<1)
    {
        (a_loc == -1) ? cout << right << "     " : cout << right << a_loc;
        cout << "           " << setw(8) << "       " << setfill(' ') << setw(20) << "   " << a_line << endl;
    }
    else
    {
        cout <<  right  << a_loc << "         "  << setw(8) << setfill('0')<< a_machinecode << setfill(' ') << setw(20)<< "   " << a_line << endl;
    }
    Errors::PrintCurrentError();
}




/*
NAME

    Assembler::RunProgramInEmulator  - The Emulator for the Assembler.

SYNOPSIS

    void  Assembler::RunProgramInEmulator()


DESCRIPTION
    Initially checks if the errors have been recorded. If errors found,
    displays errors and the program is halted. Else runs the code 
    generated by Pass II in emulator.


*/

void Assembler::RunProgramInEmulator()
{  
    if (Errors::NoErrors()) m_emul.runProgram();
    else   Errors::DisplayErrors();   
}



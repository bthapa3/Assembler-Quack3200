
#pragma once
#include"Symtab.h"
#include"Errors.h"

/*


NAME
     Instruction - Class to parse and provide information about instructions

DESCRIPTION

     Instruction class - It works with identifying the type of instruction
     from a source code and converting source code into machine code. It deals
     with identifying objects like Label, Opcode, Register,Operands from the source 
     code.It also deals with recording multiple kinds of errors.

*/


class Instruction {

public:

    Instruction() { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End                   		// end instruction.
    };
   
    InstructionType ParseInstruction(string & a_buff );  // Parse the Instruction.
    int TranslatetoMachineCode(SymbolTable m_symtab); //Translating instructions to machine level code
    int LocationNextInstruction(int a_loc); // Compute the location of the next instruction.
    
    int GetOpcodeValue( string m_reg[]);// used to extract the Opcode number from the string values.
    int GetRegisterValue();// To get the register number from the instruction line
    inline string GetOperandCode() // For extracting the Operandcode from the instruction
    {
       return (m_wordcontainer[m_wordcontainer.size() - 1]);
    }
     
    inline string &GetLabel( ) // To access the label
    {
        return m_Label;
    };
    
    inline bool isLabel() // To determine if a label is blank.
    {
        return !m_Label.empty();
    }
    
    inline size_t numofinstructions()//To determine the number of keywords in a given instruction
    {
        return m_wordcontainer.size();
    }
     
  
private:


    // The elemements of a instruction
    string m_Label;            // The label.
    int m_Register;	    // The register specified.  Use -1 if there is none.
    int m_OpCode;       // The symbolic op code.
    int m_Operand;      // The operand.
    string m_instruction;    // The original instruction.

    // Derived values.
    // int m_NumOpCode;     // The numerical value of the op code.
    //int m_NumRegister;	   // the numberic value for the register.
    InstructionType m_type; // The type of instruction.
    //vector to store  labels, opcode , register number and memory address from string. 
    vector <string> m_wordcontainer; 
    //Array containing all the possible Opcodes
    string m_OpcodeTable[13] = { "ADD","SUB", "MULT", "DIV", "LOAD", "STORE", "READ","WRITE","B","BM","BZ" , "BP", "HALT" };
};



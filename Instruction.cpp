#include "stdafx.h"
#include "Instruction.h"
#pragma once

/*
NAME

    ParseInstruction - find out the instruction type
SYNOPSIS

    Instruction::InstructionType Instruction::ParseInstruction(string & a_buff);
    a_buff--> string variable that holds a line of source code to be parsed. 

DESCRIPTION

    This function takes a line of source code and finds out the instruction type 
    for that specific line. Records error if the length of instruction is invalid.
    Returns in data type Instruction::InstructionType which is an enum data type.

*/

Instruction::InstructionType Instruction::ParseInstruction(string & a_buff) {
    m_Label = "";
    m_Register = 0;
    m_Operand = 0;
    m_OpCode = 0;
    m_instruction = a_buff;
    
    m_wordcontainer.clear();  // initially clearing the contents of the strings container vector
    //removing comment from a line
    std::string cleanstr(a_buff.begin(), std::find(a_buff.begin(), a_buff.end(), ';'));
    
    for (int i = 0; i < cleanstr.length(); i++) // replacing commas with an empty space
    {
        if (cleanstr[i] == ',') cleanstr[i] = ' ';  
    }
    
    istringstream ss(cleanstr); // To create induvidual strings from a line of an instruction
    do {
        string word;
        ss >> word;
        m_wordcontainer.push_back(word);

    } while (ss);
    m_wordcontainer.pop_back();//removing empty string at the end of vector.

    // If there is no item in vector it is Comment or blank line
    if (m_wordcontainer.size()==0)  m_type= ST_Comment;     		
    
    else if (m_wordcontainer.size() == 1 ) // If there is one item in the vector
    {   
        if (((m_wordcontainer[0]) == "end") || ((m_wordcontainer[0]) == "END")) m_type = ST_End;
        else  m_type = ST_MachineLanguage; 
    }

    else if (m_wordcontainer.size() == 2)  //If there are two items in the  vector
    {
        if (m_wordcontainer[0] == "org" || m_wordcontainer[0] == "ORG")
        {
            m_type= ST_AssemblerInstr;//  Assembler Language instruction.
        }
        else 
        {   //Label is only possible with halt
            if(m_wordcontainer[1]=="halt" || m_wordcontainer[1] == "HALT")  m_Label = m_wordcontainer[0];
            m_type= ST_MachineLanguage; //Machine language 
        }
    }
    
    else if (m_wordcontainer.size() == 3) // If there are three items in the vector
    {
        if (m_wordcontainer[1] == "ds" || m_wordcontainer[1] == "dc" ||
            m_wordcontainer[1] == "DS" || m_wordcontainer[1] == "DC" )
        {
            m_Label = m_wordcontainer[0];
            m_type= ST_AssemblerInstr; // Assembler Language instruction.
        }
        else 
        {    //Because these three Opcode donot need register.
            if ( m_wordcontainer[1] == "read" || m_wordcontainer[1] == "write" ||  m_wordcontainer[1] == "b" ||
                m_wordcontainer[1] == "READ" || m_wordcontainer[1] == "WRITE" || m_wordcontainer[1] == "B")
            {
                m_Label = m_wordcontainer[0];  
            }
            m_type= ST_MachineLanguage; //Machine language 
        }
    }
    
    else  // Machine language  if there are four items in the vector. 
    {
        m_Label = m_wordcontainer[0];  
        m_type = ST_MachineLanguage;
    }
   
    return m_type;
}


/*

NAME
    LocationNextInstruction - generates location of next instruction.
SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc)
    a_loc--> the current memory location of the instruction

DESCRIPTION

    This function generates the location of the next instruction based on the 
    instruction type of the current instruction. Returns an integer value with
    the location of the next instruction.
     
*/


int Instruction::LocationNextInstruction(int a_loc) {
    
    
    if (m_type ==ST_End || m_type==ST_Comment)// If end or Comment instruction return the same location.
    {
        return a_loc;
    }
    if (m_type == ST_AssemblerInstr) {
        
        if (m_wordcontainer[0] == "org" || m_wordcontainer[0] == "ORG")  return stoi(m_wordcontainer[1]);
        else if (m_wordcontainer[1] == "ds" || m_wordcontainer[1] == "DS")
        {    //Error check for DS operand
            for (int i = 0;i < m_wordcontainer[2].size();i++)
            {
                // Going to the next instruction in case DS instruction doesnot have valid operand. 
                if (!isdigit(m_wordcontainer[2][i]))
                {
                    return a_loc;
                }
            }
            return a_loc + stoi(m_wordcontainer[2]);//only if ds has valid operand        
        }
        
    }
    // For storage declaration; add current location and defined storage.

    return a_loc + 1; // For other instructions add one to the location. 
}

/*

NAME
    GetOpcodevalue - gets Opcode value in the instruction.
SYNOPSIS

   int Instruction::GetOpcodevalue(string a_string, string reg[]);
   a_reg[]--> an array of strings containing all the string Opcode in order.

DESCRIPTION

    This function calculates the numeric Opcode value.  Compares the string 
    opcode found in the instruction with the opcodes found in an array of 
    string opcodes to determine numeric opcode value. returns an integer 
    value with the numeric Opcode valued between 1 and 13.

*/

int Instruction::GetOpcodeValue( string a_reg[]) // Returns numeric operation code value from the string opcode value.
{
    m_OpCode = 0;
    string Opcode_val;   
    isLabel() ? Opcode_val = m_wordcontainer[1]: Opcode_val = m_wordcontainer[0];
    // converting string opcode value to uppercase
    transform(Opcode_val.begin(), Opcode_val.end(), Opcode_val.begin(), ::toupper); 
    
    for (int i = 0; i < 13;i++) 
    {   // comparing string operation code with the operation codes on array
        if (a_reg[i] == Opcode_val) { m_OpCode = i + 1; }   
    }
    
    if (m_OpCode == 0) Errors::RecordError("Error! Undefined Opcode found: "+ Opcode_val);
    return m_OpCode; 
}

/*

NAME
    GetRegisterValue - generates Register value if possible 
SYNOPSIS

    int Instruction::GetRegisterValue()

DESCRIPTION

    This function calculates numeric value of the register used in the instruction.
    If register number is found it will return integer value with register number 
    between 1 to 9. Else it will return 0.
    

*/
int Instruction::GetRegisterValue() 
{     // For 2 words instruction and 3 words instructions without label
     if ( (!isLabel() && numofinstructions() == 3))  
     {  // checks if the stored string matches the register number format
        if ( m_wordcontainer[1].length()==1 &&  isdigit(m_wordcontainer[1][0]))   
        {
            return stoi(m_wordcontainer[1]); // the register number 
        }
        // If the register is not found in its place.
        Errors::RecordError("Invalid Register format:" + m_wordcontainer[1]);
        
     }
    else if (numofinstructions()==4) 
    {
         if (m_wordcontainer[2].length() == 1 && isdigit(m_wordcontainer[2][0]))
         {
             return stoi(m_wordcontainer[2]); // the register number
         }
        Errors::RecordError("Invalid Register format:"+m_wordcontainer[2]);
    }
     return 0;
}

/*

NAME
    TranslatetoMachineCode- Generates machine code from symbolic code.
SYNOPSIS

    int Instruction::TranslatetoMachineCode(SymbolTable m_symtab)
    m_symtab--> symbol table object that holds labels and their location.

DESCRIPTION

    This function is responsible for converting a line of source code into
    machine code at a time and returning it as an integer. Numeric values of 
    Register, Opcode and Operand are put together to create machine code. It 
    also deals with recording multiple types of errors.

*/

int Instruction::TranslatetoMachineCode(SymbolTable m_symtab)
{
    int changedmachinecode = 0;
   
    if (numofinstructions()>4) // if the instruction is too large i.e more than 4 words
    {
        Errors::RecordError("Error! Instruction too long");
        return 0;
    }

    if(m_type==ST_AssemblerInstr)  // If the instruction is Assembler level instruction
    {
        // For checking errors of the operand
        if (m_wordcontainer[1] == "dc" || m_wordcontainer[1] == "DC" || (m_wordcontainer[1] == "ds" || m_wordcontainer[1] == "DS"))
        {   
            for (int i = 0;i < m_wordcontainer[2].size();i++) //Checking if the Operand are valid for Aseembly instructions
            {
                if (!isdigit(m_wordcontainer[2][i]))
                {
                    Errors::RecordError("Error! Undefined operand for assembly instruction");
                    return -1;
                }
            }
            if (stoi(m_wordcontainer[2]) > 99999)
            {
                Errors::RecordError("Error! Operand too large to handle: " + (m_wordcontainer[2]));
                return -1;
            }
        }
        //Operand for DC instruction
        if (m_wordcontainer[1] == "dc" || m_wordcontainer[1] == "DC")
        {
            changedmachinecode = stoi(m_wordcontainer[2]);
        }
        //Operand for DS instruction
        else if (m_wordcontainer[1] == "ds" || m_wordcontainer[1] == "DS") changedmachinecode = 0; 
    }

    if (m_type == ST_MachineLanguage) // If the instruction is machine level instruction
    {
        m_Register = 9; //default Register number
        m_Operand = 0;
        m_OpCode = GetOpcodeValue(m_OpcodeTable);// Getting the Opcode value from the instruction line
        
        if (numofinstructions() == 2) // There are two keywords in the instruction
        {   // Label is not present in the instruction
            // Using symbol table to get Operand/address using the symbols.
            if (!isLabel())  m_symtab.LookupSymbol(GetOperandCode(), m_Operand); 
           
        }

        else if (numofinstructions() == 3) // There are three keywords in the instruction
        {
            m_symtab.LookupSymbol(GetOperandCode(), m_Operand);// Using symbol table to get Operand/address using the symbols.
            // If label is not present register is present   
            if (!isLabel())  m_Register=GetRegisterValue();     
        }
        
        else if (numofinstructions()==4) //There are all four keywords
        {
            m_Register=GetRegisterValue();// Getting the register value
            m_symtab.LookupSymbol(GetOperandCode(),m_Operand);  // Using symbol table to get Operand/address using the symbols.
        }
        
        else if (numofinstructions() > 4) {return false;}
        changedmachinecode = m_OpCode * 1000000 + m_Register * 100000 + m_Operand;    
    }
    return changedmachinecode;
};
#include "stdafx.h"
#include"emulator.h"
#include"Errors.h"


/*


NAME

	insertMemory()

SYNOPSIS

	bool Emulator::insertMemory(int a_location, int a_contents)
	a_location--> the memory location to enter machine code
	a_contents--> the machine code to be entered


DESCRIPTION
    
	Checks if the location to insert machine code is inside the limit.
	If so inserts the machine code into the subsequent memory address.
	
RETURNS
 
	returns a boolean value to state if the insertion was succesful or not.

*/


bool Emulator::insertMemory(int a_location, int a_contents)
{   
	if (a_location>-1 && a_location<100000)
	{
		
		if(m_counter==0) // this can only run once
		{
			m_location = a_location; //startlocation of the machine code
			m_counter++;
		}
		m_memory[a_location] = (a_contents);
		return true;
	}
	else
	{
		Errors::RecordError("Invalid Memory location used to insert machine code");
		return false;
	}

};





/*


NAME
                  
	runProgram - Emulator to run the machine code
    		
SYNOPSIS

	bool Emulator::runProgram()

DESCRIPTION

	It is the simulator for the Quack 3200 computer. It uses the machine code 
	stored in the memory to produce the output. 

RETURNS

	returns a boolean value to state if the simulation is completed succesfully.



*/


bool Emulator::runProgram()
{
	while ( m_Opcodeval!=13) {
	   m_currentvalue = (m_memory[m_location]);
	   m_Opcodeval = m_currentvalue / 1000000;
	   m_registerNumber = (m_currentvalue % 1000000) / 100000;
	   m_Operandvalue = m_currentvalue % 100000;
	   string Entervalue;

		switch (m_Opcodeval)
		{

		case 1:
			// Opcode:add - Performs addition Operation on m_register and Operand
			m_reg[m_registerNumber] = m_reg[m_registerNumber] + m_memory[m_Operandvalue];;
			m_location++;
			break;

		case 2: 
			//Opcode: sub - Subtracts Operand from m_register
			m_reg[m_registerNumber] = m_reg[m_registerNumber] - m_memory[m_Operandvalue];
			m_location++;
			break;

		case 3:
			//Opcode: mul - Multiply m_register and Operands value
			m_reg[m_registerNumber] = m_reg[m_registerNumber] * m_memory[m_Operandvalue];
			
			m_location++;
			break;

		case 4:
			//Opcode: div- Divides m_register vlaue by operand value
			m_reg[m_registerNumber] = m_reg[m_registerNumber] / m_memory[m_Operandvalue];;
			m_location++;
			break;

		case 5:
			//Opcode: load- Loads Opearand value to the m_register
			m_reg[m_registerNumber] = m_memory[m_Operandvalue];
			m_location++;
			break;

		case 6:
			//Opcode:store- Stores m_register's value at the operand 
			m_memory[m_Operandvalue] = m_reg[m_registerNumber];
			m_location++;
			break;

		case 7:
			//Opcode :read - Reads a value from a user and stores it at Operand location
			cout << "?";
            cin >> Entervalue;
			 
			m_memory[m_Operandvalue] = stoi( Entervalue);
			m_location++;

			break;

		case 8:
			//Opcode: Write- Displays the memory Operand value to the user
			cout << m_memory[m_Operandvalue] << endl;
			m_location++;
			break;

		case 9:
			//Opcode :b - Makes an uncondition jump to the operand value
			m_location = m_Operandvalue;
			break;

		case 10:
			// Opcode:bm()- Makes a conditional jump of brach if negative
			
			if (m_reg[m_registerNumber] < 0)
			{
				m_location = m_Operandvalue;
			}
			else
			{
				m_location++;
			}
			break;

		case 11:
			//Opcode: bz()- Makes an conditional jump of bramch if zero
			if (m_reg[m_registerNumber] == 0)
			{
				m_location = m_Operandvalue;
			}
			else
			{
				m_location++;
			}
			break;

		case 12:
			//Opcode: bp()- Makes a conditional jump of branch if positive
			if (m_reg[m_registerNumber] > 0)
			{
				m_location = m_Operandvalue;
			}
			else
			{
				m_location++;
			}
			break;

		case 13:
			//Opcode:Halt - Stops the emualtor/end of machine code reached
			break;

		default:
			// if Opcode is invalid due to error
			cout << "Error running the machine code at:" + to_string(m_location) << endl;
	        return false;
		}	
		

	}
	return true;
}




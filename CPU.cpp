#include "CPU.h"
#include "stdio.h"
#include <unistd.h>

#define NOP 0x0
#define LDA 0x1
#define ADD 0x2
#define SUB 0x3
#define STA 0x4
#define LDI 0x5
#define JMP 0x6
#define JC  0x7
#define JZ  0x8
#define OUT 0xE
#define HALT 0xF



CPU::CPU()
{
    pc = 0;
    
    registerA = 0;
    registerB = 0;
    instructionRegister = 0;
    outputRegister = 0;
    
    for(int i=0; i<16; i++){
        memory[i] = 0;
    }
    
    CF = false;
    ZF = false;
    HLT = false;
}

void CPU::loadProgram()
{
    //FIBONACCI
  memory[0]  = (LDI << 4)  | 0x1;
  memory[1]  = (STA << 4)  | 0xE;
  memory[2]  = (LDI << 4)  | 0x0;
  memory[3]  = (STA << 4)  | 0xF;
  memory[4]  = (OUT << 4)  | 0x0;
  memory[5]  = (LDA << 4)  | 0xE;
  memory[6]  = (ADD << 4)  | 0xF;
  memory[7]  = (STA << 4)  | 0xE;
  memory[8]  = (OUT << 4)  | 0x0;
  memory[9]  = (LDA << 4)  | 0xF;
  memory[10] = (ADD << 4)  | 0xE;
  memory[11] = (JC << 4)   | 0xD;
  memory[12] = (JMP << 4)  | 0x3;
  memory[13] = (HALT << 4) | 0x0;
  memory[14] = 0x00;
  memory[15] = 0x01;

  // 7 - 3 = 4
//  memory[0]  = (LDA << 4)  | 0x8;
//  memory[1]  = (ADD << 4)  | 0x9;
//  memory[2]  = (SUB << 4)  | 0xA;
//  memory[3]  = (STA << 4)  | 0xF;
//  memory[4]  = (OUT << 4)  | 0x0;
//  memory[5]  = (HALT << 4) | 0x0;
//  memory[6]  = NOP;
//  memory[7]  = NOP;
//  memory[8]  = NOP;
//  memory[9]  = 0x07;
//  memory[10] = 0x03;
//  memory[11] = 0x02;
//  memory[12] = NOP;
//  memory[13] = NOP;
//  memory[14] = NOP;
//  memory[15] = NOP;
  
  
  //Count up to 255 then down. (Increment of 3)
//  memory[0]  = (LDI << 4)  | 0x0;
//  memory[1]  = (OUT << 4)  | 0x0;
//  memory[2]  = (ADD << 4)  | 0x9;
//  memory[3]  = (JC << 4)   | 0x5;
//  memory[4]  = (JMP << 4)  | 0x1;
//  memory[5]  = (SUB << 4)  | 0x9;
//  memory[6]  = (OUT << 4)  | 0x0;
//  memory[7]  = (JZ << 4)   | 0x2;
//  memory[8]  = (JMP << 4)  | 0x5;
//  memory[9]  = 0x02;
//  memory[10] = NOP;
//  memory[11] = NOP;
//  memory[12] = NOP;
//  memory[13] = NOP;
//  memory[14] = NOP;
//  memory[15] = NOP;

    //MULTIPLICATION (DOESNT WORK)
//  memory[0]  = (LDA << 4)  | 0xC;
//  memory[1]  = (SUB << 4)  | 0xE;
//  memory[2]  = (JC << 4)   | 0x8;
//  memory[3]  = (STA << 4)  | 0xC;
//  memory[4]  = (LDA << 4)  | 0xB;
//  memory[5]  = (ADD << 4)  | 0xD;
//  memory[6]  = (STA << 4)  | 0xB;
//  memory[7]  = (JMP << 4)  | 0x0;
//  memory[8]  = (LDA << 4)  | 0xB;
//  memory[9]  = (OUT << 4)  | 0x0;
//  memory[10] = (HALT << 4) | 0x0;
//  memory[11] = 0x00;
//  memory[12] = 0x07;
//  memory[13] = 0x06;
//  memory[14] = 0x01;
//  memory[15] = 0x00;
}

void CPU::executeOp()
{
    uint8_t opCode = (instructionRegister & 0xF0) >> 4;
    uint8_t opData = (instructionRegister & 0x0F);
    
    if(opCode == NOP)
    {
        //No operation
    }
    else if(opCode == LDA)
    {
        registerA = memory[opData];
    }
    else if(opCode == ADD)
    {
        registerB  = memory[opData];
        registerA = registerA + registerB;
        
        CF = (registerA + registerB) > 255;
        ZF = registerA == 0;
    }
    else if(opCode == SUB)
    {
        registerB  = memory[opData];
        registerA = registerA - registerB;
        
        CF = (registerA - registerB) > 255;
        ZF = registerA == 0;
    }
    else if(opCode == STA)
    {
        memory[opData] = registerA;
    }
    else if(opCode == LDI)
    {
        registerA = opData;
    }
    else if(opCode == JMP)
    {
        pc = opData;
        pc--;        //Because the run() loop increments pc automatically
    }
    else if(opCode == JC)
    {
        if(CF)
        {
            pc = opData;
            pc--;
        }
    }
    else if(opCode == JZ)
    {
        if(ZF)
        {
            pc = opData;
            pc--;
        }
    }
    else if(opCode == OUT)
    {
        outputRegister = registerA;
        printf("OUTPUT: %d (%02X)\n", outputRegister, outputRegister);
    }
    else if(opCode == HALT)
    {
        HLT = true;
    }
}

void CPU::run()
{
    while(!HLT)
    {
        instructionRegister = memory[pc];
        this->executeOp();
        usleep(100000);
        pc++;
    }
    printf("Halting the system...\n");
}


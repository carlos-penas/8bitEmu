#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
public:
    CPU();

    void loadProgram();

    void executeOp();
    
    void run();

private:
    //Program counter
    int pc;
    
    //Registers
    uint8_t registerA;
    uint8_t registerB;
    
    uint8_t instructionRegister;
    uint8_t outputRegister;
    
    //RAM
    uint8_t memory[16];
    
    //Flags
    bool CF;
    bool ZF;
    bool HLT;
};

#endif /* CPU_H */


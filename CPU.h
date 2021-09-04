/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: carlos
 *
 * Created on September 4, 2021, 10:19 AM
 */

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


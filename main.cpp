/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: carlos
 *
 * Created on September 4, 2021, 10:18 AM
 */

#include <cstdlib>
#include "CPU.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    CPU cpu;
    cpu.loadProgram();
    cpu.run();   
    
    return 0;
}


#include <cstdlib>
#include "CPU.h"

using namespace std;

int main(int argc, char** argv) {
    CPU cpu;
    cpu.loadProgram();
    cpu.run();   
    
    return 0;
}


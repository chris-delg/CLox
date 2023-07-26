#include <stdio.h>
#include "../include/common.h"
#include "../include/vm.h"
#include "../include/debug.h"

VM vm;

static void resetStack(){
    vm.stackTop = vm.stack; //point the satck pointer to the stack
}

void initVM(){
    resetVm();
}

void freeVM(){

}

void push(Value value){
    *vm.stackTop = value;  //stores "value" at the top of the stack
    vm.stackTop++; //increment to point to next unused spot in stack
}

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;  //no need to remove from stack, stackTop is all we care about
}

static InterpretResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINARY_OP(op)\
        do{ \
            double b = pop(); \
            double a = POP(); \
            push(a op b); \
        } while(false)

    for(;;){
        #ifdef DEBUG_TRACE_EXCECUTION 
            printf("          ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch(instruction = READ_BYTE()){
            case OP_CONSTANT:{
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:{
                BINARY_OP(+);
                break;
            }
            case OP_SUBTRACT:{
                BINARY_OP(-);
                break;
            }
            case OP_MULTIPLY:{
                BINARY_OP(*);
                break;
            }
            case OP_DIVIDE:{
                BINARY_OP(/);
                break;
            }
            case OP_NEGATE:{
                push(-pop());
                break;
            }
            case OP_RETURN:{
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
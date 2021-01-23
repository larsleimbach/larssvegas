//
//  stack.h
//  effi_blatt10
//
//  Created by Lars Leimbach on 18.01.21.
//

#ifndef stack_h
#define stack_h

#include <inttypes.h>
#include "aufg10.1.h"


typedef struct{
    //aufgabe 10.1a)
    uint8_t bool_darfAusgewaehltWerden;
    uint8_t bool_hasValue;
    uint16_t data;
    //children array
    int numbersOfOtherPossibleData;
    int currentSelected;
    int indexOfOtherPossibleData[S1_SIZE];//-1 = no index
}Data;

Data dataArray[S1_SIZE];
Data *dummyData;
Data *backtrackStack[OWN_STACKSIZE];

uint16_t storageForDynProg[DYNAMIC_STORAGE_SIZE];

uint32_t backtrackStack_fillSize;//ist auch gleichzeitig der Head wo sachen dran bzw weg genommen werden.


Data* stackPop(Data* stack[OWN_STACKSIZE]);
void stackPush(Data* stack[OWN_STACKSIZE], Data *value);
Data* stackGetFirst(Data* stack[OWN_STACKSIZE]);

#endif /* stack_h */

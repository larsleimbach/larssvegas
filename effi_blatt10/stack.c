//
//  stack.c
//  effi_blatt10
//
//  Created by Lars Leimbach on 18.01.21.
//
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"
#include "stack.h"
#include "aufg10.1.h"


Data* stackPop(Data* stack[OWN_STACKSIZE]){
    if (backtrackStack_fillSize > 0){
        backtrackStack_fillSize--;
        Data *tmpReturner = stack[backtrackStack_fillSize];
        tmpReturner->bool_darfAusgewaehltWerden = 1;
        stack[backtrackStack_fillSize] = dummyData;
        return tmpReturner;
    }
    return NULL;
}
void stackPush(Data* stack[OWN_STACKSIZE], Data *value){
    if (OWN_STACKSIZE > backtrackStack_fillSize){
        value->bool_darfAusgewaehltWerden = 0;
        stack[backtrackStack_fillSize] = value;
        backtrackStack_fillSize++;
    }
    else{
        printf("\n\nError:    NO PLACE in stack! make OWN_STACKSIZE higher.\n\n");
        exit(1);
    }
}

Data* stackGetFirst(Data* stack[OWN_STACKSIZE]){
    if(backtrackStack_fillSize>0 && stack[backtrackStack_fillSize-1]->bool_hasValue){
        return stack[backtrackStack_fillSize-1];
    }
    return NULL;
}

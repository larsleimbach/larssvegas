//
//  utils.h
//  effi_blatt10
//
//  Created by Lars Leimbach on 20.01.21.
//

#ifndef utils_h
#define utils_h

#include "aufg10.1.h"
#include "stack.h"

void makeDataArrayAndStack(void);

void insertionSort(Data E[S1_SIZE]);

void insertionSort_uint(uint16_t E[S1_SIZE], uint32_t currentSizeOfStorage);

void makeChildren_EmptyStack_resetSumme(uint16_t startKnoten);

void makeDynamicStorage(void);

int binSearch_uint(uint16_t E[S1_SIZE], uint16_t K, uint32_t currentSizeOfStorage);

int liniarSearch_uint(uint16_t E[S1_SIZE], uint16_t K, uint32_t currentSizeOfStorage);


#endif /* utils_h */

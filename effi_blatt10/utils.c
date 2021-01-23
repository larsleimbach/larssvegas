//
//  utils.c
//  effi_blatt10
//
//  Created by Lars Leimbach on 20.01.21.
//
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"
#include "stack.h"
#include "aufg10.1.h"

void printForAnalyse(void);

void makeDataArrayAndStack(void){
    uint16_t S[S1_SIZE] = {163, 475, 160, 674, 85, 916, 461, 307, 349, 86, 198, 466, 709, 973, 981, 374, 766, 473, 342, 191, 393, 300, 11};
   // uint16_t S[S1_SIZE] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039};
    
    for (uint16_t i = 0; i < S1_SIZE ; i++) {
        Data tmpData;
        tmpData.data = S[i];
        tmpData.bool_darfAusgewaehltWerden = 1;
        tmpData.bool_hasValue = 1;
        dataArray[i] = tmpData;
    }
    
    //achtung dumme loesung!
    insertionSort(dataArray);
    
    
    
    //make Stack
    backtrackStack_fillSize = 0;
    for (uint16_t i = 0; i < OWN_STACKSIZE ; i++) {
        backtrackStack[i] = dummyData;
    }
    
    
        
}


void makeChildren_EmptyStack_resetSumme(uint16_t startKnoten){
    summe = 0;
    
    //empty stack
    while (backtrackStack_fillSize>0) {
        stackPop(backtrackStack);
    }
    
    
    for (uint16_t curKnoten = startKnoten; curKnoten < S1_SIZE ; curKnoten++){
        
        for (uint16_t i = 0; i < S1_SIZE ; i++){
            dataArray[curKnoten].indexOfOtherPossibleData[i] = -1;
        }
        dataArray[curKnoten].numbersOfOtherPossibleData = 0;
        dataArray[curKnoten].currentSelected = -1;
        
        for (uint16_t i = startKnoten; i < S1_SIZE ; i++){
            if (i!=curKnoten && dataArray[curKnoten].bool_darfAusgewaehltWerden && dataArray[curKnoten].data < dataArray[i].data && dataArray[curKnoten].data+dataArray[i].data <= goals[GOAL_NUMBER]) {
                
                dataArray[curKnoten].currentSelected = 0;
                dataArray[curKnoten].indexOfOtherPossibleData[dataArray[curKnoten].numbersOfOtherPossibleData] = i;
                dataArray[curKnoten].numbersOfOtherPossibleData++;
                
            }
        }
        
    }
}

void printSummandenInDynaik(uint64_t currentStorage){
    //die current storage size gibt an mit welchen indezies die summe gebildet wurde
    printf("\n");
    //currentStorage ++;
    uint16_t bitCount = 0;
    uint16_t checkSumme = 0;
    while (currentStorage != 0) {
        uint8_t LSB = currentStorage & 1;//LeastSignificantBit
        if (LSB) {
            if (bitCount >= S1_SIZE) {
                printf("\nattention running out of S1 Array, bitCOunt\n");
            }
            printf("%d + ",dataArray[bitCount].data);
            checkSumme += dataArray[bitCount].data;
            
        }
        
        bitCount++;
        currentStorage = currentStorage >> 1;
    }
    if(checkSumme == goals[GOAL_NUMBER]){
        printf("= %d",goals[GOAL_NUMBER]);
        
    }else{
        printf(" != %d  THERES a fuckup Bug, good luck!",goals[GOAL_NUMBER]);
    }
    
}

void makeDynamicStorage(void){//its a kind of magic
    //hier ist die data eine Summe und die Children sind die Kntoen die diese Summe erzeugen

    uint32_t goalCounter = 0;
    
    uint64_t anzahlAllerSummen = (1<<S1_SIZE);//2^(S1_SIZE)
    
    while (anzahlAllerSummen != 0) {
        anzahlAllerSummen--;
        //pruefe ob aktuelle summe unsere ziel summe ist:
        uint16_t bitCount = 0;
        uint16_t checkSumme = 0;
        uint64_t currentStorage = anzahlAllerSummen;
        while (currentStorage != 0) {
            uint8_t LSB = currentStorage & 1;//LeastSignificantBit
            if (LSB) {
                if (bitCount >= S1_SIZE) {
                    printf("\nattention running out of S1 Array, bitCOunt\n");
                }
                checkSumme += dataArray[bitCount].data;
            }
            bitCount++;
            currentStorage = currentStorage >> 1;
        }
        
        //printe es schoen
        if (checkSumme == goals[GOAL_NUMBER]) {
            goalCounter++;
            printSummandenInDynaik(anzahlAllerSummen);
        }
        
    }
    printf("\ngoalCounter: %d\n", goalCounter);
}

void insertionSort(Data E[S1_SIZE]) {
    
    for(uint16_t i=1;i < S1_SIZE;i++){
        Data v = E[i]; // speichere E[i]
        int j;
        for (j = i; j > 0 && E[j-1].data > v.data; j--) {
            E[j] = E[j-1]; // schiebe Element j-1 nach rechts
        }
        E[j] = v; // füge E[i] an der richtigen Stelle ein 9}
    }
}

void insertionSort_uint(uint16_t E[S1_SIZE],uint32_t currentSizeOfStorage) {
    
    for(uint32_t i=1;i < currentSizeOfStorage;i++){
        uint16_t v = E[i]; // speichere E[i]
        int j;
        for (j = i; j > 0 && E[j-1] > v; j--) {
            E[j] = E[j-1]; // schiebe Element j-1 nach rechts
        }
        E[j] = v; // füge E[i] an der richtigen Stelle ein 9}
    }
}


void printForAnalyse(void){
    
    
    /*
    printf("\t|");
    //print for dynamic Programming:
    for (uint16_t i = 0; i < S1_SIZE ; i++) {
        printf("%d\t|",dataArray[i].data);
    }
    printf("\n");
    for (uint16_t i = 0; i < 150 ; i++) {
        printf("-");
    }
    printf("\n");
    for (uint16_t i = 0; i < S1_SIZE ; i++) {
        printf("%d\t|",dataArray[i].data);
        for (uint16_t j = 0; j < S1_SIZE ; j++) {
            if (j>i) {
                printf("%d\t|",dataArray[i].data + dataArray[j].data);
            }else{
                printf("\\\t|");
            }
            
        }
        printf("\n");
    }
     */
}

int liniarSearch_uint(uint16_t E[S1_SIZE], uint16_t K, uint32_t currentSizeOfStorage){
    for (uint32_t i = 0; i < currentSizeOfStorage; i++) {
        if(E[i] == K){
            return i;
        }
    }
    return -1;
}


int binSearch_uint(uint16_t E[S1_SIZE], uint16_t K, uint32_t currentSizeOfStorage) {
    int left = 0, right = currentSizeOfStorage - 1;
    int mid = ((left + right) / 2);
    
    while (left <= right) {
        mid = ((left + right) / 2); // runde ab
        if (E[mid] == K) {
            
            return mid;
        }
        if (E[mid] > K) { right = mid - 1; }
        if (E[mid] < K) { left = mid + 1; }
    }
    return -1;
 }

int binSearch(Data E[S1_SIZE], Data K) {
    int left = 0, right = S1_SIZE - 1;
    
    while (left <= right) {
        int mid = ((left + right) / 2); // runde ab
        if (E[mid].data == K.data) { return mid; }
        if (E[mid].data > K.data) { right = mid - 1; }
        if (E[mid].data < K.data) { left = mid + 1; }
    }
    return -1;
 }



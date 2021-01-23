#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"
#include "stack.h"
#include "aufg10.1.h"

//wann muss programm termenieren, wenn alle Knoten als StartKnoten ausgewaehlt wurden
int32_t summe = 0;
uint16_t goals[3] = {3652, 20000, 19362};


//functions------------------------------------------

void printSolution10_1(void);
void backtrack(uint16_t startKnoten);
void aufgabe10_1a(uint8_t *bool_foundNothing, uint64_t solutionCount);
void aufgabe10_1b(uint8_t *bool_foundNothing, uint64_t solutionCount);


int main(void){
    
    //aufgabe 10.1 a)
    
    uint64_t solutionCount = 0;
    uint8_t bool_foundNothing = 1;
    Data dummData;
    dummData.bool_darfAusgewaehltWerden = 1;
    dummData.bool_hasValue = 0;
    dummData.numbersOfOtherPossibleData = -1;
    dummyData = &(dummData);
    
    makeDataArrayAndStack();
    
//    aufgabe10_1a(&bool_foundNothing,solutionCount);
    
    aufgabe10_1b(&bool_foundNothing,solutionCount);
    

    return 0;
}


void aufgabe10_1a(uint8_t *bool_foundNothing, uint64_t solutionCount){
    
    for (uint16_t startKnoten = 0;startKnoten < S1_SIZE; startKnoten++) {
        summe = 0;
        makeChildren_EmptyStack_resetSumme(startKnoten);
        stackPush(backtrackStack, &(dataArray[startKnoten]));
        summe += dataArray[startKnoten].data;
        
        do{
            if(summe < goals[GOAL_NUMBER]){//wenn kleiner ist brauche  wir ja noch mehr summanden aus S
                //Gehe zu naechsten Child
                Data *firstOnStack = stackGetFirst(backtrackStack);
                if(firstOnStack == NULL){
                    //nothing on the stack??
                    printf("\nNothing on the stack!\n\n");
                    exit(1);
                }
                

                
                if (firstOnStack->numbersOfOtherPossibleData > 0 && firstOnStack->currentSelected < firstOnStack->numbersOfOtherPossibleData) {
                    //es gibt noch children...
                    uint16_t childIndex = firstOnStack->indexOfOtherPossibleData[firstOnStack->currentSelected];
                    
                    if (dataArray[childIndex].bool_darfAusgewaehltWerden == 0) {
                        printf("\nchoose Data on the stack!\n\n");
                        exit(1);
                    }
                    
                    if (dataArray[childIndex].data+summe == goals[GOAL_NUMBER]) {
                        firstOnStack->currentSelected++; // damit der nicht wieder angeschaut wird
                        stackPush(backtrackStack, &(dataArray[childIndex]));
                        summe += dataArray[childIndex].data;
                        
                    }
                    else if (dataArray[childIndex].data+summe < goals[GOAL_NUMBER]) {
                        // hat auswaehlbare kinder kimder
      
                        firstOnStack->currentSelected++; // damit der nicht wieder angeschaut wird
                        stackPush(backtrackStack, &(dataArray[childIndex]));
                        summe += dataArray[childIndex].data;
                    }
                    else{
                        backtrack(startKnoten);
                    }
                }
                else{
                    //entweder hat keine Kinder oder keine Kinder durfen ausgewaehlt werden
                    // -> backtrack
                    backtrack(startKnoten);
                }
                

            }
            else if (summe > goals[GOAL_NUMBER]){//backtrack
                //summe ist zu gross also loesche aktiellen knoten aus Stack
                backtrack(startKnoten);
            }
            
            
            if (summe == goals[GOAL_NUMBER]) {
                printSolution10_1();
                solutionCount++;
                //printf("%" PRIu64 "\n",solutionCount);
                //backTrack
                backtrack(startKnoten);
            }
            

        } while (dataArray[startKnoten].numbersOfOtherPossibleData > dataArray[startKnoten].currentSelected);
        
        printf("\n\n%" PRIu64 "\n",solutionCount);
        
        dataArray[startKnoten].bool_darfAusgewaehltWerden = 0;//jetzt hast du ja schon alle loesungen die in denen startknoten vorkommt
    }
}


void aufgabe10_1b(uint8_t *bool_foundNothing, uint64_t solutionCount){
    makeDynamicStorage();
}

void printSolution10_1(void){
    uint16_t testSumme = 0;
    for (uint16_t i = 0; i <= backtrackStack_fillSize ; i++){
        if( backtrackStack[i]->bool_hasValue == 1 ){
            if(i != backtrackStack_fillSize){
                testSumme += backtrackStack[i]->data;
                printf("%d + ",backtrackStack[i]->data);
            }
            else if(i == backtrackStack_fillSize){
                testSumme += backtrackStack[i]->data;
                printf("%d ",backtrackStack[i]->data);
            }
        }
    }
    
    if(testSumme == goals[GOAL_NUMBER]){
        printf("= %d",goals[GOAL_NUMBER]);
        
    }else{
        printf(" != %d  THERES a fuckup Bug, good luck!",goals[GOAL_NUMBER]);
    }
    
    printf("\n");

}

void backtrack(uint16_t startKnoten){
    Data *popedData = stackPop(backtrackStack);
    summe -= popedData->data;
    popedData->currentSelected = 0;
    
    //dont choose it again in partent Data
    Data *parentData = stackGetFirst(backtrackStack);
    if (parentData != NULL && parentData->data != dataArray[startKnoten].data) {
        //reset data of this node
        return;
    }
    //current Data is root -> break loop
    dataArray[startKnoten].currentSelected++;
}



/*
 printf("stackSize: %d\n",backtrackStack_fillSize);
 printf("on the stack: ");
 if (backtrackStack_fillSize>0) {
     for (int16_t i = backtrackStack_fillSize-1; i>=0 ; i--) {
         printf("%d, ", backtrackStack[i]->data);
     }
 }
 printf("\nsumme: %d\n",summe);
 printf("current data: %d\n", firstOnStack->data);
 printf("electable children:\n");
 for (uint16_t i = firstOnStack->currentSelected; i< firstOnStack->numbersOfOtherPossibleData; i++) {
     printf("%d, ", firstOnStack->indexOfOtherPossibleData[i]);
 }
 printf("\n---------------------------------------\n\n");
 
 
 */

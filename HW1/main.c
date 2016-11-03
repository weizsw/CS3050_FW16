/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:  CS3050_HW1
 * Author: Shaowei Zhou
 *
 * Created on 2016年9月7日, 下午2:44
 */
#include"input_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int getSize(char** argv);
void split(int* content, int low, int mid, int high, int size);
void mergeSort(int* content, int low, int high, int size);
int getMode(int* content, int size);
/*
 * 
 */
int main(int argc, char** argv) {
    //check input arguments it should be equal 2
    if(argc != 2){
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    //get the document size
    int size = getSize(argv);
//    printf("documentSize：%d\n", size);
//    
    //open document
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        exit(FILE_FAILED_TO_OPEN);
    }
    int i;
    //use the size to malloc a pointer to store the numbers
    int* content = malloc(sizeof(int)* size);
//    printf("\ndocument List\n");
    for(i = 0; i < size; ++i){
        fscanf(fp, "%ld", content + i);
    }
    //which not reach the end of file check if there is non digitor negative numbers
//    while(!feof(fp)){
//        if(!isdigit(*(content))){
//            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
//            break;
//        }
//        else{
//            content++;
//        }
//    }
//    for(i = 0; i < size; i++){
//        if(*(content + i) < 0){
//            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
//        } 
//    }
//    while(!feof(fp)){
//        if(isblank(*(content))){
//            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
//            break;
//        }
//        else{
//            content++;
//        }
//    }
    //sort the numbers in document
    mergeSort(content, 0, size -1, size);
//    printf("\nSorting\n");
//    for(i = 0; i < size; i++){
//        printf("%d ", *(content + i));
//    }
    
    int result = getMode(content, size);
    //if -1 is returned it means all frequences are same
    if(result == -1){
        printf("0\n");
    }
    else{
    
    printf("%ld\n", result);
    }
    //free memory allocated
    free(content);
    return (EXIT_SUCCESS);
    
}
    int getSize(char** argv){
    //open file and error checking
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        exit(FILE_FAILED_TO_OPEN);
    }
    char content;
    int sizeCount = 0;
    char information[100];
    //open file count everytrhing in the file
    //if reach the end of file break it
    //at the end we can know how many numbers in the file
    while(1){
        content = fscanf(fp, "%99s", information);
        if(content == EOF){
            break;
        }
        sizeCount++;
    }
    if(sizeCount == 0){
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    content = fclose(fp);
    if(content != 0){
        exit(FILE_FAILED_TO_CLOSE);
    }
    return sizeCount;
}
void mergeSort(int* content, int left, int right, int size){
    if (left < right)
    {
      
        int m = left+(right-left)/2;
 
        // Sort first and second halves
        mergeSort(content, left, m, size);
        mergeSort(content, m+1, right, size);
 
        split(content, left, m, right, size);
    }
    
}
int getMode(int* content, int size){

    int countingNumber = content[0]; 
    int numberOfCount = 1; 
    int firstMode = 0;
    int firstModeCount = 0;
    int frequenceChange = 1;
    int i = 0;
    int tempCount = 0;
    
    //count from the second number in the pointer
    //the first number is counted so the number of count should start at 1
    //because the file is sorted 
    //we just start from the left
    //when currently count number is different from the previous number
    //put the count and the number in the firstmode
    //only when the current count is bigger or equal than the firstmodecount
    //the first modecount would be changed
    //if they have same frequence
    //the bigger number would be chosen
   
    for(i = 1; i < size; i++) { 
        if(content[i] != countingNumber) {
			
            if(numberOfCount >= firstModeCount) {              
                firstMode = content[i-1];
                firstModeCount = numberOfCount;
            }
           
//            if(mode_count != current_count){
//                frequence++;
//            }
            countingNumber = content[i];
            numberOfCount = 1;
        } 
        //tempCount is used to check if the numbers have the same frequence in the file
        else {
            numberOfCount += 1;
             tempCount = numberOfCount;
	}
        if(tempCount != firstModeCount){
            frequenceChange = 2;
        }
    }   
   
    //if the last number is bigger than the previous mode
    //and the last number has same or bigger frequence
    //the mode should be the last one
	if(numberOfCount >= firstModeCount) { 
            firstMode = content[i-1]; 
            firstModeCount = numberOfCount;
	}
   
    countingNumber = content[0]; 
    numberOfCount = 1;
    int secondMode = 0;
    int secondModeCount = 0;
   
    
    //start to find the second mode(biggest number has second frequence)
    //we do the same as above
    //even when the current count is bigger or euqual than the second count
    //and the current count is smaller than the firstmode
    //it means it is the second mode in this file
    //store it in the second mode and secondmode count
    //keep the loop till end of the file
    for(i = 1; i < size; i++) { 
        if(content[i] != countingNumber) {
            
            if(numberOfCount >= secondModeCount && numberOfCount < firstModeCount) {              
                secondMode = content[i - 1];
                secondModeCount = numberOfCount;
            }
            
            countingNumber = content[i];
            numberOfCount = 1;
            
        } 
        else {
            numberOfCount += 1;
	}
    }   
    //this is for
    //if reach the last number and it is bigger than the secondMode stored in secondMode
    //also the count is samller than the firstCount
    //then it shouuld be the secondMode
    if(countingNumber >= secondMode && numberOfCount < firstModeCount && secondModeCount <= numberOfCount) { 
            secondMode = content[i-1]; 
    }
    //if frequenceChange equal 2
    //it means the file contains several frequence
    if(frequenceChange == 2){
        return secondMode;
    }
    //if the firstModeCount keeps 1
    //it means the file contails same frequence
    else if(firstModeCount != 1){
        return secondMode;
    }
    //other situation 
    else{
	return -1;
    }
    
}
void split(int* content, int left, int mid, int right, int size){

    int i, j, k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;
 
    //creat temp array
    int tempArr1[n1], tempArr2[n2];
 
   //split the data in file to two arrays
    for (i = 0; i < n1; i++)
        tempArr1[i] = content[left + i];
    for (j = 0; j < n2; j++)
        tempArr2[j] = content[mid + 1+ j];
 
   //merge temp array back
    i = 0; 
    j = 0; 
    k = left; 
    while (i < n1 && j < n2)
    {
        if (tempArr1[i] <= tempArr2[j])
        {
            content[k] = tempArr1[i];
            i++;
        }
        else
        {
            content[k] = tempArr2[j];
            j++;
        }
        k++;
    }
 
   //copy the remaining data if there are any
    while (i < n1)
    {
        content[k] = tempArr1[i];
        i++;
        k++;
    }
 
   //same above
    while (j < n2)
    {
        content[k] = tempArr2[j];
        j++;
        k++;
    }
    
}
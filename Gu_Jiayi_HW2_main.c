/**************************************************************
* Class:  CSC-415-01 Fall 2022
* Name: Jiayi Gu
* Student ID: 920024739
* GitHub UserID: Jiayi079
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: Gu_Jiayi_HW2_main.c
*
* Description:
*   We'll gain practice with structures, pointers, character strings, 
*   enumerated types, bitmap fields, and buffering data into blocks through
*   in this assignment.
*
**************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "assignment2.h"

int main(int argc, char * argv[])
{
    // initialize pointer
    personalInfo *myInfo;

    // allocate the size of the personalInfo structure
    myInfo = malloc(sizeof(personalInfo));

    /* check if memory created successfully 
       -> when memory allocate is full, pointer will be NULL */
    if (myInfo == NULL)
    {
        printf("Memory created failed!\n");
    }

    // set value of myInfo from command argument
    myInfo->firstName = argv[1];
    myInfo->lastName =  argv[2];
    myInfo->studentID = 920024739;  // set other filed
    myInfo->level = SENIOR;
    // set value of languages by using macro definition
    myInfo->languages = KNOWLEDGE_OF_JAVA | KNOWLEDGE_OF_C | KNOWLEDGE_OF_CPLUSPLUS | 
    KNOWLEDGE_OF_HTML | KNOWLEDGE_OF_INTEL_ASSEMBLER | KNOWLEDGE_OF_JAVASCRIPT | 
    KNOWLEDGE_OF_PYTHON | KNOWLEDGE_OF_SQL;

    printf("%p", myInfo->languages);
    /* do copy from 3rd command line -> argv[3] to the message field by using strncpy,
       also need to make sure the size of the message field should be message[100],
       -> strncpy() function copies portion of contents */
    strncpy(myInfo->message, argv[3], sizeof(myInfo->message));

    // check personal info structure is succeed
    if (writePersonalInfo(myInfo) != 0)
    {
        printf("Personal info structure failed!\n");
    }

    free(myInfo); // free memory allocate
    myInfo = NULL; // set myInfo to NULL pointer


    // initialize buffer and allocate its size by using BLOCK_SIZE
    char * buffer = malloc(BLOCK_SIZE);
    char * tempStr = getNext();     // get string from getNext()
    int j = 0, i;

    while (tempStr != NULL) // iterate getNext() until NULL
    {
        // get the length of tempStr, add each one to buffer by using for loop
        for (i = 0; i < strlen(tempStr); i++)
        {
            // adding each char from tempStr to buffer
            buffer[j++] = tempStr[i];

            // check if buffer is full, 
            if (j == BLOCK_SIZE)
            {
                commitBlock(buffer); // commit since buffer full
                strcpy(buffer, ""); // clean buffer
                j = 0;
            }

        }
        tempStr = getNext(); // get next string from getNext()
    }

    // check if there're some values left in the buffer, commit it
    if (j != 0)
    {
        commitBlock(buffer);
    }

    free(buffer); // free memory allocation
    buffer = NULL; // set buffer become NULL pointer

    return checkIt();
}



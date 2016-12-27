#include <stdio.h>
#include <stdlib.h>

/* Intended to assign heap memory for 2d array.
1. size of allocated memory - (row_Length) * Column_Length * sizeof(int)
*/
int * alloc2dArrInt(int colLen, int rowLen);


/*
Intended to input strings into pointer array.
    1. For each element of input, it mallocates memory space of 20bites
 */
int strArrInput(char ** arr, int num_element);

/*
Intended to input numbers into 2d array.
*/
int arrInput(int * arr, char ** name, char ** subject, int colLen, int rowLen);

/*
Prints labels and Scores all together
*/
int ScoreOutput(int * arr, char ** name, char ** subject, int colLen, int rowLen);


int main(void)
{
    //1. Declaration for subj, name length and inputs
    int subjLen=0, nameLen=0;

    printf("How many subjects and names? : ");
    scanf("%d %d", &subjLen, &nameLen);

    //2. subj, name array declaration
    char * subjArr[subjLen];
    char * nameArr[nameLen];

    //3. subj, name array inputs - strListInput
    printf("Subject Input: \n");
    strArrInput(subjArr, subjLen);
    printf("Name Input: \n");
    strArrInput(nameArr, nameLen);
    printf("\n");

    //4. Declaration, memory assignment of score array
    int (*arr)[subjLen] = alloc2dArrInt((nameLen+1), (subjLen+1));

    //5. score array inputs
    //6. Calculating total scores (edge row, column of score array)
    arrInput(arr, nameArr, subjArr, nameLen+1, subjLen+1);

    //7. Print ScoreBoard - subjArr, nameArr, and score array.
    ScoreOutput(arr, nameArr, subjArr, nameLen+1, subjLen+1);


    return 0;
}

int * alloc2dArrInt(int colLen, int rowLen)
{
    int * ptr = (int*)malloc(colLen*rowLen*sizeof(int));

    return ptr;
}

int arrInput(int * arr, char ** name, char ** subject, int colLen, int rowLen)
{
    //Part 1 : Input
    int i=0, j=0;
    int (*arr2d)[rowLen] = arr;

    for(j=0;j<(rowLen-1);j++)
    {
        //Print Which score is being put in.
        printf("%s Score Input:\n", subject[j]);

        for(i=0;i<(colLen-1);i++)
        {
            //print which person's score is being put in.
            printf("\t%d. %s\'s score input: ", i+1, name[i]);
            scanf("%d", &arr2d[i][j]);
        }
    }
    //Part 2 : Calculate Total

    //Initialize edge row, column.
    for(i=0; i<rowLen;i++)
        arr2d[colLen-1][i]=0;

    for(i=0; i<colLen;i++)
        arr2d[i][rowLen-1]=0;

    //Calculate sums
    for(j=0; j<(rowLen-1); j++)
    {
        for(i=0; i<(colLen-1); i++)
        {
            arr2d[colLen-1][j]+=arr2d[i][j];
            arr2d[i][rowLen-1]+=arr2d[i][j];
            arr2d[colLen-1][rowLen-1]+=arr2d[i][j];
        }
    }
    return 0;
}

int strArrInput(char ** arr, int num_element)
{
    int i=0;

    for(i=0;i<num_element;i++)
    {
        arr[i]=(char*)malloc(20);
        printf("%dst input : ", (i+1));
        scanf("%s", arr[i]);
    }

    return 0;
}

int ScoreOutput(int * arr, char ** name, char ** subject, int colLen, int rowLen)
{
    int i=0, j=0;
    int (*arr2d)[rowLen]=arr;

    //print 1st row
    printf("%8c", *" ");
    for(j=0;j<(rowLen-1);j++)
        printf("%8s", subject[j]);
    printf("\n");

    //Print 2nd to (last-1)th rows
    for(i=0;i<(colLen-1);i++)
    {
        printf("%8s", name[i]);
        for(j=0; j<rowLen; j++)
            printf("%8d", arr2d[i][j]);
        printf("\n");
    }

    //print the last row
    printf("%8c", *" ");
    for(j=0; j<rowLen; j++)
    {
        printf("%8d", arr2d[colLen-1][j]);
    }
    printf("\n");

    return 0;
}


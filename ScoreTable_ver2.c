/*
Abstract:
   This program builds a chart of test scores and print on screen.
It takes input of how many students and subjects user wants to input and generate chart accordingly.
The biggest issue was decision on method of storing data. I focused on satisfying two criteria:

1) To take user input of how many students and subjects to enter, within program
2) To ensure that modification of data is easy and simple

The method involves 2D array and structure variable which contain name, subject and score.

Written by ChungJun Lee
Contact : cl3224@naver.com
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define CELLWIDTH "%10s"

typedef struct{

    char name[20];
    char subject[20];
    int score;

}AcdmicRcd;

typedef enum prntMode{
    name=0, subject=1, score=2
}PrntMode;

void arrPrint(AcdmicRcd * addrs, const int colLen, const int rowLen, PrntMode m);

int main(void){
    //0. declare variables
    int cnt_name=0;
    int cnt_subj=0;
    int i=0, j=0;
    char tmp_name[20];
    char tmp_subj[20];

    //1. Take input of how many students and subjects
    printf("How many names and subjects? : ");
    scanf("%d %d", &cnt_name, &cnt_subj);

    //2. Declare 2D array of AcademicRec
    AcdmicRcd (* arr)[cnt_subj+1] = (AcdmicRcd*)malloc(sizeof(AcdmicRcd)*(cnt_name+1)*(cnt_subj+1));

    //3. input students and subject names and update each rows and columns
        //a. input names
    for(i=0; i<cnt_name;i++){
        printf("input name(%dth input) : ", i+1);
        scanf("%s", tmp_name);
        getchar(); //eliminate '\n' from buffer
        for(j=0;j<cnt_subj+1;j++){
            strcpy(arr[i][j].name, tmp_name);
        }
    }
    for(j=0; j<cnt_subj+1;j++){
        strcpy(arr[i][j].name, "total"); //for the last row, input "total" for name
    }

    printf("step3_a ended\n");
    system("pause");

        //b. input subjects
    for(j=0;j<cnt_subj;j++){
        printf("input subject(%dth input) : ", j+1);
        scanf("%s", tmp_subj);
        getchar(); //eliminate '\n' from buffer
        for(i=0;i<cnt_name+1;i++){
            strcpy(arr[i][j].subject, tmp_subj);
        }
    }
    for(i=0; i<cnt_name+1;i++){
        strcpy(arr[i][j].subject, "total"); //for the last col, input "total" for subject
    }
    printf("step3_b ended\n");
    system("pause");

    arrPrint(arr, cnt_name+1, cnt_subj+1, name);//Test run
    printf("\n\n");

    arrPrint(arr, cnt_name+1, cnt_subj+1, subject);//Test run
    printf("\n\n");

        //c. input score
    for(j=0;j<cnt_subj;j++){
        printf("%dst Subject : %s\n", j+1, arr[0][j].subject);
        for(i=0;i<cnt_name;i++){
            printf("\t%d. %s's Score : ", i+1, arr[i][0].name);
            scanf("%d", &arr[i][j].score);
            getchar(); //eliminate '\n' from buffer
        }
    }
    for(i=0;i<cnt_name+1;i++){
        arr[i][cnt_subj].score=0;
    }
    for(j=0;j<cnt_name+1;j++){
        arr[cnt_name][j].score=0;
    }


    //4. Calculate Total
    for(i=0;i<cnt_name;i++){
        for(j=0;j<cnt_subj;j++){
            arr[i][cnt_subj].score+=arr[i][j].score;
            arr[cnt_name][j].score+=arr[i][j].score;
            arr[cnt_name][cnt_subj].score+=arr[i][j].score; //All scores added
        }
    }

    //5. print array.
    arrPrint(arr, cnt_name+1, cnt_subj+1, score);

    free(arr);
    return 0;
}

//5. print array.
void arrPrint(AcdmicRcd * addrs, const int colLen, const int rowLen, PrntMode m){
    //1. set up variables
    AcdmicRcd (* ptr)[rowLen] = addrs;
    int i=0, j=0;

    printf("var setup ended\n");
    system("pause");

    //2. Print 1st row
    printf("          ");
    for(j=0;j<rowLen;j++){
        printf("%10s", ptr[0][j].subject);
    }

    printf("\n");

    printf("FirstRow printed\n");
    system("pause");

    //3. print body (print name before printing each row)
        //Diverge program flow according to prnt_mode
    if(m==name){
        for(i=0; i<colLen; i++){
            printf(CELLWIDTH, ptr[i][0].name);
            for(j=0;j<rowLen;j++){
                printf(CELLWIDTH, ptr[i][j].name);
            }
        printf("\n");
        }
    }
    else if(m==subject){
        for(i=0; i<colLen; i++){
            printf(CELLWIDTH, ptr[i][0].name);
            for(j=0;j<rowLen;j++){
                printf(CELLWIDTH, ptr[i][j].subject);
            }
        printf("\n");
        }
    }
    else if(m==score){
        for(i=0; i<colLen; i++){
            printf(CELLWIDTH, ptr[i][0].name);
            for(j=0;j<rowLen;j++){
                printf("%10d", ptr[i][j].score);
            }
        printf("\n");
        }

    }
    printf("body printed\n");
    system("pause");
}

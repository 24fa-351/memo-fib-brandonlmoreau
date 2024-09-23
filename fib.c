#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



int checkMemoization(long long int N)
{
    FILE* mFile;
    char memoizationIntegerChar[100];
    char longlongIntAsCstring[100];
    int memoizationInteger;
    bool memoizationFound = false;
    char *MemoryTxt = "memFile.txt";

    sprintf(longlongIntAsCstring, "%lld\n", N);
    mFile = fopen(MemoryTxt, "r");
    while ((fgets(memoizationIntegerChar, sizeof(memoizationIntegerChar), mFile) != NULL) && (memoizationFound == false))
    {
        memoizationFound = !strcmp(memoizationIntegerChar, longlongIntAsCstring);
        if (memoizationFound)
        {
            memoizationFound = true;//delete
            fgets(memoizationIntegerChar, sizeof(memoizationIntegerChar), mFile);
            memoizationInteger = atoi(memoizationIntegerChar);
            continue;
        }
        fgets(memoizationIntegerChar, sizeof(memoizationIntegerChar), mFile);//skip line
    }
    fclose(mFile);
    if (memoizationFound)
    {
        return memoizationInteger;
    }
    else
    {
        return -1;
    }
}
void addMemoization(long long int N, int result)
{
    FILE* mFile;
    char* MemoryTxt = "memFile.txt";
    mFile = fopen(MemoryTxt, "a");
    fprintf(mFile,"%lld\n", N);
    fprintf(mFile, "%d\n", result);
    fclose(mFile);
}
int recursiveFibWrapper(long long int N, int current, int last)//0 1 1 2 3
{//was here
    //!!!!!!
    //! 
    if ((current == 1) && (last == 0)&& (N==1))//first iteration and n=1
    {
        return 0;
    }
    else if (N!=2)
    {
        int sum = current + last;
        recursiveFibWrapper(N-1,sum,current);
    }
    else
    {
        return current;
    }

}
int iterativeFibWrapper(int N)
{
    int sum3;
    int sum2 = 1;
    int sum1 = 0;
    if (N > 3)
    {
        for (int i = 2; i < N; i++)
        {
            sum3 = sum2 + sum1;
            sum1 = sum2;
            sum2 = sum3;
        }
        return sum3;

    }
    else if (N == 1)
    {
        sum3 = 0;
        return sum3;

    }
    else if ((N == 2) || (N == 3))
    {
        sum3 = 1;
        return sum3;
    }
}
int recursiveFib(long long int N, int current, int last)
{
    int answer = checkMemoization(N);
    if (answer == -1)
    {
        answer= recursiveFibWrapper(N, current, last);
        addMemoization(N,answer);
        return answer;
    }
    else
    {
        return answer;
    }
}
int iterativeFib(long long int N)
{
    int answer = checkMemoization(N);
    if ( answer == -1)
    {
        answer = iterativeFibWrapper(N);
        addMemoization(N, answer);
        return answer;
    }
    else
    {
        return answer;
    }
}


int main(int argc, char *argv[]) {
    

    FILE* file;

    int IntegerChoice= atoi(argv[1]);
    char R_or_i_Choice = argv[2][0];
    char *FileChoice = argv[3];
    char FileInteger[100];
  
    long long int N;//prompt says to use single letter "N"

    

    //*****************************reads file data
    file = fopen(FileChoice, "r");
    fgets(FileInteger , sizeof(FileInteger) , file);
    fclose(file);

    
    
    //*********combine user and txt numeral into sum
    N = IntegerChoice;
    N = N + (atoi(FileInteger));
    
    //************fork into recursion or iteration
    if (R_or_i_Choice=='r')
    {
        int value = recursiveFib(N, 1, 0);
        printf("%d\n", value);
    }
    else if (R_or_i_Choice=='i')
    {

        int value = iterativeFib(N);
        printf("%d\n", value);
    }
    return 0;
 }

#include <iostream>
#include <string>
#include "Directory.h"

using namespace std;

string intToString(unsigned int number)
{
    int quotient = number;
    int bynary[9];
    string bynStr;
    for(int i = 0; i < 9;i++)
    {
        bynary[i] = 0;
    }
    int i = 8;
    while(quotient != 0)
    {
        int remainder = quotient % 2;
        bynary[i] = remainder;
        quotient = quotient/2;
        i--;    
    }

    bynStr = to_string(bynary[0]);
    for(int i = 1;i < 9;i++)
    {
        bynStr += to_string(bynary[i]);
    }

    return bynStr;
}

int main()
{
    srand(2);
    Directory *dir = new Directory(1,2);
    string keys[10];
    for(int i = 0;i < 10;i++)
    {
        keys[i] = intToString(rand() % 511);
    }

    for(int i = 0;i < 10;i++)
    {
        dir->insert(keys[i]);
    }
    return 0;
}
#include <iostream>
#include<fstream>
#include <string>
#include <math.h>
#include "Directory.h"

using namespace std;

string intToString(unsigned int number,int bitNumber)
{
    int quotient = number;
    int bynary[bitNumber];
    string bynStr;
    for(int i = 0; i < bitNumber;i++)
    {
        bynary[i] = 0;
    }
    int i = bitNumber - 1;
    while(quotient != 0)
    {
        int remainder = quotient % 2;
        bynary[i] = remainder;
        quotient = quotient/2;
        i--;    
    }

    bynStr = to_string(bynary[0]);
    for(int i = 1;i < bitNumber;i++)
    {
        bynStr += to_string(bynary[i]);
    }

    return bynStr;
}

void randomInsertionTest(int keyNumber,int bitNumber,int bucketSize)
{
    float loadFactor[5];
    float pointerAllocation[5];
    float bucketAllocation[5];
    string randomKeys[keyNumber];
    int maxNumber = pow(2,bitNumber) - 1;
    Directory *dir;
    ofstream outfile("saidas.txt",ios::app);

    outfile << "Inserção de " << keyNumber << " pseudo-chaves aleatórias:" << endl;
    outfile << "Fator de carga,Alocação de ponteiros,Alocação de baldes" << endl;

    for(int i = 0;i < 5;i++)
    {
        srand(i+1);
        for(int i = 0; i < keyNumber;i++)
        {
            randomKeys[i] = intToString(rand() % maxNumber,bitNumber);
        }
        dir = new Directory(1,bucketSize);
        for(int i = 0; i < keyNumber;i++)
        {
            dir->insert(randomKeys[i]);
        }
        loadFactor[i] = dir->getAllocatedKeys()/dir->getAvaliableSpaces();
        pointerAllocation[i] = dir->getPointersAllocated();
        bucketAllocation[i] = dir->getBucketsAllocated();
        outfile << loadFactor[i] << "," << pointerAllocation[i] << "," << bucketAllocation[i] << endl;
        delete dir;
    }

    float averageLoadFactor = 0;
    float averagePointerAllocation = 0;
    float averageBucketAllocation = 0;
    for(int i = 0;i < 5;i++)
    {
        averageLoadFactor += loadFactor[i];
        averagePointerAllocation += pointerAllocation[i];
        averageBucketAllocation += bucketAllocation[i];
    }
    averageLoadFactor = averageLoadFactor/5;
    averagePointerAllocation = averagePointerAllocation/5;
    averageBucketAllocation = averageBucketAllocation/5;

    outfile << "Médias:" << endl << averageLoadFactor << "," << averagePointerAllocation << "," << averageBucketAllocation << endl << endl;

    outfile.close();
}

void standardizedInsertionTest(int keyNumber,int bitNumber,int bucketSize)
{
    float loadFactor[5];
    float pointerAllocation[5];
    float bucketAllocation[5];
    string randomKeys[keyNumber];
    int maxNumber = pow(2,bitNumber - 5) - 1;
    Directory *dir;
    ofstream outfile("saidas.txt",ios::app);

    outfile << "Inserção de " << keyNumber << " pseudo-chaves iniciadas com o mesmo padrão de bits:" << endl;
    outfile << "Fator de carga,Alocação de ponteiros,Alocação de baldes" << endl;

    for(int i = 0;i < 5;i++)
    {
        srand(i+1);
        for(int i = 0; i < keyNumber;i++)
        {
            randomKeys[i] = intToString(rand() % maxNumber,bitNumber);
        }
        dir = new Directory(1,bucketSize);
        for(int i = 0; i < keyNumber;i++)
        {
            dir->insert(randomKeys[i]);
        }
        loadFactor[i] = dir->getAllocatedKeys()/dir->getAvaliableSpaces();
        pointerAllocation[i] = dir->getPointersAllocated();
        bucketAllocation[i] = dir->getBucketsAllocated();
        outfile << loadFactor[i] << "," << pointerAllocation[i] << "," << bucketAllocation[i] << endl;
        delete dir;
    }

    float averageLoadFactor = 0;
    float averagePointerAllocation = 0;
    float averageBucketAllocation = 0;
    for(int i = 0;i < 5;i++)
    {
        averageLoadFactor += loadFactor[i];
        averagePointerAllocation += pointerAllocation[i];
        averageBucketAllocation += bucketAllocation[i];
    }
    averageLoadFactor = averageLoadFactor/5;
    averagePointerAllocation = averagePointerAllocation/5;
    averageBucketAllocation = averageBucketAllocation/5;

    outfile << "Médias:" << endl << averageLoadFactor << "," << averagePointerAllocation << "," << averageBucketAllocation << endl << endl;

    outfile.close();
}

int main()
{
    bool run = true;
    Directory *dir;

    cout << "Teste de Hashing Extensível - EDII 2020.3" << endl;
    cout << "Digite o tamanho dos baldes a serem utilizados: ";
    int bucketSize;
    cin >> bucketSize;
    cout << "Digite o número de bits a serem utilizados para a formação de chaves: ";
    int bitNumber;
    cin >> bitNumber;
    cout << "Digite o número de pseudo-chaves a serem armazenadas a serem inseridas na tabela: ";
    int keyNumber;
    cin >> keyNumber;

    dir = new Directory(1,bucketSize);

    while(run)
    {
        cout << "Menu:" << endl << "1 - Testes de inserção (Chaves aleatórias X Chaves iniciadas com o mesmo padrão)" << endl;
        cout << "2 - Inserção de uma chaves qualquer" << endl;
        cout << "3 - Busca de chave" << endl;
        cout << "0 - Encerrar execução" << endl;
        cout << "Selecione sua opção: ";
        int option;
        int number;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Realizando teste com chaves aleatórias..." << endl;
            randomInsertionTest(keyNumber,bitNumber,bucketSize);
            cout << "Realizando teste com chaves iniciadas com o mesmo padrão..." << endl;
            standardizedInsertionTest(keyNumber,bitNumber,bucketSize);
            cout << "Testes realizados e resultados armazenados em saidas.txt" << endl;
            cout << "Encerrando execução..." << endl;
            run = false;
            break;
        case 2:
            cout << "Digite uma chave em decimal (valor não pode ultrapassar " << pow(2,bitNumber) - 1 << "): ";
            cin >> number;
            if(number <= pow(2,bitNumber) - 1)
            {
                string key = intToString(number,bitNumber);
                dir->insert(key);
                cout << "Processo de inserção de chave " << key << " concluído." << endl;
            }
            else
            {
                cout << "Valor inválido!" << endl;
            }
            break;
        case 3:
            cout << "Digite uma chave em decimal (valor não pode ultrapassar " << pow(2,bitNumber) - 1 << "): ";
            cin >> number;
            if(number <= pow(2,bitNumber) - 1)
            {
                string key = intToString(number,bitNumber);
                dir->search(key);
                cout << "Processo de busca de chave " << key << " concluído." << endl;
            }
            else
            {
                cout << "Valor inválido!" << endl;
            }
            break;

        default:
            cout << "Encerrando execução..." << endl;
            run = false;
            break;
        }
    }
    return 0;
}
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include<iostream>
#include<vector>
#include<string>
#include <math.h>
#include "Bucket.h"

using namespace std;

//Classe resposável pela criação e armazenamento dos baldes e a correta organização das chaves dentro deles
class Directory
{
private:
    //Variável que armazena o tamanho global do diretório
    int globalDepth;
    //Variável que armazena o máximo de chaves que cada balde deve conter
    int bucketSize;
    //Variável para controlar quantas chaves foram armazenadas neste diretório, este valor é usado mais tarde para o cálculo do fator de carga
    float allocatedKeys;
    //Variável para controlar o número espaços criados para armazenar chaves dentro deste diretório, este valor é usado mais tarde para o cálculo do fator de carga
    float avaliableSpaces;
    //Variável para controlar o número de ponteiros de baldes criados neste diretório
    float pointersAllocated;
    //Variável para controlar quantos baldes foram alocados neste diretório
    float bucketsAllocated;
    //Vector criado para armazenar todos os baldes deste diretório através de ponteiros, cada índice do vector representa um índice do diretório
    vector<Bucket*> buckets;
    /**
     * Função interna responsável por dividir os baldes cheios em baldes de profundidade maior, ela recebe como parâmetro o balde cheio,
     * cria um balde de profundidade maior, expande a profundidade do balde original, redistribui as chaves baseado no índice do balde original e 
     * reorganiza as referências dos diretórios para receber os dois baldes de profudidade local maior 
     * 
     * @param int bucket_key
     * @return void
    */
    void splitBucket(int bucket_key);
    /**
     * Função interna responsável pela duplicação dos índices do diretório, a nova distribuição deixa o ponteiro original e sua cópia 
     * um seguido do outro na sequência
     * 
     * @return void
    */ 
    void duplicateDirectory();
    /**
     * Função interna que calcula o índice correto do diretório a ser acessado beaseando no prefixo da chave definido pela profundidade dada
     * 
     * @param string key
     * @param int depth
     * @return int
    */
    int getPrefix(string key,int depth);
    /**
     * Função interna que retorna uma string de número binários que representa o indice dado, o tamanho da string é definido
     * diretamente pela profundidade global atual do diretório
     * 
     * @param int index
     * @return string
    */
    string binaryIndex(int index);
public:
    /**
     * Construtor da classe
     * 
     * @param int depth
     * @param int bucketSize
    */
    Directory(int depth, int bucketSize);
    /**
     * Destrutor da classe
     * 
    */
    ~Directory();
    /**
     * Insere uma chave dentro do seu respectivo balde no diretório, a função realiza os tratamentos necessários caso ocorra overflow
     * e verifica se a chave já está presente no diretório
     * 
     * @param string key
     * @return void
    */
    void insert(string key);
    /**
     * Função que manda uma mensagem no console se determinada chave existe no diretorio
     * 
     * @param string key
     * @return void
    */
    void search(string key);
    /**
     * Função que retorna o número de chaves armazenadas no diretório
     * 
     * @return float
    */
    float getAllocatedKeys();
    /**
     * Função que retorna o número de criados para armazenar chaves
     * 
     * @return float
    */
    float getAvaliableSpaces();
    /**
     * Função que retorna o número de ponteiros criados para armazenar endereços de baldes
     * 
     * @return float
    */
    float getPointersAllocated();
    /**
     * Retorna o número de baldes alocados dinâmincamente dentro do diretório
     * 
     * @return float
    */
    float getBucketsAllocated();
};

#endif
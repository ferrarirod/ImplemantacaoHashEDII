#ifndef BUCKET_H
#define BUCKET_h

#include<iostream>
#include<vector>
#include<string>

using namespace std;

//Classe responsável por armazenar as pseudo-chaves
class Bucket
{
private:
    //Variável que armazena a profundidade local do balde
    int localDepth;
    //Variável que armazena o máximo de valores que este balde pode manter sem precisar se dividir
    int size;
    //Vector que armazena todas as pseudo-chaves em formato de string
    vector<string> keys;
public:
    /**
     * Construtor da classe
     * 
     * @param int depth
     * @param int size
    */
    Bucket(int depth,int size);
    /**
     * Destrutor da classe
     * 
    */
    ~Bucket();
    /**
     * Função responsável pela adição de uma nova chave única diretamente no vector de chaves
     * 
     * @param string key
     * @return void
    */
    void insert(string key);
    /**
     * Função responsável pela remoção de uma chave do vector de chaves, a chave é removida e o vector é reajustado 
     * para não haver "buracos" na sequencia de chaves
     * 
     * @param string key
     * @return void
    */
    void remove(string key);
    /**
     * Função que verifica se uma chave existe dentro de um balde
     * 
     * @param string key
     * @return bool
    */
    bool search(string key);
    /**
     * Funçao que incrementa a profundidade local do balde em 1
     * 
     * @return void
    */
    void increaseDepth();
    /**
     * Função que retorna a profundidade local atual de um balde
     * 
     * @return int
    */
    int getLocalDepth();
    /**
     * Função que retorna uma chave armazenada no balde, baseada na sua posição no vector de chaves
     * 
     * @param int index
     * @return string
    */
    string getKey(int index);
    /**
     * Função que retorna o espaço utilizado naquele momento pelo vector de chaves
     * 
     * @return int
    */
    int getUsedSize();
};

#endif
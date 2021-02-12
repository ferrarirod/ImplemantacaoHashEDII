#ifndef BUCKET_H
#define BUCKET_h

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Bucket
{
private:
    int localDepth;
    int size;
    vector<string> keys;
public:
    Bucket(int depth,int size);
    ~Bucket();
    bool insert(string key);
    void remove(string key);
    bool search(string key);
    int increaseDepth();
    int getLocalDepth();
    string getKey(int index);
    int getUsedSize();
};

#endif
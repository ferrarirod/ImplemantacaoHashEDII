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
    void search(string key);
    int increaseDepth();
};

#endif
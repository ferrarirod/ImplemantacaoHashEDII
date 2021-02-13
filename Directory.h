#ifndef DIRECTORY_H
#define DIRECTORY_H

#include<iostream>
#include<vector>
#include<string>
#include <math.h>
#include "Bucket.h"

using namespace std;

class Directory
{
private:
    int globalDepth;
    int bucketSize;
    float allocatedKeys;
    float avaliableSpaces;
    float pointersAllocated;
    float bucketsAllocated;
    vector<Bucket*> buckets;
    void splitBucket(int bucket_key);
    void duplicateDirectory();
    int getPrefix(string key,int depth);
    string binaryIndex(int index);
public:
    Directory(int depth, int bucketSize);
    ~Directory();
    void insert(string key);
    void search(string key);
    float getAllocatedKeys();
    float getAvaliableSpaces();
    float getPointersAllocated();
    float getBucketsAllocated();
};

#endif
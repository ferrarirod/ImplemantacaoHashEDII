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
    vector<Bucket*> buckets;
    void splitBucket(int bucket_key);
    void duplicateDirectory();
    int getPrefix(string key,int depth);
    int getPairIndex(int key);
public:
    Directory(int depth, int bucketSize);
    ~Directory();
    void insert(string key);
    void search(string key);
};

#endif
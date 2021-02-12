#include "Directory.h"

Directory::Directory(int depth,int bucketSize)
{
    this->globalDepth = depth;
    this->bucketSize = bucketSize;
    for(int i = 0; i < 1 << this->globalDepth;i++)
    {
        this->buckets.push_back(new Bucket(this->globalDepth,bucketSize));
    }
}

Directory::~Directory(){}

int Directory::getPrefix(string key,int depth)
{
    string prefix = key.substr(0,depth);
    int index = 0;
    for(int i = 0;i < prefix.length();i++)
    {
        index += ((int)prefix[i] - 48) * pow(2,(prefix.length() - 1) - i);
    }

    return index;
}

int Directory::getPairIndex(int key)
{
    if(key % 2 == 0)
    {
        return key + 1;
    }
    else
    {
        return key - 1;
    }
}

void Directory::duplicateDirectory()
{
    vector<Bucket*> temp;
    for(int i = 0;i < this->buckets.size();i++)
    {
        temp.push_back(buckets[i]);
        temp.push_back(buckets[i]);
    }
    this->buckets = temp;
    this->globalDepth++;
}

void Directory::splitBucket(int bucketKey)
{
    Bucket *temp = new Bucket(this->buckets[bucketKey]->getLocalDepth() + 1,this->bucketSize);
    this->buckets[bucketKey]->increaseDepth();
    for(int i = 0;i < this->bucketSize; i++)
    {
        if(getPrefix(this->buckets[bucketKey]->getKey(i),this->buckets[bucketKey]->getLocalDepth()) != bucketKey)
        {
            temp->insert(this->buckets[bucketKey]->getKey(i));
            this->buckets[bucketKey]->remove(this->buckets[bucketKey]->getKey(i));
        }
        else
        {
            continue;
        }
    }

    this->buckets[getPairIndex(bucketKey)] = temp;
}
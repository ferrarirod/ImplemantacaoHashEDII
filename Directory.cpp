#include "Directory.h"

Directory::Directory(int depth,int bucketSize)
{
    this->globalDepth = depth;
    this->bucketSize = bucketSize;
    this->allocatedKeys = 0;
    this->avaliableSpaces = 0;
    this->bucketsAllocated = 0;
    this->pointersAllocated = 0;
    for(int i = 0; i < 1 << this->globalDepth;i++)
    {
        this->buckets.push_back(new Bucket(this->globalDepth,bucketSize));
        this->avaliableSpaces += bucketSize;
        this->pointersAllocated++;
        this->bucketsAllocated++;
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

string Directory::binaryIndex(int index)
{
    int quotient = index;
    int bynary[this->globalDepth];
    string bynStr;
    for(int i = 0; i < this->globalDepth;i++)
    {
        bynary[i] = 0;
    }
    int i = this->globalDepth - 1;
    while(quotient != 0)
    {
        int remainder = quotient % 2;
        bynary[i] = remainder;
        quotient = quotient/2;
        i--;    
    }

    bynStr = to_string(bynary[0]);
    for(int i = 1;i < this->globalDepth;i++)
    {
        bynStr += to_string(bynary[i]);
    }

    return bynStr;
}

void Directory::duplicateDirectory()
{
    vector<Bucket*> temp;
    for(int i = 0;i < this->buckets.size();i++)
    {
        temp.push_back(buckets[i]);
        temp.push_back(buckets[i]);
        this->pointersAllocated++;
    }
    this->buckets = temp;
    this->globalDepth++;
}

void Directory::splitBucket(int bucketKey)
{
    Bucket *temp = new Bucket(this->buckets[bucketKey]->getLocalDepth() + 1,this->bucketSize);
    this->bucketsAllocated++;
    this->avaliableSpaces += this->bucketSize;
    this->buckets[bucketKey]->increaseDepth();
    for(int i = 0;i < this->buckets[bucketKey]->getUsedSize(); i++)
    {
        if(getPrefix(this->buckets[bucketKey]->getKey(i),this->buckets[bucketKey]->getLocalDepth()) != getPrefix(binaryIndex(bucketKey),this->buckets[bucketKey]->getLocalDepth()))
        {
            temp->insert(this->buckets[bucketKey]->getKey(i));
        }
        else
        {
            continue;
        }
    }

    for(int i = 0;i < temp->getUsedSize(); i++)
    {
        this->buckets[bucketKey]->remove(temp->getKey(i));
    }

    for(int i = 0; i < this->buckets.size(); i++)
    {
        if(this->buckets[i] == this->buckets[bucketKey])
        {
            if(getPrefix(binaryIndex(i),this->buckets[bucketKey]->getLocalDepth()) != getPrefix(binaryIndex(bucketKey),this->buckets[bucketKey]->getLocalDepth()))
            {
                this->buckets[i] = temp;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
}

void Directory::search(string key)
{
    int index = getPrefix(key,this->globalDepth);
    if(this->buckets[index]->search(key))
    {
        cout << "Chave " << key << " encontrada no hash" << endl;
    }
    else
    {
        cout << "Chave " << key << " não encontrada" << endl;
    }
}

void Directory::insert(string key)
{
    int index = getPrefix(key,this->globalDepth);
    if(!this->buckets[index]->search(key))
    {
        if(this->buckets[index]->getUsedSize() < this->bucketSize)
        {
            this->buckets[index]->insert(key);
            this->allocatedKeys++;
        }
        else
        {
            if(this->buckets[index]->getLocalDepth() == this->globalDepth)
            {
                this->buckets[index]->insert(key);
                this->duplicateDirectory();
                this->splitBucket(index);
                this->allocatedKeys++;
            }
            else
            {
                this->buckets[index]->insert(key);
                this->splitBucket(index);
                this->allocatedKeys++;
            }
        }
    }
    else
    {
        cout << "Chave já presente no hash" << endl;
    }
}

float Directory::getAllocatedKeys()
{
    return this->allocatedKeys;
}

float Directory::getAvaliableSpaces()
{
    return this->avaliableSpaces;
}

float Directory::getBucketsAllocated()
{
    return this->bucketsAllocated;
}

float Directory::getPointersAllocated()
{
    return this->pointersAllocated;
}
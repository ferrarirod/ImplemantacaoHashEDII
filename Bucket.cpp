#include "Bucket.h"

Bucket::Bucket(int depth,int size)
{
    this->localDepth = depth;
    this->size = size;
}

Bucket::~Bucket(){}

void Bucket::insert(string key)
{
    this->keys.push_back(key);
}

void Bucket::remove(string key)
{
    for(int i = 0;i < this->keys.size();i++)
    {
        if(this->keys[i] == key)
        {
            this->keys.erase(this->keys.begin() + i);
            break;
        }
        else
        {
            continue;
        }
    }
}

bool Bucket::search(string key)
{
    for(int i = 0; i < this->keys.size();i++)
    {
        if(this->keys[i] == key)
        {
            return true;
        }
        else
        {
            continue;
        }
    }

    return false;
}

void Bucket::increaseDepth()
{
    this->localDepth++;
}

int Bucket::getLocalDepth()
{
    return this->localDepth;
}

string Bucket::getKey(int index)
{
    return this->keys[index];
}

int Bucket::getUsedSize()
{
    return this->keys.size();
}

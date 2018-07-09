#include "../include/List.hpp"

List::List(int c)
{
    capacity = c;
    arr = new HeapNode *[capacity];
    inUse = 0;
}
List::~List()
{
    for (int i = 0; i < inUse; i++)
    {
        delete arr[i];
    }
    delete[] arr;
}

HeapNode *List::getMin()
{
    return arr[0];
}
void List::update(int index, double time)
{
    int i = 0;
    for (i = 0; i < inUse; i++)
    {
        if (arr[i]->getIndex() == index)
            break;
    }
    if (i < inUse)
        arr[i]->setTime(time);
    sort();
}
void List::insertKey(int index, double time)
{
    if (inUse < capacity)
    {
        arr[inUse] = new HeapNode(index, time);
        inUse++;
    }
    sort();
}
void List::swap(int i, int j)
{
    int index = arr[i]->getIndex();
    double time = arr[i]->getTime();
    arr[i]->setIndex(arr[j]->getIndex());
    arr[i]->setTime(arr[j]->getTime());
    arr[j]->setIndex(index);
    arr[j]->setTime(time);
}
void List::sort()
{
    int i, j;
    HeapNode *chosed;
    for (i = 1; i < inUse; i++)
    {
        chosed = arr[i];
        j = i - 1;
        while ((j >= 0) && (arr[j]->getTime() > chosed->getTime()))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chosed;
    }
}
void List::print()
{
    for (int i = 0; i < inUse; i++)
    {
        cout << arr[i]->getIndex() << " : " << arr[i]->getTime() << endl;
    }
}

bool List::isSort()
{
    if (inUse > 0)
    {
        HeapNode *n = arr[0];
        for (int i = 1; i < inUse; i++)
        {
            if (n->getTime() > arr[i]->getTime())
                return false;
            else
                n = arr[i];
        }
    }
    else
        return true;
    return true;
}
HeapNode *List::getNode(int index)
{
    for (int i = 0; i < inUse; i++)
    {
        if (arr[i]->getIndex() == index)
            return arr[i];
    }
    return nullptr;
}

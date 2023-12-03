#include "objPosArrayList.h"



objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on the heap
    listSize = 0;                      // no valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;     // array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // check if listSize is equal to arrayCapacity. If yes, at capacity, don't insert.
    if(listSize == arrayCapacity)
    {
        return; // List is full, no insertion allowed
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]); // this will shuffle all the elements towards the tail
    }

    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return; // List is full, no insertion is allowed
    }

    aList[listSize].setObjPos(thisPos);
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
    {
        return;
    }

    for(int i = 0; i < listSize - 1;i++)
    {
        aList[i].setObjPos(aList[i + 1]); // shuffling towards the head
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        return; // list is empty, no removal allowed
    }
    listSize--; // lazy delete
}

void objPosArrayList::getHeadElement(objPos &returnPos) const
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos) const
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index) const
{
    if(listSize == 0 || index < 0 || index >= listSize)
    {
        return; // index out of bound, no element retrieval allowed
    }

    returnPos = aList[index];
}

void objPosArrayList::addSize(int addition) {
    listSize += addition;
}
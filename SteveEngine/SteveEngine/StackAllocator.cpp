#include "StackAllocator.h"

StackAllocator::StackAllocator(int bufferSize)
{
    this->bufferSize = bufferSize;
    buffer = new char[bufferSize];
    head = buffer;
}

void StackAllocator::clear()
{
    head = buffer;
}
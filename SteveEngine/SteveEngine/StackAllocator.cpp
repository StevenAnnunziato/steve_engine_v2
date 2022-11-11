#include "StackAllocator.h"

StackAllocator::StackAllocator(int bufferSize)
{
    this->bufferSize = bufferSize;
    buffer = new char[bufferSize];
    head = buffer;
}

StackAllocator::~StackAllocator()
{
    delete buffer;
}

void StackAllocator::clear()
{
    head = buffer;
}
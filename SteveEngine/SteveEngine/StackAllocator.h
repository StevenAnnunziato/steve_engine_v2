#pragma once
class StackAllocator
{
public:
    StackAllocator(int bufferSize);

    // Allocate a single piece of data
    template <typename T>
    T* alloc(size_t numArrayElements = 1) // let the user get an array if needed by specifying array size
    {
        // find how much memory to allocate and where
        size_t sizeToAlloc = sizeof(T) * numArrayElements;
        char* allocationPoint = head;

        // make sure it won't go past the end of the stack
        if (allocationPoint + sizeToAlloc > buffer + bufferSize)
            return nullptr;

        // return the correct address and update head for next time
        head += sizeToAlloc;
        return (T*)allocationPoint;
    }

    char* getHeadAddress() { return head; }

    // reset head back to the beginning of the stack
    void clear();

private:
    int bufferSize;
    char* buffer; // location to start allocating memory this frame
    char* head; // running location of where to return the next memory address this frame
};

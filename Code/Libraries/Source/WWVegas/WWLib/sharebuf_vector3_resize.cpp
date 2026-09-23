// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Target extension of the donor ShareBuffer layout. The matched Vector3
// constructor at 0x169780 establishes raw/aligned pointers and alignment.
// Mesh geometry readers at 0x16AF80 and 0x16AFD0 call this resize operation.
#include "refcount.h"
#include <string.h>

void __cdecl operator delete[](void *) throw();

class Vector3
{
public:
    float x, y, z;
    Vector3() {}
};

template<class T>
class ShareBufferClass : public RefCountClass
{
public:
    void Resize(int newsize);
protected:
    T *RawBuffer;
    T *Array;
    int Count;
    int Alignment;
};

template<class T>
void ShareBufferClass<T>::Resize(int newsize)
{
    if (newsize < 0 || newsize == Count)
        return;

    T *new_raw;
    T *new_array;
    if (Alignment == 0) {
        new_raw = new T[newsize];
        new_array = new_raw;
    } else {
        new_raw = (T *)new char[newsize * sizeof(T) + Alignment];
        new_array = (T *)(((unsigned int)new_raw + Alignment - 1) & ~(unsigned int)(Alignment - 1));
    }
    if (Count > 0 && newsize > 0) {
        int copycount = (Count < newsize) ? Count : newsize;
        // Retail copies the raw allocation, including in the aligned case.
        memcpy(new_raw, RawBuffer, copycount * sizeof(T));
    }
    delete[] RawBuffer;
    Array = new_array;
    RawBuffer = new_raw;
    Count = newsize;
}

template void ShareBufferClass<Vector3>::Resize(int);

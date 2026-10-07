// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// The target wrapper forwards owning texture assignment and returns this.
// Fog processing and two read_v3_materials call sites use it on four-byte
// handles. The original wrapper type name is unknown.
class TextureClass;

template<class T>
class RefCountPtr
{
public:
    ~RefCountPtr();
    const RefCountPtr &operator=(const RefCountPtr &);
private:
    T *Ptr;
};

class BfmeTextureHandle
{
public:
    RefCountPtr<TextureClass> Handle;
    BfmeTextureHandle &operator=(const BfmeTextureHandle &other);
};

BfmeTextureHandle &BfmeTextureHandle::operator=(const BfmeTextureHandle &other)
{
    Handle = other.Handle;
    return *this;
}

// BFME1 1399ad37 BfmeHandleCXVectorDeletingDestructor.cpp provides the clean
// array-deletion emission pattern. Retail4559C uses element stride4 and the
// proven RefCountPtr<TextureClass> destructor17098D, both as scalar call and
// the array callback to the native vector destructor iterator629110.
// The original spelling of this wrapper is not asserted by the donor name.
void operator delete[](void *);
// ?DeleteTextureHandleArray absent-from-retail
void DeleteTextureHandleArray(RefCountPtr<TextureClass> *p)
{ delete[] p; }

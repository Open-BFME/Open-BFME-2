// cl: /G7 /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

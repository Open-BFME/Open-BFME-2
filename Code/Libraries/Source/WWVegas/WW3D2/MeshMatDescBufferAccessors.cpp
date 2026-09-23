// cl: /G7 /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Target buffer views used by the material fog pass at 0x189CD0.
// The caller uses MaterialArray at +0xE8/+0xEC and TextureArray at +0xC8.
// Texture handles follow the same WORD refcount ABI as the matched getter.
class VertexMaterialClass;

class MatBufferClass
{
    unsigned char prefix[8];
    VertexMaterialClass **RawBuffer;
public:
    VertexMaterialClass *Peek_Element(int index);
};

VertexMaterialClass *MatBufferClass::Peek_Element(int index)
{
    return RawBuffer[index];
}

class TextureClass
{
public:
    void Add_Ref() { ++RefCount; }
    void Release_Ref();
private:
    void *VTable;
    unsigned short RefCount;
};

template<class T>
class RefCountPtr
{
public:
    T *p;
};

class TexBufferClass
{
    unsigned char prefix[8];
    RefCountPtr<TextureClass> *RawBuffer;
public:
    void Set_Element(int index, const RefCountPtr<TextureClass> &value);
};

void TexBufferClass::Set_Element(int index, const RefCountPtr<TextureClass> &value)
{
    RefCountPtr<TextureClass> &slot = RawBuffer[index];
    if (value.p)
        value.p->Add_Ref();
    if (slot.p)
        slot.p->Release_Ref();
    slot.p = value.p;
}

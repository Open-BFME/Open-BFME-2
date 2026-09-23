// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/meshmatdesclayout /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Neutral view of the pointer buffer stored at descriptor+108. The target
// allocation names FXShaderArray; the original pointee/class names are unknown.
// Reader 0x188AF0 calls setter 0x15D300, which obtains the buffer through 0x15B7A0.
// The MatBuffer constructor supplies the reference pattern; target 0x15B230
// independently establishes the 24-byte layout and vtables 0xBD3C8C/0xBD3CA4.
#include "always.h"
#include <string.h>
#include <sharebuf.h>
extern void __cdecl operator delete[](void *) throw();

// Target buffer destructors free the raw array without clearing the base fields.
template <>
ShareBufferClass<RefCountClass *>::~ShareBufferClass()
{
    ::operator delete[](RawBuffer);
}

class OpaqueRefBuffer : public ShareBufferClass<RefCountClass *> {
public:
    OpaqueRefBuffer(int count, const char *msg) : ShareBufferClass<RefCountClass *>(count, msg) { Clear(); }
    virtual ~OpaqueRefBuffer();
    RefCountClass **Raw_Elements() { return RawBuffer; }
};
OpaqueRefBuffer::~OpaqueRefBuffer()
{
    for (int i = 0; i < Count; ++i) {
        if (RawBuffer[i]) {
            RawBuffer[i]->Release_Ref();
            RawBuffer[i] = 0;
        }
    }
}
class MeshMatDescClass {
public:
    int PassCount, VertexCount, PolyCount;
private:
    char padding[0xFC];
    OpaqueRefBuffer *OpaqueTailBuffers[4];
public:
    __declspec(noinline) OpaqueRefBuffer *Get_Rva0015B7A0(int pass, bool create);
    void Set_Rva0015D300(int index, void *entry, int pass);
};
OpaqueRefBuffer *MeshMatDescClass::Get_Rva0015B7A0(int pass, bool create)
{
    if (create && OpaqueTailBuffers[pass] == 0) {
        OpaqueTailBuffers[pass] = new OpaqueRefBuffer(PolyCount, "MeshMatDescClass::FXShaderArray");
    }
    return OpaqueTailBuffers[pass];
}
void MeshMatDescClass::Set_Rva0015D300(int index, void *entry, int pass)
{
    RefCountClass *value = (RefCountClass *)entry;
    OpaqueRefBuffer *buffer = Get_Rva0015B7A0(pass, true);
    if (value) value->Add_Ref();
    if (buffer->Raw_Elements()[index]) buffer->Raw_Elements()[index]->Release_Ref();
    buffer->Raw_Elements()[index] = value;
}

// Emission aid for the scalar deleting destructor selected by vtable 0xBD3CA4.
// ?ForceDelete_OpaqueRefBuffer@@YAXPAVOpaqueRefBuffer@@@Z absent-from-retail
void ForceDelete_OpaqueRefBuffer(OpaqueRefBuffer *p) { delete p; }

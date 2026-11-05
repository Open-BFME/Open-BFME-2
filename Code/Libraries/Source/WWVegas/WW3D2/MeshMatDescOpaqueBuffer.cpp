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
#include <new.h>
#include <new>
// Use the CRT operators instead of always.h's duplicate allocation declarations.
#define _OPERATOR_NEW_DEFINED_
#include "always.h"
#include <string.h>
// Retail's reference-count inline copies use size optimization. Preserve the
// inline base teardown while sharing the canonical declaration with the descriptor.
#pragma optimize("s", on)
#include "../WWLib/RefCountData.h"
inline RefCountClass::~RefCountClass() {}
#define REFCOUNT_H
#pragma optimize("", on)
#include <sharebuf.h>

// Target buffer destructors free the raw array without clearing the base fields.
template <>
ShareBufferClass<RefCountClass *>::~ShareBufferClass()
{
    ::operator delete[](RawBuffer);
}

// The base copy constructor is rowed in sharebuf_refcount_pointer_copy_ctor.cpp (0x0015ACB0);
// declared here so this unit calls that body instead of emitting a differing copy.
template <>
ShareBufferClass<RefCountClass *>::ShareBufferClass(const ShareBufferClass<RefCountClass *> &that);

class OpaqueRefBuffer : public ShareBufferClass<RefCountClass *> {
public:
    OpaqueRefBuffer(int count, const char *msg) : ShareBufferClass<RefCountClass *>(count, msg) { Clear(); }
    OpaqueRefBuffer(const OpaqueRefBuffer &that);
    virtual ~OpaqueRefBuffer();
    RefCountClass **Raw_Elements() { return RawBuffer; }
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline OpaqueRefBuffer::OpaqueRefBuffer(const OpaqueRefBuffer &that) : ShareBufferClass<RefCountClass *>(that)
{
    for (int i = 0; i < Count; ++i) {
        if (RawBuffer[i])
            RawBuffer[i]->Add_Ref();
    }
}

// ?bfmeAnchorOpaqueRefBufferCtor absent-from-retail
void *bfmeAnchorOpaqueRefBufferCtor(void *where, const OpaqueRefBuffer &that)
{
	return ::new (where) OpaqueRefBuffer(that);
}

OpaqueRefBuffer::~OpaqueRefBuffer()
{
    for (int i = 0; i < Count; ++i) {
        if (RawBuffer[i]) {
            RawBuffer[i]->Release_Ref();
            RawBuffer[i] = 0;
        }
    }
}
#include "MeshMatDescClass.h"

OpaqueRefBuffer *MeshMatDescClass::Get_Rva0015B7A0(int pass, bool create)
{
    if (create && field_108[pass] == 0) {
        field_108[pass] = new OpaqueRefBuffer(PolyCount, "MeshMatDescClass::FXShaderArray");
    }
    return field_108[pass];
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
void ForceDelete_OpaqueRefBuffer(OpaqueRefBuffer *opaqueRefBuffer) { delete opaqueRefBuffer; }

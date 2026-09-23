// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/meshmatdesclayout /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 MatBufferClass destructor adapted to the target's raw pointer array.
// MatBuffer constructor 0x15B1A0 installs vtable 0xBD3C9C; its deleting
// destructor at 0x15D040 calls this body at 0x15B300.
#include "always.h"
#include <string.h>
#include <sharebuf.h>
extern void __cdecl operator delete[](void *) throw();

// Target buffer destructors free the raw array without clearing the base fields.
// Only the established RefCountClass prefix is used here.
class VertexMaterialClass : public RefCountClass {};

template <>
ShareBufferClass<VertexMaterialClass *>::~ShareBufferClass()
{
    ::operator delete[](RawBuffer);
}

class MatBufferClass : public ShareBufferClass<VertexMaterialClass *> {
public:
    virtual ~MatBufferClass();
};
MatBufferClass::~MatBufferClass()
{
    for (int i = 0; i < Count; ++i) {
        if (RawBuffer[i]) {
            RawBuffer[i]->Release_Ref();
            RawBuffer[i] = 0;
        }
    }
}

// ?ForceDelete_MatBuffer@@YAXPAVMatBufferClass@@@Z absent-from-retail
void ForceDelete_MatBuffer(MatBufferClass *p) { delete p; }

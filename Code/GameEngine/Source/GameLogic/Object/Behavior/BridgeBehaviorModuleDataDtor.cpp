// cl: /Ireference/shims/moduledata /ICode/GameEngine/Include /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common /Ivendor/stlport
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 BridgeBehaviorModuleData destructor adapted to target list fields.
// Matched constructor 0x457FF1 installs vtable 0xC40A10; slot zero selects
// deleting destructor 0x45824C, which calls the destructor at 0x45804A.
// The registered FX/OCL callbacks establish the lists at +0x10 and +0x14.
#include <list>
#include "Common/AsciiString.h"
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BridgeBehaviorListValue12;
namespace _STL { template <> void _List_base<BridgeBehaviorListValue12,allocator<BridgeBehaviorListValue12> >::clear(); }
// Suppress this TU's non-retail copy of ??1?$_List_base@UBridgeBehaviorListValue12@@V?$allocator@UBridgeBehaviorListValue12@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _List_base<BridgeBehaviorListValue12,allocator<BridgeBehaviorListValue12> >::~_List_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@UBridgeBehaviorListValue12@@@_STL@@@_STL@@QBEXPAU?$_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<_List_node<BridgeBehaviorListValue12> >::deallocate(_List_node<BridgeBehaviorListValue12> *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct BridgeBehaviorTimeInfo8 {
    unsigned int delay_00;
    AsciiString boneName_04;
};
struct BridgeBehaviorListValue12 {
    void *object_00;
    BridgeBehaviorTimeInfo8 timeInfo_04;
};

#include "Common/Snapshot.h"
#include "Common/BfmeModuleData.h"
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

// Retail teardown restores Snapshot at BBB554, never an UpdateModuleData table.
class __declspec(novtable) UpdateModuleData : public ModuleData {
public:
	virtual ~UpdateModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

class BridgeBehaviorModuleData : public UpdateModuleData {
public:
	virtual ~BridgeBehaviorModuleData();

private:
	unsigned int unused04;
	float lateralScaffoldSpeed;
	float verticalScaffoldSpeed;
	std::list<BridgeBehaviorListValue12> bridgeDieFX;
	std::list<BridgeBehaviorListValue12> bridgeDieOCL;
};

BridgeBehaviorModuleData::~BridgeBehaviorModuleData()
{
	bridgeDieFX.clear();
	bridgeDieOCL.clear();
}

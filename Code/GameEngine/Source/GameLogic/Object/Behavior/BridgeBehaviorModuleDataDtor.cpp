// cl: /G7 /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common /Ivendor/stlport
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

struct BridgeBehaviorTimeInfo8 {
    unsigned int delay_00;
    AsciiString boneName_04;
};
struct BridgeBehaviorListValue12 {
    void *object_00;
    BridgeBehaviorTimeInfo8 timeInfo_04;
};

class UpdateModuleData {
public:
	virtual ~UpdateModuleData() {}
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

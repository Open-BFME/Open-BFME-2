// ??0SlaughterHordeContainModuleData@@QAE@XZ, retail 0x0048104D (136B).
// Factory 0x0024C071 news 0xEC and calls this ctor (sole caller); vtable
// 0x00C48DC0 whose slot 0 is the rowed deleting dtor 0x00481113 -> dtor
// 0x004810D5. Base HordeGarrisonContainModuleData (rowed ctor 0x0047A251),
// float 0.5f at +0xD4, member +0xD8 (rowed ctor 0x003623E5, pinned
// initFromStorages 0x00362087, dtor 0x00360D26), bitset<128> at +0xDC whose
// default ctor folds with the rowed reset 0x0024CA24; two 28-byte
// BfmeFixedStorage0004543D by-value args from prototype 0x00DFEFA4 (copy
// ctor 0x0004543D, ret 0x38 at the callee proves 2x28).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// Native 0x0048104D..0x004810D4 (136B). Factory 0x0024C071 news 0xEC and
// calls this ctor; vtable 0x00C48DC0 (deleting dtor 0x00481113 -> rowed dtor
// 0x004810D5). Base HordeGarrisonContainModuleData (rowed ctor 0x0047A251),
// float 0.5 at +0xD4, member +0xD8 (rowed ctor 0x003623E5, pinned
// initFromStorages 0x00362087), bitset<128> at +0xDC (rowed reset 0x0024CA24);
// two 28-byte BfmeFixedStorage temps from prototype 0x00DFEFA4.
#include <bitset>

#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// 0x00DFEFA4 is KINDOFMASK_NONE (ThingIsAnyKindOf.cpp); this unit copies it
// through its storage view.
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

#include "../../../../Include/GameLogic/Module/HordeGarrisonContainModuleData.h"

class SlaughterHordeContainModuleData : public HordeGarrisonContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();
private:
	float m_floatD4;
	Rva003623E5Member m_filterD8;
	_STL::bitset<128> m_bitsDC;
};

SlaughterHordeContainModuleData::SlaughterHordeContainModuleData()
	: m_floatD4(0.5f), m_filterD8(), m_bitsDC()
{
	m_filterD8.initFromStorages(reinterpret_cast<BfmeFixedStorage0004543D &>(KINDOFMASK_NONE), reinterpret_cast<BfmeFixedStorage0004543D &>(KINDOFMASK_NONE));
}

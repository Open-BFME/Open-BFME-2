// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ, retail 0x00484EA9,
// 75 bytes. ModuleData dtor destroying the UpgradeRequired string at +0x24
// through the folded 0x36410 and the AllowFilter at +0x20 through the
// pinned 0x360D26 and the ModifierName vector at +0x14 through the rowed
// 0x2CC70 then restoring the Snapshot base vtable 0xBBB554. Member order
// vector plus filter plus string drives states 0 plus 1 plus 2 so teardown
// reads 2 plus 1 plus 0 exactly as retail. Shape follows
// LargeGroupBonusUpdateModuleDataDtor (shared Snapshot base dtor, novtable
// suppressing the entry derived-vtable
// store retail lacks). Identity is the ctor TU 0x484DF4 plus own vtable
// 0x00C4A490 plus table 0x00C4A388 plus factory 0x24C724 which news 0x38
// plus slot 0 deleting dtor 0x484E8D calling this body. BFME1 donor
// PassiveAreaEffectBehaviorModuleDataDestructorThunk.cpp proves virtual
// public UAE spelling.

#include <vector>
#include "Common/Snapshot.h"

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"
class Rva003B31ADMember
{
public:
	Rva003B31ADMember();

private:
	int m_handle;
};

class __declspec(novtable) PassiveAreaEffectBehaviorModuleData : public Snapshot
{
public:
	PassiveAreaEffectBehaviorModuleData();
	virtual ~PassiveAreaEffectBehaviorModuleData();

private:
	unsigned int m_unused04; // +0x04, unstored gap
	float m_effectRadius; // +0x08
	float m_healPercentPerSecond; // +0x0C
	int m_pingDelay; // +0x10
	_STL::vector<AsciiString> m_modifierName; // +0x14
	Rva003623E5Member m_allowFilter; // +0x20
	AsciiString m_upgradeRequired; // +0x24, inline-zeroed string (silent EH state)
	bool m_nonStackable; // +0x28
	unsigned char m_pad29[3];
	Rva003B31ADMember m_antiCategories; // +0x2C
	int m_antiFX; // +0x30
	int m_healFX; // +0x34
};

// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ @0x00484EA9
PassiveAreaEffectBehaviorModuleData::~PassiveAreaEffectBehaviorModuleData()
{
}

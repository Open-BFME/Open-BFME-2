// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-23
// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ, retail 0x004901BD, 104 bytes.
//
// LargeGroupBonus-side ModuleData for horde-size bonuses. Identity is the own
// table at 0x00C4D1A8 (UpdateRate at +0x8 plus HordeMemberFilter at +0xC plus
// Count at +0x10 plus Radius at +0x14 plus RubOffRadius at +0x1C plus
// AlliesOnly at +0x18 plus FlagSubObjectNames at +0x20 plus
// AttributeModifier at +0x2C) matching every store below, plus the rowed
// LargeGroupBonusUpdate pool key at 0x48FFD4 in the same cluster, plus the
// rowed buildFieldParse at 0x4900A0, plus the ModuleData factory at 0x24D43F
// which news 0x30 with this ctor as sole caller. Field names follow the
// HordeUpdateModuleData donor in HordeUpdate.cpp (same family and defaults:
// UpdateRate plus Count plus Radius plus RubOffRadius 20.0 plus AlliesOnly).
// Shape follows SpawnBehaviorModuleDataCtor (non-virtual empty base plus
// init-listed explicit vtable plus AsciiString member) over
// TerrainResourceBehaviorModuleDataCtor (Devastate V5: virtual-free base with
// declared-only dtor is the TU sole unwindable which arms the single state-0
// store while the filter member carries no dtor so its call advances no
// state). The flag-name vector storage is a trivially destructible 12-byte
// wrapper whose inline ctor placement-constructs the rowed _Vector_base at
// 0x211E58 through the folded AsciiString pin, so it advances no state
// either; a real vector member would add a state store retail lacks. The two
// default globals stay TU-local externs (DIR32 slots patch from retail).

#include <vector>
#include <new>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();

private:
	unsigned char m_data[4];
};

struct FlagSubObjectNames
{
	typedef _STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > Base;

	__forceinline FlagSubObjectNames(const _STL::allocator<AsciiString> &alloc = _STL::allocator<AsciiString>())
	{
		Base *const basePtr = reinterpret_cast<Base *>(&m_storage);
		__assume(basePtr != 0);
		new (basePtr) Base(alloc);
	}

	unsigned char m_storage[12];
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

extern int g_largeGroupBonusDefaultUpdateRate;
extern float g_largeGroupBonusDefaultRubOffRadius;

class LargeGroupBonusUpdateModuleData : public UpdateModuleData
{
public:
	LargeGroupBonusUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	int m_updateRate; // +8
	Rva003623E5Filter m_hordeMemberFilter; // +0xC
	int m_count; // +0x10
	float m_radius; // +0x14
	bool m_alliesOnly; // +0x18
	float m_rubOffRadius; // +0x1C
	FlagSubObjectNames m_flagSubObjectNames; // +0x20
	AsciiString m_attributeModifier; // +0x2C
};

// ??0LargeGroupBonusUpdateModuleData@@QAE@XZ @0x4901BD
LargeGroupBonusUpdateModuleData::LargeGroupBonusUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4D2A8))
	, m_updateRate(g_largeGroupBonusDefaultUpdateRate)
	, m_hordeMemberFilter()
	, m_count(0)
	, m_radius(0.0f)
	, m_alliesOnly(true)
	, m_rubOffRadius(g_largeGroupBonusDefaultRubOffRadius)
	, m_flagSubObjectNames()
	, m_attributeModifier()
{
}

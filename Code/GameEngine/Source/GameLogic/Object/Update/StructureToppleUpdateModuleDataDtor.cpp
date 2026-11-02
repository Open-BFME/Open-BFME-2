// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// ??1StructureToppleUpdateModuleData@@UAE@XZ, retail 0x00257B7A, 109 bytes.
// StructureTopple data dtor: slot-0 deleting dtor 0x00257B5E of vtable
// 0x00BF43A8 (installed by the rowed ctor 0x00257A5E, 0xBC bytes, news in the
// rowed data factory 0x00257BE7) calls it. It was pinned as
// StructureCollapseUpdateModuleData (and 0x00257B5E rowed as its ??_G), but the
// Collapse dtor is 0x00256B94 (vtable 0xBF3E30); the Topple ctor's layout is
// exactly what this dtor tears down.
//
// Layout (from the ctor TU StructureToppleUpdateModuleDataCtor.cpp): DieMux
// +0x08, AsciiString +0x64, three 12-byte vectors +0x70 through the eh vector
// destructor iterator 0x00629110 (element dtor 0x0047FAB3), vector<FXBoneInfo>
// +0xA0 through the rowed vector dtor 0x00257544, and vector<AngleFXInfo>
// +0xAC whose POD range-destroy is empty so only the buffer free (0x00030830)
// remains. Empty body: the four member destroys in reverse order (EH states
// 3..0) and the Snapshot base restore (0x00BBB554) are compiler-generated.
//
// /EHs (not /EHsc) is what keeps the buffer free a throwing call, which gives
// the angle vector its own unwind state (3); under /EHsc its state merges
// with the next one and the first store is 2.
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"

class ObjectCreationList;

// The 8-byte bone element; the vector dtor row 0x00257544 is spelled by this
// element name (see StlportVectorDtorFamily.cpp).
struct RvaPair00257544
{
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;
};

struct AngleFXInfo
{
	float m_angle;
	const void *m_fxList;
};

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

namespace _STL
{
// Declared-only so the call stays external to the rowed body.
template <>
vector<RvaPair00257544, allocator<RvaPair00257544> >::~vector();
// Keep allocator<AngleFXInfo>::deallocate inline-only: nothing here calls it out
// of line, and this TU's COMDAT copy is not retail's body.
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void allocator<AngleFXInfo>::deallocate(AngleFXInfo *__p, size_t) const
{ if (__p != 0) ::free((void *)__p); }
}

class __declspec(novtable) StructureToppleUpdateModuleData : public Snapshot
{
public:
	virtual ~StructureToppleUpdateModuleData();

private:
	int m_unused04; // +4
	DieMuxData m_dieMuxData; // +0x08
	int m_scalars[11]; // +0x38..+0x63
	AsciiString m_crushingWeaponName; // +0x64
	int m_burstDelays[2]; // +0x68
	_STL::vector<const ObjectCreationList *> m_ocls[3]; // +0x70
	int m_oclCount[3]; // +0x94
	_STL::vector<RvaPair00257544> m_fxbones; // +0xA0
	_STL::vector<AngleFXInfo> m_angleFX; // +0xAC
	float m_unkB8; // +0xB8
};

// Select-any like every other TU's copy of the class; the anchor keeps this
// unit's out-of-line body.
__declspec(noinline) inline StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData()
{
}

// ?bfmeAnchorStructureToppleUpdateModuleDataDtor absent-from-retail
void bfmeAnchorStructureToppleUpdateModuleDataDtor(StructureToppleUpdateModuleData *structureToppleUpdateModuleData)
{
	structureToppleUpdateModuleData->StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData();
}

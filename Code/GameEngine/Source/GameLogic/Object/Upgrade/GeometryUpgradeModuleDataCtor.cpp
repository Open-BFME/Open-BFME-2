// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /GX /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// ??0GeometryUpgradeModuleData@@QAE@XZ, retail 0x004B6EE2 (131 bytes).
// Upgrade-side ModuleData for wall/fortress geometry swaps. Identity is the
// own table at 0x00858918 (ShowGeometry/+118 and HideGeometry/+124 parsed by
// 0x42E896, then WallBoundsMesh/+130, RampMesh1/+134 and RampMesh2/+138
// parsed by 0x42F11E) matching every store below, plus the rowed
// GeometryUpgrade pool key at 0x4B6ABF in the same cluster, plus the BFME1
// GeometryUpgradeModuleDataConstructor donor (same class and fields; BFME2
// offsets are wider). The chained buildFieldParse at 0x4B6A3C calls the
// Upgrade base proc 0x4CE29D then adds that table; the ModuleData factory at
// 0x250642 news 0x13C and is the only raw caller. Shape follows
// UnitCrateCollideModuleDataCtor: the derived vtable store is
// compiler-emitted through the ??_7 pin at the true vtable 0x008589F0 (slot0
// is the scalar-deleting dtor at 0x4B6F65), which places it right after the
// rowed Rva00253487Base base call; the two vectors construct from the
// one-byte stack allocator temporary, the three strings null through their
// inline default ctors and clear through the rowed 0x36410 fold in the body
// (BFME1 donor calls clear() the same way). /Oy- forces the ebp frame with
// the __EH_prolog prologue.

#include <vector>
#include "ascii_string.h"
// The native field table uses parseAsciiStringVectorAppend for both lists;
// the rowed destructor also destroys vector<AsciiString> at these offsets.
// Keep the existing imported force-inline wrapper: its base constructor
// remains a declared nothrow call to the existing ICF provider (0x00211E58).
namespace _STL {
template <> vector<AsciiString,allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString,allocator<AsciiString> >::_Vector_base(const allocator<AsciiString> &) throw();
template <> __declspec(dllimport) __forceinline
vector<AsciiString, allocator<AsciiString> >::vector(const allocator<AsciiString> &__a)
	: _Vector_base<AsciiString, allocator<AsciiString> >(__a) {}
}

class Rva00253487Base
{
public:
	Rva00253487Base();
	virtual ~Rva00253487Base();

private:
	unsigned char m_pad[0x118 - 4];
};

class GeometryUpgradeModuleData : public Rva00253487Base
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_showGeometry; // +0x118
	_STL::vector<AsciiString> m_hideGeometry; // +0x124
	AsciiString m_wallBoundsMesh; // +0x130
	AsciiString m_rampMesh1; // +0x134
	AsciiString m_rampMesh2; // +0x138
};

// ??0GeometryUpgradeModuleData@@QAE@XZ @0x4B6EE2
GeometryUpgradeModuleData::GeometryUpgradeModuleData()
{
	m_wallBoundsMesh.clear();
	m_rampMesh1.clear();
	m_rampMesh2.clear();
}

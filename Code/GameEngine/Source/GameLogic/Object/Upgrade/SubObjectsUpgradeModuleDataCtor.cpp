// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /GX /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SubObjectsUpgradeModuleData@@QAE@XZ, retail 0x00257768, 136 bytes.
// Framed Upgrade ctor over the rowed Rva00253487Base base (0x253487):
// folded vtable 0x00BF41A8, four AsciiString vectors at +0x118/+0x124/
// +0x130/+0x13C through the rowed Vector_base (0x211E58, AsciiString
// spelling alias pin), float from 0.5f at +0x148, zero bytes at
// +0x150..+0x153, zero float at +0x14C. Own table 0x00857D38 holds
// ShowSubObjects/HideSubObjects/UpgradeTexture/FadeTimeInSeconds/
// WaitBeforeFadeInSeconds/RecolorHouse; the SubObjectsUpgrade pool key at
// 0x4B4D1E ends near the rowed proc; the factory at 0x25780C news 0x154
// and calls this ctor as sole caller. Recipe: GeometryUpgrade (plain
// _STL::vector members, bfmealloc shim) over StatusBits (EBO base,
// frameless shape) over SpawnBehavior (AsciiString member shape).
// Shape laws used: (1) /GX keeps the vector-init calls out-of-line (under
// /GX- they fold to inline stores); no EH states materialize so the body
// stays frameless-style with an ebp frame for the one-byte stack allocator
// temporary. (2) EBO-empty base keeps the base call this-direct (a 0x114
// pad in the base would offset it). (3) volatile on the explicit m_vtable
// pins its init-list store below the hoisted first-vector setup (both
// source orders emit the call first under /O1); the store bytes are the
// plain mov. Row supersedes the pinned ctor.

extern "C" const void *const vtbl_00BF41A8[];  // ??_7SubObjectsUpgradeModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF41A8=??_7SubObjectsUpgradeModuleData@@6B@")

#include <vector>

#include "ascii_string.h"

class Rva00253487Base
{
public:
	Rva00253487Base();
};


class SubObjectsUpgradeModuleData : public Rva00253487Base
{
public:
	SubObjectsUpgradeModuleData();

private:
	volatile const void *m_vtable; // +0
	unsigned char m_pad[0x118 - 4]; // +4
	_STL::vector<AsciiString> m_v118; // +0x118
	_STL::vector<AsciiString> m_v124; // +0x124
	_STL::vector<AsciiString> m_v130; // +0x130
	_STL::vector<AsciiString> m_v13C; // +0x13C
	float m_148; // +0x148
	float m_14C; // +0x14C
	unsigned char m_f150; // +0x150
	unsigned char m_f151; // +0x151
	unsigned char m_f152; // +0x152
	unsigned char m_f153; // +0x153
};

// ??0SubObjectsUpgradeModuleData@@QAE@XZ @0x257768
inline SubObjectsUpgradeModuleData::SubObjectsUpgradeModuleData()
	: m_vtable(reinterpret_cast<volatile const void *>(((unsigned int)vtbl_00BF41A8)))
{
	m_148 = 0.5f;
	m_f150 = 0;
	m_f151 = 0;
	m_f152 = 0;
	m_f153 = 0;
	m_14C = 0.0f;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeSubObjectsUpgradeModuleDataInlineAnchor@@YAXPAVSubObjectsUpgradeModuleData@@@Z absent-from-retail
void _bfmeSubObjectsUpgradeModuleDataInlineAnchor(SubObjectsUpgradeModuleData *p)
{
    p->SubObjectsUpgradeModuleData::SubObjectsUpgradeModuleData();
}
#pragma inline_depth()

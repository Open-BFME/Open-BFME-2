// cl: /O1 /Oy- /GX /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SubObjectsUpgradeModuleData@@QAE@XZ, retail 0x00257768, 136 bytes.
// Framed Upgrade ctor over the rowed OpenContainModuleData base (0x253487):
// folded vtable 0x00BF41A8, four AsciiString vectors at +0x118/+0x124/
// +0x130/+0x13C through the rowed Vector_base (0x211E58, AsciiString
// spelling alias pin), float from g_bfmeK1253 at +0x148, zero bytes at
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

#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class OpenContainModuleData
{
public:
	OpenContainModuleData();
};

extern const float g_bfmeK1253;

class SubObjectsUpgradeModuleData : public OpenContainModuleData
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
SubObjectsUpgradeModuleData::SubObjectsUpgradeModuleData()
	: m_vtable(reinterpret_cast<volatile const void *>(0x00BF41A8))
{
	m_148 = g_bfmeK1253;
	m_f150 = 0;
	m_f151 = 0;
	m_f152 = 0;
	m_f153 = 0;
	m_14C = 0.0f;
}

// cl: /O1 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??0Rva0026E7C8Ctor@@QAE@XZ, retail 0x0026E7C8, 28 bytes.
//
// Frameless thiscall ctor abutting the AIUpdate parseLocomotorSet body
// (sole raw caller is the unclaimed 0x26EA66). Stores the opaque data
// anchor 0xBFA3A4 at +0 (a .rdata blob near the LuaSpyData string, not a
// vtable: its slots do not decode as functions) and builds the +4 member
// as an empty 16B-element vector through the rowed BfmeE16 _Vector_base
// 0x211E58 with the 1-byte stack allocator temp idiom. Class identity
// unproven; Rva vehicle asserts no false name.

#include <vector>

struct BfmeE16
{
	unsigned char m_pad[16];
};

class Rva0026E7C8Ctor
{
public:
	Rva0026E7C8Ctor();

private:
	void *m_unk0;
	_STL::vector<BfmeE16> m_vec;
};

extern unsigned char Rva0026E7C8DataAnchor;

// ??0Rva0026E7C8Ctor@@QAE@XZ @0x0026E7C8
Rva0026E7C8Ctor::Rva0026E7C8Ctor() :
	m_unk0(&Rva0026E7C8DataAnchor)
{
}

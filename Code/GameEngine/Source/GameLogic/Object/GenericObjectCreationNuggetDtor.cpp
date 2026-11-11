// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1GenericObjectCreationNugget@@MAE@XZ at retail 0x001F31C6 (169B).
// Dedicated TU (the parseObject caller lives in the sibling
// GenericObjectCreationNuggetParseObject.cpp).
//
// The retail teardown sequence dictates the member model (states 8 down
// to 0, all byte-read): three AsciiString-vector members (+0x04/+0x114/
// +0x120 via range-destroy 0x2CC70), one AnimSet-vector member (+0x14 via
// 0x1F0801), four AsciiStrings (+0x10/+0x24/+0x108/+0x10C via the 0x36410
// fold), and a nullable pool handle at +0x7C whose INLINE null-checking
// dtor accounts for the mid-sequence test/je/call via the 0x50ED3 pin.
// The +0xB4 memset region needs no teardown (trivial). The trailing base
// vptr store falls out of the inline-empty base dtor. Everything else is
// padding; the ctor stash (reverse/attempts/0x001f0e32.cpp) carries the
// full scalar map.

#include "ascii_string.h"
#include <new.h>

#include "../../../Include/Common/PoolMember.h"

// Nullable owning handle: the inline dtor reproduces the conditional
// teardown (test/je/call) at +0x7C without a new pin.
struct NullablePoolHandle
{
	PoolMember *m_ptr;

	__forceinline ~NullablePoolHandle()
	{
		if (m_ptr)
			m_ptr->Rva0050ED3();
	}
};

// Stand-ins for the vector members (12B each): only the out-of-line
// range-destroy calls appear in a dtor, so opaque types pinned at the
// destroy addresses are sufficient and honest.
struct RvaVecAscii
{
	~RvaVecAscii();

private:
	unsigned char m_data[12];
};

struct RvaVecAnimSet
{
	~RvaVecAnimSet();

private:
	unsigned char m_data[12];
};

class ObjectCreationNugget
{
public:
	ObjectCreationNugget();
	virtual ~ObjectCreationNugget();
};
// ??0ObjectCreationNugget@@QAE@XZ @0x001F0102 9B: the default constructor, storing the
// class's own vtable (VA 0x00BE09D0) and returning this.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline ObjectCreationNugget::ObjectCreationNugget()
{
}

// ?bfmeAnchorObjectCreationNugget absent-from-retail
void *bfmeAnchorObjectCreationNugget(void *where)
{
	return new (where) ObjectCreationNugget();
}


class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();

protected:
	virtual ~GenericObjectCreationNugget();

private:
	RvaVecAscii m_names; // +0x04
	AsciiString m_putInContainer; // +0x10
	RvaVecAnimSet m_animSets; // +0x14
	unsigned char m_pad20[0x24 - 0x20]; // +0x20 (fxFinal lives here)
	AsciiString m_particleSysName; // +0x24
	unsigned char m_pad28[0x7C - 0x28]; // +0x28 (debris/mass/scalars)
	NullablePoolHandle m_unk7C; // +0x7C
	unsigned char m_pad80[0x108 - 0x80]; // +0x80 (B4 memset region inside)
	AsciiString m_unk108; // +0x108
	AsciiString m_unk10C; // +0x10C
	unsigned char m_pad110[0x114 - 0x110]; // +0x110
	RvaVecAscii m_tailVec114; // +0x114
	RvaVecAscii m_tailVec120; // +0x120
};

typedef char NuggetSizeMatchesRetail[(sizeof(GenericObjectCreationNugget) == 0x12C) ? 1 : -1];

// ??1GenericObjectCreationNugget@@MAE@XZ
GenericObjectCreationNugget::~GenericObjectCreationNugget()
{
}

// ??1ObjectCreationNugget@@UAE@XZ @0x001F0409 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline).
inline ObjectCreationNugget::~ObjectCreationNugget()
{
}

// cl: /DNDEBUG /MD
//
// BfmeResetTextureRef::clear, retail 0x0004D75B, 19 bytes.
// Dedicated TU so the assign unit cannot see this body. /O1 for and-zero
// of the holder after Release_Ref.

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

void BfmeResetTextureRef::clear()
{
	if (pointer)
	{
		pointer->Release_Ref();
		pointer = 0;
	}
}

class Member0C00739C70
{
public:
	void clear();
};

class Rva0004D754
{
public:
	void clear();
	Member0C00739C70 *m_ptr;
};

void Rva0004D754::clear()
{
	m_ptr->clear();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?clear@Rva00180023@@QAEXXZ=?clear@BfmeResetTextureRef@@QAEXXZ")
#pragma comment(linker, "/alternatename:?clear@HAnimPrototypeOwner@@QAEXXZ=?clear@BfmeResetTextureRef@@QAEXXZ")
#pragma comment(linker, "/alternatename:?clear@HTreePrototypeOwner@@QAEXXZ=?clear@BfmeResetTextureRef@@QAEXXZ")

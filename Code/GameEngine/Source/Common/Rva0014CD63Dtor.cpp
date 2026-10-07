// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1Rva0014CD63@@UAE@XZ @ 0x0014CD63 (82 bytes). Prototype dtor for the
// vtable at 0x00BD37EC: stores the vtable, releases the counted +0x14 tree
// link inline (same shape as Rva0014CDCB_ReleaseTree, without the final
// null), tears down the +0x18 StringClass via Free_String at 0x00610A40, then
// delegates to the 0x0061ED80 base. Class view mirrors the sibling
// Rva0014CDCBReleaseTree.cpp TU (PrototypeTreeRef + pad + m_tree); the
// StringClass member is TU-local with a declared-only dtor so the call
// resolves to the ledger address instead of capturing locally.

class PrototypeTreeRef
{
public:
	virtual void DeleteThis(); // slot 0, destroys on final release
	int m_refCount; // +0x04
};

class StringClass
{
public:
	~StringClass() { Free_String(); }
private:
	void Free_String();
};

class Rva0061ED80
{
public:
	virtual ~Rva0061ED80();
};

class Rva0014CD63 : public Rva0061ED80
{
public:
	virtual ~Rva0014CD63();

	char m_pad04[0x10]; // +0x04..+0x13, untouched by this body
	PrototypeTreeRef *m_tree; // +0x14
	StringClass m_name; // +0x18
};

// ??1Rva0014CD63@@UAE@XZ
inline Rva0014CD63::~Rva0014CD63()
{
	PrototypeTreeRef *tree = m_tree;
	if (tree != 0)
	{
		if (--tree->m_refCount == 0)
			tree->DeleteThis();
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva0014CD63InlineAnchor@@YAXPAVRva0014CD63@@@Z absent-from-retail
void _bfmeRva0014CD63InlineAnchor(Rva0014CD63 *p)
{
    p->Rva0014CD63::~Rva0014CD63();
}
#pragma inline_depth()

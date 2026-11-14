// cl: /EHs /MD
// ?bfmeGoEBC@BfmeThingEBC@@QAEXPAX@Z, retail 0x00460A85 (19B) and
// ?bfmeGoEBD@BfmeThingEBD@@QAEXXZ, retail 0x003862CA (17B). Ported from
// Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv802.cpp (BFME1 0x001F8660
// and 0x006374B0). Trimmed to the two placed owner/sub dispatches; the EBE
// lookup is declared-only here. Callees resolve via new ledger pins at
// 0x0046094C (bfmeCallEBC) and 0x00383EEA (bfmeCallEBD), the donor's own
// family names on unclaimed ground.

// LINK: the owner call binds the rowed 0x0046094C (DynamicPortalBehaviour::rva0046094C, DynamicPortalBehaviour.cpp).
#include "../../Include/GameLogic/Module/DynamicPortalBehaviour.h"

struct BfmeThingEBC
{
	void bfmeGoEBC(void *unused);
	unsigned char m_bfmeHead[0x21];
	char m_bfmeFlag;
};

// ?bfmeGoEBC@BfmeThingEBC@@QAEXPAX@Z
void BfmeThingEBC::bfmeGoEBC(void *unused)
{
	((DynamicPortalBehaviour *)((char *)this - 0x1c))->rva0046094C();
	m_bfmeFlag = 1;
}

// Reference algorithm: STLport4.5.3 stl/_tree.c::_M_erase and _tree.h::clear.
// This subobject is independently anchored by bfmeGoEBD at3862CA: it passes
// this+18 to clear383EEA, which passes header->parent to erase383A95.
// Keep the donor's opaque application identity; the actual key/value names
// are not established. Node links are proven by both recursive traversal and
// clear's root/extreme resets, not by the shared byte shape alone.
struct BfmeNodeEBD
{
	unsigned int color;
	BfmeNodeEBD *parent, *left, *right;
};

// Declaration-only view, never sized or instantiated. Destructor382879 is
// independently reached by scalar-deleting destructor382B47 and the value
// cleanup wrapper383415. It adjusts +4 to mapped-value dtor38240F; pair
// constructor3829E5 constructs that same mapped subobject at +4.
#include "../../Include/Common/BfmeNodeValueEBD.h"

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

// STLport's owning header proxy. Destructor384DEB calls the proven clear on
// the same receiver, then destroys this header on normal and exceptional exits.
// /EHs preserves the retail cleanup-state transition before calling free.
struct BfmeHeaderEBD
{
	BfmeNodeEBD *data;
	__forceinline ~BfmeHeaderEBD() { if (data) free(data); }
};

class BfmeSubEBD
{
public:
	~BfmeSubEBD();
	void bfmeCallEBD();
	void bfmeEraseSubtree(BfmeNodeEBD *node);
private:
	BfmeHeaderEBD m_header;
	unsigned int m_nodeCount;
};

BfmeSubEBD::~BfmeSubEBD()
{
	bfmeCallEBD();
}

void BfmeSubEBD::bfmeEraseSubtree(BfmeNodeEBD *node)
{
	while (node) {
		bfmeEraseSubtree(node->right);
		BfmeNodeEBD *left = node->left;
		reinterpret_cast<BfmeNodeValueEBD *>(node + 1)->~BfmeNodeValueEBD();
		free(node);
		node = left;
	}
}

// Reference _Rb_tree::clear, now linked to the verified recursive eraser.
void BfmeSubEBD::bfmeCallEBD()
{
	if (m_nodeCount != 0) {
		bfmeEraseSubtree(m_header.data->parent);
		m_header.data->left = m_header.data;
		m_header.data->parent = 0;
		m_header.data->right = m_header.data;
		m_nodeCount = 0;
	}
}

struct BfmeThingEBD
{
	void bfmeGoEBD();
	unsigned char m_bfmeHead[0x18];
	BfmeSubEBD m_tree;
	// The recovered tree occupies eight bytes. Preserve the verified flag+6C.
	unsigned char m_bfmePad[0x4c];
	char m_bfmeFlag;
};

// ?bfmeGoEBD@BfmeThingEBD@@QAEXXZ
void BfmeThingEBD::bfmeGoEBD()
{
	m_tree.bfmeCallEBD();
	m_bfmeFlag = 0;
}

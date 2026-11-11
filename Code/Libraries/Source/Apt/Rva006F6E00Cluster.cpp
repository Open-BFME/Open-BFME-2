// cl: /DNDEBUG /MD
// AptDisplayList.cpp node-create insert at retail 0x006F6E00 (199 bytes).
// Allocates the 0x60-byte display-list node through the 0xE176F4 pool
// (Rva006D2A60::allocBlock), constructs Rva006CBDE0(type, p1, 0), checks the
// already-found depth item with an AptArray-style assert at AptDisplayList.cpp
// line 0x1EC, stores the p1 back-pointer at +0x4C, folds the 17-bit key into
// +0x58 and splices the node after pOldItem through the rowed link helper
// Rva006F6D60 (0x006F6D60).

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "AptValue.h"
#include "AptCIHClass.h"

#include "Rva006D2A60.h"

extern Rva006D2A60 *g_pChainBlockAllocatorF4; // VA 0x00E176F4

class Rva006CBDE0
{
public:
	Rva006CBDE0(int type, void *p1, AptValue *p2);

	static void *operator new(unsigned int size)
	{
		return g_pChainBlockAllocatorF4->allocBlock((int)size);
	}

	char m_storage[0x60];
};

class BfmeNestedBE;
struct BfmeQueryNode1279;
class BfmeQuery1279
{
public:
	void bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem);
	BfmeNestedBE *rva006F7D50(int nDepth);
	int rva006F6CE0() const;
	AptCIH *insert(AptCIH *pOldItem, AptCIH *pNewItem);
	AptCIH *rva006F6E00(int key, int type, void *p1, AptCIH *pOldItem, AptValue *pItemAtDepth);
	BfmeQueryNode1279 *m_root; // +0x00
};

AptCIH *BfmeQuery1279::rva006F6E00(int key, int type, void *p1, AptCIH *pOldItem, AptValue *pItemAtDepth)
{
	AptCIH *node = (AptCIH *)new Rva006CBDE0(type, p1, 0);

	if (!(pItemAtDepth == 0 || pItemAtDepth->isUndefined())) {
		g_bfmeAptAssertAtE17734("pItemAtDepth == NULL || pItemAtDepth->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x1EC);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	node->field4C = p1;
	node->field58 = node->field58 ^ ((node->field58 ^ (unsigned int)key) & 0x1FFFFu);
	return insert(pOldItem, node);
}

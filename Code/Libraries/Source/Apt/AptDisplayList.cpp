// cl: /O2 /DNDEBUG /MD
//
// ?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAXPAPAX@Z, retail 0x006F6BB0
// (297 bytes). BFME2 AptDisplayList query: three CRT-style asserts name
// this TU's path (ppPrev / ppItem / nDepth at lines 381-383), then the
// BFME1 BfmeQuery1279 donor shape (name walk with an isUndefined gate and
// an outlined string compare, key walk over a 16-bit node key, three
// out-param epilogues).
//
// Identity: the rowed forwards in BfmeQueryForward1279.cpp call this
// address as BfmeQuery1279::bfmeQuery1279; the in-body assert file string
// proves the definition lives in AptDisplayList.cpp in retail. The served
// ledger name takes the first parameter as void*; retail checks it with a
// signed jge (a void* >= 0 folds to unconditional), so the parameter is a
// signed int depth/key (the key walk compares it against the 16-bit node
// key); the row carries the corrected (int, int, void**, void**)
// signature and supersedes the void*-spelled pin. Query nodes embed an
// EAStringC name at +0x8, chain at +0x54, and carry a 16-bit key at
// +0x58; they are passed to the rowed AptValue isUndefined check.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class EAStringC
{
public:
	bool IsEqualTo(const EAStringC *other) const;
};

struct BfmeQueryNode1279
{
	void *m_bfme00;
	void *m_bfme04;
	void *m_nameHandle;
	char m_pad0C[0x54 - 0x0C];
	BfmeQueryNode1279 *m_next;
	int m_key;
};

// BfmeNestedBE link pair, retail-proven by the unlink asserts below
// (pItem/pPrev/pNext). BFME1's BfmeNestedBE carries the same links as
// m_bfme50/m_bfme54 plus a virtual; this TU-local model keeps the plain
// data layout the free unlink function needs.
class BfmeNestedBE
{
public:
	char m_pad00[0x50];
	BfmeNestedBE *pPrev;
	BfmeNestedBE *pNext;
	int m_bfme58;
	char m_pad5C[0x64 - 0x5C];
};

BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *pItem);

class BfmeQuery1279
{
public:
	void bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem);

private:
	BfmeQueryNode1279 *m_root;
};

// ?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAXPAPAX@Z
void BfmeQuery1279::bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem)
{
	if (ppPrev == 0) {
		g_bfmeAptAssertAtE17734("ppPrev", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17D);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (ppItem == 0) {
		g_bfmeAptAssertAtE17734("ppItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17E);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!(nDepth >= 0)) {
		g_bfmeAptAssertAtE17734("nDepth >= 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x17F);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	BfmeQuery1279 *self = this;
	BfmeQueryNode1279 *node = self->m_root->m_next;
	BfmeQueryNode1279 *namePrevious = self->m_root;

	if (name != 0 && node != 0) {
		do {
			if (((BfmeAptValue006DCD20 *)node)->isUndefined()) {
				if (((EAStringC *)name)->IsEqualTo((EAStringC *)&node->m_nameHandle)) {
					*ppItem = node;
					*ppPrev = namePrevious;
					return;
				}
			}
			namePrevious = node;
			node = node->m_next;
		} while (node != 0);
	}

	node = self->m_root->m_next;
	BfmeQueryNode1279 *keyPrevious = self->m_root;
	while (node != 0 && ((node->m_key << 15) >> 15) < nDepth) {
		keyPrevious = node;
		node = node->m_next;
	}
	if (node != 0 && ((node->m_key << 15) >> 15) == nDepth)
		*ppItem = node;
	else
		*ppItem = 0;
	*ppPrev = keyPrevious;
}

// ?bfmeUnlinkNestedBE@@YAPAVBfmeNestedBE@@PAV1@@Z, retail 0x006F7090
// (75 bytes). Unlinks a nested bounding-entry node from its pPrev/pNext
// list and returns it; the three asserts name this TU's path and prove
// the pItem/pPrev/pNext identifiers.
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *pItem)
{
	if (pItem == 0) {
		g_bfmeAptAssertAtE17734("pItem != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x221);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (pItem->pPrev != 0) {
		if (pItem->pPrev->pNext != pItem) {
			g_bfmeAptAssertAtE17734("pItem->pPrev->pNext == pItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x225);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		pItem->pPrev->pNext = pItem->pNext;
	}
	if (pItem->pNext != 0) {
		if (pItem->pNext->pPrev != pItem) {
			g_bfmeAptAssertAtE17734("pItem->pNext->pPrev == pItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x22A);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		pItem->pNext->pPrev = pItem->pPrev;
	}
	pItem->pPrev = 0;
	pItem->pNext = 0;
	return pItem;
}

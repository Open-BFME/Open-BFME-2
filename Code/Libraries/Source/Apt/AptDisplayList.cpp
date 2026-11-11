// cl: /DNDEBUG /MD
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

#include "BfmeAptValue006DCD20.h"

#include "EAStringC.h"

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
	BfmeNestedBE *rva006F7D50(int nDepth);
	int rva006F6CE0() const;

private:
	BfmeQueryNode1279 *m_root;
};

// Query provider rehomed to AptMovieFrameControls.cpp; public symbol preserved.

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

// ?rva006F6AC0@Rva006F6AC0@@QAEXHPAPAX0@Z, retail 0x006F6AC0 (188 bytes).
// Depth-ordered AptDisplayList lookup in the same TU: asserts ppPrev/ppItem/
// nDepth at lines 0xB0-0xB2, then walks m_root->m_next (next at +8) while
// node depth at +0x10 is below nDepth, returning the equal node or 0 with
// its predecessor. Mirrors the key-walk tail of bfmeQuery1279 above.
struct AptDepthNode006F6AC0
{
	char m_pad00[8];
	AptDepthNode006F6AC0 *m_next;
	char m_pad0C[4];
	int m_depth;
};

class Rva006F6AC0
{
public:
	void rva006F6AC0(int nDepth, void **ppPrev, void **ppItem);

private:
	AptDepthNode006F6AC0 *m_root;
};

void Rva006F6AC0::rva006F6AC0(int nDepth, void **ppPrev, void **ppItem)
{
	if (ppPrev == 0) {
		g_bfmeAptAssertAtE17734("ppPrev", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0xB0);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (ppItem == 0) {
		g_bfmeAptAssertAtE17734("ppItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0xB1);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!(nDepth >= 0)) {
		g_bfmeAptAssertAtE17734("nDepth >= 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0xB2);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	AptDepthNode006F6AC0 *prev = m_root;
	AptDepthNode006F6AC0 *node = m_root->m_next;
	while (node != 0 && node->m_depth < nDepth) {
		prev = node;
		node = node->m_next;
	}
	if (node != 0 && node->m_depth == nDepth)
		*ppItem = node;
	else
		*ppItem = 0;
	*ppPrev = prev;
}

// ?DisplayListItem@AptDisplayListState@@QAEXPAX@Z, retail 0x006F6D30 (45 bytes).
// GC-mark walk over the m_next chain (next at +0x54, same as BfmeQueryNode1279):
// get/setGCMark(true)/virtual 0x34 triple per node. Takes one ignored dword
// (ret 4) like the AptNativeHashMark precedent.
class Rva006DBB40ShrAndField
{
public:
	bool get() const;
};

#include "AptValue.h"
#include "AptCIHClass.h"

class AptDisplayListState
{
public:
	void DisplayListItem(void *arg);

private:
	BfmeQueryNode1279 *m_root;
};

void AptDisplayListState::DisplayListItem(void *arg)
{
	(void)arg;
	BfmeQueryNode1279 *node = m_root;
	if (node == 0)
		return;
	do {
		if (!((const Rva006DBB40ShrAndField *)node)->get()) {
			((AptValue *)node)->setGCMark(true);
			((AptValue *)node)->RegisterReferences();
		}
		node = node->m_next;
	} while (node != 0);
}

// ?rva006F6D00@Rva006F6D00List@@QAEPAXH@Z, retail 0x006F6D00 (33 bytes).
// Ghidra-unlisted n-th node of the singly linked list headed at +0 and
// chained through each node's +0x54 link; null when the list runs out.
// Owning class unrecovered: address-derived view.
struct Rva006F6D00Node
{
    char pad[0x54];
    Rva006F6D00Node *next;
};
class Rva006F6D00List
{
public:
    void *rva006F6D00(int n);
private:
    Rva006F6D00Node *m_head;
};
void *Rva006F6D00List::rva006F6D00(int n)
{
    for (Rva006F6D00Node *p = m_head; p != 0; p = p->next)
    {
        if (n == 0)
            return p;
        --n;
    }
    return 0;
}

// ?rva006F7D50@BfmeQuery1279@@QAEPAVBfmeNestedBE@@H@Z, retail 0x006F7D50
// (39 bytes, RET 4): query the item at a depth (no name) on the same
// receiver, then unlink it through bfmeUnlinkNestedBE and return it; retail
// keeps the found item in the depth argument's home. Address name.
BfmeNestedBE *BfmeQuery1279::rva006F7D50(int nDepth)
{
	void *pPrev;
	void *pItem;
	bfmeQuery1279(nDepth, 0, &pPrev, &pItem);
	return bfmeUnlinkNestedBE((BfmeNestedBE *)pItem);
}

// ?rva006F8220@Rva006F8220List@@QAEXPAURva006F8220CIH@@@Z, retail 0x006F8220
// (346 bytes, RET 4): recursive walk over a display list's items (from the
// query root's +0x54 link) under their parent instance. Each item must name
// that parent (assert "0", line 0x761); a named, defined item under a parent
// is searched for in the parent sprite instance's native hash (+0x4C ->
// +0x10) by value or by name, after the line 0x767 isSpriteInstBase assert;
// a sprite item (AptCIH.h's inline isSpriteInstBase: defined and type 0xD or
// 0x12, its 0x7D assert re-testing it) recurses into its own display list
// (+0x4C instance +0x24). Target facts: offsets, strings, call order. Class
// and member names are address-derived.
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"

#include "Rva006CFCD0.h"

class AsciiString;
#include "AptNativeHash.h"

struct AptNativeHash::Entry
{
	EAStringC *keyView() { return (EAStringC *)this; }
	void *m_key;
	BfmeAptValue006DCD20 *m_value;
};

struct Rva006F8220CIH;
class Rva006F8220List;

struct Rva006F8220Inst
{
	char m_pad00[0x10];
	AptNativeHash *m_hash;
	char m_pad14[0x24 - 0x14];
	void *m_displayList;
};

struct Rva006F8220Root
{
	char m_pad00[0x54];
	Rva006F8220CIH *m_next;
};

struct Rva006F8220Query
{
	Rva006F8220Root *m_root;
};

struct Rva006F8220CIH
{
	char m_pad00[8];
	void *m_name;
	char m_pad0C[0x48 - 0x0C];
	Rva006F8220CIH *m_parent;
	Rva006F8220Inst *m_inst;
	char m_pad50[4];
	Rva006F8220CIH *m_next;

	const BfmeAptValue006DCD20 *value() const { return (const BfmeAptValue006DCD20 *)this; }
	EAStringC *name() { return (EAStringC *)&m_name; }
	bool isSpriteInstBase() const
	{
		return !value()->isUndefined() &&
			(((const Rva006DBB30SarDwordField *)this)->get() == 0xD ||
			 ((const Rva006DBB30SarDwordField *)this)->get() == 0x12);
	}
	Rva006F8220List *displayList()
	{
		if (!isSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return (Rva006F8220List *)&m_inst->m_displayList;
	}
};

class Rva006F8220List
{
public:
	void rva006F8220(Rva006F8220CIH *pParent);

private:
	Rva006F8220Query *m_query;
};

void Rva006F8220List::rva006F8220(Rva006F8220CIH *pParent)
{
	for (Rva006F8220CIH *cih = m_query->m_root->m_next; cih; cih = cih->m_next) {
		if (cih->m_parent != pParent) {
			g_bfmeAptAssertAtE17734("0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x761);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		if (pParent && !cih->name()->IsEmpty() && !cih->value()->isUndefined()) {
			Rva006F8220CIH *pParentInst = cih->m_parent;
			if (!((const Rva006CFCD0 *)pParentInst)->isSpriteInstBase()) {
				g_bfmeAptAssertAtE17734("pParentInst->isSpriteInstBase()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x767);
				if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
			}
			for (AptNativeHash::Entry *e = (AptNativeHash::Entry *)pParentInst->m_inst->m_hash->rva0070AA40(); e; e = pParentInst->m_inst->m_hash->rva0070AAA0(e)) {
				BfmeAptValue006DCD20 *v = e->m_value;
				if (v->isCIH(false)) {
					if (v == cih->value())
						break;
					if (e->keyView()->IsEqualTo(cih->name()))
						break;
				}
			}
		}
		if (cih->isSpriteInstBase())
			cih->displayList()->rva006F8220(cih);
	}
}

// ?rva006F6CE0@BfmeQuery1279@@QBEHXZ, retail 0x006F6CE0 (17 bytes): count
// the nodes on the root's +0x54 chain. Skeleton twin of Open-BFME-1's
// Rva008BD1B0ChainCount.cpp (BFME 1 0x008BD1B0); address name.
int BfmeQuery1279::rva006F6CE0() const
{
	int count = 0;
	for (BfmeQueryNode1279 *node = m_root; node; node = node->m_next)
		++count;
	return count;
}

// Native 0x006F8B70..0x006F8D61, RET0x30. WB 0x017928B0 identifies
// AptDisplayList.cpp and the submit/assert/hash-walk structure. Retail stores
// the transform at CIH+0x24 and color at +0x0C (WB's revision uses +4).
// Keep the live item distinct from the address-taken output parameter: the
// instantiate call writes item, while subsequent calls retain live in EBX.
// A textual volatile read pins that initial copy; the outer positive guard
// preserves retail's common null-return tail. The predicate's caller tests
// AL even though its established ledger spelling returns int.

class Rva006F7E00
{
public:
    void rva006F7E00(AptCIH *, int);
};

class Rva006DBB60ShrNAndField
{
public:
    bool get() const;
};

class AsciiString;
class AptNativeHashRoot
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void *v03();
};

EAStringC *Rva0070B4F0GetString(int index);

struct AptActionInterpreter
{
public:
    bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int, int, int);
};
extern AptActionInterpreter g_aptDateInterpreter;

// Rowed at 0x006F85E0 (Rva006F6A50Cluster.cpp) under its real signature;
// the submit forwards its raw words through unchanged.
struct AptCharacter;
#include "AptDisplayList.h"

#include "BfmeSubmitter1283.h"

struct BfmeSubmitCopy8
{
    int m_words[8];
};
struct BfmeSubmitCopy6
{
    int m_words[6];
};

void *BfmeSubmitter1283::bfmeSubmit1283(AptCIH *item, int a1, int pCharacter, int a3, int a4,
    int a5, int a6, float *copy0, int copy1, int v9, int v10, int hash)
{
    AptCIH *live = *(AptCIH * volatile *)&item;
    int created = 0;
    AptDisplayList *list = (AptDisplayList *)this;
    if (pCharacter == 0 && live == 0)
    {
        g_bfmeAptAssertAtE17734("pCharacter || pItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x37F);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (live == 0) {
        list->instantiateCharacter(a1, (AptCharacter *)pCharacter, (EAStringC *)a3, (AptCIH *)a4, a5, a6, &item, &created);
        live = item;
    }
    if (live != 0)
    {
        if (copy0 != 0)
            *(BfmeSubmitCopy8 *)((char *)live + 0x24) = *(BfmeSubmitCopy8 *)copy0;
        if (copy1 != 0)
            *(BfmeSubmitCopy6 *)((char *)live + 0x0C) = *(BfmeSubmitCopy6 *)copy1;
        if (v9 != 0)
        {
            if (!((Rva006CFCD0 *)live)->isSpriteInstBase())
            {
                g_bfmeAptAssertAtE17734("pItem->isSpriteInstBase()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x391);
                if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
            }
            if (!((Rva006CFCD0 *)live)->isSpriteInstBase())
            {
                g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
                if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
            }
            *(int *)((char *)(*(void **)((char *)live + 0x4C)) + 0x20) = v9;
        }
        if ((unsigned char)((BfmeAptValue006DCD20 *)live)->rva006E0350())
        {
            void *field = live->rva006E1020();
            *(int *)((char *)field + 0x18) = v10;
        }
        if (created)
            ((Rva006F7E00 *)list)->rva006F7E00((AptCIH *)live, 1);
        if (((Rva006CFCD0 *)live)->isSpriteInstBase())
        {
            if (hash != 0)
            {
                if (((Rva006DBB60ShrNAndField *)hash)->get())
                {
                    void *root = ((AptNativeHashRoot *)hash)->v03();
                    AptNativeHash *map = (AptNativeHash *)root;
                    void *entry = map->rva0070AA40();
                    while (entry != 0)
                    {
                        EAStringC *name = (EAStringC *)entry;
                        if (!name->IsEqualTo(Rva0070B4F0GetString(0)) &&
                            !name->IsEqualTo(Rva0070B4F0GetString(0x78)))
                            g_aptDateInterpreter.setVariable((AptValue *)live, 0, name,
                                *(AptValue **)((char *)entry + 4), 1, 1, 0);
                        entry = map->rva0070AAA0((AptNativeHash::Entry *)entry);
                    }
                }
            }
            live->rva006E2EE0();
        }
    }
    return live;
}

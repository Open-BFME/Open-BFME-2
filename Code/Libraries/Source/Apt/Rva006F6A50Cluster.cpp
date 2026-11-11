// cl: /DNDEBUG /MD /EHsc
//
// Apt display-list / AptCIH neighbourhood cluster at 0x006F6A50.  Class
// layouts come from the recovered BFME2 siblings in this directory
// (Rva006E1DD0Cluster.cpp AptCIH layout, Rva006F8060Assert.cpp head holder)
// and the BFME1 donor tree (AptDisplayList.cpp / AptCIH.cpp).  Identity of the
// node class is AptCIH: the 0x006E24E0/0x006E2560/0x006E2D60 callees assert
// through AptCIH.h.  Names stay address-derived until a caller proves more.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"

#include "EAStringC.h"
struct AptCharacter;struct AptCharacterInst;
class AptRenderingContext;
#include "AptValue.h"
#include "AptCIHClass.h"
#include "BfmeAptValue006DCD20.h"
// AptCIH::field58 packs the signed 17-bit display depth (0x006F72F0), the
// 14-bit creation frame and a high flag; this view reads and writes them.
struct AptCIHKeyBits {int depth:17;int created:14;unsigned high:1;};
static __forceinline AptCIHKeyBits &cihKeyBits(AptCIH *cih){return *(AptCIHKeyBits *)&cih->field58;}

// ?rva006F7AC0@Rva006F7AC0List@@QAE_NXZ @0x006F7AC0 33B
class Rva006F7AC0List
{
public:
	bool rva006F7AC0();
	void rva006F7AF0(int arg);

	AptCIH *m_head;
};

bool Rva006F7AC0List::rva006F7AC0()
{
	AptCIH *node = m_head;
	if (node == 0)
		return false;
	do
	{
		if (node->rva006E24E0())
			return true;
		node = node->field54;
	} while (node != 0);
	return false;
}

// ?rva006F7AF0@Rva006F7AC0List@@QAEXH@Z @0x006F7AF0 36B
void Rva006F7AC0List::rva006F7AF0(int arg)
{
	AptCIH *node = m_head;
	if (node == 0)
		return;
	do
	{
		node->rva006E2560(arg);
		node = node->field54;
	} while (node != 0);
}

// ---------------------------------------------------------------------------
// AptDisplayList.cpp bodies: BfmeQuery1279 root holder and the AptDisplayList
// owner that allocates it.  The BFME1 donor names both classes.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../GameEngine/Include/Common/Rva006DB270.h"

#include "../../../GameEngine/Include/Common/Rva006DB160.h"

class Rva006D2A60
{
public:
	void *allocBlock(int size);
	void freeBlock(void *block, int size);
};

extern Rva006DB270 *g_pChainBlockAllocator;   // VA 0x00E176E8
extern Rva006D2A60 *g_pChainBlockAllocatorF4; // VA 0x00E176F4

// The sentinel/display-list node.  Its out-of-line constructor is the rowed
// ??0Rva006CBDE0@@QAE@HPAXPAVAptValue@@@Z; the fields below are the ones this
// cluster touches (prev +0x50, next +0x54, key/GC word +0x58).
void Rva006F12F0Free(void*,int);
class Rva006CBDE0
{
public:
	Rva006CBDE0(int type, void *p1, AptValue *p2);
	// Native failed-construction cleanup uses the same F4 pool as allocation.
	static void operator delete(void*p,unsigned n){g_pChainBlockAllocatorF4->freeBlock(p,(int)n);}

	static void *operator new(unsigned int size)
	{
		return g_pChainBlockAllocatorF4->allocBlock((int)size);
	}

	char m_storage[0x60];
};

class BfmeQuery1279
{
public:
	BfmeQuery1279();
	~BfmeQuery1279();

	void bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem);
	void rva006F6FB0(int key, AptCIH *pNewItem);
	AptCIH *rva006F6ED0(int key,int type,void*pData);
	void rva006F7030(int key, AptCIH *pNewItem, AptCIH *pPrev, AptCIH *pItemAtDepth);
	AptCIH *insert(AptCIH *pOldItem, AptCIH *pNewItem);

	static void *operator new(unsigned int size)
	{
		return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)size);
	}

	static void operator delete(void *block, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(block, (int)size);
	}

	AptCIH *m_root;
};

// ??0BfmeQuery1279@@QAE@XZ @0x006F7B20 153B: construct the root sentinel from
// the 0xE176F4 pool, mark it undefined with one GC root, clear its key link.
BfmeQuery1279::BfmeQuery1279()
{
	m_root = (AptCIH *)new Rva006CBDE0(0x2e, (void *)0xbaadf00d, 0);
	m_root->setIsDefined(false);
	((BfmeAptValue006DCD20 *)m_root)->setGCRootCount(1);
	m_root->AddRef();
	m_root->field58 |= 0x1ffff;
	m_root->field54 = 0;
	m_root->field50 = 0;
}

// ?BfmeQuery1279::~BfmeQuery1279 @0x006F7BC0 65B: assert the root sentinel is
// undefined, clear its +0x4C then tail-call its second virtual.
BfmeQuery1279::~BfmeQuery1279()
{
	if (!((const BfmeAptValue006DCD20 *)m_root)->isUndefined()) {
		g_bfmeAptAssertAtE17734("pHead->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x8A4);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	m_root->field4C = 0;
	m_root->ForceDelete();
}

class AptDisplayList
{
public:
	AptDisplayList();
	~AptDisplayList();
	void clear(bool flag);
	void rva006F8190();
	void rva006F76B0();
	void rva006F79B0(void *arg1, void *arg2);
	void rva006F7A30();
	void rva006F7AB0(int, void *);
 void bfmeProcess1279(void*);
 void instantiateCharacter(int,AptCharacter*,EAStringC*,AptCIH*,int,int,AptCIH**,int*);

	BfmeQuery1279 *m_query;
};

// ??0AptDisplayList@@QAE@XZ @0x006F7FF0 103B: allocate the 4-byte BfmeQuery1279
// through the pool and construct it; the EH frame is the throwing new.
AptDisplayList::AptDisplayList() : m_query(new BfmeQuery1279())
{
}

// ??1AptDisplayList@@QAE@XZ @0x006F84F0 93B
AptDisplayList::~AptDisplayList()
{
	clear(false);
	delete m_query;
}

// ?rva006F8190@AptDisplayList@@QAEXXZ @0x006F8190 142B
void AptDisplayList::rva006F8190()
{
	if (m_query == 0) {
		g_bfmeAptAssertAtE17734("pState", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x602);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	clear(false);
	delete m_query;
	m_query = 0;
}

// ---------------------------------------------------------------------------
// AptCIH descriptor wrapper at 0x006F6A50: holds a descriptor pointer and builds
// a 0x1C interpretation of it only when the descriptor reports kind 3.

class Rva006F69D0
{
public:
	Rva006F69D0(void *descriptor, int second, int fourth) throw();

	char m_pad[0x1c];

	static void *operator new(unsigned int size)
	{
		return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)size);
	}
};

class Rva006F6A50
{
public:
	Rva006F6A50(void *descriptor, int second, int third, int fourth);

	void *m_00;
	Rva006F69D0 *m_04;
	int m_08;
	int m_0c;
	int m_10;
};

// ??0Rva006F6A50@@QAE@PAXHHH@Z @0x006F6A50 101B
Rva006F6A50::Rva006F6A50(void *descriptor, int second, int third, int fourth)
{
	m_00 = descriptor;
	m_10 = third;
	if (descriptor != 0 && *(int *)descriptor == 3)
		m_04 = new Rva006F69D0(descriptor, second, fourth);
	else
		m_04 = 0;
	m_08 = 0;
	m_0c = 0;
}

// ---------------------------------------------------------------------------
// Rva006F8D70 (0x20 bytes) ctor: vtable + a AptDisplayList sub-object at +0x1C
// and an AptNativeHash at +0x10.  Its deleting dtor (0x006F8D70), complete dtor
// (0x006F8DA0) and the vtable RVA 0x008ED398 already exist in the ledger.

extern const void *const g_00CED398[];

class AptNativeHash
{
public:
	AptNativeHash(int size);
 void Set(const EAStringC*const,AptValue*const);
	void Unset(const EAStringC *const);

	static void *operator new(unsigned int size)
	{
		return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)size);
	}
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocator->freeBlock(p, size); }

	char m_pad[0x14];
};

// The base's inlined ctor writes +0x14, +0x04, +0x0C and +0x10; its vtable store
// is dead and dropped, so the derived vtable store below is the only one left.
class Rva006F8460
{
public:
	Rva006F8460()
	{
		m_14 = 0;
		m_04 = -1;
		m_0c = 0;
		m_10 = 0;
	}

	virtual ~Rva006F8460();
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocator->freeBlock(p, size); }

	int m_04;
	int m_pad08;
	int m_0c;
	AptNativeHash *m_10;
	unsigned char m_14;
	char m_pad15[3];
};

class Rva006F8D70 : public Rva006F8460
{
public:
	Rva006F8D70();
 static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
	virtual ~Rva006F8D70();

	char m_pad18[4];
	AptDisplayList m_holder;
public:
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocator->freeBlock(p, size); }
};

// ??0Rva006F8D70@@QAE@XZ @0x006F8550 134B
Rva006F8D70::Rva006F8D70()
{
	m_10 = new AptNativeHash(4);
}

// ---------------------------------------------------------------------------
// AptDisplayList list-link helper at 0x006F6D60: asserts pNewItem's data then
// splices pNewItem in after pOldItem.  The inline type-14 predicate carries the
// AptCIH.h:0xB5 "this" assertion that the byte stream shows.

static __forceinline int rva006F6D60IsType14(const AptCIH *pNewItem)
{
	if (pNewItem == 0) {
		g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (((const Rva006DBB30SarDwordField *)pNewItem)->get() == 0xe) {
		if (!((const BfmeAptValue006DCD20 *)pNewItem)->isUndefined())
			return 1;
	}
	return 0;
}

// ?insert@@YGPAVAptCIH@@PAV1@0@Z @0x006F6D60 159B
AptCIH *BfmeQuery1279::insert(AptCIH *pOldItem, AptCIH *pNewItem)
{
	if (pNewItem->rva006CFCD0() || rva006F6D60IsType14(pNewItem)) {
		if (pNewItem->field4C == 0) {
			g_bfmeAptAssertAtE17734("pNewItem->pData != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x1D8);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
	}
	pNewItem->field54 = pOldItem->field54;
	pNewItem->field50 = pOldItem;
	pNewItem->AddRef();
	if (pNewItem->field54 != 0)
		pNewItem->field54->field50 = pNewItem;
	pNewItem->field50->field54 = pNewItem;
	return pNewItem;
}

// ?rva006F6FB0@BfmeQuery1279@@QAEXHPAVAptCIH@@@Z @0x006F6FB0 122B: query the
// key, assert the found old item is undefined, splice the new item after the
// query's previous node and set its 17-bit key.
void BfmeQuery1279::rva006F6FB0(int key, AptCIH *pNewItem)
{
	AptCIH *pOldItem;
	void *pPrev;
	bfmeQuery1279(key, 0, &pPrev, (void **)&pOldItem);
	if (pOldItem != 0 && !((const BfmeAptValue006DCD20 *)pOldItem)->isUndefined()) {
		g_bfmeAptAssertAtE17734("pOldItem == NULL || pOldItem->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x208);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	AptCIH *node = insert((AptCIH *)pPrev, pNewItem);
	node->field58 = node->field58 ^ ((node->field58 ^ (unsigned int)key) & 0x1FFFFu);
}

// ---------------------------------------------------------------------------
// AptDisplayList child-list walk at 0x006F79B0: starts at m_query->m_root->next
// and for each defined node that is not kind 19 with a negative pData->+4 calls
// AptCIH::rva006E1C40 with the walk's two arguments.  The kind-19 inline
// predicate carries the AptCIH.h:0xD8 "this" assertion.

static __forceinline int rva006F79B0IsType19(const AptCIH *pNode)
{
	if (pNode == 0) {
		g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xD8);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (((const Rva006DBB30SarDwordField *)pNode)->get() == 0x13) {
		if (!((const BfmeAptValue006DCD20 *)pNode)->isUndefined())
			return 1;
	}
	return 0;
}

// ?rva006F79B0@AptDisplayList@@QAEXPAX0@Z @0x006F79B0 126B
void AptDisplayList::rva006F79B0(void *arg1, void *arg2)
{
	AptCIH *node = (AptCIH *)m_query->m_root->field54;
	while (node != 0) {
		if (!((const BfmeAptValue006DCD20 *)node)->isUndefined()) {
			if (!rva006F79B0IsType19(node)) {
				if (*(int *)((char *)node->field4C + 4) < 0)
					node->rva006E1C40((AptRenderingContext *)arg1, (int)arg2);
			}
		}
		node = node->field54;
	}
}

// ?rva006F7A30@AptDisplayList@@QAEXXZ @0x006F7A30 127B: same child walk;
// rebuilds (0x006E2D60) defined kind-13/18 nodes and kind-14 nodes.
void AptDisplayList::rva006F7A30()
{
	AptCIH *node = (AptCIH *)m_query->m_root->field54;
	for (;;) {
		if (node == 0)
			break;
		// An inlined AptCIH.h "this" assertion the optimizer proves dead; its
		// inline-asm break survives as retail's 'jmp $+3; int3' at 0x006F7A3C
		// (the __debugbreak spelling leaves nothing). Line unknown: the dead
		// report's strings are not emitted.
		if (node == 0) {
			g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				{__asm int 3}
		}
		if (!((const BfmeAptValue006DCD20 *)node)->isUndefined() &&
			(((const Rva006DBB30SarDwordField *)node)->get() == 0xd ||
			 ((const Rva006DBB30SarDwordField *)node)->get() == 0x12)) {
			node->rva006E2D60();
		} else if (rva006F6D60IsType14(node)) {
			node->rva006E2D60();
		}
		node = node->field54;
	}
}

// ?rva006F7AB0@AptDisplayList@@QAEXHPAX@Z @0x006F7AB0 13B
void AptDisplayList::rva006F7AB0(int, void *item)
{
	bfmeProcess1279(item);
}


// Target 0x006F7330 is a 112-byte cdecl callback. Its retail bytes test the
// rowed AptCIH predicate before changing render state, push the colour and
// vertex stacks, pass this+0x24 to the rowed 1209 helper, conditionally pass
// this+0x48 to the address-derived 0x006E1260 helper, and then call the
// address-derived 0x006E15C0 renderer with (context, 0, flags). The matching
// WorldBuilder body labels that renderer AptCIH::render and uses +0x28/+0x4C;
// this callback's target offsets and cdecl argument order follow game.dat.
// The callback's original source name remains unproven, so it stays RVA-based.
class AptRenderingContext
{
public:
	void pushColourTransform();
	void pushVertexMatrix();
	void popVertexMatrix();
	void popColourTransform();
};

struct BfmeS1209;
class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *value);
};

class BfmeThingDXH
{
public:
	void bfmeGoDXH(void *value);
};

class Rva006E1260
{
public:
	void call(void *value);
};

#include "Rva006E15C0.h"

void __cdecl rva006F7330(AptRenderingContext *context, AptCIH *item, int flags)
{
	if (!((const AptCIH *)item)->rva006E24E0())
		return;

	context->pushColourTransform();
	((BfmeA1209 *)context)->bfmeOp1209((const BfmeS1209 *)((const char *)item + 0x24));
	context->pushVertexMatrix();
	if ((char)((const BfmeAptValue006DCD20 *)item)->rva006E02B0())
		((Rva006E1260 *)item)->call(*(void **)((char *)item + 0x48));
	((BfmeThingDXH *)context)->bfmeGoDXH((char *)item + 0x0c);
	((Rva006E15C0 *)item)->call(context, 0, flags);
	context->popVertexMatrix();
	context->popColourTransform();
}

class Rva006F7540
{
public:
	Rva006F7540() { m_nElements = 0; }
	~Rva006F7540()
	{
		if (m_nElements != 0) {
			g_bfmeAptAssertAtE17734("nElements == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x537);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
	}

	void *m_items[32];
	int m_nElements;
};

// ?rva006F76B0@AptDisplayList@@QAEXXZ @0x006F76B0 100B
void AptDisplayList::rva006F76B0()
{
	AptCIH *node = (AptCIH *)m_query->m_root->field54;
	Rva006F7540 array;
	while (node != 0) {
		((BfmeAptValue006DCD20 *)node)->rva006E1540();
		node = node->field54;
	}
}

// ?clear@AptDisplayList@@QAEX_N@Z @0x006F80C0 202B chain from AptNativeHash::Unset.
// Walks m_query list via +0x54 saving next; v0 then skip undefined; provider
// slot 3 lookup compare erase via 0x70B380/AptNativeHash::Unset; unlink+finish; flag
// clears GC root + AptCIH 1; release-vector GC check; v1 then next.
// Evidence: chain lane; callee 0x0070B2C0 just landed; LINK pin name.

struct BfmeKey1279
{
	EAStringC m_str;
};
#include "../../../GameEngine/Include/Common/Rva0070B380.h"
class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *item);
class BfmeProvider1279
{
public:
	virtual void reserved0() = 0;
	virtual void reserved1() = 0;
	virtual void reserved2() = 0;
	virtual AptNativeHash *bfmeGetLookup1279() = 0;
};
class BfmeNode1279 : public BfmeAptValue006DCD20
{
public:
	void bfmeFinish1279();
	BfmeKey1279 m_key;
	char m_pad0C[0x48 - 0x0C];
	BfmeProvider1279 *m_provider;
	char m_pad4C[0x54 - 0x4C];
	BfmeNode1279 *m_next;
};
class CullableClass;
class CullSystemClass
{
protected:
	CullableClass *Get_First_Collected_Object_Internal();
	friend class AptDisplayList;
};
#include "AptValueVector.h"
extern AptValueVector *g_releaseVectorAtE17710;
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
void AptDisplayList::clear(bool flag)
{
	BfmeQuery1279 *query = m_query;
	if (query == 0)
		return;
	BfmeNode1279 *cur = (BfmeNode1279 *)query->m_root->field54;
	if (cur == 0)
		return;
	do {
		BfmeNode1279 *next = cur->m_next;
		cur->AddRef();
		if (!cur->isUndefined()) {
			BfmeProvider1279 *prov = cur->m_provider;
			if (prov != 0) {
				AptNativeHash *lookup = prov->bfmeGetLookup1279();
				EAStringC &skey = (EAStringC &)cur->m_key;
				if (!skey.IsEmpty()) {
					if (lookup != 0) {
						void *found = ((Rva0070B380 *)lookup)->lookup(skey);
						if (found == cur)
							lookup->Unset(&skey);
					}
				}
			}
			bfmeUnlinkNestedBE((BfmeNestedBE *)cur);
			cur->bfmeFinish1279();
		}
		if (flag) {
			cur->setGCRootCount(0);
			((AptCIH *)cur)->ClearCIH(1);
		}
		AptValueVector *vec = g_releaseVectorAtE17710;
		CullableClass *collected = ((CullSystemClass *)vec)->Get_First_Collected_Object_Internal();
		if (collected != 0) {
			if (*reinterpret_cast<void **>(&g_aptDateInterpreter) == 0)
				g_releaseVectorAtE17710->ReleaseValues();
		}
		cur->Release();
		cur = next;
	} while (cur != 0);
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?rva006F7AC0@Rva006F7AC0@@QBE_NXZ=?rva006F7AC0@Rva006F7AC0List@@QAE_NXZ")

// Native6F7030..6F7090 RET16. Same item assertion and 17-bit key write
// as rva006F6FB0; this sibling receives the already-found previous/depth
// items instead of querying them. Original method name remains unknown.
void BfmeQuery1279::rva006F7030(int key, AptCIH *pNewItem, AptCIH *pPrev,
                              AptCIH *pItemAtDepth)
{
    if (pItemAtDepth != 0 &&
        !((const BfmeAptValue006DCD20 *)pItemAtDepth)->isUndefined()) {
        g_bfmeAptAssertAtE17734("pItemAtDepth == NULL || pItemAtDepth->isUndefined()",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x211);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    AptCIH *node = insert(pPrev, pNewItem);
    node->field58 = node->field58 ^ ((node->field58 ^ (unsigned int)key) & 0x1FFFFu);
}

// Native6F6ED0..6F6FAD221B: allocate/construct a60B CIH, query the
// old depth entry, set its17-bit key and link it. Existing query297B is
// visible but noinline, allowing its two nonescaping outputs to reuse dead
// argument homes exactly. Native unwind7AA020 also proves sized pool
// cleanup Rva006F12F0Free for this60B new expression. Its inline COMDAT
// is identical to the provider
// retained in AptMovieFrameControls.cpp for the other matched consumer.
struct BfmeQueryNode1279
{
	void *m_bfme00;
	void *m_bfme04;
	void *m_nameHandle;
	char m_pad0C[0x54 - 0x0C];
	BfmeQueryNode1279 *m_next;
	int m_key;
};

inline __declspec(noinline) void BfmeQuery1279::bfmeQuery1279(int nDepth, int name, void **ppPrev, void **ppItem)
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
	BfmeQueryNode1279 *node = ((BfmeQueryNode1279*)self->m_root)->m_next;
	BfmeQueryNode1279 *namePrevious = (BfmeQueryNode1279*)self->m_root;

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

	node = ((BfmeQueryNode1279*)self->m_root)->m_next;
	BfmeQueryNode1279 *keyPrevious = (BfmeQueryNode1279*)self->m_root;
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

AptCIH *BfmeQuery1279::rva006F6ED0(int key, int type, void *pData)
{
	AptCIH *pOldItem;
	void *pPrev;
	AptCIH *node = (AptCIH *)new Rva006CBDE0(type, pData, 0);

	bfmeQuery1279(key, 0, &pPrev, (void **)&pOldItem);
	if (pOldItem != 0 && !((const BfmeAptValue006DCD20 *)pOldItem)->isUndefined()) {
		g_bfmeAptAssertAtE17734("pItem == NULL || pItem->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x1FB);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	node->field58 = node->field58 ^ ((node->field58 ^ (unsigned int)key) & 0x1FFFFu);
	node->field4C = pData;
	return insert((AptCIH *)pPrev, node);
}

// ?instantiateCharacter@AptDisplayList@@QAEXHPAUAptCharacter@@PAVEAStringC@@PAVAptCIH@@HHPAPAV4@PAH@Z
// @0x006F85E0 1417B. Target evidence: the in-body asserts name this TU
// (pParent / pState at 0x254-0x255, NOT_REACHED at 0x2B9, the new-movie-clip
// pool bound at 0x2F3, pCurCIH at 0x30B) and AptCIH.h's isSpriteInstBase()
// accessor (line 0x7D). Queries the depth slot (0x006F6BB0), replaces or
// revives the existing CIH, instantiates the inst by character type
// (5/4/2 pool-new with sized-delete cleanup, states 0..2 of the EH frame;
// 10/1/8 without cleanup), links it (0x006F6ED0 / 0x006F6FB0), names and
// hashes it, queues movie clips in the pool or initialises text, then
// binds parent, character and value. Codegen evidence: the 10/1/8 ctors
// are this TU's own out-of-line bodies (0x006F7D80 / 0x006F7DA0, in the
// TU's contiguous range), which is why their new-expressions carry no EH
// state; the type-2 inst copies nine character fields; the type-5 flag
// word is read, or-ed and written back (volatile), and the assert block
// before the pool append reloads the pool pointer after its int3 join.
// Field names past the asserted ones are structural, not target names.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define POOL_NEW static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
#define POOL_DELETE static void operator delete(void*p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}
#define CHECK(c,s,l) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
struct AptCharacter {int type;int value04,value08,value0c,value10,value14;int value18,value1c,value20,value24;char unknown28[0x34-0x28];const char*defaultText;const char*variable;};
struct AptCharacterInst {const void*vtable;int value;int frame;AptCharacter*character;AptNativeHash*hash;int word14,word18;volatile unsigned word1c;int word20,word24;char unknown28[0x3c-0x28];int word3c;char unknown40[0x50-0x40];int word50,word54,word58,word5c;int word60,word64;char unknown68[0x78-0x68];};
class Rva006ED150 {public:Rva006ED150();virtual ~Rva006ED150();char rest[0x30-4];};
class Rva006F7140Derived:public Rva006ED150 {public:POOL_NEW POOL_DELETE __declspec(dllimport) __forceinline Rva006F7140Derived(){} };
class Rva006ED2A0 {public:Rva006ED2A0();char storage[0x78];POOL_NEW POOL_DELETE};

// ??0Rva006F7D80@@QAE@XZ @0x006F7D80 27B and ??0Rva006F7DA0@@QAE@XZ
// @0x006F7DA0 27B: store the vtable (0x008ED358 / 0x008ED364), -1 at +4
// and zeros at +0xC +0x10 +0x14. Sole callers are the type-10/1 and type-8
// paths of instantiateCharacter (pool sizes 0x18 and 0x1C); retail keeps
// them out of line.
// The retail table at RVA 0x008ED358: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?ReportError@@YAXPADH@Z")();
void __identifier("??_GRva006F8460@@UAEPAXI@Z")();
void __identifier("?go@Rva008A2C60@@QAEXXZ")();
}
extern const void *const g_00CED358[3] = {
	(const void *)&__identifier("?ReportError@@YAXPADH@Z"), // slot 0 0x0069E440
	(const void *)&__identifier("??_GRva006F8460@@UAEPAXI@Z"), // slot 1 0x006F8490
	(const void *)&__identifier("?go@Rva008A2C60@@QAEXXZ"), // slot 2 0x006E5FD0
};
// The retail table at RVA 0x008ED364: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?ReportError@@YAXPADH@Z")();
void __identifier("??_GRva006F84C0@@UAEPAXI@Z")();
void __identifier("?go@Rva008A2C60@@QAEXXZ")();
}
extern const void *const g_00CED364[3] = {
	(const void *)&__identifier("?ReportError@@YAXPADH@Z"), // slot 0 0x0069E440
	(const void *)&__identifier("??_GRva006F84C0@@UAEPAXI@Z"), // slot 1 0x006F84C0
	(const void *)&__identifier("?go@Rva008A2C60@@QAEXXZ"), // slot 2 0x006E5FD0
};
class Rva006F7D80
{
public:
    __declspec(noinline) Rva006F7D80();
    POOL_NEW
private:
    const void *m_vtable;
    int m_04;
    int m_pad08;
    int m_0c;
    int m_10;
    unsigned char m_14;
};
Rva006F7D80::Rva006F7D80()
{
    m_14 = 0;
    m_04 = -1;
    m_0c = 0;
    m_10 = 0;
    *(const void **)this = g_00CED358;
}
class Rva006F7DA0
{
public:
    __declspec(noinline) Rva006F7DA0();
    POOL_NEW
private:
    const void *m_vtable;
    int m_04;
    int m_pad08;
    int m_0c;
    int m_10;
    unsigned char m_14;
    char m_pad15[0x1c - 0x15];
};
Rva006F7DA0::Rva006F7DA0()
{
    m_14 = 0;
    m_04 = -1;
    m_0c = 0;
    m_10 = 0;
    *(const void **)this = g_00CED364;
}
class Rva006EBFF0 {public:void rva006EBE60(AptValue*);};
struct TextInst {const void*vtable;int value;int frame;AptCharacter*character;char unknown10[8];EAStringC text,variable;char unknown20[0x6c-0x20];int flags;};
#include "Rva006E34D0.h"
extern Rva006E34D0*g_bfmeAptPtrAtE176D0;
static __forceinline AptCharacterInst*spriteInst(AptCIH*aptCIH)
{
 if(!aptCIH->rva006CFCD0()) {
  g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return (AptCharacterInst*)aptCIH->field4C;
}
void AptDisplayList::instantiateCharacter(int depth,AptCharacter*character,EAStringC*name,AptCIH*parent,int replace,int value,AptCIH**out,int*created)
{
 CHECK(parent,"pParent",0x254);
 CHECK(m_query,"pState",0x255);
 bool isNew;
 AptCIH*current=0;
 AptCIH*previous,*existing;
 m_query->bfmeQuery1279(depth,(int)name,(void**)&previous,(void**)&existing);
 AptCharacter*definition=character;
 if(existing) {
  if(replace) {
   if(existing){bfmeUnlinkNestedBE((BfmeNestedBE*)existing);bfmeProcess1279(existing);existing=0;}
   isNew=true;
  } else if(((BfmeAptValue006DCD20*)existing)->isUndefined()) {
   if(name && name->IsEqualTo(&existing->field08)) {((AptValue*)existing)->setIsDefined(true);current=existing;}
   isNew=true;
  } else {current=existing;isNew=false;goto finish;}
 }
 {
  isNew=true;
  AptCharacterInst*inst=0;
  int type=13;
  if(definition->type==5) {
   inst=(AptCharacterInst*)new Rva006F7140Derived;
   inst->word18=-1;
   type=13;
   inst->word1c|=0x03000000;
  } else if(definition->type==4) {
   inst=(AptCharacterInst*)new Rva006F8D70;
   type=14;inst->word18=0;
  } else if(definition->type==2) {
   inst=(AptCharacterInst*)new Rva006ED2A0;
   type=15;
   inst->character=definition;
   inst->word24=definition->value20;
   inst->word60=definition->value24;
   inst->word3c=definition->value1c;
   inst->word64=definition->value18;
   inst->word5c=definition->value14;
   inst->word50=definition->value08;
   inst->word58=definition->value10;
   inst->word54=definition->value0c;
  } else if(definition->type==10) {inst=(AptCharacterInst*)new Rva006F7D80;type=16;}
  else if(definition->type==1) {inst=(AptCharacterInst*)new Rva006F7D80;type=12;}
  else if(definition->type==8) {inst=(AptCharacterInst*)new Rva006F7DA0;type=17;}
  else {CHECK(false,"NOT_REACHED",0x2b9);}
  if(parent->rva006CFCD0()) {
   inst->frame=spriteInst(parent)->word18;
  } else inst->frame=-1;
  if(!current) {
   current=m_query->rva006F6ED0(depth,type,inst);
  } else {
   if(depth!=cihKeyBits(current).depth) {
    bfmeUnlinkNestedBE((BfmeNestedBE*)current);
    m_query->rva006F6FB0(depth,current);
    current->Release();
   }
   current->field4C=inst;
  }
  if(parent->rva006CFCD0())cihKeyBits(current).created=inst->frame;
  else cihKeyBits(current).created=-1;
  if(name) {
   current->field08=*name;
   if(!name->IsEmpty()){AptNativeHash*hash=((AptCharacterInst*)parent->rva006E1170())->hash;hash->Set(name,(AptValue*)current);}
  }
  if(type==13 || type==14) {
   if(!(g_bfmeAptPtrAtE176D0->m_field04<g_bfmeAptPtrAtE176D0->m_fieldA4)) {
    g_bfmeAptAssertAtE17734("gpPool->nNewInsts < gpPool->GetMaxNewMovieClips()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",0x2f3);
    if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
    _ReadWriteBarrier();
   }
   g_bfmeAptPtrAtE176D0->m_field00[g_bfmeAptPtrAtE176D0->m_field04]=current;
   ++g_bfmeAptPtrAtE176D0->m_field04;
   current->AddRef();
  } else if(type==15) {
   TextInst*text=(TextInst*)((BfmeAptValue006DCD20*)current)->rva006E0F40();
   if(text->character->defaultText){EAStringC str(text->character->defaultText);text->text=str;}
   else {EAStringC str("");text->text=str;}
   if(text->character->variable){EAStringC str(text->character->variable);text->variable=str;}
   else {EAStringC str("");text->variable=str;}
   ((Rva006EBFF0*)text)->rva006EBE60((AptValue*)parent);
   text->flags=6;
  }
 }
finish:
 CHECK(current,"pCurCIH",0x30b);
 parent->AddRef();
 if(current->field48)current->field48->Release();
 current->field48=parent;
 ((AptCharacterInst*)current->field4C)->character=definition;
 ((AptCharacterInst*)current->field4C)->value=value;
 if(definition->type==4)current->rva006E1F00(1);
 *out=current;
 *created=isNew;
}


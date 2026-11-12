// AptLinker::Load, retail 0x006D1F80 (1525B, RET8).
// Target evidence: assert strings name AptLoad.cpp line 0x262
// "(*i)->GetTarget() != (*j)->GetTarget()" and the inlined AptCIH.h:0x7D
// isSpriteInstBase() accessor; the log "target ('%s') for '%s' is undefined;
// not loading" and the callers' AptLinker::Load(const EAStringC&, EAStringC)
// ABI (Apt.cpp, AptActionInterpreterConstantHandlers.cpp). The WorldBuilder
// AptLinker::Load (AptLoad.cpp) is the semantic guide; offsets and layouts
// come from retail (WB's CIH fields sit 4 bytes later). The callee classes
// keep their ledger names, so one object appears under several views.
// cl: /O2 /arch:SSE /G6 /MD /EHsc
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

#define CHECK(c, s, f, l) if (!(c)) { g_bfmeAptAssertAtE17734(s, f, l); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
#define APTLOAD_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptLoad.cpp"
#define APTCIH_H "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"

#include "EAStringC.h"

// Retail inlines this empty test (a temporary "" compared through IsEqualTo).
static __forceinline bool isEmptyString(const EAStringC &text)
{
	return text.IsEqualTo(&EAStringC(""));
}

void __cdecl Rva006CC110Log(int, const char *, ...);

#include "../../../GameEngine/Include/Common/Rva006DB270.h"
#include "../../../GameEngine/Include/Common/Rva006DB160.h"
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;

class Rva006D0280
{
public:
	~Rva006D0280();
	int m_useCount;
	int unused4;
	void *name8;
	int typeC;
};

__forceinline static int dec(int *m_refCount) { return --*m_refCount; }

class Rva006D07E0Key
{
public:
	Rva006D07E0Key(Rva006D0280 *p = 0) : m_object(p) { if (p) ++p->m_useCount; }
	Rva006D07E0Key(const Rva006D07E0Key &other) : m_object(other.m_object) { if (m_object) ++m_object->m_useCount; }
	__forceinline Rva006D07E0Key &operator=(const Rva006D07E0Key &other)
	{
		if (&other != this) {
			if (m_object && dec(&m_object->m_useCount) == 0) {
				Rva006D0280 *p = m_object;
				p->~Rva006D0280();
				g_pChainBlockAllocator->freeBlock(p, 0x1c);
			}
			m_object = other.m_object;
			if (m_object)
				++m_object->m_useCount;
		}
		return *this;
	}
	~Rva006D07E0Key()
	{
		if (m_object && dec(&m_object->m_useCount) == 0) {
			Rva006D0280 *countedObject = m_object;
			countedObject->~Rva006D0280();
			g_pChainBlockAllocator->freeBlock(countedObject, 0x1c);
		}
	}
	Rva006D0280 *m_object;
};

// The same counted pointer under the view whose out-of-line assignment retail
// calls on the loaded-file key.
class BfmeRefVGO
{
public:
	BfmeRefVGO &assign(const BfmeRefVGO &);
	Rva006D0280 *m_object;
};

int __cdecl Rva006CFDF0DecRef(int *p);
void __cdecl bfmeDropVGO(void *p);
#include "../../../GameEngine/Include/Common/Rva00894D80Accessor.h"
__declspec(noinline) inline BfmeRefVGO &BfmeRefVGO::assign(const BfmeRefVGO &other)
{
	if (&other != this)
	{
		if (m_object && Rva006CFDF0DecRef((int *)m_object) == 0)
			bfmeDropVGO(m_object);
		m_object = other.m_object;
		if (m_object)
			Rva00894D80Accessor::increment((unsigned int *)m_object);
	}
	return *this;
}

class BfmeHolderDB
{
public:
	BfmeHolderDB(const BfmeHolderDB &other) : m_object(other.m_object) { if (m_object) ++m_object->m_useCount; }
	~BfmeHolderDB()
	{
		if (m_object && dec(&m_object->m_useCount) == 0) {
			Rva006D0280 *countedObject = m_object;
			countedObject->~Rva006D0280();
			g_pChainBlockAllocator->freeBlock(countedObject, 0x1c);
		}
	}
	Rva006D0280 *m_object;
};

class Gen_00895650 { public: BfmeHolderDB bfmeGet() const; };

#include "Rva006D0A30List.h"
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;

// The linker's counted link record: count, file key, target CIH, flag.
class Rva006D0790
{
public:
	Rva006D0790(Rva006D07E0Key, void *);
	static void *operator new(unsigned size) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(size); }
	static void operator delete(void *p, unsigned size) { g_pChainBlockAllocator->freeBlock(p, size); }
	int count;
	Rva006D07E0Key key;
	void *target;
	bool flag;
	__forceinline void *GetTarget() const { return target; }
};

class Rva006D0790Ref
{
public:
	Rva006D0790Ref(Rva006D0790 *p) : ptr(p) { if (p) ++p->count; }
	Rva006D0790Ref(const Rva006D0790Ref &other) : ptr(other.ptr) { if (ptr) ++ptr->count; }
	__forceinline Rva006D0790 *operator->() const { return ptr; }
	~Rva006D0790Ref()
	{
		Rva006D0790 *record = ptr;
		if (record && dec(&record->count) == 0) {
			Rva006D0280 *fileObject = record->key.m_object;
			if (fileObject && dec(&fileObject->m_useCount) == 0) {
				Rva006D0280 *q = record->key.m_object;
				if (q) {
					q->~Rva006D0280();
					g_pChainBlockAllocator->freeBlock(q, 0x1c);
				}
			}
			g_pChainBlockAllocator->freeBlock(record, 0x10);
		}
	}
	Rva006D0790 *ptr;
};

class BfmeNodeVMU { public: Rva006D0790Ref entry; BfmeNodeVMU *next; };
#include "../../../GameEngine/Include/Common/Rva006CD530.h"
class BfmeListVMU
{
public:
	void bfmeEraseVMU(BfmeNodeVMU **);
	BfmeNodeVMU *head; // +0x00
};
// The rowed 0x006D1C90 erase body, visible here so that passing an
// iterator's address to it does not keep the iterator in memory.
__declspec(noinline) inline void BfmeListVMU::bfmeEraseVMU(BfmeNodeVMU **it)
{
	BfmeNodeVMU *target = *it;
	BfmeNodeVMU *h = head;
	if (target == h) {
		if (h != 0) {
			BfmeNodeVMU *next = h->next;
			((Rva006CD530 *)h)->detach();
			g_pChainBlockAllocator->freeBlock(h, 8);
			head = next;
		}
		return;
	}
	BfmeNodeVMU *prev = head;
	while (prev != 0) {
		if (prev->next == target)
			break;
		prev = prev->next;
	}
	BfmeNodeVMU *node = prev->next;
	if (node != 0) {
		prev->next = node->next;
		((Rva006CD530 *)node)->detach();
		g_pChainBlockAllocator->freeBlock(node, 8);
	}
}
struct Rva006D15B0Node
{
	Rva006D15B0Node(int *const *handle)
	{
		m_count = *handle;
		if (m_count != 0)
			++*m_count;
		m_next = 0;
	}
	static void *operator new(unsigned int size) { return (*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock((int)size); }
	static void operator delete(void *, unsigned int) {}
	int *m_count;
	Rva006D15B0Node *m_next;
};
class Rva006D15B0Stack
{
public:
	// The same node push as rva006D15B0, for the caller that retail inlines it into.
	__forceinline void push(int *const *handle)
	{
		Rva006D15B0Node *node = new Rva006D15B0Node(handle);
		node->m_next = m_head;
		m_head = node;
	}
	void rva006D15B0(int *const *);
	Rva006D15B0Node *m_head;
};
__declspec(noinline) inline void Rva006D15B0Stack::rva006D15B0(int *const *handle)
{
	Rva006D15B0Node *node = new Rva006D15B0Node(handle);
	node->m_next = m_head;
	m_head = node;
}

#include "AptValue.h"
struct AptActionInterpreter
{
	AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int = 1, int = 1, int = 0);
};
extern AptActionInterpreter g_aptDateInterpreter;

class AptLinker;
#include "BfmeAptValue006DCD20.h"

#include "AptNativeHash.h"
#include "AptDisplayList.h"
class AptCIH;
#include "BfmeSubmitter1283.h"
class Rva006CFCD0 { public: bool isSpriteInstBase() const; };
class BfmeNestedBE;
BfmeNestedBE *__cdecl bfmeUnlinkNestedBE(BfmeNestedBE *);

class AptCIH;
class AptSpriteInstBase
{
public:
	unsigned char pad0[0x24];
	AptDisplayList m_displayList;
};

class AptCIHParent
{
public:
	virtual void vslot0();
	virtual void release();
	virtual void vslot2();
	virtual AptNativeHash *getHash();
	unsigned char pad4[0x48];
	AptSpriteInstBase *m_spriteInst;
	__forceinline AptSpriteInstBase *getSpriteInst() const
	{
		CHECK(((const Rva006CFCD0 *)this)->isSpriteInstBase(), "isSpriteInstBase()", APTCIH_H, 0x7D);
		return m_spriteInst;
	}
};

AptCIH *__cdecl _AptGetAnimationAtLevel(int);

#include "AptCIHClass.h"
struct AptCIHLoadBits
{
	int m_depth : 17;
	unsigned m_rest58 : 15;
	unsigned m_flags5c : 18;
	unsigned m_kind : 2;
	unsigned m_rest5c : 12;
};
static __forceinline AptCIHLoadBits &cihBits(AptCIH *cih) { return *(AptCIHLoadBits *)&cih->field58; }
static __forceinline AptCIHParent *cihParent(AptCIH *cih) { return (AptCIHParent *)cih->field48; }
static __forceinline void cihRelink(AptCIH *cih)
{
	if (cih->field50)
		cih->field50->field54 = cih;
	if (cih->field54)
		cih->field54->field50 = cih;
}

class Rva006CBDE0
{
public:
	Rva006CBDE0(int, void *, AptValue *);
	static void *operator new(unsigned size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
	static void operator delete(void *p, unsigned size);
	unsigned char pad[0x60];
};

class AptLinker
{
public:
	void rva006D17F0();
	void rva006D1450(Rva006D07E0Key);
	void Load(const EAStringC &file, EAStringC target);
protected:
	// The link list's iterator, spelled as WorldBuilder's AptLoad.cpp calls it
	// (begin, end, ==, !=, ++, *, a user-written copy constructor).
	struct Iter
	{
		BfmeNodeVMU *node;
		__forceinline Iter(BfmeNodeVMU *n) : node(n) {}
		__forceinline Iter(const Iter &iter) : node(iter.node) {}
		__forceinline Iter &operator++() { node = node->next; return *this; }
		__forceinline Rva006D0790Ref &operator*() const { return node->entry; }
		__forceinline bool operator!=(const Iter &other) const { return node != other.node; }
		__forceinline bool operator==(const Iter &other) const { return node == other.node; }
	};
	__forceinline Iter begin() const { return Iter(m_head); }
	__forceinline Iter end() const { return Iter(0); }
	__forceinline Iter findLink(void *target)
	{
		for (Iter it = begin(); it != end(); ++it)
			if ((*it)->GetTarget() == target)
				return it;
		return end();
	}
	__forceinline void erase(Iter &it) { ((BfmeListVMU *)this)->bfmeEraseVMU(&it.node); }
	__forceinline void add(const Rva006D07E0Key &file, AptCIH *target)
	{
		Rva006D0790Ref link(new Rva006D0790(Rva006D07E0Key(file.m_object), target));
		((Rva006D15B0Stack *)this)->rva006D15B0((int *const *)&link);
	}
	BfmeNodeVMU *m_head;
};

void AptLinker::Load(const EAStringC &file, EAStringC target)
{
	AptValue *value = g_aptDateInterpreter.getVariable((AptValue *)_AptGetAnimationAtLevel(0), 0, &target, 1, 1, 0);
	if (!value || !((BfmeAptValue006DCD20 *)value)->isCIH(false)) {
		Rva006CC110Log(4, "target ('%s') for '%s' is undefined; not loading\n", target.rva00620090(), file.rva00620090());
		return;
	}

	for (BfmeNodeVMU *i = m_head; i; i = i->next)
		for (BfmeNodeVMU *j = m_head; j; j = j->next)
			if (i != j)
				CHECK(i->entry->GetTarget() != j->entry->GetTarget(), "(*i)->GetTarget() != (*j)->GetTarget()", APTLOAD_CPP, 0x262);

	Rva006D07E0Key loaded; // retail unwinds it through the key destructor at 0x000A9DF3
	if (!isEmptyString(file)) {
		loaded = ((Rva006D0A30List *)g_rva00893030Manager)->findSpecial(&file);
		if (!loaded.m_object)
			((BfmeRefVGO &)loaded).assign((const BfmeRefVGO &)((Rva006D0A30List *)g_rva00893030Manager)->rva006D0B40(file));
		else
			rva006D1450(Rva006D07E0Key(loaded.m_object));
	}

	AptCIH *cih = (AptCIH *)((BfmeAptValue006DCD20 *)value)->rva006DCF60(false);
	cih->ClearCIH(1);
	if (cihBits(cih).m_kind == 1) {
		Iter it = findLink(cih);
		Rva006D0790Ref link(*it);
		Rva006D0280 *owner = ((Gen_00895650 *)link.ptr)->bfmeGet().m_object;
		if (owner->typeC != 5) {
			erase(it);
			owner->typeC = 5;
		}

		AptCIH *copy = (AptCIH *)new Rva006CBDE0(0x13, 0, (AptValue *)cih->field48);
		cihBits(copy).m_depth = cihBits(cih).m_depth;
		copy->field08 = cih->field08;
		if (cih->field48) {
			copy->field50 = cih->field50;
			copy->field54 = cih->field54;
			cihParent(cih)->getHash()->Set(&cih->field08, (AptValue *)copy);
			cihParent(cih)->getSpriteInst()->m_displayList.bfmeProcess1279(cih);
			cihRelink(copy);
			cih->AddRef();
			((BfmeSubmitter1283 *)&cihParent(copy)->getSpriteInst()->m_displayList)->bfmeSubmit1283(
				copy, cihBits(copy).m_depth, 0, (int)&copy->field08, (int)copy->field48, 1, -1,
				(float *)&copy->field24, (int)&copy->field0C, 0, 0, 0);
			((AptValue *)cih)->setIsDefined(true);
			cihParent(copy)->release();
			cih->field48 = 0;
		} else {
			copy->field50 = cih->field50;
			copy->field54 = cih->field54;
			bfmeUnlinkNestedBE((BfmeNestedBE *)cih);
			cihRelink(copy);
		}
		copy->AddRef();
		((BfmeAptValue006DCD20 *)cih)->setGCRootCount(1);
		cih = copy;
	}

	((BfmeAptValue006DCD20 *)cih)->setTypeAt006DBBC0(0x13);
	cih->field4C = 0;
	((AptValue *)cih)->setIsDefined(true);
	Iter it = findLink(cih);
	if (it == end()) {
		if (loaded.m_object)
			add(loaded, cih);
	} else {
		erase(it);
		if (loaded.m_object)
			add(loaded, cih);
	}
}

struct Rva006D07E0Iterator
{
	Rva006D07E0Iterator(BfmeNodeVMU *p) : node(p) {}
	Rva006D0790Ref &operator*() const { return node->entry; }
	BfmeNodeVMU *node;
};
class Rva006D07E0List { public: Rva006D07E0Iterator find(Rva006D07E0Key); BfmeNodeVMU *head; };

// AptLinker under the pinned neutral name of retail 0x006D1D10 (615B, RET8), called from 0x006D2773.
// List nodes hold a counted record reference; the push uses the rowed 0x006D15B0 node shape.
class Rva006D1D10 : public AptLinker
{
public:
	void update(Rva006D07E0Key first, Rva006D07E0Key second);
private:
	__forceinline void push_front(const Rva006D0790Ref &link) { ((Rva006D15B0Stack *)this)->push((int *const *)&link); }
};

// WB 0x01752A20 shape: found = *find(first), it = findLink(target), end() test, erase only when found.
// Both record constructors copy second; native loads [esp+0x38] after two pushes.
void Rva006D1D10::update(Rva006D07E0Key first, Rva006D07E0Key second)
{
	rva006D1450(second);
	Rva006D0790Ref found(*((Rva006D07E0List *)this)->find(first));
	void *name = found->GetTarget();
	Iter it = findLink(name);
	if (it == end())
		push_front(new Rva006D0790(second, name));
	else {
		erase(it);
		push_front(new Rva006D0790(second, name));
	}
}

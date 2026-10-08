// cl: /MD /EHsc
// A counted-handle getter and a doubly-linked unlink.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp); trimmed to the two T1
// bodies the sweep places.

class BfmeRefDB
{
public:
	int m_bfmeCount;					// +0x00
};

class BfmeHolderDB
{
public:
	BfmeHolderDB(void)
	{
		m_bfmeRef = 0;
	}

	BfmeHolderDB(const BfmeHolderDB &other)
	{
		BfmeRefDB *ref = other.m_bfmeRef;

		m_bfmeRef = ref;

		if (ref)
			++ref->m_bfmeCount;
	}

	~BfmeHolderDB(void)
	{
		if (m_bfmeRef)
			--m_bfmeRef->m_bfmeCount;
	}

	BfmeRefDB *m_bfmeRef;					// +0x00
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeHolderDB m_bfmeHolder;				// +0x04
};

// ?bfmeGet@Gen_00895650@@QBE?AVBfmeHolderDB@@XZ
BfmeHolderDB Gen_00895650::bfmeGet(void) const
{
	return m_bfmeHolder;
}

class Gen_008F7AC0
{
public:
	void bfmeUnlink(void);

private:
	int m_bfmeHead[5];					// +0x00
	Gen_008F7AC0 **m_bfmePrev;				// +0x14
	Gen_008F7AC0 *m_bfmeNext;				// +0x18
};

// ?bfmeUnlink@Gen_008F7AC0@@QAEXXZ
void Gen_008F7AC0::bfmeUnlink(void)
{
	*m_bfmePrev = m_bfmeNext;

	Gen_008F7AC0 *next = m_bfmeNext;

	if (next != 0)
		next->m_bfmePrev = m_bfmePrev;

	m_bfmePrev = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?unlink@PartitionData@@QAEXXZ=?bfmeUnlink@Gen_008F7AC0@@QAEXXZ")

// Growth helper 0x006D1130..0x006D1202. Semantic guide: BFME1
// Gen00896320Append.cpp at ba7ddda7, rva00896100. Target facts: signed
// capacity +4, count +0, pointer +8, one inline slot +12; unlike the donor,
// the copy helper receives two three-word iterator values by value.
// Neither the original container nor the iterator class name is known.
unsigned __cdecl bfmeDecVGO(unsigned *p);
void __cdecl bfmeDropVGO(void *p);
class BfmeRefVGO
{
public:
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &other);
	unsigned *m_bfmeP;
};
class Rva006D1130Item : public BfmeRefVGO
{
public:
	Rva006D1130Item() { m_bfmeP = 0; }
	~Rva006D1130Item()
	{
		if (m_bfmeP && bfmeDecVGO(m_bfmeP) == 0)
			bfmeDropVGO(m_bfmeP);
	}
};
struct Rva006D1130Iterator
{
	BfmeRefVGO *position;
	BfmeRefVGO *begin;
	BfmeRefVGO *end;
};
void __cdecl Rva006CE3D0Cleanup(void *, int, int);
BfmeRefVGO *__cdecl Rva006D05E0Copy(Rva006D1130Iterator first,
	Rva006D1130Iterator last, BfmeRefVGO *result);
class Rva006D1130
{
public:
	void grow(int capacity);
private:
	unsigned m_count;
	int m_capacity;
	Rva006D1130Item *m_begin;
	Rva006D1130Item m_inline[1];
};
void Rva006D1130::grow(int capacity)
{
	int current = m_capacity;
	if (capacity <= current)
		return;
	if (capacity <= 1)
	{
		m_capacity = capacity;
		return;
	}
	// Existing pin uses the cleanup spelling. Its allocator mode returns
	// the pointer in EAX when called with (0, 0, capacity+1).
	Rva006D1130Item *newData = (Rva006D1130Item *)
		((void *(__cdecl *)(void *, int, int))Rva006CE3D0Cleanup)(0, 0, capacity + 1);
	Rva006D1130Item *oldEnd = m_begin + m_count;
	Rva006D1130Iterator first = {m_begin, m_begin, oldEnd};
	Rva006D1130Iterator last = {oldEnd, m_begin, oldEnd};
	Rva006D05E0Copy(first, last, newData);
	m_capacity = capacity;
	if (m_begin != m_inline)
		Rva006CE3D0Cleanup(m_begin, 0, 0);
	m_begin = newData;
	const Rva006D1130Item empty;
	m_begin[m_count].bfmeAssignVGO(empty);
	__assume(empty.m_bfmeP == 0);
}

// Target 6D07E0..6D085B: head at0; entry key at4; by-value counted
// owner parameter released through independently rowed pool providers.
// BFME1 ba7ddda7 Rva008951B0Find supplies the linked-list search guide;
// target uses a counted key instead of the donor's borrowed void pointer.
class Rva006DB270 { public: void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
// The independent EAStringC providers prove the 4-byte string ABI used
// by the 6D0660 comparison: C-string ctor6D4C80 equal6D3090 dtor6D3010.
class EAStringC {
public:
 EAStringC(const char *);
 ~EAStringC();
 bool IsEqualTo(const EAStringC *) const;
 void *data;
};
struct Rva006D0280 {
 void teardown();
 int m_useCount;
 int unknown4;
 EAStringC name8;
};
class Rva006D07E0Key {
public:
 Rva006D07E0Key(const Rva006D07E0Key &other) {
  m_object=other.m_object;
  if(m_object) ++m_object->m_useCount;
 }
 ~Rva006D07E0Key() {
  Rva006D0280 *p=m_object;
  if(p && --p->m_useCount==0) {
   p->teardown();
   g_pChainBlockAllocator->freeBlock(p,0x1c);
  }
 }
 Rva006D0280 *m_object;
};
struct Rva006D07E0Entry { int unknown0; Rva006D0280 *key4; };
struct Rva006D07E0Node { Rva006D07E0Entry *entry; Rva006D07E0Node *next; };
struct Rva006D07E0Iterator {
 Rva006D07E0Iterator(Rva006D07E0Node *p):node(p) {}
 Rva006D07E0Node *node;
};
class Rva006D07E0List {
public:
 Rva006D07E0Iterator find(Rva006D07E0Key key);
 Rva006D07E0Node *head;
};
Rva006D07E0Iterator Rva006D07E0List::find(Rva006D07E0Key key) {
 Rva006D07E0Node *node=head;
 while(node) {
  if(node->entry->key4==key.m_object) return Rva006D07E0Iterator(node);
  node=node->next;
 }
 return Rva006D07E0Iterator(0);
}

// Native Ghidra6D0660..6D0766; comparator called by6D0860 with
// counted owner key. The provider is at14; its string table is28/2c
// with10-byte stride (hex). All offsets are target facts; purpose and
// original owner/table names are unknown.
struct Rva006D0660Record { const char *text; char unknown4[12]; };
struct Rva006D0660Table {
 char unknown0[0x28];
 int count28;
 Rva006D0660Record *records2c;
};
class Rva006D0660 {
public:
 int contains(Rva006D07E0Key key);
 char unknown0[0x14];
 Rva006D0660Table *table14;
};
int Rva006D0660::contains(Rva006D07E0Key key) {
 for(int i=0;i<table14->count28;++i) {
  if(EAStringC(table14->records2c[i].text).IsEqualTo(&key.m_object->name8))
   return 1;
 }
 return 0;
}

// Native6D0460..6D04C4: raw four-byte owner range copy. Semantic
// guide BFME1 ba7ddda7 Rva008953C0RefRangeCopy.cpp; target's pooled
// owner release uses existing6D0280/6DB270 providers and1c bytes.
BfmeRefVGO *__cdecl Rva006D0460Copy(BfmeRefVGO *first,
 BfmeRefVGO *last, BfmeRefVGO *result) {
 if(first!=last) {
  do {
   BfmeRefVGO *destination=result++;
   if(first!=destination) {
    unsigned *old=destination->m_bfmeP;
    if(old && --*old==0) {
     Rva006D0280 *p=(Rva006D0280 *)destination->m_bfmeP;
     if(p) {
      p->teardown();
      g_pChainBlockAllocator->freeBlock(p,0x1c);
     }
    }
    destination->m_bfmeP=first->m_bfmeP;
    if(destination->m_bfmeP) ++*destination->m_bfmeP;
   }
   ++first;
  } while(first!=last);
 }
 return result;
}

// Native6D04D0..6D0537. Two three-word source iterators and raw
// output start proven by the two12-byte pushes at native caller6D1306;
// walks backward over the pointer difference, retaining
// each replacement exactly as6D0460. Original algorithm name unknown.
BfmeRefVGO *__cdecl Rva006D04D0CopyBackward(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result) {
 int count=last.position-first.position;
 --last.position;
 result+=count-1;
 while(count) {
  if(last.position!=result) {
   unsigned *old=result->m_bfmeP;
   if(old && --*old==0) {
    Rva006D0280 *p=(Rva006D0280 *)result->m_bfmeP;
    if(p) {
     p->teardown();
     g_pChainBlockAllocator->freeBlock(p,0x1c);
    }
   }
   result->m_bfmeP=last.position->m_bfmeP;
   if(result->m_bfmeP) ++*result->m_bfmeP;
  }
  --last.position;
  --result;
  --count;
 }
 return result;
}

// cl: /O2 /MD /EHsc
// Apt counted owners, container operations and linker processing.
//
// The counted-handle getter and the doubly-linked unlink come from a BFME1
// byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp).

#include <new>
#include <string.h>

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
	BfmeRefVGO &assign(const BfmeRefVGO &other);
	unsigned *m_bfmeP;
};
// The ref-counted assign (rowed 0x006CDB10, BfmeConv1355.cpp) is visible
// here as an out-of-line COMDAT copy of the same body: seeing that it never
// writes its argument lets MSVC drop the empty handles' destructors in
// insert (retail has no release call there) and keeps retail's slot choice.
#include "../../Include/Common/Rva00894D80Accessor.h"
__declspec(noinline) inline BfmeRefVGO &BfmeRefVGO::assign(const BfmeRefVGO &o)
{
	if (&o != this)
	{
		if (m_bfmeP && bfmeDecVGO(m_bfmeP) == 0)
			bfmeDropVGO(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			Rva00894D80Accessor::increment(m_bfmeP);
	}
	return *this;
}
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
inline void rva006D1130RangeCheck(bool) {}
struct Rva006D1130Iterator
{
	BfmeRefVGO *position;
	BfmeRefVGO *begin;
	BfmeRefVGO *end;
	// Same release range check as Apt.cpp's PlaybackIterator (empty even in
	// the WB debug build); spelling the loop test through it keeps retail's
	// top-tested copy loop (0x006D05E0) instead of cl's rotated one.
	bool operator!=(const Rva006D1130Iterator &other) const
	{
		rva006D1130RangeCheck(begin == other.begin && end == other.end);
		return position != other.position;
	}
	Rva006D1130Iterator() {}
	Rva006D1130Iterator(BfmeRefVGO *initialPosition, BfmeRefVGO *rangeBegin, BfmeRefVGO *rangeEnd) : position(initialPosition), begin(rangeBegin), end(rangeEnd) {}
	int operator-(const Rva006D1130Iterator &other) const { return position - other.position; }
	Rva006D1130Iterator operator+(int amount) const { return Rva006D1130Iterator(position + amount, begin, end); }
	Rva006D1130Iterator operator++(int) {
		Rva006D1130Iterator old=*this;
		++position;
		return old;
	}
};
class Rva004A9DF3Element;
Rva004A9DF3Element *__cdecl Rva006CE3D0Resize(Rva004A9DF3Element *, int, int);
BfmeRefVGO *__cdecl Rva006D05E0Copy(Rva006D1130Iterator first,
	Rva006D1130Iterator last, BfmeRefVGO *result);
class Rva006D1130
{
public:
	void grow(int capacity);
	void insert(Rva006D1130Item *const &first, Rva006D1130Item *const &last,
		const Rva006D1130Iterator &position);
	void append(Rva006D1130Item *value);
	Rva006D1130Iterator begin() { return Rva006D1130Iterator(m_begin, m_begin, m_begin + m_count); }
	Rva006D1130Iterator end() { return Rva006D1130Iterator(m_begin + m_count, m_begin, m_begin + m_count); }
private:
	unsigned m_count;
	int m_capacity;
	Rva006D1130Item *m_begin;
	Rva006D1130Item m_inline[1];
};
void Rva006D1130::grow(int capacity)
{
	int currentCapacity = m_capacity;
	if (capacity <= currentCapacity)
		return;
	if (capacity <= 1)
	{
		m_capacity = capacity;
		return;
	}
	// The rowed ref-array resizer also allocates an empty array when called
	// with (0, 0, capacity+1), and destroys one when the last two args are 0.
	Rva006D1130Item *newData = (Rva006D1130Item *)
		Rva006CE3D0Resize(0, 0, capacity + 1);
	Rva006D1130Item *oldEnd = m_begin + m_count;
	Rva006D1130Iterator first(m_begin, m_begin, oldEnd), last(oldEnd, m_begin, oldEnd);
	Rva006D05E0Copy(first, last, newData);
	m_capacity = capacity;
	if (m_begin != m_inline)
		Rva006CE3D0Resize((Rva004A9DF3Element *)m_begin, 0, 0);
	m_begin = newData;
	const Rva006D1130Item empty;
	m_begin[m_count].assign(empty);
	__assume(empty.m_bfmeP == 0);
}

BfmeRefVGO *__cdecl Rva006D0460Copy(BfmeRefVGO *first, BfmeRefVGO *last, BfmeRefVGO *result);
BfmeRefVGO *__cdecl Rva006D04D0CopyBackward(Rva006D1130Iterator first, Rva006D1130Iterator last, BfmeRefVGO *result);
Rva006D1130Iterator __cdecl Rva006D0540Copy(BfmeRefVGO *first, BfmeRefVGO *last, Rva006D1130Iterator result);

// Native 6D1230..6D13D6 RET 0xC: range insert of [first, last) at position,
// the 4-byte-element twin of the matched Rva006CE660Vec::insert 0x006CE890
// (PlaybackBufferResize.cpp): in place when the capacity allows (copy at the
// end, or shift the tail with the backward copy 0x006D04D0 and copy into the
// gap with 0x006D0540, then store an empty terminator), otherwise grow to
// max(2 * capacity, count + added) and retry at the same offset. Calls and
// layout are target facts; the shape and names follow the sibling.
void Rva006D1130::insert(Rva006D1130Item *const &first, Rva006D1130Item *const &last,
	const Rva006D1130Iterator &position)
{
	int insertCount = last - first;
	if (!insertCount)
		return;
	int requiredCount = m_count + insertCount;
	if (requiredCount < m_capacity)
	{
		Rva006D1130Item *end = m_begin + m_count;
		if (position.position == end)
		{
			Rva006D0460Copy(first, last, end);
			m_begin[requiredCount].assign(Rva006D1130Item());
		}
		else
		{
			BfmeRefVGO *begin = m_begin, *finish = end;
			Rva006D1130Iterator tail(finish, begin, finish);
			Rva006D04D0CopyBackward(position, tail, begin + ((position.position - begin) + insertCount));
			Rva006D0540Copy(first, last, position);
			m_begin[requiredCount].assign(Rva006D1130Item());
		}
		m_count = requiredCount;
	}
	else
	{
		int newCapacity = (int)(2.0 * m_capacity);
		if (newCapacity < requiredCount)
			newCapacity = requiredCount;
		int insertionOffset = position - begin();
		grow(newCapacity);
		Rva006D1130Iterator insertionPosition = begin() + insertionOffset;
		insert(first, last, insertionPosition);
	}
}

// Native 6D13E0..6D141F RET4: append one element at end() through the
// unrowed range insert 0x006D1230 (two element references plus the position
// iterator), the 4-byte-element twin of the matched
// Rva006CE660Vec::append 0x006CEA90 (PlaybackBufferResize.cpp, 8-byte
// elements, insert 0x006CE890). Target facts: count at +0, data at +8, the
// last = value + 1 reference built in the argument slot, the by-value end
// iterator {data + count, data, data + count}. Names address-derived.
void Rva006D1130::append(Rva006D1130Item *value)
{
	Rva006D1130Item *last = value + 1, *first = value;
	insert(first, last, end());
}

// Target 6D07E0..6D085B: head at0; entry key at4; by-value counted
// owner parameter released through independently rowed pool providers.
// BFME1 ba7ddda7 Rva008951B0Find supplies the linked-list search guide;
// target uses a counted key instead of the donor's borrowed void pointer.
#include "../../Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
// The independent EAStringC providers prove the 4-byte string ABI used
// by the 6D0660 comparison: C-string ctor6D4C80 equal6D3090 dtor6D3010.
#include "../../../Libraries/Source/Apt/EAStringC.h"
class Rva006DB160 {public:void*allocBlock(int);};
void __cdecl Rva006D8680Free(void*,int);
struct Rva006D0280 {
 ~Rva006D0280();
 __forceinline Rva006D0280(const EAStringC*name):m_useCount(0),name8(*name),typeC(1),object14(0),buffer18(0){}
 __forceinline int increaseCount(){return ++m_useCount;}
 __forceinline int decreaseCount(){int &referenceCount=m_useCount;return --referenceCount;}
 __forceinline static void*operator new(unsigned int n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
 __forceinline static void operator delete(void*p,unsigned int n){((Rva006DB270*)g_pChainBlockAllocator)->freeBlock(p,n);}
 int m_useCount;
 int unknown4;
 EAStringC name8;
 int typeC;
 int argument10; void*object14;void*buffer18;
};
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
	    BfmeRefDB *counted = m_bfmeRef;
	    if (counted && (--counted->m_bfmeCount, counted->m_bfmeCount == 0))
	    {
	        Rva006D0280 *object = (Rva006D0280 *)m_bfmeRef;
	        object->~Rva006D0280();
	        g_pChainBlockAllocator->freeBlock(object, 0x1c);
	    }
	}

	BfmeRefDB *m_bfmeRef;					// +0x00
};

class Gen_00895650
{
public:
	__declspec(noinline) BfmeHolderDB bfmeGet(void) const;

	int m_bfmeHead;						// +0x00
	__forceinline int decreaseCount() { return --m_bfmeHead; }
	BfmeHolderDB m_bfmeHolder;				// +0x04
	void *m_cih;                         // +0x08
	unsigned char m_state;                // +0x0c
};

// ?bfmeGet@Gen_00895650@@QBE?AVBfmeHolderDB@@XZ
BfmeHolderDB Gen_00895650::bfmeGet(void) const
{
	return m_bfmeHolder;
}

struct Rva006D0660Table;
class Rva006D07E0Key {
public:
 Rva006D07E0Key(Rva006D0280 *referencedObject=0):m_object(referencedObject) {
  if(referencedObject) referencedObject->increaseCount();
 }
 Rva006D07E0Key(const Rva006D07E0Key &other) {
  m_object=other.m_object;
  if(m_object) m_object->increaseCount();
 }
 ~Rva006D07E0Key() {
  Rva006D0280 *countedObject=m_object;
  if(countedObject && countedObject->decreaseCount()==0) {
   Rva006D0280 *releasedObject=m_object;
   if(releasedObject) { releasedObject->~Rva006D0280(); g_pChainBlockAllocator->freeBlock(releasedObject,0x1c); }
  }
 }
 Rva006D0280 *m_object;
 Rva006D0660Table *getTable()const{return (Rva006D0660Table*)m_object->object14;}
 bool isNull()const{return m_object==0;}
};
struct Rva006D07E0Entry { int unknown0; Rva006D0280 *key4; };
struct Rva006D07E0Node { Rva006D07E0Entry *entry; Rva006D07E0Node *next; };
struct Rva006D07E0Iterator {
 Rva006D07E0Iterator(Rva006D07E0Node *initialNode):node(initialNode) {}
 Rva006D07E0Node *node;
};
class Rva006D07E0List {
public:
 Rva006D07E0Iterator find(Rva006D07E0Key key);
 int contains(Rva006D07E0Key key);
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
 for(int recordIndex=0;recordIndex<table14->count28;++recordIndex) {
  if(EAStringC(table14->records2c[recordIndex].text).IsEqualTo(&key.m_object->name8))
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
    unsigned *previousReferenceCount=destination->m_bfmeP;
    if(previousReferenceCount && --*previousReferenceCount==0) {
     Rva006D0280 *releasedObject=(Rva006D0280 *)destination->m_bfmeP;
     if(releasedObject) {
      releasedObject->~Rva006D0280();
      g_pChainBlockAllocator->freeBlock(releasedObject,0x1c);
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

// Native 6D05E0..6D0656 RET0: the forward copy grow (0x006D1130) calls,
// two three-word source iterators by value and a raw output pointer. The
// post-incremented source copy is retail's two dead begin/end stores; each
// element is released and retained as in 0x006D0460. Target facts: the
// ABI, loop head (top test against last.position) and refcount sequence.
// Original algorithm name unknown.
BfmeRefVGO *__cdecl Rva006D05E0Copy(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result) {
 while(first!=last) {
  BfmeRefVGO *destination=result++;
  Rva006D1130Iterator source=first++;
  if(source.position!=destination) {
   unsigned *previousReferenceCount=destination->m_bfmeP;
   if(previousReferenceCount && --*previousReferenceCount==0) {
    Rva006D0280 *releasedObject=(Rva006D0280 *)destination->m_bfmeP;
    if(releasedObject) {
     releasedObject->~Rva006D0280();
     g_pChainBlockAllocator->freeBlock(releasedObject,0x1c);
    }
   }
   destination->m_bfmeP=source.position->m_bfmeP;
   if(destination->m_bfmeP) ++*destination->m_bfmeP;
  }
 }
 return result;
}

// Native6D04D0..6D0537. Two three-word source iterators and raw
// output start proven by the two12-byte pushes at native caller6D1306;
// walks backward over the pointer difference, retaining
// each replacement exactly as6D0460. Original algorithm name unknown.
BfmeRefVGO *__cdecl Rva006D04D0CopyBackward(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result) {
 int remainingCount=last.position-first.position;
 --last.position;
 result+=remainingCount-1;
 while(remainingCount) {
  if(last.position!=result) {
   unsigned *previousReferenceCount=result->m_bfmeP;
   if(previousReferenceCount && --*previousReferenceCount==0) {
    Rva006D0280 *releasedObject=(Rva006D0280 *)result->m_bfmeP;
    if(releasedObject) {
     releasedObject->~Rva006D0280();
     g_pChainBlockAllocator->freeBlock(releasedObject,0x1c);
    }
   }
   result->m_bfmeP=last.position->m_bfmeP;
   if(result->m_bfmeP) ++*result->m_bfmeP;
  }
  --last.position;
  --result;
  --remainingCount;
 }
 return result;
}

// Native6D0540..6D05D1, including RET before the INT3 padding:
// raw source range and a by-value three-word output iterator. The
// returned iterator carries output position plus unchanged begin/end.
Rva006D1130Iterator __cdecl Rva006D0540Copy(BfmeRefVGO *first,
 BfmeRefVGO *last, Rva006D1130Iterator result) {
 if(first!=last) {
  do {
   Rva006D1130Iterator destination=result++;
   if(first!=destination.position) {
    unsigned *previousReferenceCount=destination.position->m_bfmeP;
    if(previousReferenceCount && --*previousReferenceCount==0) {
     Rva006D0280 *releasedObject=(Rva006D0280 *)destination.position->m_bfmeP;
     if(releasedObject) {
      releasedObject->~Rva006D0280();
      g_pChainBlockAllocator->freeBlock(releasedObject,0x1c);
     }
    }
    destination.position->m_bfmeP=first->m_bfmeP;
    if(destination.position->m_bfmeP) ++*destination.position->m_bfmeP;
   }
   ++first;
  } while(first!=last);
 }
 return result;
}

// Native6D0A30..6D0A82: same counted-owner family as6D07E0.
// Head0 nodes carry owner0/next4. Its existing compare provider6D36C0
// is the signed zero-equality string operation at owner8. Returned
// counted value supplies the construction slot that the old out-pointer
// reconstruction had to force with a volatile local.
struct Rva006D0A30Node { Rva006D0280 *entry; Rva006D0A30Node *next;
 Rva006D0A30Node(Rva006D0280*entryObject):entry(entryObject),next(0){}
 __forceinline static void*operator new(unsigned int n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);}
};
class Rva006D0A30List {
public:
 void rva006D1680();
 Rva006D07E0Key find(const EAStringC *key);
 Rva006D07E0Key findSpecial(const EAStringC *key);
 Rva006D07E0Key rva006D0B40(const EAStringC&);
 Rva006D0A30Node *head;
};
Rva006D07E0Key Rva006D0A30List::find(const EAStringC *key) {
 Rva006D0A30Node *node=head;
 while(node) {
  if(node->entry->name8.rva006D36C0(key)==0)
   return Rva006D07E0Key(node->entry);
  node=node->next;
 }
 return Rva006D07E0Key();
}

// Native6D0A90..6D0B35. Filters the counted lookup result by
// target owner tagC values4/5; value copying and local destruction
// preserve ownership even for a rejected non-null result.
Rva006D07E0Key Rva006D0A30List::findSpecial(const EAStringC *key) {
 Rva006D07E0Key found=find(key);
 if(found.m_object && (found.m_object->typeC==4 || found.m_object->typeC==5))
  return found;
 return Rva006D07E0Key();
}

Rva006D07E0Key Rva006D0A30List::rva006D0B40(const EAStringC&name){
 Rva006D07E0Key found=find(&name);
 Rva006D0280*existingObject=found.m_object;
 if(existingObject)return Rva006D07E0Key(existingObject);
 Rva006D07E0Key key(new Rva006D0280(&name));
 Rva006D0A30Node*newNode=new Rva006D0A30Node(key.m_object);
 newNode->next=head;
 head=newNode;
 return key;
}
class Rva00893030Manager;extern Rva00893030Manager*g_rva00893030Manager;
Rva006D07E0Key Rva006CE110(const char*name){
 return ((Rva006D0A30List*)g_rva00893030Manager)->rva006D0B40(EAStringC(name));
}

// New target family6D0B40/6CE110: pooled28B owner count0/name8/typeC1,
// argument10 remains uninitialized, object14/buffer18 begin null; raw8B
// list nodes track it. Target shared lookup and allocator providers establish
// these fields independently of donor names. Returning updated counts through
// inline helpers gives native register cleanup; all11 existing home rows
// stay exact. Borrowed string pointer ABI is expressed as a const reference.

// Complete native 6D1450..6D151F RET4: register a counted owner unless its
// pointer is already in the vector at +4. The 6D1520 caller supplies the Apt
// linker global, establishing the owner; the original method name is unknown.
// The argument is released on both paths. Native leaves no stable pointer
// result in EAX, so the old pointer-return pin is replaced by this void view.
// The iterator's existing range check preserves the top-tested search and
// separate found-path release. The count reference above and reloaded owner
// in the key destructor preserve both retail decrement sequences and all
// earlier bodies in this unit; the complete exception graph is also exact.
struct BfmeLoadNode;
class Rva006D17F0Vector;
class AptLinker {
public:
 BfmeLoadNode *m_chain; // +0x00
 Rva006D1130 entries; // +0x04
 void rva006D1450(Rva006D07E0Key key);
 void rva006D17F0();
 __forceinline Rva006D17F0Vector &pending() { return *(Rva006D17F0Vector *)&entries; }
};
void AptLinker::rva006D1450(Rva006D07E0Key key) {
 Rva006D1130Iterator entryIterator=entries.begin(),last=entries.end();
 for(;entryIterator!=last;entryIterator++) if(entryIterator.position->m_bfmeP==(unsigned*)key.m_object) return;
 entries.append((Rva006D1130Item*)&key);
}

// Linker processing uses the counted-owner vector at +4 and the load chain at +0.
// Ownership, restart paths and layouts follow retail and WB 0x01752E70.

// 0x00E176D4 playback flag; 0x00E176EC checkpoints; 0x00E176CC load list.
extern int g_bfmeAptFlagAtE176D4;
class Rva006CEB10Playback;
extern Rva006CEB10Playback *g_aptPlaybackCheckpoints;
// 0x00E176CC is defined (as its manager pointer) by Rva00893030RefDispatch.cpp.
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
// Diagnostics state (0x00E176F0, 0x00E17708, 0x00E17740, 0x00E17754).
extern int g_rva00891FA0Value;
extern int g_rva00891FA0Ready;
extern "C" void (__cdecl *Rva00891FA0SendRecord)(const void *, unsigned int);
extern void (__cdecl *g_rva00A17754)(const char *, const char *);

class Rva006D17F0ValueHandle
{
public:
    Rva006D17F0ValueHandle(Gen_00895650 *value) : m_value(value)
    {
        if (value) ++value->m_bfmeHead;
    }
    ~Rva006D17F0ValueHandle()
    {
        if (m_value && m_value->decreaseCount() == 0)
        {
            Rva006D0280 *load = (Rva006D0280 *)m_value->m_bfmeHolder.m_bfmeRef;
            if (load && load->decreaseCount() == 0)
            {
                Rva006D0280 *object = (Rva006D0280 *)m_value->m_bfmeHolder.m_bfmeRef;
                if (object)
                {
                    object->~Rva006D0280();
                    g_pChainBlockAllocator->freeBlock(object, 0x1c);
                }
            }
            g_pChainBlockAllocator->freeBlock(m_value, 0x10);
        }
    }
    Gen_00895650 *m_value;
};

class Rva008A2BA0Handle
{
public:
	Rva008A2BA0Handle(BfmeRefDB *ref) : m_ref((int *)ref) { if (m_ref) ++*m_ref; }
	Rva008A2BA0Handle(const Rva008A2BA0Handle &other) : m_ref(other.m_ref) { if (m_ref) ++*m_ref; }
	~Rva008A2BA0Handle()
    {
        int *counted = m_ref;
        if (counted && (--*counted, *counted == 0))
        {
            Rva006D0280 *object = (Rva006D0280 *)m_ref;
            object->~Rva006D0280();
            g_pChainBlockAllocator->freeBlock(object, 0x1c);
        }
    }
	int *m_ref;
};

class Rva008A2C80
{
public:
	Rva008A2C80(Rva008A2BA0Handle handle);
	virtual ~Rva008A2C80();
	static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocator->freeBlock(p, n); }
	char m_unknown04[0x34];
};

class AptCharacterAnimationInst
{
public:
	int getSwfVersion();
};

extern int Rva006CD220Get();
extern void Rva006CD210Set(int version);

class AptCIH
{
public:
	void ClearCIH(int clear);
	__declspec(dllimport) void *rva006CFF40() const;
	void rva006E2D60();
};

#include "../../../Libraries/Source/Apt/AptValue.h"

class AptLinker;
#include "../../../Libraries/Source/Apt/BfmeAptValue006DCD20.h"

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

#include "../../../Libraries/Source/Apt/AptAnimationPoolData.h"

class Rva004A9DF3Element
{
public:
	// Match the sibling Apt array view: retail's EH vector constructor
	// takes the void default-argument closure at 0x00013260.
	Rva004A9DF3Element(unsigned int *value = 0) : m_value(value) {}
	~Rva004A9DF3Element();
	unsigned int *m_value;
};

class ModuleTagString
{
public:
	ModuleTagString() : m_count(0), m_capacity(0), m_data(m_inline) {}
	void swap(ModuleTagString &other);
	~ModuleTagString();
private:
	int m_count;		// +0x00
	int m_capacity;		// +0x04
	void *m_data;		// +0x08
	Rva004A9DF3Element m_inline[2];	// +0x0c
};

class Gen_uw_00893e70
{
public:
	void Rva00895340();
};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *test, const char *file, int line);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
// Defined as Rva006E34D0 * by Rva006CC950Mouse.cpp; read here as the pool data.
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

inline void rva006D17F0IteratorCheck(bool, const char *) {}

struct Rva006D17F0Iterator
{
    bool operator!=(const Rva006D17F0Iterator &other) const
    {
        rva006D17F0IteratorCheck(begin == other.begin && end == other.end, "Iterators are not in same range");
        return position != other.position;
    }
    int *&operator*() const
    {
        rva006D17F0IteratorCheck(position >= begin && position < end, "Trying to dereference an invalid iterator");
        return *position;
    }
    int **position;
    int **begin;
    int **end;
    Rva006D17F0Iterator(int **initialPosition, int **rangeBegin, int **rangeEnd) : position(initialPosition), begin(rangeBegin), end(rangeEnd) {}
};

struct BfmeLoadNode
{
	Gen_00895650 *m_value;	// +0x00
	BfmeLoadNode *m_next;	// +0x04
};

class Rva006D17F0Vector
{
public:
    int size() const { return m_count; }
    Rva006D17F0Iterator begin() { return Rva006D17F0Iterator(m_data, m_data, m_data + m_count); }
    Rva006D17F0Iterator end() { return Rva006D17F0Iterator(m_data + m_count, m_data, m_data + m_count); }
    int m_count;
    int m_capacity;
    int **m_data;
    int *m_inline[2];
};

#define SPRITE_ASSERT(cih) do { \
	if (((BfmeAptValue006DCD20 *)(cih))->isUndefined() || \
		(((Rva006DBB30SarDwordField *)(cih))->get() != 0xd && \
		 ((Rva006DBB30SarDwordField *)(cih))->get() != 0x12)) { \
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", \
			"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d); \
		if (g_bfmeAptBreakOnAssertAtDDC01C) \
			__debugbreak(); } } while (0)

class AptValueNameEntry
{
public:
    EAStringC m_name;
    int m_value;
};
typedef AptValueNameEntry PlaybackItem;
inline void iteratorCheck(bool, const char *) {}
class PlaybackIterator
{
    PlaybackItem *cur, *first, *last;
public:
    PlaybackIterator(PlaybackItem *playbackItem, PlaybackItem *rangeBegin, PlaybackItem *rangeEnd) : cur(playbackItem), first(rangeBegin), last(rangeEnd) {}
    PlaybackIterator &operator++() { ++cur; return *this; }
    PlaybackItem &operator*()
    {
        iteratorCheck(cur >= first && cur < last, "Trying to dereference an invalid iterator");
        return *cur;
    }
    bool operator!=(const PlaybackIterator &other)
    {
        iteratorCheck(first == other.first && last == other.last, "Iterators are not in same range");
        return cur != other.cur;
    }
};
class PlaybackRange
{
    PlaybackItem *first, *last;
public:
    PlaybackRange(PlaybackItem *playbackItem, PlaybackItem *lastItem) : first(playbackItem), last(lastItem) {}
    PlaybackIterator begin() { return PlaybackIterator(first, first, last); }
    PlaybackIterator end() { return PlaybackIterator(last, first, last); }
};
class Rva006CEB10Playback
{
public:
    int size, capacity;
    PlaybackItem *items;
    PlaybackItem inlineItems[2];
    PlaybackIterator begin() { return PlaybackRange(items, items + size).begin(); }
    PlaybackIterator end() { return PlaybackRange(items, items + size).end(); }
    __forceinline bool readyFor(int firstAcceptedValue, int secondAcceptedValue)
    {
        for (PlaybackIterator checkpointIterator = begin(); checkpointIterator != end(); ++checkpointIterator)
            if ((*checkpointIterator).m_value != firstAcceptedValue && (*checkpointIterator).m_value != secondAcceptedValue) return false;
        return true;
    }
};

__forceinline void *AptCIH::rva006CFF40() const
{
    SPRITE_ASSERT(this);
    return *(void **)((char *)this + 0x4c);
}

struct Rva006D17F0Record
{
    int value;
    unsigned char kind;
    char text[255];
};

void AptLinker::rva006D17F0()
{
    ((Rva006D0A30List *)g_rva00893030Manager)->rva006D1680();
    if (g_bfmeAptFlagAtE176D4 &&
        !g_aptPlaybackCheckpoints->readyFor(3, 2)) return;

    int pendingCount = pending().size();
    Rva006D17F0Iterator pendingIterator = pending().begin();
    for (;;)
    {
        if (!(pendingIterator != pending().end())) break;
        bool restarted = false;
        Rva008A2BA0Handle element(*(const Rva008A2BA0Handle *)&*pendingIterator);
        for (BfmeLoadNode *loadNode = m_chain; loadNode; loadNode = loadNode->m_next)
        {
            Rva006D17F0ValueHandle owner(loadNode->m_value);
            Gen_00895650 *value = owner.m_value;
            if (((Rva006D0280 *)value->bfmeGet().m_bfmeRef == (Rva006D0280 *)element.m_ref) && value->m_state == 0)
            {
                Rva008A2C80 *animationInstance = new Rva008A2C80(element);
                AptCIH *characterInstance = (AptCIH *)value->m_cih;
                if (Rva006CD220Get() == 0)
                    Rva006CD210Set(((AptCharacterAnimationInst *)animationInstance)->getSwfVersion());
                characterInstance->ClearCIH(1);
                ((BfmeAptValue006DCD20 *)characterInstance)->setTypeAt006DBBC0(0x12);
                *(void **)((char *)characterInstance + 0x4c) = animationInstance;
                ((AptValue *)characterInstance)->setIsDefined(true);
                *(int *)((char *)characterInstance->rva006CFF40() + 0x18) = -1;
                *(int *)((char *)characterInstance->rva006CFF40() + 0x1c) |= 0x1000000;
                characterInstance->rva006E2D60();
                value->m_state = 1;
                if (g_rva00A17754)
                {
                    g_rva00A17754(((Rva006D0280 *)element.m_ref)->name8.rva00620090(),
                        ((EAStringC *)((char *)characterInstance + 8))->rva00620090());
                }
                if (g_rva00891FA0Ready)
                {
                    EAStringC *loadedName = &((Rva006D0280 *)element.m_ref)->name8;
                    unsigned int nameLength = loadedName->rva006D3750();
                    Rva006D17F0Record outgoingRecord;
                    outgoingRecord.value = g_rva00891FA0Value;
                    outgoingRecord.kind = 6;
                    strcpy(outgoingRecord.text, loadedName->rva00620090());
                    Rva00891FA0SendRecord(&outgoingRecord, nameLength + 6);
                }
                if (pendingCount != pending().size())
                {
                    pendingIterator = pending().begin();
                    pendingCount = pending().size();
                    restarted = true;
                    break;
                }
            }
        }
        if (!restarted) ++pendingIterator.position;
    }
    if (g_bfmeAptFlagAtE176D4)
        ((Gen_uw_00893e70 *)g_aptPlaybackCheckpoints)->Rva00895340();
    if (pendingCount > 0)
    {
        ModuleTagString pendingEntries;
        ((ModuleTagString *)&pending())->swap(pendingEntries);
        ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006E6540();
    }
}

// Checked iterators preserve range expressions; owners release on both restart and normal exit.
// Native caller, layouts and full boundary: reverse/attempt_support/aptlinker-006d17f0-w2.md.

// Native6D0D70..6D0F1F RET4 431B; WB1752640 supplies the resource
// release graph and nested handle/string lifetimes. Target proves states
// 1/2/3/4/5, cancel slotE1774C, table14 count28/record2C stride16 and
// named-string recursive release. Lookups82B and contains203B are owned.
// Both explicit reference release and scope teardown are present in native.
// Original resource/container names remain unknown; layouts are narrow
// target views.
class Rva006D1090 {
public:
 void rva006D0D70(void *requestedName);
};
extern AptLinker *g_bfmeAptLinkerAtE176F8;
extern void *g_aptFreeAnimationSlot;

void Rva006D1090::rva006D0D70(void *requestedName) {
 Rva006D07E0Key key=((Rva006D0A30List*)this)->find((const EAStringC*)requestedName);
 if(key.isNull())return;
 int entryType=key.m_object->typeC;
 if(entryType==1){}
 else if(entryType==2){
  if(key.m_object->buffer18)
   ((void(__cdecl*)(void*))g_aptFreeAnimationSlot)(key.m_object->buffer18);
 }else if(entryType==3||entryType==4||entryType==5){
  for(int dependencyIndex=0;dependencyIndex<key.getTable()->count28;++dependencyIndex){
   Rva006D07E0Key dependent=((Rva006D0A30List*)this)->find(
    &EAStringC(key.getTable()->records2c[dependencyIndex].text));
   if(!dependent.isNull() && !((Rva006D07E0List*)g_bfmeAptLinkerAtE176F8)->contains(dependent))
    rva006D0D70(&EAStringC(key.getTable()->records2c[dependencyIndex].text));
  }
 }
 Rva006D0280 *releasedEntry=key.m_object;
 int remainingReferences=releasedEntry->decreaseCount();
 if(remainingReferences==0){
  releasedEntry->~Rva006D0280();
  g_pChainBlockAllocator->freeBlock(releasedEntry,0x1c);
 }
}

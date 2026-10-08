// ?Rva006D05E0Copy@@YAPAVBfmeRefVGO@@URva006D1130Iterator@@0PAV1@@Z
// partial score=0.9 date=2026-10-08
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
class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D0280
{
public:
	void teardown();
	unsigned m_count;
};

struct Rva006D1130Iterator
{
	BfmeRefVGO *position;
	BfmeRefVGO *begin;
	BfmeRefVGO *end;
	Rva006D1130Iterator operator++(int)
	{
		Rva006D1130Iterator previous = *this;
		++position;
		return previous;
	}
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

// 0x006D05E0..0x006D0657: target iterator copy, slot alias guard,
// inline refcount, teardown and 28-byte pool free. BFME1's
// Rva008953C0RefRangeCopy.cpp is the ownership/algorithm guide; its raw
// pointer iterators and free callback differ from these target facts.
BfmeRefVGO *Rva006D05E0Copy(Rva006D1130Iterator first,
 Rva006D1130Iterator last, BfmeRefVGO *result)
{
 for (;;)
 {
  if (first.position == last.position)
   break;
  BfmeRefVGO *destination = result++;
  BfmeRefVGO *source = (first++).position;
  if (source == destination)
   continue;
  Rva006D0280 *release = (Rva006D0280 *)destination->m_bfmeP;
  if (release && --release->m_count == 0)
  {
   release = (Rva006D0280 *)destination->m_bfmeP;
   if (release)
   {
    release->teardown();
    g_pChainBlockAllocator->freeBlock(release, 28);
   }
  }
  destination->m_bfmeP = source->m_bfmeP;
  if (!destination->m_bfmeP)
   continue;
  ++*destination->m_bfmeP;
 }
 return result;
}

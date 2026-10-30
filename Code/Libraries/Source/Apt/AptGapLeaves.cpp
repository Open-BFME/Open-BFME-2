// cl: /O2 /MD
// Small Apt-runtime leaf bodies from .text gaps no Ghidra function covers.
// Retail bytes establish every shape; the owning classes are not recovered,
// so each keeps an address-derived name and a view of only the bits it
// touches. Neighbouring rows (0x006CBC10 getters, 0x006CBD60 clip stack)
// place them in the Apt runtime.

#include <string.h>

// ?set@Rva006CBC20Flag5@@QAEX_N@Z @ 0x006CBC20 (30B): stores a bool into
// bit 5 of the +4 flag word (xor/and/xor bitfield insert).
class Rva006CBC20Flag5
{
public:
	void set(bool value);
private:
	unsigned int m_00;
	unsigned int m_unused0 : 5;
	unsigned int m_flag5 : 1;
};

void Rva006CBC20Flag5::set(bool value)
{
	m_flag5 = value ? 1 : 0;
}

// ?set@Rva006CBDA0Field18@@QAEXH@Z @ 0x006CBDA0 (25B): stores the low two
// bits of an int into bits 18..19 of the +0x5C word.
class Rva006CBDA0Field18
{
public:
	void set(int value);
private:
	char m_pad[0x5C];
	unsigned int m_unused0 : 18;
	unsigned int m_field18 : 2;
};

void Rva006CBDA0Field18::set(int value)
{
	m_field18 = value;
}

// ?set@Rva006E0180Flag16@@QAEXH@Z @ 0x006E0180 (32B): stores a normalised
// int flag into bit 16 of the +0x5C word.
class Rva006E0180Flag16
{
public:
	void set(int value);
private:
	char m_pad[0x5C];
	unsigned int m_unused0 : 16;
	unsigned int m_flag16 : 1;
};

void Rva006E0180Flag16::set(int value)
{
	m_flag16 = value ? 1 : 0;
}

// ?clear@Rva006E3C50Table@@QAEXXZ @ 0x006E3C50 (36B): resets the 16-bit
// count at +0 and zero-fills the +4 slot array over the 16-bit capacity at +2.
#pragma intrinsic(memset)
class Rva006E3C50Table
{
public:
	void clear();
private:
	unsigned short m_count;
	unsigned short m_capacity;
	void **m_slots;
};

void Rva006E3C50Table::clear()
{
	m_count = 0;
	memset(m_slots, 0, m_capacity * sizeof(void *));
}

// ?set@Rva006F6980Bits24@@QAEXH@Z @ 0x006F6980 (31B) and
// ?clear@Rva006F6980Bits24@@QAEXH@Z @ 0x006F69A0 (37B): OR a mask into, or
// mask it out of, the signed 24-bit field at the bottom of the +0x1C word.
class Rva006F6980Bits24
{
public:
	void set(int mask);
	void clear(int mask);
private:
	char m_pad[0x1C];
	int m_bits : 24;
};

void Rva006F6980Bits24::set(int mask)
{
	m_bits |= mask;
}

void Rva006F6980Bits24::clear(int mask)
{
	m_bits &= ~mask;
}

// Two refcounted pointer setters (AddRef slot 0, Release slot 1 of the held
// Apt value). ?set@Rva006FBA20Holder@@QAEXPAVRva006FBA20Ref@@@Z @ 0x006FBA20
// (36B) swaps in the +0x1C pointer first and releases the old one after the
// AddRef; ?set@Rva006FBA70Holder@@QAEXPAVRva006FBA20Ref@@@Z @ 0x006FBA70
// (38B) AddRefs, releases the current +0x10 pointer and then stores.
class Rva006FBA20Ref
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006FBA20Holder
{
public:
	void set(Rva006FBA20Ref *value);
private:
	char m_pad[0x1C];
	Rva006FBA20Ref *m_value;
};

void Rva006FBA20Holder::set(Rva006FBA20Ref *value)
{
	Rva006FBA20Ref *old = m_value;
	m_value = value;
	if (value)
		value->AddRef();
	if (old)
		old->Release();
}

class Rva006FBA70Holder
{
public:
	void set(Rva006FBA20Ref *value);
private:
	char m_pad[0x10];
	Rva006FBA20Ref *m_value;
};

void Rva006FBA70Holder::set(Rva006FBA20Ref *value)
{
	if (value)
		value->AddRef();
	if (m_value)
		m_value->Release();
	m_value = value;
}

// Iterator helpers of an Apt pointer vector {count +0, capacity +4, data +8}
// whose iterators are {position, begin, end} triples returned by value:
// ?begin@Rva006D0350Vector@@QAE?AURva006D0350Iterator@@XZ @ 0x006D0350 (23B),
// ?end@Rva006D0350Vector@@QAE?AURva006D0350Iterator@@XZ @ 0x006D0370 (23B),
// and the iterator's ?advance@Rva006D0350Iterator@@QBE?AU1@H@Z @ 0x006D0170
// (32B) that offsets the position by n slots. Address-derived views.
struct Rva006D0350Iterator
{
	void **position, **begin, **end;
	Rva006D0350Iterator(void **current, void **b, void **e) : position(current), begin(b), end(e) {}
	Rva006D0350Iterator advance(int n) const;
};

class Rva006D0350Vector
{
public:
	Rva006D0350Iterator begin();
	Rva006D0350Iterator end();
private:
	int m_count;
	int m_capacity;
	void **m_data;
};

Rva006D0350Iterator Rva006D0350Vector::begin()
{
	return Rva006D0350Iterator(m_data, m_data, m_data + m_count);
}

Rva006D0350Iterator Rva006D0350Vector::end()
{
	return Rva006D0350Iterator(m_data + m_count, m_data, m_data + m_count);
}

Rva006D0350Iterator Rva006D0350Iterator::advance(int n) const
{
	return Rva006D0350Iterator(position + n, begin, end);
}

// ?Rva006CE180Release@@YA_NPAURva006CE180Block@@@Z @ 0x006CE180 (53B): notes whether a
// refcounted block's +0xC kind is 4, then drops one reference through the
// rowed decrement 0x006CFDF0 and frees it through the rowed 0x006D0440 when
// that was the last; returns the note.
int Rva006CFDF0DecRef(int *refCount);
void bfmeDropVGO(void *block);
struct Rva006CE180Block
{
	int refs;
	int pad[2];
	int kind;
};
bool Rva006CE180Release(Rva006CE180Block *block)
{
	bool wasKind4 = block && block->kind == 4;
	if (block && !Rva006CFDF0DecRef(&block->refs))
		bfmeDropVGO(block);
	return wasKind4;
}

// ?isSet@Rva006DAE30Table@@QAE_NI@Z @ 0x006DAE30 (26B): whether the slot for
// a dword-aligned key (key >> 2) in the +0 table is non-null.
class Rva006DAE30Table
{
public:
	bool isSet(unsigned int key);
private:
	void **m_slots;
};

bool Rva006DAE30Table::isSet(unsigned int key)
{
	return m_slots[key >> 2] != 0;
}

// ?set@Rva006E0060Flags@@QAEXI@Z @ 0x006E0060 (15B), ?clear@...@QAEXI@Z
// @ 0x006E0070 (17B) and ?test@...@QBEII@Z @ 0x006E0090 (10B): OR a mask
// into, AND its complement out of, and AND a mask against the +0x10 flag
// word, the three adjacent RET4 leaves after the AptMath clip stack.
class Rva006E0060Flags
{
public:
	void set(unsigned int mask);
	void clear(unsigned int mask);
	unsigned int test(unsigned int mask) const;
private:
	char m_pad[0x10];
	unsigned int m_flags;
};

void Rva006E0060Flags::set(unsigned int mask)
{
	m_flags |= mask;
}

void Rva006E0060Flags::clear(unsigned int mask)
{
	m_flags &= ~mask;
}

unsigned int Rva006E0060Flags::test(unsigned int mask) const
{
	return m_flags & mask;
}

// ?release@Rva006E3200Owner@@QAEXXZ @ 0x006E3200 (10B): hands the +0 block
// to the rowed array free Rva006CD460Free (0x006CD460).
void Rva006CD460Free(void *);
class Rva006E3200Owner
{
public:
	void release();
private:
	void *m_block;
};

void Rva006E3200Owner::release()
{
	Rva006CD460Free(m_block);
}

// ?isValue@Rva006E3210Field@@QBEHH@Z @ 0x006E3210 (19B): compares the
// argument with the +8 word.
class Rva006E3210Field
{
public:
	int isValue(int value) const;
private:
	int m_0, m_4, m_8;
};

int Rva006E3210Field::isValue(int value) const
{
	return value == m_8;
}

// ??_GRva006E00B0Triple@@QAEPAXI@Z @ 0x006E00B0 (40B): scalar deleting
// destructor of a 0x1C-byte chain-pool object whose destructor clears its
// first three words.
class Rva006DB270 {public:void freeBlock(void *, int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006E00B0Triple
{
public:
	~Rva006E00B0Triple() { m_0 = 0; m_4 = 0; m_8 = 0; }
	static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocator->freeBlock(p, n); }
private:
	int m_0, m_4, m_8;
	char m_pad[0x1C - 12];
};
// The delete helper only makes the compiler emit the deleting destructor.
// ?deleteRva006E00B0Triple absent-from-retail
void deleteRva006E00B0Triple(Rva006E00B0Triple *p) { delete p; }


// ?rva006D0410@Rva006D0410Table@@QAE_NXZ @0x006D0410 44B.
// Same skeleton as Apt.cpp's Rva006CEB10Playback::ready (0x006CE7A0, kinds
// 4/2): true unless some 8-byte entry (count +0, data +8, kind +4) has a kind
// other than 3 or 2. Retail's unrotated top-tested loop comes from the same
// checked iterator/range pair (empty range checks) the twin uses.
struct Rva006D0410Entry { int m_name; int m_kind; };
inline void rva006D0410Check(bool, const char *) {}
class Rva006D0410Iterator {
 Rva006D0410Entry *cur, *first, *last;
public:
 Rva006D0410Iterator(Rva006D0410Entry *c, Rva006D0410Entry *f, Rva006D0410Entry *l) : cur(c), first(f), last(l) {}
 Rva006D0410Iterator &operator++() { ++cur; return *this; }
 Rva006D0410Entry &operator*() { rva006D0410Check(cur >= first && cur < last, "Trying to dereference an invalid iterator"); return *cur; }
 bool operator!=(const Rva006D0410Iterator &other) { rva006D0410Check(first == other.first && last == other.last, "Iterators are not in same range"); return cur != other.cur; }
};
class Rva006D0410Range {
 Rva006D0410Entry *first, *last;
public:
 Rva006D0410Range(Rva006D0410Entry *f, Rva006D0410Entry *l) : first(f), last(l) {}
 Rva006D0410Iterator begin() { return Rva006D0410Iterator(first, first, last); }
 Rva006D0410Iterator end() { return Rva006D0410Iterator(last, first, last); }
};
class Rva006D0410Table {
public:
 int size, capacity; Rva006D0410Entry *items;
 Rva006D0410Iterator begin() { return Rva006D0410Range(items, items + size).begin(); }
 Rva006D0410Iterator end() { return Rva006D0410Range(items, items + size).end(); }
 __forceinline bool readyFor(int a, int b) {
  for (Rva006D0410Iterator it = begin(); it != end(); ++it)
   if ((*it).m_kind != a && (*it).m_kind != b) return false;
  return true;
 }
 bool rva006D0410();
};
bool Rva006D0410Table::rva006D0410() { return readyFor(3, 2); }

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME2 PartitionFilterRejectByKindOf::allow, retail RVA 0x0026115D (25B).
// Dedicated TU shares the constructor provider's measured three-slot base
// and two 28-byte masks. Retail reads Set at +0x8 and Clear at +0x24 and the
// isKindOfMulti core at 0x30A142 loops 7 dwords, so BFME2 masks are 28 bytes.
// The BFME1 sibling (PartitionFilterRejectByKindOf.cpp) uses the same
// this-relative cast idiom with ITS offsets (+0x08/+0x20); the offsets here
// are BFME2 retail immediates. Callees resolve by name (isKindOfMulti pin).

typedef bool Bool;

template<int NUM_BITS>
class BitFlags
{
public:
	// Retail-measured: 7 words (isKindOfMulti core compares 7 dwords).
	// The template argument keeps the ?$BitFlags@$0HE mangling.
	unsigned int m_words[7];
};

class Thing
{
public:
	Bool isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const;
};

class Object : public Thing
{
};

class Object;
class Rva000421C8 {
public:
 Rva000421C8() : m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object *) = 0;
 virtual int getPlayerMask() { return -1; }
 Rva000421C8 *m_next;
};
class BfmeFixedStorage0004543D {
 char m_bytes[28];
public:
 __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
class PartitionFilterRejectByKindOf : public Rva000421C8 {
public:
 PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &,const BfmeFixedStorage0004543D &);
 __declspec(noinline) virtual ~PartitionFilterRejectByKindOf();
 virtual bool allow(Object *);
private:
 BfmeFixedStorage0004543D m_08,m_24;
};

Bool PartitionFilterRejectByKindOf::allow(Object *objOther)
{
	const BitFlags<116> &mustBeSet = *(const BitFlags<116> *)((const char *)this + 0x08);
	const BitFlags<116> &mustBeClear = *(const BitFlags<116> *)((const char *)this + 0x24);
	return !objOther->isKindOfMulti(mustBeSet, mustBeClear);
}

// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// Two partition-filter variants with measured 28-byte set/clear storage.
// Retail BC2908 and C071D8 have the same three-slot base: deleting dtor
// 395A19, each filter's predicate, and inherited all-players mask 36CC7A.
// Both deleting dtors call the seven-byte base-vptr reset at 0x0049C38A.
// Keep that call outlined; inline definitions share identical COMDAT copies
// emitted by other views (including CurseSpecialPowerSlots.cpp).
// The classes retain their constructor addresses; their original names are
// unproven. The base interface is corroborated by 0x000421C8/0x000421D5 and the native
// filter chain. ZH PartitionFilterAcceptByKindOf is the semantic lead for
// the 20B predicate; target establishes two 28B fields at +0x08/+0x24 and callees.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();

private:
	unsigned char m_bytes[28];
};

class Object;
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask() { return -1; }
	Rva000421C8 *m_next;
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	__declspec(noinline) virtual ~Rva0004584D();
	virtual bool allow(Object *);

private:
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// ??0Rva0004584D@@QAE@ABVBfmeFixedStorage0004543D@@0@Z
Rva0004584D::Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b)
	: m_08(a)
	, m_24(b)
{
}

// The sibling constructor at 0x002FDF47 installs VA 0x00C071D8. Its
// predicate differs, while the two destructor entries and inherited mask
// have the same retail targets as the first filter.

class Rva002FDF47 : public Rva000421C8
{
public:
	Rva002FDF47(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	__declspec(noinline) virtual ~Rva002FDF47();
	virtual bool allow(Object *obj);
private:
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

Rva002FDF47::Rva002FDF47(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b)
	: m_08(a)
	, m_24(b)
{
}

// The one-mask sibling installs C1A25C. Native slot 1 is 2610F2;
// ctor 3959FA copies one 28-byte mask at +8 and returns at 395A19.
class Rva003959FA : public Rva000421C8 {
public:
 Rva003959FA(const BfmeFixedStorage0004543D &);
 __declspec(noinline) virtual ~Rva003959FA();
 virtual bool allow(Object *);
 BfmeFixedStorage0004543D m_08;
};
Rva003959FA::Rva003959FA(const BfmeFixedStorage0004543D &mask) : m_08(mask) {}
inline Rva003959FA::~Rva003959FA() {}

template<int N>
class BitFlags
{
public:
	unsigned int m_bits[7];
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
	bool isKindOfMulti(const BitFlags<116> &, const BitFlags<116> &) const;
};

class Object : public Thing
{
};

// ?allow@Rva002FDF47@@UAE_NPAVObject@@@Z @0x00261102 46B slot 1 of
// vtable VA 0xc071d8. First mask at +0x24, second at +0x08 via FixedStorage
// reinterpreted as BitFlags<69>. Callers none rowed. Donor is the same TU
// shape with two 28B storages. Identity beyond the slot and masks is unproven
// so the method name stays honest address-derived.

bool Rva002FDF47::allow(Object *obj)
{
	const BitFlags<69> &mask1 = *(const BitFlags<69> *)&m_24;
	if (obj->isAnyKindOf(mask1))
		return true;
	const BitFlags<69> &mask2 = *(const BitFlags<69> *)&m_08;
	return !obj->isAnyKindOf(mask2);
}


inline Rva0004584D::~Rva0004584D() {}
inline Rva002FDF47::~Rva002FDF47() {}
bool Rva0004584D::allow(Object *obj)
{
	return obj->isKindOfMulti(*(const BitFlags<116> *)&m_08, *(const BitFlags<116> *)&m_24);
}

bool Rva003959FA::allow(Object *obj) {
 return obj->isAnyKindOf(*(const BitFlags<69> *)&m_08);
}

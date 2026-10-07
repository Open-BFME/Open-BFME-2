// cl: /Ob0

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

class BfmeWideResultSource
{
public:
	BfmeWideResult bfmeMakeWideResult(int a, int b, int c, int d, int e, int f);
};

class BfmeWideForwardB
{
	char m_pad[0x10];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideB(int a, int b, int c, int d);
};

struct Coord3D;
class Object;

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0): filters
// chain through +0x04 and the partition manager's queries walk the chain.
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);
	Rva000421C8 *m_next;
};

// The partition manager's range-query implementation behind +0x10
// (0x00628770): position, radius, 0, distance type, filter chain, order.
class Rva00628770Impl
{
public:
	BfmeWideResult rva00628770(const Coord3D *pos, float radius, int zero, int distType,
		Rva000421C8 *filters, int order);
};

// ThePartitionManager (0x00DFE748): 44 matched callers reference this
// method by name with a const Coord3D *, a float radius, a distance type,
// the filter chain and an iteration order.
class PartitionManager
{
	char m_pad[0x10];
	Rva00628770Impl *m_impl;

public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distType,
		Rva000421C8 *filters, int order);
};

class BfmeWideForward009F29A0
{
	char m_pad[0x10];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult forward009F29A0(int a, int b, int c);
};

BfmeWideResult PartitionManager::iterateObjectsInRange(const Coord3D *pos, float radius,
	int distType, Rva000421C8 *filters, int order)
{
	return m_impl->rva00628770(pos, radius, 0, distType, filters, order);
}

BfmeWideResult BfmeWideForward009F29A0::forward009F29A0(int a, int b, int c)
{
	return m_source->bfmeMakeWideResult(0, 0, a, b, 0, c);
}

BfmeWideResult BfmeWideForwardB::bfmeForwardWideB(int a, int b, int c, int d)
{
	return m_source->bfmeMakeWideResult(0, 0, a, b, c, d);
}

// Appends `next` at the tail of this filter's +0x04 chain and returns this,
// so callers build a chain inline: a.link(&b)->link(&c). 66 matched callers
// reference it (pin 0x00625790).
Rva000421C8 *Rva000421C8::link(Rva000421C8 *next)
{
	Rva000421C8 *x;
	for (x = this; x->m_next != 0; x = x->m_next)
		;
	x->m_next = next;
	return this;
}

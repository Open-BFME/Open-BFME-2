// cl: /DNDEBUG /MD /EHsc
// ?rva0050B519@Made002CCB04@@QAEXPAX0@Z @0x0050B519 130B
// Partition query then per-object rva0050B479: max(m_12C global) range via SSE, native range query 0x6255D0 with (b range 3 0), EOF loop calling rowed 0x0050B479. Evidence: vtable slot 6 of 0x00864D10, members 0x12C in Ctor, globals g_Va00BBB8D8 plus ThePartitionManager, callees rowed Forward plus EOF plus rva plus WideResult dtor, chain from 0x0050B479.
extern float g_Va00BBB8D8;
class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Object;

#include "../../Common/PartitionRangeQueryCallView.h"

class Object;
class Made002CCB04
{
public:
	virtual ~Made002CCB04();
	virtual bool check(void *a, void *b);
	void rva0050B479(void *a, Object *b);
	void rva0050B519(void *a, void *b);
private:
	char m_pad[0x128 - 4];
	int m_128;
	float m_12C;
	unsigned int m_130;
};

void Made002CCB04::rva0050B519(void *a, void *b)
{
	float range = (m_12C > g_Va00BBB8D8) ? m_12C : g_Va00BBB8D8;
	BfmeWideResult iterator = ThePartitionManager->rva006255D0((const Coord3D *)b, range, 3, 0);
	for (void *other = iterator.next(); other; other = iterator.next())
		rva0050B479(a, (Object *)other);
}

// Separate retail receiver: 0050921D reads a float at +128, unlike the
// Made002CCB04 neighbour's +12C. Its vtable slot +4 filters each result
// before the direct 00508FA8 call with the same receiver and two arguments.
// WB's unnamed twin corroborates those calls and the range-query purpose;
// it does not establish a class or method name.
class Rva00508FA8
{
public:
	virtual ~Rva00508FA8();
	virtual bool check(void *a, Object *b);
	void rva00508FA8(void *a, Object *b);
	void rva0050921D(void *a, void *b);
private:
	char m_pad04[0x128 - 4];
	float m_range128;
};

// Native 0050921D..005092B2 (149 bytes), thiscall ret 8.
void Rva00508FA8::rva0050921D(void *a, void *b)
{
	float range = (m_range128 > g_Va00BBB8D8) ? m_range128 : g_Va00BBB8D8;
	BfmeWideResult iterator = ThePartitionManager->rva006255D0((const Coord3D *)b, range, 3, 0);
	for (void *other = iterator.next(); other; other = iterator.next())
		if (check(a, (Object *)other))
			rva00508FA8(a, (Object *)other);
}

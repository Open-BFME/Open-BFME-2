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

// cl: /O1 /MD /EHsc /DNDEBUG
// ?rva002B35F7@Rva002BA8F1Logic@@QAEXXZ @0x002B35F7 42B: Rva002BA8F1Logic method
// forwarding item +0x98 int with float g_00BCEAFC to rowed RadarWindowOverrideSource::rva002D3772.
// Evidence: caller 0x002B4D6B passes this in ecx; callee 0x002B2B2D pin-only returns
// Rva002B3740Item; callee 0x002D3772 rowed; globals theRadarWindowOverrideSource and g_00BCEAFC.

struct Rva002B3740Item
{
	char m_pad[0x98];
	int m_98;
};

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();
	void rva002B35F7();
};

class RadarWindowOverrideSource
{
public:
	void rva002D3772(int a, float b);
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern float g_00BCEAFC;

void Rva002BA8F1Logic::rva002B35F7()
{
	Rva002B3740Item *item = rva002B2B2D();
	if (!item)
		return;
	int v = item->m_98;
	if (v <= 0)
		return;
	theRadarWindowOverrideSource->rva002D3772(v, g_00BCEAFC);
}

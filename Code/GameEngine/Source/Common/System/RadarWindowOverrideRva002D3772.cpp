// cl: /O1 /arch:SSE
// ?rva002D3772@RadarWindowOverrideSource@@QAEXHM@Z retail 0x002D3772 65 bytes. RadarWindowOverrideSource setter allocating an 8-byte pair then forwarding to rowed Rva002D3389 at inner+0xEC. Evidence: caller 0x002B361B passes int plus float from 0x00BCEAFC with this equal theRadarWindowOverrideSource; callee 0x002D3389 rowed.
void *__cdecl operator new(unsigned int);

class Rva002D3389
{
public:
	void rva002D3389(void *p);
};

extern int g_009BA4E8;

struct Rva002D3772Pair
{
	Rva002D3772Pair(int a, float b);
	int m_scaled;
	int m_arg;
};

// ??0Rva002D3772Pair@@QAE@HM@Z present-unmatched
inline Rva002D3772Pair::Rva002D3772Pair(int a, float b)
{
	m_scaled = (int)((float)g_009BA4E8 * b);
	m_arg = a;
}

class RadarWindowOverrideSource
{
public:
	void rva002D3772(int a, float b);
private:
	char m_pad[0x10];
	char *m_inner;
};

void RadarWindowOverrideSource::rva002D3772(int a, float b)
{
	Rva002D3772Pair *p = new Rva002D3772Pair(a, b);
	((Rva002D3389 *)(m_inner + 0xEC))->rva002D3389(p);
}

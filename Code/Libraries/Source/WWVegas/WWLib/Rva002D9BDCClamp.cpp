// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D9BDC@Rva002D9BDC@@QAEXMM@Z @ 0x002D9BDC 43B
// Evidence: honest address method; thiscall void(float float) ret 8; member float at +0x64 clamped via rowed clamp<float>(lo val hi); callers at 0x0005AAC2 0x0005D60F; neighbours AsciiStringRvoGetters and Rva002D9C2FAssign.
template <class NUM>
NUM clamp(NUM lo, NUM val, NUM hi);

class Rva002D9BDC
{
	char m_pad[0x64];
	float m_64;

public:
	void rva002D9BDC(float lo, float hi);
};

void Rva002D9BDC::rva002D9BDC(float lo, float hi)
{
	m_64 = clamp(lo, m_64, hi);
}

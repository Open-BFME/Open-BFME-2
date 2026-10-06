// cl: /EHsc /DNDEBUG /MD
//
// ?rva004DD843@Rva004DD843@@QAEMXZ @ 0x004DD843 (10B).
// Thiscall float getter forwarding int at +0x24 through rowed
// ?Rva004DD722Get@@YAMH@Z at 0x004DD722. Evidence: caller at 0x0028AD67;
// prev/next both /O1.
// ?rva004DE511@Rva004DD843@@QAEXHH@Z @ 0x004DE511 (27B).
// Target bytes end in ret 8 at 0x004DE52B; the next function starts at
// 0x004DE52C. The existing pin and Object forwarder identify the receiver
// as this subobject; the target reads +0x24, converts it through 0x004DD722,
// then forwards (int, float, int) to pinned 0x004DE109. Function identity
// remains address-derived.

// The matched multiplier operand places this scalar at VA 0x00C52AD4.
// Its four initialized bytes (92 0A 06 3F) match BFME2 retail; retain the
// existing declaration's writable storage without inferring a retail owner.
float g_integerToFloatScale = 0.52359879f;

__declspec(noinline) float __cdecl Rva004DD722Get(int value)
{
	if (value == 0)
		return 0.0f;
	return (float)value * g_integerToFloatScale;
}

class Rva004DD843
{
public:
	float rva004DD843();
	void rva004DE109(int first, float value, int last);
	void rva004DE511(int first, int last);
private:
	unsigned char m_pad[0x24];
	int m_x24;
};

float Rva004DD843::rva004DD843()
{
	return Rva004DD722Get(m_x24);
}

void Rva004DD843::rva004DE511(int first, int last)
{
	rva004DE109(first, Rva004DD722Get(m_x24), last);
}

// cl: /DNDEBUG /MD
// ?rva0028F528@Rva0028F528@@QAEHXZ @ 0x0028F528 52B: dword SWAR popcount of
// m_bits[0]; same fold as BitFlags<11>::countIntersection tail in neighbour
// BitFlagsCountIntersection.cpp. Unblocks 0x002907A1 0x00292414 0x00318871 0x004BE781.
class Rva0028F528
{
public:
	int rva0028F528();
private:
	unsigned m_bits;
};

int Rva0028F528::rva0028F528()
{
	unsigned v = m_bits;
	v = v - ((v >> 1) & 0x55555555u);
	v = (v & 0x33333333u) + ((v >> 2) & 0x33333333u);
	v = (v + (v >> 4)) & 0x0F0F0F0Fu;
	return (int)((v * 0x01010101u) >> 24);
}

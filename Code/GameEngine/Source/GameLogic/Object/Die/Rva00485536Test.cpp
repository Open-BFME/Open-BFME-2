// cl: /MD
//
// ?Rva00485536Test@@YG_NPAX0@Z, retail 0x00485536 47B: null-checked BitFlags testSetAndClear gate.
// Evidence: free function ret 8 with rowed testSetAndClear 0x0030A146 plus g_defaultStorage009FEFA4 0x009FEFA4; offsets +0x1C/+0x108; caller 0x004857B3.

template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
private:
	unsigned m_words[7];
};

class BfmeFixedStorage0004543D
{
private:
	unsigned char m_bytes[28];
};

extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

bool __stdcall Rva00485536Test(void *a, void *b)
{
	if (b == 0)
		return false;
	const BitFlags<116> *pSet = (const BitFlags<116> *)((char *)a + 0x1c);
	const BitFlags<116> *pClear = (const BitFlags<116> *)&g_defaultStorage009FEFA4;
	return ((const BitFlags<116> *)((char *)*(void *const *)((char *)b + 4) + 0x108))->testSetAndClear(*pSet, *pClear) ? true : false;
}

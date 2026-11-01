// Another two-member swap (trimmed from a five-body donor; the other four
// are declared-only here).

inline void bfmeSwapIntCT(int *first, int *second)
{
	int value = *first;

	*first = *second;
	*second = value;
}

class Gen_00350E60
{
public:
	void bfmeSwap(Gen_00350E60 *other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

// ?bfmeSwap@Gen_00350E60@@QAEXPAV1@@Z
void Gen_00350E60::bfmeSwap(Gen_00350E60 *other)
{
	bfmeSwapIntCT(&m_bfmeFirst, &other->m_bfmeFirst);
	bfmeSwapIntCT(&m_bfmeSecond, &other->m_bfmeSecond);
}




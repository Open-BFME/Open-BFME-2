// cl: /O1 /MD /DNDEBUG
// ?rva001B2DC4@Rva001B2DC4@@QAEII@Z RVA 0x001B2DC4 104B
// Target evidence: count at +0x0C and a pointer to 16-bit ordered values at
// +0x14. The body masks bit 15 and returns the greatest index whose value is
// not greater than the unsigned key. Ghidra bounds the body at 104 bytes;
// callers and the owning class identity remain unknown, so the names are
// address-derived and this view records only offsets used by this body.

class Rva001B2DC4
{
public:
	unsigned int rva001B2DC4(unsigned int key);

private:
	unsigned char m_pad00[0x0C];
	int m_count;
	unsigned char m_pad10[4];
	const unsigned short *m_values;
};

// ?rva001B2DC4@Rva001B2DC4@@QAEII@Z
unsigned int Rva001B2DC4::rva001B2DC4(unsigned int key)
{
	const int mask = ~0x8000;
	const unsigned short *values = m_values;
	if (key <= (values[0] & mask))
		return 0;

	unsigned int count = m_count;
	if (key >= (values[count - 1] & mask))
		return count - 1;

	int low = 0;
	int high = (int)count - 2;
	for (;;) {
		int middle = (high + low) / 2;
		if (key < (values[middle] & mask)) {
			high = middle;
		} else if (key >= (values[middle + 1] & mask)) {
			if ((middle ^ low) != 0)
				low = middle;
			else
				++low;
		} else {
			return (unsigned int)middle;
		}
	}
}

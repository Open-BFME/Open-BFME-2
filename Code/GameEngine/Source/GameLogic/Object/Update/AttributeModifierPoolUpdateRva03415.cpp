// cl: /DNDEBUG /MD
// ?rva00403415@AttributeModifierPoolUpdate@@QAEXPAHH@Z @0x00403415 51B
// Conditional 15-dword fill at this+0x30: for each i in 0..14, if bit i of the
// mask is set, store value. Evidence: caller at 0x00484A49 passes the pool
// from findAttributeModifierPoolUpdate as this, a mask at esi+0x2c and an int
// value; 4 more callers; 15 matches m_poolCounts[15] in the ctor TU.
class AttributeModifierPoolUpdate
{
public:
	void rva00403415(int *mask, int value);

private:
	char _pad[0x30];
	int m_30[15];
};

void AttributeModifierPoolUpdate::rva00403415(int *mask, int value)
{
	for (unsigned int i = 0; i < 15; ++i)
	{
		if (mask[i >> 5] & (1 << (i & 31)))
			m_30[i] = value;
	}
}

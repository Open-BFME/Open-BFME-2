// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AABEE@Rva002AABEE@@QAEXXZ @0x002AABEE (64B): refresh the current
// value (+0x20) from a per-level float table (vector at +8) for the level at
// +4, clamped to the last entry; level 0 gives 0. The record is built by the
// unclaimed ctor 0x002AF581 (AsciiString +0, level +4, the +8 table through
// the folded vector<unsigned int> copy ctor, an AsciiString vector at +0x14,
// +0x20 zeroed, then this call); also called from 0x002B0E55 and 0x002B212A.
// Retail compares level-1 against size-1 in min(size-1, level-1) argument
// order. Names are address-derived.
#include <vector>
#include <algorithm>

class Rva002AABEE
{
public:
	void rva002AABEE();

private:
	void *m_name;
	unsigned int m_level;
	_STL::vector<float> m_values;
	char m_pad14[0xC];
	float m_value;
};

void Rva002AABEE::rva002AABEE()
{
	if (m_level == 0)
	{
		m_value = 0.0f;
		return;
	}
	unsigned int index = m_level - 1;
	unsigned int last = m_values.size() - 1;
	const unsigned int &bound = index < last ? index : last;
	m_value = m_values[bound];
}

// cl: /DNDEBUG /MD
// stlport
// ?rva0043D3A8@Rva0043D3A8@@QAEXXZ @0x0043D3A8 22B
// Clears the +0x08 Science vector via full-range erase then zeroes +0x14.
// Evidence: retail calls rowed vector<ScienceType>::erase @0x00532803 with
// begin/end from +0x08; caller @0x0043D3DA passes outer+0x288 as this;
// and [esi+0x14],0 is the /O1 zero-store idiom.
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class Rva0043D3A8
{
public:
	void rva0043D3A8();

private:
	char m_unk0[8];
	_STL::vector<ScienceType> m_sciences;
	int m_unk14;
};

void Rva0043D3A8::rva0043D3A8()
{
	m_sciences.clear();
	m_unk14 = 0;
}

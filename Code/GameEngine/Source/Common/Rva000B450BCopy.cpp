// cl: /DNDEBUG /MD
// ??4Rva000B690BRecord@@QAEAAU0@ABU0@@Z @0x000B450B 33B
// Assignment of the 0x18-byte record that _STL::__copy at 0x000B690B
// (StlHelperRva000B690B.cpp) copies element by element: the record at +0 is
// assigned via the rowed ??4BfmeRecord000B43E5 (0x000B43E5: three dwords, a
// byte, then AsciiString set), the member at +0x14 via the rowed
// ??4Rva000B3F15; returns this. Memberwise operator=, not a copy ctor: the
// +0 callee assigns its AsciiString through StringBase::set rather than
// constructing it.
#include "../../Include/Common/BfmeRecord000B43E5.h"

class Rva000B3F15
{
public:
	Rva000B3F15 &operator=(const Rva000B3F15 &other);
private:
	void *m_ptr;
};

struct Rva000B690BRecord
{
	Rva000B690BRecord &operator=(const Rva000B690BRecord &other);
private:
	BfmeRecord000B43E5 m_record;
	Rva000B3F15 m_other;
};

Rva000B690BRecord &Rva000B690BRecord::operator=(const Rva000B690BRecord &other)
{
	m_record = other.m_record;
	m_other = other.m_other;
	return *this;
}

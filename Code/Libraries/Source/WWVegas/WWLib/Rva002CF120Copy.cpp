// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002CF120@@QAE@ABU0@@Z @0x002CF120 27B.
// Small copy ctor: copy-constructs the leading BfmeObject872Header through
// the rowed 0x002CF108, copies the dword at +0x10, returns this in eax with
// ret 4. Same return-this shape as the rowed 0x002CF380 copy ctor tail.
// Owner class unproven: honest Rva dummy holder with a real Header first
// member (cf. Rva005E7198 precedent); the Header ctor is declared only via
// Object872.h so the call stays external. Caller at 0x002CF368.
#include "Object872.h"

struct Rva002CF120
{
	BfmeObject872Header m_header;
	int m_field10;
	Rva002CF120(const Rva002CF120 &other);
};

Rva002CF120::Rva002CF120(const Rva002CF120 &other) : m_header(other.m_header)
{
	m_field10 = other.m_field10;
}

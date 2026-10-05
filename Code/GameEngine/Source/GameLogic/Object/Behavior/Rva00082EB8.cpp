// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00082EB8@Rva00082EB8@@QAEXABURva00082EB8Rec@@@Z @0x00082EB8 61B: Vector find-or-insert by compareNoCase with assign-or-push_back. Evidence: linkbody lane plus 20 callers plus compare-assign-push_back shape plus 0x24 stride.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>
struct Rva0007BB16Record { char m_pad[36]; public: Rva0007BB16Record(const Rva0007BB16Record &); ~Rva0007BB16Record(); };
struct BfmeAssignRecord36 { BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &rhs); };
struct Rva00082EB8Rec { AsciiString m_key; char m_pad[32]; };
class Rva00082EB8 {
public:
	void rva00082EB8(const Rva00082EB8Rec &rec);
private:
	Rva00082EB8Rec *m_begin;
	Rva00082EB8Rec *m_end;
};
void Rva00082EB8::rva00082EB8(const Rva00082EB8Rec &rec)
{
	Rva00082EB8Rec *p = m_begin;
	for (; p != m_end; ++p) {
		if (p->m_key.compareNoCase(rec.m_key) == 0)
			break;
	}
	if (p != m_end)
		*(BfmeAssignRecord36 *)p = *(const BfmeAssignRecord36 *)&rec;
	else
		(( _STL::vector<Rva0007BB16Record> *)this)->push_back(*(const Rva0007BB16Record *)&rec);
}

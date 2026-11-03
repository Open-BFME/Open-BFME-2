// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva002E2F39@Rva002E2F39@@QAEXABURva002E2D10Record@@@Z 0x002E2F39 11: tail-forwards to vector push_back.
// Evidence: rowed push_back 0x002E2D10 plus caller 0x0037EB3C.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// The record is the rowed UnitRevivalEntry (copy ctor 0x002E134C); the
// address-derived name is only a view. Forward to the real body so _Construct
// binds the canonical symbol instead of an undefined address-named twin.
#include "../../Include/GameLogic/UnitRevivalEntry.h"
struct Rva002E2D10Record
{
	Rva002E2D10Record();
	__declspec(dllimport) __forceinline Rva002E2D10Record(const Rva002E2D10Record &that)
	{
		((UnitRevivalEntry *)this)->UnitRevivalEntry::UnitRevivalEntry(*(const UnitRevivalEntry *)&that);
	}
	~Rva002E2D10Record();
	Rva002E2D10Record&operator=(const Rva002E2D10Record&);
private:
	char bytes[216];
};

class Rva002E2F39
{
private:
	char m_pad[0x1A8];
	_STL::vector<Rva002E2D10Record> m_vec;
public:
	void rva002E2F39(const Rva002E2D10Record &x);
};

void Rva002E2F39::rva002E2F39(const Rva002E2D10Record &x)
{
	return m_vec.push_back(x);
}

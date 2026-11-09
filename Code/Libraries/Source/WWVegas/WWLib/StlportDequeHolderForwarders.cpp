// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Unreferenced holders of an STLport deque at +0 whose members tail-jump
// into the rowed deque bodies; declaration-only specialisations keep those
// calls out of line, as retail does. Element spellings are copied from the
// rowed units; the owners are address-derived.
//   0x000581F0 (5B)  holder destructor -> ~deque<Rva00056DEBElement> 0x000579DE
//   0x000554F0 (5B)  back()            -> deque<Rva003B5603Element>::back 0x003B5603
#include <deque>
#include <string>

struct Rva00056DEBElement { char bytes[1]; ~Rva00056DEBElement(); bool operator<(const Rva00056DEBElement&)const; bool operator==(const Rva00056DEBElement&)const; };
// 4 bytes in retail: this deque's _M_decrement is 0x003B3EA8, a 0x80-byte node stepped by -4.
struct Rva003B5603Element { void *value; bool operator<(const Rva003B5603Element&)const; bool operator==(const Rva003B5603Element&)const; };

namespace _STL {
template <> deque<Rva00056DEBElement>::~deque();
template <> Rva003B5603Element &deque<Rva003B5603Element>::back();
}

class Rva000581F0
{
public:
	~Rva000581F0();
private:
	_STL::deque<Rva00056DEBElement> m_00;
};

Rva000581F0::~Rva000581F0()
{
}

class Rva000554F0
{
public:
	Rva003B5603Element &rva000554F0();
private:
	_STL::deque<Rva003B5603Element> m_00;
};

Rva003B5603Element &Rva000554F0::rva000554F0()
{
	return m_00.back();
}

// 0x00056B34 (5B): pop() of a holder of deque<OpaqueRefElement4> (the
// stack-over-deque shape) -> the rowed pop_back 0x0005555F.
#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"
namespace _STL {
template <> void deque<OpaqueRefElement4>::pop_back();
}

class Rva00056B34
{
public:
	void rva00056B34();
private:
	_STL::deque<OpaqueRefElement4> m_00;
};

void Rva00056B34::rva00056B34()
{
	m_00.pop_back();
}

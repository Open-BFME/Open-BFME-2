// cl: /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva005961D6@@UAE@XZ retail 0x00596225 68B
// Own vptr C70A4C; the owned buffer at +0x98 is freed when set (EH state 0),
// then the rowed base dtor ??1Rva0025BFE3@@UAE@XZ 0x0025BFE3. Caller: the
// slot-0 ??_G 0x005962CB. Names address-derived.

#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"

class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();

private:
	_STL::vector<BfmeE16> m_vec04;
};

class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement();
};

class Rva005961D6 : public Rva0025BFE3
{
public:
	virtual ~Rva005961D6();
	Rva005961D6();
	void rva00596269();

private:
	Rva003ECA4BElement m_e10;
	char m_pad11[0x43];
	Rva003ECA4BElement m_e54;
	char m_pad55[0x43];
	_STL::vector<BfmeE16> m_vec98;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva005961D6::~Rva005961D6()
{
}

// ?bfmeAnchorRva005961D6Dtor absent-from-retail
void bfmeAnchorRva005961D6Dtor(Rva005961D6 *p)
{
	p->Rva005961D6::~Rva005961D6();
}

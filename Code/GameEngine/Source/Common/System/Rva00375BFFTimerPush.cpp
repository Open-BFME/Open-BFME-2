// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00375BFF@Rva00375BFF@@QAEXIM@Z @0x00375BFF 41B conditional timer push to list at +0x10 via rowed list<BfmeSpecialPowerTimer8>::push_back 0x004DE74D.
// Evidence: null-checked first word plus movss float second word assembled into 8B record; caller 0x00201042 in 0x00200EE4 tail; honest Rva name.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

namespace _STL {
template<> void list<BfmeSpecialPowerTimer8, allocator<BfmeSpecialPowerTimer8> >::push_back(const BfmeSpecialPowerTimer8 &);
}

class Rva00375BFF
{
public:
	void rva00375BFF(unsigned int a, float b);
private:
	char m_pad[0x10];
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > m_list; // +0x10
};

void Rva00375BFF::rva00375BFF(unsigned int a, float b)
{
	if (a == 0)
		return;
	BfmeSpecialPowerTimer8 timer;
	timer.m_templateID = a;
	*(float *)&timer.m_readyFrame = b;
	m_list.push_back(timer);
}

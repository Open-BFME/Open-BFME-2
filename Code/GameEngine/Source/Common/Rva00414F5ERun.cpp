// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?run@Rva00414F5EHost@@QAEXXZ @0x00414F5E 39B: vector clear via rowed erase 0x00414760 on the +0x1C vector plus global load at 0x00DFEEE8 plus tail method at pinned 0x00414DAA. Evidence: erase pushes plus global->[0x10] plus and-0 at +0x2C plus tail jmp; sibling 0x00414B0A pattern.
#include <vector>

#include "ascii_string.h"

struct BfmeAssignRecord44
{
	AsciiString s;
	int a[10];
};

struct Rva00414F5EGlobal
{
	char m_pad[0x10];
	int m_10;
};
extern class PlayerList *ThePlayerList;

class Rva00414F5EHost
{
public:
	void run();
	void tail();
private:
	char m_00[0x1C];
	_STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> > m_vec1C;
	int m_28;
	int m_2C;
};

void Rva00414F5EHost::run()
{
	_STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> > &v = m_vec1C;
	v.erase(v.begin(), v.end());
	m_28 = (*(Rva00414F5EGlobal **)&ThePlayerList)->m_10;
	m_2C = 0;
	return tail();
}

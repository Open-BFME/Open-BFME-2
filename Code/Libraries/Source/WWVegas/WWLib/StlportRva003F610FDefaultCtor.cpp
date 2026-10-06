// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??0Rva003F610FElement@@QAE@XZ @0x003F5322 57B: default ctor (int plus vector<int> plus vector<BfmeAssignRecord104> plus 5 dwords)
// Evidence: adjacent dtor ??1Rva003F610FElement@@QAE@XZ @0x003F535B and copy ctor ??0Rva003F610FElement@@QAE@ABU0@@Z @0x003F54DC prove class Rva003F610FElement layout; retail zeroes m_00 then constructs two vectors then zeroes tail.
#include <vector>

struct BfmePod104 { int a[26]; };

struct RvaTail20 { int w[5]; };

struct Rva003F610FElement
{
	Rva003F610FElement();
	int m_00;
	_STL::vector<unsigned int> m_04;
	_STL::vector<BfmePod104> m_10;
	RvaTail20 m_1C;
};

Rva003F610FElement::Rva003F610FElement()
	: m_00(0)
	, m_04()
	, m_10()
{
	m_1C.w[0] = 0;
	m_1C.w[1] = 0;
	m_1C.w[2] = 0;
	m_1C.w[3] = 0;
	m_1C.w[4] = 0;
}

// cl: /Ireference/shims/bfmealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva003F9FA9@@QAE@ABVAsciiString@@@Z @0x003F9FA9 61B
// Constructor taking AsciiString: copy-constructs m_00 at +0x00 via retail's
// AsciiString copy ctor 0x001D8F56, default-constructs _STL::vector<BfmeE16> at
// +0x04 via the rowed _Vector_base ctor 0x00211E58 (its allocator passed on
// the stack at [ebp+0x0B]), zeroes six ints at +0x10..+0x24 with -1 at
// +0x28/+0x2C, and reads back through the _ReadWriteBarrier. Evidence:
// unlock lane beside the matched copy ctor Rva003F9FE6CopyCtor.cpp, caller
// 0x00214060 news 0x30 bytes then calls this with an AsciiString, callees
// AsciiString copy 0x001D8F56 and Vector_base 0x00211E58 both rowed. BfmeE16
// is 16 bytes (stlport_vector_e16_o1.cpp). The AsciiString view is TU-local
// so its copy ctor resolves to the AsciiString row at 0x001D8F56; the shared
// bfme2_ascii shim would instead emit a call to StringBase<char> (0x000365F0).
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// class-gate: allow AsciiString retail calls its own copy ctor 0x001D8F56 here
// while the shared shim routes the same constructor to StringBase<char> at
// 0x000365F0; the target bytes pin the AsciiString spelling and only this view
// reproduces them.
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
private:
	char *m_text;
};

struct BfmeE16 { float x, y, z, w; };

class Rva003F9FA9
{
public:
	Rva003F9FA9(const AsciiString &s);
private:
	AsciiString m_00;
	_STL::vector<BfmeE16> m_04;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
};

Rva003F9FA9::Rva003F9FA9(const AsciiString &s)
	: m_00(s)
	, m_04(_STL::allocator<BfmeE16>())
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_1C(0)
	, m_20(0)
	, m_24(0)
{
	_ReadWriteBarrier();
	m_28 = -1;
	m_2C = -1;
}
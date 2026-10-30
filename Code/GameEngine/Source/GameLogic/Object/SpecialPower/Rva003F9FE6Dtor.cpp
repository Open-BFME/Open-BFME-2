// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva003F9FE6@@QAE@XZ @0x003FA0C7 81B
// Gap dtor between copy ctors in Rva003F9FE6CopyCtor.cpp: destroys AsciiString
// at +0x18/+0x14 via inlined releaseBuffer 0x00036410, vector<AsciiString> at
// +8 via rowed 0x0002CC70, AsciiString at +4 via releaseBuffer, EH states
// 2/1/0/-1, no vptr store, no base call. Evidence: same TU layout (vptr +0,
// m_04 +4, m_08 +8/12B, m_14 +0x14, m_18 +0x18), caller thunk at 0x00402F23,
// novtable suppresses vptr store while copy ctor TU keeps it.
#include <vector>
#include "ascii_string.h"


namespace _STL
{
// Bind vector<AsciiString>'s copy ctor and dtor to their rowed workers
// (0x0002CC70 dtor). Declarations only: the definitions live in the row owners.
template <class T, class A> class vector;
template <> class vector<AsciiString, allocator<AsciiString> >
{
public:
	vector(const vector &other);
	~vector();
private:
	char m_pad[12];
};
}

class __declspec(novtable) Rva003F9FE6
{
public:
	virtual void v00() = 0;
	~Rva003F9FE6();
private:
	AsciiString m_04;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_08;
	AsciiString m_14;
	AsciiString m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_55;
	unsigned char m_56;
};

inline Rva003F9FE6::~Rva003F9FE6()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva003F9FE6InlineAnchor@@YAXPAVRva003F9FE6@@@Z absent-from-retail
void _bfmeRva003F9FE6InlineAnchor(Rva003F9FE6 *p)
{
    p->Rva003F9FE6::~Rva003F9FE6();
}
#pragma inline_depth()

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0051F87B@@QAE@XZ @ 0x0051FAFC size 86.
// Default ctor for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4, int at +8, AsciiString at +0xC, int at +0x10, vector<SaveMapPreview>
// at +0x14 (Rva0051ECC3 view), vector<PrereqUnitRec> at +0x20 (Rva0051ED0A view),
// three vector<unsigned> at +0x2C/+0x38/+0x44. Evidence: same vtable as rowed
// copy 0x0051F87B; offsets from lea pairs; empty Vector_base folds to 0x00211E58.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct SaveMapPreview
{
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
};

class Rva0051F87B
{
public:
	virtual ~Rva0051F87B();
	Rva0051F87B();
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	_STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > m_14;
	_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > m_20;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_2C;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_38;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_44;
};

Rva0051F87B::Rva0051F87B()
{
}

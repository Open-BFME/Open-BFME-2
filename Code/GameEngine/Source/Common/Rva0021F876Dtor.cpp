// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport46
// ??1Rva0021F876@@QAE@XZ @0x0021F8F3 104B. Dtor of the five-AsciiString plus
// vector<CreateAHeroSubClass> record proven by the copy ctor at 0x0021F876 in
// Rva0021F876Copy.cpp: vector at +0x14 via rowed 0x0021F7A7 then
// releaseBuffer at +0x10/+0x0C/+0x08/+0x04/+0x00 via rowed 0x00036410.
// Evidence: callers at 0x0021FA95 and 0x0021FDDC plus jmp at 0x0021FAEC.
// BfmeNarrowRecord000BFDC7 (a 0x20B basic_string layout) cannot emit these
// calls; its destructor is the 15B fold at 0x000796BC, so the owner stays
// CreateAHeroClass. Element stays size-free with a declared-only dtor so the
// vector call binds the rowed non-trivial Destroy shape.
#include "ascii_string.h"
#include <vector>



class CreateAHeroManager
{
public:
    class CreateAHeroClass;
    class CreateAHeroSubClass { public: ~CreateAHeroSubClass(); };
};
typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

class CreateAHeroManager::CreateAHeroClass
{
public:
	~CreateAHeroClass();
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	_STL::vector<CreateAHeroManager::CreateAHeroSubClass, _STL::allocator<CreateAHeroManager::CreateAHeroSubClass> > m_14;
};

CreateAHeroClass::~CreateAHeroClass()
{
}

// The scalar deleting destructor at 0x0021FA92 calls the destructor above
// (retail REL32 at 0x0021FA95); deleting through the class emits it here.
// This anchor only makes the unit compile that copy; it is not retail code.
// ?_bfmeRva0021F876DeleteAnchor@@YAXPAVRva0021F876@@@Z absent-from-retail
void _bfmeRva0021F876DeleteAnchor(CreateAHeroClass *p)
{
	delete p;
}

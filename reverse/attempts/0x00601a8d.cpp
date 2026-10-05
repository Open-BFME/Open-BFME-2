// ?rva00601A8D@Rva00601BBCHelper@@QAEXXZ
// partial score=0.8 date=2026-10-05
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The 0x34-byte helper BFME 2 added to INI at +0x838 (INI_ctor.cpp):
//   ??0Rva00601BBCHelper@@QAE@XZ   0x00601BBC  constructor
//   ??1Rva00601BBCHelper@@UAE@XZ   0x00601BF3  destructor
//   ??_GRva00601BBCHelper@@UAEPAXI@Z 0x00602056 scalar deleting destructor
// Layout from these bodies: a one-slot vtable (0x00C7A6B0, slot 0 the
// deleting destructor), a 0x18-byte member at +4 built by the rowed
// Rva00524415 constructor (two vectors) and torn down by 0x00601AE9, and two
// four-byte-element vectors at +0x1C and +0x28 whose storage is freed
// directly. The constructor runs the once-only table init 0x006016C9; the
// destructor first clears everything through 0x00601A8D. The class's identity
// (a token/lexer table, by its ctype-table init) is not established, so the
// names stay address-derived; the callees are pinned.

#include <vector>

void operator delete[](void*);

void Rva006016C9Init() throw();

struct Rva00524415
{
	Rva00524415();
	~Rva00524415();
	void clear();
	char m_body[0x18];
};

class Rva00601BBCHelper
{
public:
	Rva00601BBCHelper();
	virtual ~Rva00601BBCHelper();

	void rva00601A8D();

private:
	Rva00524415 m_04;            // +0x04
	_STL::vector<int> m_1C;      // +0x1C
	_STL::vector<int> m_28;      // +0x28
};

Rva00601BBCHelper::Rva00601BBCHelper()
{
	Rva006016C9Init();
}

Rva00601BBCHelper::~Rva00601BBCHelper()
{
	rva00601A8D();
}

// Banked native601A8D..601AE9 Ghidra92B. Matching caller601C11 proves helper method.
// Member+4 clear calls newly fullverified28B at601A71; legacy24B class name
// is an ABI view from a folded constructor and does not identify payload.
// Arrays+28 deleted through verified2FD80 and zeroed only when nonnull.
// Both ranges cleared through31BD55 fullverified34B pointer erase.
// Natural vector<int>::erase independently reproduces complete34B too but
// resolves another folded address688710; must bind a caller-proven ABI alias.
// Current O1 body94B keeps begin in EAX and size in ECX at loop test instead
// of native EAX size and begin reload. O1/G7/Ob2/pointer/reference/do variants
// and direct byte-pointer delete preserve or worsen this register mismatch.
void Rva00601BBCHelper::rva00601A8D()
{
    m_04.clear();
    _STL::vector<int>& arrays=m_28;
    for (unsigned i=0;i<arrays.size();++i) {
        if (arrays[i]) {
            operator delete[](reinterpret_cast<void*>(arrays[i]));
            arrays[i]=0;
        }
    }
    arrays.erase(arrays.begin(),arrays.end());
    _STL::vector<int>& other=m_1C;
    other.erase(other.begin(),other.end());
}
#pragma comment(linker, "/alternatename:?clear@Rva00524415@@QAEXXZ=?clear@Rva00601B30@@QAEXXZ")

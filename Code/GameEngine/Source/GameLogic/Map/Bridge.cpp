// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??1Bridge@@UAE@XZ @0x0027FBAC 82B. Dtor stores vtable 0x00BFB1E0,
// null-checked delete of +0xC8 via first virtual with int arg 0 returning
// pointer freed by rowed ??3@YAXPAX@Z, then releases AsciiString at +8 via
// rowed ?releaseBuffer@?$StringBase@D@@AAEXXZ. Caller 0x00280C05 is its ??_G.
// Identity: 0x00BFB1E0 is Bridge's vftable. The matched Bridge constructors
// (0x00280C21 in BridgeObjectCtor.cpp, BridgeCtor.cpp) store it, its only slot
// is this ??_G, and the class keeps its AsciiString template name at +8 and
// the pointer at +0xC8 the Bridge(Object *) constructor clears.
// The canonical frozen StringBase replaces the private copy. The public narrow
// teardown spelling resolves to the verified 133-byte releaseBuffer worker at
// RVA 0x36410. Wide teardown is unchanged.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Rva0027FBACHelper {
public: virtual void *Get(int);
};

class Bridge {
public: virtual ~Bridge();
private: char m_pad04[4];
         StringBase<char> m_str;
         char m_pad0C[188];
         Rva0027FBACHelper *m_c8;
};
Bridge::~Bridge()
{
	if (m_c8) {
		::operator delete(m_c8->Get(0));
		m_c8 = 0;
	}
}

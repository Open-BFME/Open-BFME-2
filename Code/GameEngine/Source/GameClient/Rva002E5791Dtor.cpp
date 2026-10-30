// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva002E5791@@QAE@XZ 0x002E5791 53B
// Evidence: EH dtor calls wide releaseBuffer 0x00036E70 at +4 then narrow 0x00036410 at +0; prev Rva002E5711Dtor; unblocks 0x002E5E5A.
// The canonical frozen StringBase replaces the private copy. The public narrow
// teardown spelling resolves to the verified 133-byte releaseBuffer worker at
// RVA 0x36410. Wide teardown is unchanged.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Rva002E5791
{
public:
	~Rva002E5791();

private:
	StringBase<char> m_narrow;
	StringBase<unsigned short> m_wide;
};

Rva002E5791::~Rva002E5791()
{
}

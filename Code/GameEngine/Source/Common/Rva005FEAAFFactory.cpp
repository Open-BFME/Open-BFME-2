// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
// Inline release body for this unit; the header only declares the destructor.
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}
struct Rva005FEAAFSourceRef {
 TargetRef00217D4C *m_ptr;
 ~Rva005FEAAFSourceRef() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class Rva005FEAAFHost {
public:
 virtual void v0(); virtual void v1();
 virtual Rva005FEAAFSourceRef createRaw(int level, const AsciiString &name);
 TreeHintRef00217D4C create(int level, const AsciiString &name);
};
TreeHintRef00217D4C Rva005FEAAFHost::create(int level, const AsciiString &name)
{
 Rva005FEAAFSourceRef raw = createRaw(level, name);
 return TreeHintRef00217D4C(raw.m_ptr);
}

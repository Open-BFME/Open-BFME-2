// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005FEAAFSourceRef {
 TargetRef00217D4C *m_ptr;
 ~Rva005FEAAFSourceRef() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(const Rva005FEAAFSourceRef &value) : m_ptr(value.m_ptr) { if(m_ptr) ++m_ptr->references; }
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
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
 return TreeHintRef00217D4C(raw);
}

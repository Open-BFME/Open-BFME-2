// cl: /O1 /EHsc /MD
// Native 0x005C90F1..0x005C9217, called by the rowed range wrapper
// HostClass005C815B::method_005C839B. Its established opaque spelling and
// two-int ABI are retained; the first argument is a transfer interface.
// Native accesses prove ref +8, word +44, byte +46 and low nibble +47.
// WB 0x01569E00 supplies a transfer algorithm lead, not a target class name.
// The exception identity comes from retail throw-info CFFD18 and its rowed
// constructor/copy/destructor, independently of that WB lead.
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
#include "../../Include/Common/BfmePoolRef10.h"
#include "../../Include/Common/OpaqueRefElement4.h"
class Rva0051D93
{
public:
    Rva0051D93(const OpaqueRefElement4 &, int);
private:
    char m_bytes[0x90];
};
#include "../../Include/Common/XferException.h"
#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"
class Rva002D9FD9Arg;
#include "../../../GameEngineDevice/Include/Rva002D9FD9Owner.h"
class HostClass005C8E0A { public: void method_005C9069(); };
struct Rva005C847BRecord
{
    int m_00, m_04;
    BfmePoolRef10 m_ref;
    char m_unknown0C[0x38];
    unsigned short m_44;
    unsigned char m_46;
    unsigned char m_low : 4;
    unsigned char m_high : 4;
    void method_005C90F1(int a0, int a1);
};
typedef char Verify005C847BRecord[(sizeof(Rva005C847BRecord) == 0x48) ? 1 : -1];

void Rva005C847BRecord::method_005C90F1(int a0, int)
{
    Xfer *xfer = (Xfer *)a0;
    bool hasRef = m_ref.m_target != 0;
    *xfer == hasRef;
    if (hasRef && !m_ref.m_target)
        m_ref.rva00053D26((BfmePoolHolder88 *)new Rva0051D93(OpaqueRefElement4(), 0));
    if (hasRef) {
        ((Rva002D9FD9Owner *)m_ref.m_target)->rva002D9FD9((Rva002D9FD9Arg *)xfer);
        ((HostClass005C8E0A *)this)->method_005C9069();
    }
    *xfer == m_44;
    *xfer == m_46;
    unsigned char count = m_low;
    *xfer == count;
    m_low = count;
    if (count != m_low)
        throw XferException(0, "Lock count does not fit into 4 bits");
}

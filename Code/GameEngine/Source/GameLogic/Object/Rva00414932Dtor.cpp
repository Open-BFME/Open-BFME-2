// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva00414932@@UAE@XZ @ 0x00414932 75B: novtable dtor restoring Snapshot vtable 0x007BB554,
// calls vector<BfmeAssignRecord44> dtor at +0x1C, Rva00360D26Member dtor at +0x14,
// StringBase releaseBuffer at +0x04. Precedent Rva0040DB52Dtor plus
// stlport_asciistring_record_bodies layout; callers include ??_G at 0x00414AEE.
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"

struct BfmeAssignRecord44 { AsciiString s; int a[10]; };

class Rva00360D26Member
{
public:
    ~Rva00360D26Member();
private:
    unsigned m_unknown;
};

class __declspec(novtable) Rva00414932 : public Snapshot
{
public:
    virtual ~Rva00414932();
private:
    AsciiString m_str04;
    char m_pad08[0x14 - 0x08];
    Rva00360D26Member m_member14;
    char m_pad18[0x1C - 0x18];
    _STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> > m_vec1C;
};

Rva00414932::~Rva00414932()
{
}

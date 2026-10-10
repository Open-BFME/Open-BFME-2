// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?addRevivableUnit@UnitRevivalTracker@@QAEXABURva002E2D10Record@@H@Z @0x0037F38F 15B
// Evidence: unlock lane; forwards member +4 vector push_back 0x002E2D10;
// caller 0x001EC8C0 passes local and int; ret 8 with unused second slot.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva002E2D10Record
{
    Rva002E2D10Record();
    Rva002E2D10Record(const Rva002E2D10Record &that);
    ~Rva002E2D10Record();
    Rva002E2D10Record &operator=(const Rva002E2D10Record &that);

private:
    char bytes[216];
};

class UnitRevivalTracker
{
    int m_unk00;
    _STL::vector<Rva002E2D10Record> m_vec04;

public:
    void addRevivableUnit(const Rva002E2D10Record &item, int unused);
};

void UnitRevivalTracker::addRevivableUnit(const Rva002E2D10Record &item, int)
{
    m_vec04.push_back(item);
}

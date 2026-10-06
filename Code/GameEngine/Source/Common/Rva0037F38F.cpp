// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva0037F38F@Rva0037F38F@@QAEXABURva002E2D10Record@@H@Z @0x0037F38F 15B
// Evidence: unlock lane; forwards member +4 vector push_back 0x002E2D10;
// caller 0x001EC8C0 passes local and int; ret 8 with unused second slot.
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

class Rva0037F38F
{
    int m_unk00;
    _STL::vector<Rva002E2D10Record> m_vec04;

public:
    void rva0037F38F(const Rva002E2D10Record &item, int unused);
};

void Rva0037F38F::rva0037F38F(const Rva002E2D10Record &item, int)
{
    m_vec04.push_back(item);
}

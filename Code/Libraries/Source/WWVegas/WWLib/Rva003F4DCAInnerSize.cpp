// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F4DCA@Rva003F4DCA@@QAEHHH@Z, retail 0x003F4DCA, 36 bytes.
// Inner-vector size accessor of the triple-nested vector family modelled in
// Rva003F498ALoops.cpp: outer vector<28B> at +0x18, middle vector<48B> at +4
// of each outer, inner vector<int> at +4 of each middle. Returns
// m_outers[i].inners[j].vals.size() which is (finish-start)>>2. Callers
// 0x002B2E64 0x002B7A47 0x003F5691 0x003F56B8 0x0040FA8B 0x005FB070 pass the
// same container in ecx with two int indices. Flags are the neighbour STL
// TUs' // cl: plus /G7: plain /O1 strength-reduces the j*0x30 imul into
// lea+shl while retail keeps imul.
#include <vector>

struct Rva003F4DCAInner {
    int unk0;
    _STL::vector<int> vals;
    char pad[32];
};

struct Rva003F4DCAOuter {
    int unk0;
    _STL::vector<Rva003F4DCAInner> inners;
    char pad[12];
};

class Rva003F4DCA {
    char m_pad0[0x18];
    _STL::vector<Rva003F4DCAOuter> m_outers;
public:
    int rva003F4DCA(int i, int j);
};

int Rva003F4DCA::rva003F4DCA(int i, int j)
{
    return (int)m_outers[i].inners[j].vals.size();
}

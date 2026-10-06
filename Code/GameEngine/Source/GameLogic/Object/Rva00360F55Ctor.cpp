// cl: /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00360F55@@QAE@XZ @0x00360F55 134B
// Record ctor for the 0x94-byte ObjectFilter science-cluster record used by
// iniParseObjectFilter at 0x00361CA5 and 9 other callers in 0x361817-0x3623E5.
// Six empty vectors at +0x00/+0x0C/+0x18/+0x24/+0x30/+0x3C via the folded
// _Vector_base at 0x00211E58, two Rva0024C7B3Member (0x1C memset) at +0x48
// and +0x64 via the rowed 0x0024C7B3, then ints 0 at +0x84/+0x8C/+0x90 and
// 3 at +0x80 plus byte 1 at +0x88. No vtable (non-virtual QAE), no EH
// (/GX), EBP frame for the 1-byte allocator temp at [ebp-1]. Element types
// of the six vectors are unproven size-only views; BfmeE16 is the rowed
// 16-byte stand-in whose empty base folds to the same 29B body. Unblocks
// 0x00362192 with the landed 0x00360CB0 release for GarrisonContain and
// TunnelContain ModuleData ctors.
#include <vector>

struct BfmeE16
{
    float x;
    float y;
    float z;
    float w;
};

class Rva0024C7B3Member
{
public:
    Rva0024C7B3Member();

private:
    unsigned char m_data[0x1C];
};

namespace _STL
{

// Declared-only explicit specialization: keeps the six empty-base calls
// external through the rowed BfmeE16 body at 0x00211E58 instead of inlining
// them to stores. Retail calls the base out of line with the 1-byte
// allocator temp at [ebp-1].
template <>
_Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(
    const allocator<BfmeE16> &storage);

}

class Rva00360F55
{
public:
    Rva00360F55();

private:
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_00;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_18;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_24;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_30;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_3C;
    Rva0024C7B3Member m_48;
    Rva0024C7B3Member m_64;
    int m_80;
    int m_84;
    unsigned char m_88;
    char m_pad89[3];
    int m_8C;
    int m_90;
};

Rva00360F55::Rva00360F55()
{
    m_84 = 0;
    m_8C = 0;
    m_90 = 0;
    m_80 = 3;
    m_88 = 1;
}

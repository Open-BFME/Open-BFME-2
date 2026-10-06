// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Dump range 18 setter 0x003F1AB9 (70B): vector assign at +0x158 via rowed
// 0x0021C21B plus three ints at +0x14C/+0x150/+0x154 and two bytes at
// +0x1A0/+0x1A1. Straight-line thiscall with six stack args, ret 0x18.
#include <vector>
#include "ascii_string.h"

class Rva003F1AB9Owner
{
public:
    void rva003F1AB9(const _STL::vector<int> &v, int a, int b, int c, bool d, bool e);
private:
    char m_pad[0x14C];
    int m_14C;
    int m_150;
    int m_154;
    _STL::vector<int> m_158;
    char m_after158[0x1A0 - (0x158 + 12)];
    unsigned char m_1A0;
    unsigned char m_1A1;
};

void Rva003F1AB9Owner::rva003F1AB9(const _STL::vector<int> &v, int a, int b, int c, bool d, bool e)
{
    m_158 = v;
    m_14C = a;
    m_150 = b;
    m_154 = c;
    m_1A0 = d;
    m_1A1 = e;
}

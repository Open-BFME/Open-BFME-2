// ?init@AIWall@@QAE_NXZ
// partial score=0.82 date=2026-10-09
// Named WB137B990/405 and complete native4EBEB7..4EBF4B establish AIWall::init.
// Actual STLport vector operations eliminate the old bank's invented volatile
// field qualifiers. This complete trial emits146B against native148B: frame,
// sort argument construction and loop/state logic agree, but post-sort median
// load order/register allocation still differ. Four source shapes were tested;
// retaining an explicit median gives143B and incorrectly elides the reload.
// Helper4EBB58's full673B native body was read and proves ECX/RET0. Its original
// name is unknown (WB's Coord2D::Set label is an inline-source attribution).
// No helper pin was added while the caller remains a byte mismatch.
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva004EBE74Item {
    unsigned char unknown00[0x50];
    unsigned m_50;
    unsigned getKey() const { return m_50; }
};
struct Rva004EBE74Cmp {
    bool operator()(const Rva004EBE74Item *a, const Rva004EBE74Item *b) const {
        return a->m_50 < b->m_50;
    }
};
namespace _STL {
    template<class Iterator, class Predicate>
    void sort(Iterator first, Iterator last, Predicate predicate);
}
class AIWall {
public:
    bool init();
    void rva004EBB58();
    void *unknown00;
    Rva004EBE74Item *selected04;
    _STL::vector<Rva004EBE74Item *> orders08;
    unsigned char unknown14[0x20];
    int state34;
    unsigned index38;
    int state3c;
    unsigned index40;
};
bool AIWall::init()
{
    if (orders08.size() > 1) {
        _STL::sort(orders08.begin(), orders08.end(), Rva004EBE74Cmp());
        unsigned count = orders08.size();
        selected04 = orders08[count / 2];
        bool valid = true;
        unsigned index = (unsigned)-1;
        _STL::vector<Rva004EBE74Item *>::iterator end = orders08.end();
        for (_STL::vector<Rva004EBE74Item *>::iterator p = orders08.begin(); p != end && valid; ++p) {
            if ((*p)->getKey() != ++index)
                valid = false;
        }
        if (valid) {
            index38 = selected04->getKey();
            index40 = selected04->getKey();
            rva004EBB58();
            return true;
        }
    }
    return false;
}

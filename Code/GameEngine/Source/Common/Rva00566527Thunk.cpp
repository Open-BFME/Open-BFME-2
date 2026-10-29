// cl: /MD
// stlport
// ?rva00566527@Rva00566527@@QAEXABVFXList@@@Z @0x00566527 8B: tail-jump.
// Adds 8 then jumps to row 0x0056625E vector FXList push_back. Owner holds
// vector at +8. Unlocks 0x004E1579. Caller is 0x004E15B8.
class FXList
{
    char _m[8];
};

#include <vector>

namespace _STL
{
template <> class vector<FXList, allocator<FXList> >
{
public:
    void push_back(const FXList &x);
};
}

class Rva00566527
{
public:
    void rva00566527(const FXList &x);
private:
    char m_pad[8];
    _STL::vector<FXList, _STL::allocator<FXList> > m_vec;
};

void Rva00566527::rva00566527(const FXList &fXList)
{
    m_vec.push_back(fXList);
}

struct BfmePod40
{
    int a[10];
};

namespace _STL
{
template <> class vector<BfmePod40, allocator<BfmePod40> >
{
public:
    void push_back(const BfmePod40 &x);
};
}

class Rva0056652FOwner
{
public:
    void rva0056652F(const BfmePod40 &x);
private:
    char m_pad[0x14];
    _STL::vector<BfmePod40, _STL::allocator<BfmePod40> > m_vec;
};

void Rva0056652FOwner::rva0056652F(const BfmePod40 &x)
{
    m_vec.push_back(x);
}

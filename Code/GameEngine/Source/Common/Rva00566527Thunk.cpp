// cl: /MD
// stlport
// ?rva00566527@Rva00566527@@QAEXABVFXList@@@Z @0x00566527 8B: tail-jump.
// Adds 8 then jumps to row 0x0056625E vector FXList push_back. Owner holds
// vector at +8. Unlocks 0x004E1579. Caller is 0x004E15B8.
class FXList
{
public:
	FXList(const FXList &that);
private:
	char _m[8]; // +0x00
};

#include <vector>

namespace _STL
{
template <> void vector<FXList, allocator<FXList> >::push_back(const FXList &);
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
	virtual ~BfmePod40();
	int a[9];
};

namespace _STL
{
template <> void vector<BfmePod40, allocator<BfmePod40> >::push_back(const BfmePod40 &);
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

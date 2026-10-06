// cl: /MD
// ?rva00566527@Rva00566527@@QAEXABVFXList@@@Z @0x00566527 8B: tail-jump.
// Adds 8 then jumps to row 0x0056625E vector FXList push_back. Owner holds
// vector at +8. Unlocks 0x004E1579. Caller is 0x004E15B8.
class FXList
{
    char _m[8];
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
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

void Rva00566527::rva00566527(const FXList &x)
{
    m_vec.push_back(x);
}

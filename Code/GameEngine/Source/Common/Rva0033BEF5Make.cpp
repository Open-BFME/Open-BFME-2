// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?Rva0033BEF5Make@@YA?AURva0033B830@@ABV?$StringBase@D@@ABVRva002390CB@@@Z @0x0033BEF5 27B.
// Hidden-dest forwarder over the rowed Rva0033B830 two-member ctor 0x33B830.
// Chain from 0x33B830: this makes the 0x33DBE5 container parse/buttons path
// ready. Same 27B shape as the rowed make_pair 0x32ACCF. The dtors below force
// the retail ebp frame plus and [ebp-4] 0 EH state. Callee rowed 0x33B830.
template <typename T>
class StringBase
{
    friend struct Rva0033B830;
    StringBase(const StringBase<T> &other);
    void releaseBuffer();
    void *m_data;
public:
    ~StringBase() { releaseBuffer(); }
};

class Rva002390CB
{
    void *m00;
    void *m04;
public:
    Rva002390CB(const Rva002390CB &other);
    ~Rva002390CB();
};

struct Rva0033B830
{
    StringBase<char> m0;
    Rva002390CB m4;
    Rva0033B830(const StringBase<char> &a, const Rva002390CB &b);
    ~Rva0033B830();
};

Rva0033B830 Rva0033BEF5Make(const StringBase<char> &a, const Rva002390CB &b);

Rva0033B830 Rva0033BEF5Make(const StringBase<char> &a, const Rva002390CB &b)
{
    return Rva0033B830(a, b);
}

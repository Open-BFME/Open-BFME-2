// cl: /O1 /MD /EHsc
// Reference guide: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/Common/BigChainBaseDtors.cpp.
// Target 001F9025..001F9060 is a nonvirtual destructor: the null-preserving
// this+4 conversion identifies a second base, destroyed before the first.
// The first base owns one pointer and calls the verified 001F4206 cleanup.
// Target caller Sub005CD540Outer (001FA95A) establishes the existing donor
// address-derived Rva005C9D30 spelling. Original game class names are unknown.
class Rva001F4206
{
public:
    void rva001F4206();
};
class BigChainO1Hold
{
public:
    void *m_pointer;
    ~BigChainO1Hold();
};
// ?BigChainO1Hold::~BigChainO1Hold present-unmatched
inline BigChainO1Hold::~BigChainO1Hold()
{
    ((Rva001F4206 *)this)->rva001F4206();
}
class Rva005C67C0
{
public:
    ~Rva005C67C0();
};
class Rva005C9D30 : public BigChainO1Hold, public Rva005C67C0
{
public:
    ~Rva005C9D30();
};
Rva005C9D30::~Rva005C9D30() {}

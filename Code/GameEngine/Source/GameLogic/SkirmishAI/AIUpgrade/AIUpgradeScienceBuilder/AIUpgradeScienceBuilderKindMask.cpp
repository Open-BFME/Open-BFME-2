// cl: /DNDEBUG /MD /GX /O1 /G7
// AIUpgradeScienceBuilder kind exclusion check: native 0x0059764A..0x00597693.
// WB 0x015326C0 confirms bits 60 61 150 156 189 201 203 and the Thing query.
// The outer method name remains unresolved; the address-derived name is deliberate.
// Word-reference access follows the reference BitFlags/bitset implementation.
#include <string.h>

template<int N> class BitFlags;
class Thing { public: bool isAnyKindOf(const BitFlags<69> &) const; };
class Object;
struct Rva0059764AMask
{
    Rva0059764AMask() { memset(this, 0, sizeof(*this)); }
    unsigned &word(unsigned bit) { return m_bits[bit / 32]; }
    void set(unsigned bit) { word(bit) |= 1UL << (bit % 32); }
    unsigned m_bits[7];
};
class AIUpgradeScienceBuilder
{
public:
    bool rva0059764A(Object *object);
};

bool AIUpgradeScienceBuilder::rva0059764A(Object *object)
{
    Rva0059764AMask mask;
    mask.set(60); mask.set(61); mask.set(150); mask.set(156);
    mask.set(189); mask.set(201); mask.set(203);
    if (((Thing *)object)->isAnyKindOf(*(const BitFlags<69> *)&mask))
        return true;
    return false;
}

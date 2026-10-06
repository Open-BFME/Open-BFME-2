// cl: /DNDEBUG /MD
// ?rva002627E8@Rva002627E8@@QBEMXZ @0x002627E8 28B
// Float getter via member at +0x1f0 with null returning BfmeZeroRange. Evidence: callers 0x000CE5E7 0x002734A3 plus 12 more; callee 0x001E46E1 pinned plus BfmeZeroRange rowed.
class Object;
class Rva001E46E1 {
public:
    float rva001E46E1(Object *obj);
};
extern const float BfmeZeroRange; // ?BfmeZeroRange@@3MB
class Rva002627E8 {
public:
    char m_pad00[8];
    Object *m_obj08;
    char m_pad0C[0x1f0 - 0x0c];
    Rva001E46E1 *m_ptr1F0;
    float rva002627E8() const;
};
float Rva002627E8::rva002627E8() const
{
    Rva001E46E1 *p = m_ptr1F0;
    if (p != 0)
        return p->rva001E46E1(m_obj08);
    return BfmeZeroRange;
}

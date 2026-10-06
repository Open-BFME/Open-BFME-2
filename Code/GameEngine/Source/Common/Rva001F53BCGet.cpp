// cl: /MD
// ?get@Rva001F53BCSlot@@QBEPBURGBColor@@XZ @0x001F53BC 18B.
// Null-checked RGBColor holder at +0x1B0 via virtual slot +0x10 with tail jmp.
// Shape matches 0x001F4E1B family. Caller at 0x001F6FFF.
// Honest Rva names; /O1 for je plus tail-jmp shape.
struct RGBColor {
    float r;
    float g;
    float b;
};
class Rva001F53BCHelper {
public:
    virtual ~Rva001F53BCHelper();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual const RGBColor* get() const;
};
class Rva001F53BCSlot {
public:
    const RGBColor* get() const;
    char m_pad[0x1B0];
    Rva001F53BCHelper* m_ptr;
};
const RGBColor* Rva001F53BCSlot::get() const
{
    Rva001F53BCHelper* p = m_ptr;
    if (p)
        return p->get();
    return 0;
}

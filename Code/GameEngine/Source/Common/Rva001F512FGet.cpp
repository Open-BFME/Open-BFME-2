// cl: /MD
// ?get@Rva001F512FSlot@@QBEPBURGBColor@@XZ @0x001F512F 18B.
// Null-checked RGBColor holder at +0x1B8 via virtual slot +0x14 with tail jmp.
// Shape matches 0x001F4E1B sibling. Callers at 0x001F75DE and 0x0055F0D0.
// Honest Rva names; /O1 for je plus tail-jmp shape.
struct RGBColor {
    float r;
    float g;
    float b;
};
class Rva001F512FHelper {
public:
    virtual ~Rva001F512FHelper();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual const RGBColor* get() const;
};
class Rva001F512FSlot {
public:
    const RGBColor* get() const;
    char m_pad[0x1B8];
    Rva001F512FHelper* m_ptr;
};
const RGBColor* Rva001F512FSlot::get() const
{
    Rva001F512FHelper* p = m_ptr;
    if (p)
        return p->get();
    return 0;
}

// cl: /MD
// ?get@Rva001F53AASlot@@QBEPBURGBColor@@XZ @0x001F53AA 18B.
// Null-checked RGBColor holder at +0x1AC via virtual slot +0x14 with tail jmp.
// Shape matches 0x001F4E1B and 0x001F512F siblings. Callers at 0x001F6F7D and 0x001F70E0.
// Honest Rva names; /O1 for je plus tail-jmp shape.
struct RGBColor {
    float r;
    float g;
    float b;
};
class Rva001F53AAHelper {
public:
    virtual ~Rva001F53AAHelper();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual const RGBColor* get() const;
};
class Rva001F53AASlot {
public:
    const RGBColor* get() const;
    char m_pad[0x1AC];
    Rva001F53AAHelper* m_ptr;
};
const RGBColor* Rva001F53AASlot::get() const
{
    Rva001F53AAHelper* p = m_ptr;
    if (p)
        return p->get();
    return 0;
}

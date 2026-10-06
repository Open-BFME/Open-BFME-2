// cl: /MD
// ?get@Rva001F4E1BSlot@@QBEPBURGBColor@@XZ @0x001F4E1B 18B.
// Null-checked RGBColor holder at +0x94 via virtual slot +0x14 with tail jmp.
// Callers at 0x0055C60E copy 12B or zero and at 0x0004D1E7 use getAsInt.
// Honest Rva names; /O1 for je plus tail-jmp shape.
struct RGBColor {
    float r;
    float g;
    float b;
};
class Rva001F4E1BHelper {
public:
    virtual ~Rva001F4E1BHelper();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual const RGBColor* get() const;
};
class Rva001F4E1BSlot {
public:
    const RGBColor* get() const;
    char m_pad[0x94];
    Rva001F4E1BHelper* m_ptr;
};
const RGBColor* Rva001F4E1BSlot::get() const
{
    Rva001F4E1BHelper* p = m_ptr;
    if (p)
        return p->get();
    return 0;
}

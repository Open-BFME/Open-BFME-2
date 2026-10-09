// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Hidden value-return flags explain the prior banks' missing push ecx and
// AND [EBP-4],0. Each native ABI and payload is separately supported below.
class TextureClass;
template <class T> class RefCountPtr {
public:
    RefCountPtr(const RefCountPtr &other);
    ~RefCountPtr();
    T *ptr;
};
struct BfmeRoadTypeTexturesView {
    RefCountPtr<TextureClass> rva000D6A3F();
    void *textures[2];
};
class Rva00167E5A {
public:
    RefCountPtr<TextureClass> rva00167E5A();
    char pad[0xE4];
    BfmeRoadTypeTexturesView textures;
};
// Native167E5A..167E77 RET4; D6A3F provider independently proves a returned
// RefCountPtr<TextureClass>. Only the +E4 subobject is inferred here.
RefCountPtr<TextureClass> Rva00167E5A::rva00167E5A()
{
    return textures.rva000D6A3F();
}

struct TreeHintRef00217D4C {
    void *ptr;
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
    ~TreeHintRef00217D4C();
};
class Rva005747B2Target {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual TreeHintRef00217D4C slot30();
};
class Rva005747B2 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual TreeHintRef00217D4C rva005747B2();
    char pad04[0x14-4];
    Rva005747B2Target *target;
};
// Native5747B2..5747CC RET4; vslot6 of86E4C4. Caller57473A uses4B result,
// assigns through real2174A4 and releases its word with47DEEF, proving the
// established reference handle payload independently of this wrapper.
TreeHintRef00217D4C Rva005747B2::rva005747B2()
{
    return target->slot30();
}

struct Rva00596BB7Result {
    float x,y,z;
    Rva00596BB7Result() : x(0.0f), y(0.0f), z(0.0f) {}
    Rva00596BB7Result(const Rva00596BB7Result &other);
    ~Rva00596BB7Result();
};
class Rva00596BB7 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30();
    virtual Rva00596BB7Result rva00596BB7();
};
// Native596BB7..596BD7 RET4, vslot13 of870A98, constructs all three native
// float words to0. The source result type is unknown; float stores and12B
// payload are target facts, the nontrivial return type is an ABI inference.
Rva00596BB7Result Rva00596BB7::rva00596BB7()
{
    return Rva00596BB7Result();
}

struct Rva005F4AD7 {
    void *ptr;
    Rva005F4AD7(const Rva005F4AD7 &other) throw();
    ~Rva005F4AD7();
};
class Rva005EE26F {
public:
    virtual void slot00();
    virtual void slot04();
    virtual Rva005F4AD7 slot08(int a, int b);
    Rva005F4AD7 rva005EE26F(int a, int b);
};
// Native5EE26F..5EE28C RET12; caller5D4F27 builds4B result in dead argument
// slot EBP+C and assigns/destroys with rowed Rva005F4AD7 5FD4FF/5F4AD7,
// establishing the handle independently. Virtual callback at slot8 is opaque.
Rva005F4AD7 Rva005EE26F::rva005EE26F(int a, int b)
{
    return slot08(a, b);
}

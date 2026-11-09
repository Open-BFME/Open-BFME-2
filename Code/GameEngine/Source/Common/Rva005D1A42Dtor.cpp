// cl: /MD
// ??1Rva005D19F8@@UAE@XZ @0x005D1A42 14B
// Virtual dtor storing vtable 0x00875688 then tail-jmp to rowed member clear 0x005D18C8 at +4.
// Evidence: chain from just-landed 0x005D18C8; deleting dtor caller 0x005D1A50; thunk and unwind callers; 14B store-plus-jmp precedent Rva000AD6F4Members family.
class Rva005D18C8
{
public:
    void rva005D18C8();
private:
    char m_pad[4];
};
class Rva005D19F8
{
public:
    virtual ~Rva005D19F8();
    virtual void bfmePureSlot1() = 0; // retail table slot 1 is __purecall
    virtual void bfmePureSlot2() = 0; // retail table slot 2 is __purecall
private:
    Rva005D18C8 m_04;
};
Rva005D19F8::~Rva005D19F8()
{
    m_04.rva005D18C8();
}

// cl: /MD
// ??1Rva005D1A42@@UAE@XZ @0x005D1A42 14B
// Virtual dtor storing vtable 0x00875688 then tail-jmp to rowed member clear 0x005D18C8 at +4.
// Evidence: chain from just-landed 0x005D18C8; deleting dtor caller 0x005D1A50; thunk and unwind callers; 14B store-plus-jmp precedent Rva000AD6F4Members family.
class Rva005D18C8
{
public:
    void rva005D18C8();
private:
    char m_pad[4];
};
class Rva005D1A42
{
public:
    virtual ~Rva005D1A42();
private:
    Rva005D18C8 m_04;
};
Rva005D1A42::~Rva005D1A42()
{
    m_04.rva005D18C8();
}

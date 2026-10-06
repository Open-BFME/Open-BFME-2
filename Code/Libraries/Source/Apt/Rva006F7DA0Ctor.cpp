// cl: /DNDEBUG /MD
// ??0Rva006F7DA0@@QAE@XZ @0x006F7DA0 27B evidence stores vtable 0x008ED364 at +0 plus -1 at +4 and zeros at +0xC +0x10 +0x14; caller 0x006F8870
extern const void *const g_00CED364[];
class Rva006F7DA0
{
public:
    Rva006F7DA0();
private:
    const void *m_vtable;
    int m_04;
    int m_pad08;
    int m_0c;
    int m_10;
    unsigned char m_14;
};
Rva006F7DA0::Rva006F7DA0()
{
    m_14 = 0;
    m_04 = -1;
    m_0c = 0;
    m_10 = 0;
    *(const void **)this = g_00CED364;
}

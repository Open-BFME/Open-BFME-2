// cl: /DNDEBUG /MD
// ??0Rva006F7D80@@QAE@XZ @0x006F7D80 27B evidence stores vtable 0x008ED358 at +0 plus -1 at +4 and zeros at +0xC +0x10 +0x14; callers 0x006F8808 0x006F883F
extern const void *const g_00CED358[];
class Rva006F7D80
{
public:
    Rva006F7D80();
private:
    const void *m_vtable;
    int m_04;
    int m_pad08;
    int m_0c;
    int m_10;
    unsigned char m_14;
};
Rva006F7D80::Rva006F7D80()
{
    m_14 = 0;
    m_04 = -1;
    m_0c = 0;
    m_10 = 0;
    *(const void **)this = g_00CED358;
}

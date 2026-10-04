// cl: /O1 /G7 /arch:SSE /MD
// ?rva001DD240@Rva001DD240@@QAEXPAI@Z @0x001DD240 54B unlock lane max-of-two-uints to float with constant store.
// Evidence: callers at 0x001DD533 and 0x001DD7CB context; data refs g_00BBB9AC g_00BC26EC; honest address name.
extern const float g_00BBB9AC;
struct Rva001DD276Elem
{
	char m_pad00[4];
	float m_04;
	char m_pad08[0x2C];
};
class Rva001DD240 {
public:
    float m_0;
    float m_4;
    void rva001DD240(unsigned int *p);
    void rva001DD276(unsigned char flag);
private:
    char m_pad08[0x54];
    Rva001DD276Elem *m_5C;
    Rva001DD276Elem *m_60;
    char m_pad64[0x18];
    unsigned char m_7C;
};
void Rva001DD240::rva001DD240(unsigned int *p)
{
    m_4 = g_00BBB9AC;
    unsigned int *sel = p;
    if (*sel < sel[2])
        sel = &sel[2];
    unsigned int v = *sel;
    m_0 = (float)v;
}
void Rva001DD240::rva001DD276(unsigned char flag)
{
    if (flag == m_7C)
        return;
    if (flag)
        goto set;
    {
        Rva001DD276Elem *p = m_5C;
        Rva001DD276Elem *e = m_60;
        if (p != e) {
            do {
                p->m_04 = g_00BBB9AC;
                p = (Rva001DD276Elem *)((char *)p + 0x34);
            } while (p != e);
        }
    }
set:
    m_7C = flag;
}

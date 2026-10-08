// cl: /DNDEBUG /MD
// ?rva003FAC3F@Rva003FAC3F@@QAEXXZ @0x003FAC3F 68B
// Unlock over global 0x00DFE6E8. Evidence: m_2c gate >=5, m_14 null and +0xB0
// checks, global slot 0x8c with 1 1 0 else slot 0x6c with m_2c, then m_2c=1.
class GlobalSlotTarget {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual void slot27(int a);
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34();
    virtual void slot35(int a, int b, int c);
};
extern class AudioManager *TheAudio;
struct Inner14 {
    unsigned char pad[0xB0];
    int flag;
};
class Rva003FAC3F {
public:
    void rva003FAC3F();
private:
    void *m_vptr;
    unsigned char pad04[0x10];
    Inner14 *m_14;
    unsigned char pad18[0x14];
    unsigned int m_2c;
};
void Rva003FAC3F::rva003FAC3F()
{
    GlobalSlotTarget *g = (*(GlobalSlotTarget **)&TheAudio);
    if (g == 0)
        return;
    unsigned int v = m_2c;
    if (v < 5)
        return;
    Inner14 *p = m_14;
    if (p != 0 && p->flag == 0) {
        g->slot35(1, 1, 0);
    } else {
        g->slot27(v);
    }
    m_2c = 1;
}

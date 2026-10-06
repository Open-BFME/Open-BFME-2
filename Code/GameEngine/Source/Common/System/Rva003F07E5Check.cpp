// cl: /DNDEBUG /MD /GX-
// ?rva003F07E5@Rva003F07E5@@QAE_NPAVCreateAHeroData@@PAH@Z @0x003F07E5 85B:
// __thiscall bool check: hero+0x1C must equal this else *out=5 false;
// this+0x1A3 must be zero else *out=3 false; hero+0x20 must be zero
// else *out=4 false; else *out=0 true. Sibling of Rva003F1093Check
// (out codes 2/1/0) with the extra this+0x1A3 gate. Callers 0x003F1B7C
// and 0x002B3416 pass hero and out. Honest address name.
class CreateAHeroData
{
public:
    char m_pad1C[0x1c];
    void *m_1C;
    int m_20;
};
class Rva003F07E5
{
public:
    bool rva003F07E5(CreateAHeroData *hero, int *out);
private:
    char m_pad1A3[0x1a3];
    unsigned char m_1A3;
};
bool Rva003F07E5::rva003F07E5(CreateAHeroData *hero, int *out)
{
    if (hero->m_1C != this) {
        if (out)
            *out = 5;
        return false;
    }
    if (m_1A3 != 0) {
        if (out)
            *out = 3;
        return false;
    }
    if (hero->m_20 != 0) {
        if (out)
            *out = 4;
        return false;
    }
    if (out)
        *out = 0;
    return true;
}

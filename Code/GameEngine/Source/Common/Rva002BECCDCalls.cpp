// cl: /MD
//
// ?rva002BECCD@Rva002BECCD@@QAEXMMM@Z, RVA 0x002BECCD, 67 bytes.
// Three-float method: builds a 12-byte local {a, b, 0.0f} then calls virtual
// slot 0x58 with &local and virtual slot 0x7c with c. SSE movss/xorps for the
// local plus x87 fld/fstp for the float arg under /arch:SSE.
// Evidence: caller 0x002B2A0A builds {x, y, 0.0} via sub+movss+fldz on the
// stack and calls with this from 0x00DFEF18; caller 0x003FD584 calls with the
// same singleton as this; ret 0xc for three floats.

struct Rva002BECCDVec
{
    float x;
    float y;
    float z;
};

class Rva002BECCD
{
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
    virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21();
    virtual void virt58(Rva002BECCDVec *p);
    virtual void q23(); virtual void q24(); virtual void q25(); virtual void q26();
    virtual void q27(); virtual void q28(); virtual void q29(); virtual void q30();
    virtual void virt7c(float f);
    void rva002BECCD(float a, float b, float c);
};

void Rva002BECCD::rva002BECCD(float a, float b, float c)
{
    Rva002BECCDVec local;
    local.x = a;
    local.y = b;
    local.z = 0.0f;
    virt58(&local);
    virt7c(c);
}

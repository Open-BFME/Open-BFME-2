// cl: /MD
// ?rva002B4FEB@Rva002B4FEB@@QAEXXZ @0x002B4FEB 56B.
// Chain lane; calls 0x002B41F4 and 0x002B4280 just landed plus virtuals via 0x009FEF18.
// First cond slot 0x8C calls 41F4 then second cond slot 0x90 tail-jmps 4280.
// Caller 0x002BD9B4. TU-local honest-address class.
// ?rva002B41F4@Rva002B41F4@@QAEXXZ @0x002B41F4 140B.
// ?rva002B4280@Rva002B4280@@QAEXXZ @0x002B4280 140B.
extern class Rva002D3627Host *g_00DFEF18;

class Rva002B41F4 {
public:
    void rva002B41F4();
};
class Rva002B4280 {
public:
    void rva002B4280();
};
class Rva002B4FEBGlobal {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34();
    virtual bool cond8C();
    virtual bool cond90();
};
#define TheGlobal002B4FEB (*(Rva002B4FEBGlobal **)&g_00DFEF18)
class Rva002B4FEB {
public:
    void rva002B4FEB();
};
void Rva002B4FEB::rva002B4FEB()
{
    if (TheGlobal002B4FEB->cond8C())
        ((Rva002B41F4 *)this)->rva002B41F4();
    if (TheGlobal002B4FEB->cond90())
        ((Rva002B4280 *)this)->rva002B4280();
}

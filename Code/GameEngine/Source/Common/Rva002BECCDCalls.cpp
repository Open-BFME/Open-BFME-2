// cl: /MD
// Native 0x002BECCD..0x002BED10. Caller 0x002B2A0A constructs a
// nontrivial eight-byte float pair in the first two argument words, then
// supplies a separate scalar in the third word. A three-scalar declaration
// reproduced this callee but could not reproduce that caller's copy ABI.
// The pair copy constructor and destructor recover the observed argument
// construction. The callee builds {pair.x, pair.y, 0} for virtual slot 0x58
// and passes the independent height to virtual slot 0x7c; ret 0x0c.
// Application-level names remain unknown; the pair is a partial value view.

struct RvaFloatPair {
 float x,y;
 RvaFloatPair(){}
 RvaFloatPair(const RvaFloatPair&a){x=a.x;y=a.y;}
 ~RvaFloatPair(){}
};
struct Rva002BECCDVec {float x,y,z;};
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
    void rva002BECCD(RvaFloatPair pair, float height);
};

void Rva002BECCD::rva002BECCD(RvaFloatPair pair, float height)
{
    Rva002BECCDVec local;
    local.x = pair.x;
    local.y = pair.y;
    local.z = 0.0f;
    virt58(&local);
    virt7c(height);
}

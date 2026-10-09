// cl: /O1 /MD /EHsc /DNDEBUG /G7 /arch:SSE
// Native108D33 constructor and10C785 destructor share table7CF9C4;
// WB777D40 parent construction identifies the projected-shadow-manager role.
// Address owner retained until legacy W3DProjectedShadowManager views reconcile.
// Base table7CF994 has destructor108475 plus five pure entries; its native
// destructor10846E is empty. Derived table has seven entries:10C825,10BE72,
// 10C065,10C145,108790,1087A6,10C2D5. RET boundaries and the two existing
// forwarding bodies establish the declarations below; method-purpose names
// other than the owned forwarding bodies are not asserted. These declarations
// model observed dispatch ABI; this change does not assert provider linking.
// Constructor108D33 is now owned upstream by Rva00108DBC; this TU emits only the destructor.
// Native ctor13F410 at member24 plus paired dtor69E440 and228 extent establish
// LightEnvironmentClass. Native dtor109BEB owns the two-pointer texture table,
// not the old bank's virtual destructor. Full bodies and EH graphs verified.
class Rva00108475 {
public:
 virtual ~Rva00108475() {}
 virtual void rva0010BE72()=0; virtual void *rva0010C065(void *)=0;
 virtual void *rva0010C145(void *,void *,bool,bool)=0; virtual void forward(unsigned,unsigned,unsigned)=0;
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned)=0;
};
class LightEnvironmentClass {
public: LightEnvironmentClass(); ~LightEnvironmentClass();
private: char body[0x228];
};
class BfmeThing928F {public:void bfmeOne928F();void bfmeTwo928F();};
class Rva00109DCF {public:void rva00109DCF();};
class BfmeSub928F {public: ~BfmeSub928F();};
struct Rva0010C785Ref {virtual void Release();int m_ref;};
class Rva0010C785 : public Rva00108475 {
public:
 
 Rva0010C785();
 __declspec(noinline) virtual ~Rva0010C785();
 virtual void rva0010BE72(); virtual void *rva0010C065(void *);
 virtual void *rva0010C145(void *,void *,bool,bool); virtual void forward(unsigned,unsigned,unsigned);
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned);
 virtual unsigned dispatch(unsigned,void *,unsigned,unsigned);
private:
 unsigned m_04,m_08,m_0c,m_10,m_14,m_18,m_1c; Rva0010C785Ref *m_20;
 LightEnvironmentClass m_light;
 BfmeSub928F *m_24c; unsigned m_250,m_254,m_258,m_25c,m_260,m_264,m_268,m_26c,m_270;
};

void operator delete(void *) throw();
Rva0010C785::~Rva0010C785(){
((BfmeThing928F*)this)->bfmeOne928F();
((BfmeThing928F*)this)->bfmeTwo928F();
((Rva00109DCF*)this)->rva00109DCF();
Rva0010C785Ref *p=m_20; if(p){if(--p->m_ref==0)p->Release();m_20=0;}
BfmeSub928F *q=m_24c; if(q){q->BfmeSub928F::~BfmeSub928F();::operator delete(q);}m_24c=0;
}


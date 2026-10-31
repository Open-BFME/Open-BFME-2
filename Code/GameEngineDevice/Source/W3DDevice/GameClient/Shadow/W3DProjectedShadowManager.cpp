// cl: /O1 /MD /EHsc /DNDEBUG /G7 /arch:SSE
// Native108D33 constructor and10C785 destructor share table7CF9C4;
// WB777D40 parent construction identifies the projected-shadow-manager role.
// Base table7CF994 has destructor108475 plus five pure entries; its native
// destructor10846E is empty. Derived table has seven entries:10C825,10BE72,
// 10C065,10C145,108790,1087A6,10C2D5. RET boundaries and the two existing
// forwarding bodies establish the declarations below; method-purpose names
// other than the owned forwarding bodies are not asserted. These declarations
// model observed dispatch ABI; this change does not assert provider linking.
// Constructor108D33 is defined in Rva00108DBCCtor.cpp with this same virtual view; this TU emits only the destructor.
// Native ctor13F410 at member24 plus paired dtor69E440 and228 extent establish
// LightEnvironmentClass. Native dtor109BEB owns the two-pointer texture table,
// not the old bank's virtual destructor. Full bodies and EH graphs verified.
class W3DProjectedShadow;
class RenderObjClass;
struct Rva0010C065Info;
class Shadow { public: struct ShadowTypeInfo; };
class Rva00108475 {
public:
 virtual ~Rva00108475() {}
 virtual void rva0010BE72()=0; virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *)=0;
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool)=0; virtual void forward(unsigned,unsigned,unsigned)=0;
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned)=0;
};
class LightEnvironmentClass {
public: LightEnvironmentClass(); ~LightEnvironmentClass();
private: char body[0x228];
};
class BfmeThing928F {public:void bfmeOne928F();void bfmeTwo928F();};
class Rva00109DCF {public:void rva00109DCF();};
class BfmeSub928F {public: ~BfmeSub928F();};
class CameraClass {public:virtual void Delete_This();void Release_Ref(){if(--m_ref==0)Delete_This();}int m_ref;};
class W3DShadowTextureManager;
class W3DProjectedShadowManager : public Rva00108475 {
public:
 
 W3DProjectedShadowManager();
 __declspec(noinline) virtual ~W3DProjectedShadowManager();
 virtual void rva0010BE72(); virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *);
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool); virtual void forward(unsigned,unsigned,unsigned);
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned);
 virtual W3DProjectedShadow *rva0010C2D5(int,RenderObjClass *,Shadow::ShadowTypeInfo *,Shadow::ShadowTypeInfo *);
private:
 W3DProjectedShadow *m_shadowList,*m_decalList,*m_simpleDecalList,*m_freeShadowList,*m_dualDecalList,*m_freeDualList,*m_list1C; CameraClass *m_shadowCamera;
 LightEnvironmentClass m_shadowLightEnv;
 W3DShadowTextureManager *m_W3DShadowTextureManager; unsigned m_numDecalShadows,m_vb,m_ib,m_nShadowDecalVertsInBuf,m_260,m_nShadowDecalIndicesInBuf,m_268,m_26C,m_270;
};

#include <new>
W3DProjectedShadowManager::~W3DProjectedShadowManager(){
((BfmeThing928F*)this)->bfmeOne928F();
((BfmeThing928F*)this)->bfmeTwo928F();
((Rva00109DCF*)this)->rva00109DCF();
if(m_shadowCamera){m_shadowCamera->Release_Ref();m_shadowCamera=0;}
BfmeSub928F *q=(BfmeSub928F*)m_W3DShadowTextureManager; if(q){q->BfmeSub928F::~BfmeSub928F();::operator delete(q);}m_W3DShadowTextureManager=0;
}


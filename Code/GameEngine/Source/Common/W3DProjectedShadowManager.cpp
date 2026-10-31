// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// Native unwind action76457B calls the existing base destructor10846E.
class W3DProjectedShadow;
class RenderObjClass;
struct Rva0010C065Info;
class Shadow { public: struct ShadowTypeInfo; };
class Rva00108475 {
public:
 virtual ~Rva00108475();
 virtual void rva0010BE72()=0; virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *)=0;
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool)=0; virtual void forward(unsigned,unsigned,unsigned)=0;
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned)=0;
};
class LightEnvironmentClass {
public: LightEnvironmentClass();
private: char body[0x228];
};
// The virtual view matches Rva0010C785Lifecycle.cpp (the destructor's unit),
// so both units emit the one vtable 0x7CF9C4 this constructor installs.
class W3DProjectedShadowManager : public Rva00108475 {
public:
 W3DProjectedShadowManager();
 __declspec(noinline) virtual ~W3DProjectedShadowManager();
 virtual void rva0010BE72(); virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *);
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool); virtual void forward(unsigned,unsigned,unsigned);
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned);
 virtual W3DProjectedShadow *rva0010C2D5(int,RenderObjClass *,Shadow::ShadowTypeInfo *,Shadow::ShadowTypeInfo *);
private:
 W3DProjectedShadow *m_shadowList,*m_decalList,*m_simpleDecalList,*m_freeShadowList,*m_dualDecalList,*m_freeDualList,*m_list1C;
 unsigned m_shadowCamera;
 LightEnvironmentClass m_shadowLightEnv;
 unsigned m_W3DShadowTextureManager,m_numDecalShadows,m_vb,m_ib,m_nShadowDecalVertsInBuf,m_260,m_nShadowDecalIndicesInBuf,m_268,m_26C,m_270;
};
W3DProjectedShadowManager::W3DProjectedShadowManager() {
 m_simpleDecalList=0;m_shadowList=0;m_decalList=0;m_freeShadowList=0;m_dualDecalList=0;m_freeDualList=0;m_list1C=0;
 m_numDecalShadows=0;m_W3DShadowTextureManager=0;m_shadowCamera=0;m_vb=0;m_ib=0;m_nShadowDecalVertsInBuf=0;
 m_260=0;m_nShadowDecalIndicesInBuf=0;m_268=0;m_26C=0;m_270=0;
}

// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Target: native boundary 0x00100981..0x00100A0B (138B), ret 4,
// lazy shader holder at this+0x128, "watershader.fx" / "DepthOnly",
// factory 0x00152C47, holder assignment 0x00072A94 and device lock/unlock.
// WB 0x00768DB0 carries the same literals but no recovered method name.
// Structural guide: verified ParticleSystemManager::GetShaderSetup at
// 0x001F47F8; the target's complete instruction sequence differs only in
// holder offset and relocated literals. The owning class name is unknown.
// RefCountClass, RefCountPtr and lock ABI follow that existing provider view;
// native accesses independently establish the referent count at +4.
class RefCountClass {
public:
 virtual void Delete_This();
 void Add_Ref() { ++NumRefs; }
 void Release_Ref() { --NumRefs; if (!NumRefs) Delete_This(); }
private:
 int NumRefs;
};

class FXShaderSetup : public RefCountClass {};

template<class T> class RefCountPtr {
public:
 RefCountPtr() : m_ptr(0) {}
 explicit RefCountPtr(T *p) : m_ptr(p) {}
 RefCountPtr(const RefCountPtr &o) : m_ptr(o.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
 ~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
 T *m_ptr;
};

class Rva00072A94 {
public:
 Rva00072A94 &operator=(const Rva00072A94 &);
};

namespace _STL {
template<class T> class allocator;
template<class T, class A = allocator<T> > class vector;
}
struct Rva0007BB16Record;
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(
 const char *, const char *, const _STL::vector<Rva0007BB16Record> *, int);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock {
public:
 BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
 ~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva00100981 {
public:
 RefCountPtr<FXShaderSetup> rva00100981();
private:
 char opaque00[0x128];
 RefCountPtr<FXShaderSetup> m_depthShader;
};

RefCountPtr<FXShaderSetup> Rva00100981::rva00100981()
{
 if (!m_depthShader.m_ptr) {
  BFMEDX8DeviceLock lock;
  *reinterpret_cast<Rva00072A94 *>(&m_depthShader) =
   reinterpret_cast<const Rva00072A94 &>(
    Rva00152C47_CreateFXShaderSetup("watershader.fx", "DepthOnly", 0, 4));
 }
 return m_depthShader;
}

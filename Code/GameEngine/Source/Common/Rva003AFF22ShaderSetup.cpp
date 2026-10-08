// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva003AFF22@Rva003B0401@@UAE?AV?$RefCountPtr@VFXShaderSetup@@@@XZ, retail
// 0x003AFF22..0x003AFFBE (156 bytes, EH, RET 4): slot 15 of Rva003B0401's
// vtable. It ignores this and returns the particle shader setup -- from
// TheParticleSystemManager's rowed GetShaderSetup when the manager exists,
// else an empty reference -- as a counted reference (count at +4, released
// through slot 0). The conditional's two temporaries give the flag-guarded
// cleanup retail shows. WorldBuilder's twin (0x00FAA240) is unnamed.

class RefCountClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { ++NumRefs; }
	void Release_Ref() { --NumRefs; if (!NumRefs) Delete_This(); }
private:
	int NumRefs;
};

class FXShaderSetup : public RefCountClass {};

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	RefCountPtr(const RefCountPtr &o) : m_ptr(o.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

namespace FXParticleSystem
{
class ParticleSystemManager
{
public:
	RefCountPtr<FXShaderSetup> GetShaderSetup();
};
}

extern FXParticleSystem::ParticleSystemManager *TheParticleSystemManager;

class Rva003B0401
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual RefCountPtr<FXShaderSetup> rva003AFF22();	// slot 15
};

RefCountPtr<FXShaderSetup> Rva003B0401::rva003AFF22()
{
	return TheParticleSystemManager ? TheParticleSystemManager->GetShaderSetup() : RefCountPtr<FXShaderSetup>();
}

// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?rva003AFF22@Rva003B0401@@UAE?AV?$RefCountPtr@VFXShaderSetup@@@@XZ, retail
// 0x003AFF22..0x003AFFBE (156 bytes, EH, RET 4): slot 15 of Rva003B0401's
// vtable. It ignores this and returns the particle shader setup -- from
// TheParticleSystemManager's rowed GetShaderSetup when the manager exists,
// else an empty reference -- as a counted reference (count at +4, released
// through slot 0). The conditional's two temporaries give the flag-guarded
// cleanup retail shows. WorldBuilder's twin (0x00FAA240) is unnamed.

#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

#include "../../../Libraries/Source/WWVegas/WW3D2/FXShaderSetup.h"

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	RefCountPtr(const RefCountPtr &refCountPtr) : m_ptr(refCountPtr.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
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

class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;

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
	return TheParticleSystemManager ? reinterpret_cast<FXParticleSystem::ParticleSystemManager *>(TheParticleSystemManager)->GetShaderSetup() : RefCountPtr<FXShaderSetup>();
}

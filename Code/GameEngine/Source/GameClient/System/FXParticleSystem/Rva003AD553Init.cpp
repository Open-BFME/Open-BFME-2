// cl: /O1 /EHs-c-
// ?Rva003AD553Init@@YAXXZ @0x003AD553 33B guarded initializer calling rowed OrthoEmissionVelocity getInstance at 0x003AB053 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8066 (RVA 0x007B8066 ret). Evidence: caller staticInitModules at 0x003AE3CC; prev 0x003AD532 Rva003AD532Init; guard data VA 0x00E02C10.
namespace FXParticleSystem
{
struct OrthoEmissionVelocityModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef OrthoEmissionVelocityModuleTag OrthoTag;
template <> class ConcreteModuleClass<OrthoTag>
{
public:
	static const ConcreteModuleClass<OrthoTag> &getInstance();
};
}
struct Holder003AD553
{
	Holder003AD553() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::OrthoTag>::getInstance(); }
	~Holder003AD553();
};
void __cdecl Rva003AD553Init()
{
	static Holder003AD553 s_holder;
}

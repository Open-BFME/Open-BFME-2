// cl: /EHs-c-
// ?Rva003AD4CFInit@@YAXXZ @0x003AD4CF 33B guarded initializer calling rowed DefaultModuleTag7 getInstance at 0x003AAF21 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB806A (RVA 0x007B806A ret). Evidence: caller staticInitModules at 0x003AE39A; prev 0x003AD4AE Rva003AD4AEInit; guard data VA 0x00E02C00.
namespace FXParticleSystem
{
template <int N> class DefaultModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef DefaultModuleTag<7> Tag7;
template <> class ConcreteModuleClass<Tag7>
{
public:
	static const ConcreteModuleClass<Tag7> &getInstance();
};
}
struct Holder003AD4CF
{
	Holder003AD4CF() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::Tag7>::getInstance(); }
	~Holder003AD4CF();
};
void __cdecl Rva003AD4CFInit()
{
	static Holder003AD4CF s_holder;
}

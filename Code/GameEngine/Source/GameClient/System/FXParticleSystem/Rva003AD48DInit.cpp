// cl: /O1 /EHs-c-
// ?Rva003AD48DInit@@YAXXZ @0x003AD48D 33B guarded initializer calling rowed DefaultModuleTag3 getInstance at 0x003AACCF then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB806C (RVA 0x007B806C ret). Evidence: caller staticInitModules at 0x003AE390; prev 0x003AD46C Rva003AD46CInit; guard data VA 0x00E02BF8.
namespace FXParticleSystem
{
template <int N> class DefaultModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef DefaultModuleTag<3> Tag3;
template <> class ConcreteModuleClass<Tag3>
{
public:
	static const ConcreteModuleClass<Tag3> &getInstance();
};
}
struct Holder003AD48D
{
	Holder003AD48D() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::Tag3>::getInstance(); }
	~Holder003AD48D();
};
void __cdecl Rva003AD48DInit()
{
	static Holder003AD48D s_holder;
}

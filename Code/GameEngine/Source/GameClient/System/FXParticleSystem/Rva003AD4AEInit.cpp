// cl: /EHs-c-
// ?Rva003AD4AEInit@@YAXXZ @0x003AD4AE 33B guarded initializer calling rowed DefaultModuleTag2 getInstance at 0x003AADF8 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB806B (RVA 0x007B806B ret). Evidence: caller staticInitModules at 0x003AE395; prev 0x003AD48D Rva003AD48DInit; guard data VA 0x00E02BFC.
namespace FXParticleSystem
{
template <int N> class DefaultModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef DefaultModuleTag<2> Tag2;
template <> class ConcreteModuleClass<Tag2>
{
public:
	static const ConcreteModuleClass<Tag2> &getInstance();
};
}
struct Holder003AD4AE
{
	Holder003AD4AE() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::Tag2>::getInstance(); }
	~Holder003AD4AE();
};
void __cdecl Rva003AD4AEInit()
{
	static Holder003AD4AE s_holder;
}

// cl: /O1 /EHs-c-
// ?Rva003AD46CInit@@YAXXZ @0x003AD46C 33B guarded initializer calling rowed DefaultModuleTag0 getInstance at 0x003AABA6 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB806D (RVA 0x007B806D ret). Evidence: caller staticInitModules at 0x003AE386; prev 0x003AD44B Rva003AD44BInit; guard data VA 0x00E02BF4.
namespace FXParticleSystem
{
template <int N> class DefaultModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef DefaultModuleTag<0> Tag0;
template <> class ConcreteModuleClass<Tag0>
{
public:
	static const ConcreteModuleClass<Tag0> &getInstance();
};
}
struct Holder003AD46C
{
	Holder003AD46C() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::Tag0>::getInstance(); }
	~Holder003AD46C();
};
void __cdecl Rva003AD46CInit()
{
	static Holder003AD46C s_holder;
}

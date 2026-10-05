// cl: /O1 /EHs-c-
// ?Rva003AD44BInit@@YAXXZ @0x003AD44B 33B guarded initializer calling rowed DefaultModuleTag1 getInstance at 0x003AAA7D then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB806E (RVA 0x007B806E ret). Evidence: caller staticInitModules at 0x003AE381; prev 0x003AD3F2 getClass in NamedModuleClassInstances.cpp; next 0x003ADCE5 ConstIntGetters4.cpp; guard data VA 0x00E02BF0.
namespace FXParticleSystem
{
template <int N> class DefaultModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef DefaultModuleTag<1> Tag1;
template <> class ConcreteModuleClass<Tag1>
{
public:
	static const ConcreteModuleClass<Tag1> &getInstance();
};
}
struct Holder003AD44B
{
	Holder003AD44B() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::Tag1>::getInstance(); }
	~Holder003AD44B();
};
void __cdecl Rva003AD44BInit()
{
	static Holder003AD44B s_holder;
}

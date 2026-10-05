// cl: /O1 /EHs-c-
// ?Rva003AD5F8Init@@YAXXZ @0x003AD5F8 33B guarded initializer calling rowed PointEmissionVolume getInstance at 0x003AB3AA then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8061 (RVA 0x007B8061 ret). Evidence: caller staticInitModules at 0x003AE3E5; prev 0x003AD5D7 Rva003AD5D7Init; guard data VA 0x00E02C24.
namespace FXParticleSystem
{
struct PointEmissionVolumeModuleTag
{
};
template <class Tag> class ConcreteModuleClass;
typedef PointEmissionVolumeModuleTag PointTag;
template <> class ConcreteModuleClass<PointTag>
{
public:
	static const ConcreteModuleClass<PointTag> &getInstance();
};
}
struct Holder003AD5F8
{
	Holder003AD5F8() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::PointTag>::getInstance(); }
	~Holder003AD5F8();
};
void __cdecl Rva003AD5F8Init()
{
	static Holder003AD5F8 s_holder;
}

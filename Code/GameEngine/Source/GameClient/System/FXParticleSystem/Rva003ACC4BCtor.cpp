// cl: /O1 /MD
// ??0Rva003ACC4B@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@FXParticleSystem@@PBVPointEmissionVolumeModuleTemplate@2@@Z @0x003ACC4B 49B
// Chain ctor calling rowed PointEmissionVolumeModule base 0x003ABF85 then vtable
// plus three immediates. Evidence: call target rowed; stores match retail order
// vtable s_slot g_00C1C72C g_00C1CB24; caller at 0x003AD283.
extern const void *const g_00C1CB34[];
extern "C" void *s_slot3E4first;
extern const void *const g_00C1C72C[];
extern const void *const g_00C1CB24[];
namespace FXParticleSystem
{
class ParticleSystem;
template <class T> class TrackingPtr
{
};
class PointEmissionVolumeModuleTemplate;
class PointEmissionVolumeModule
{
public:
	PointEmissionVolumeModule(TrackingPtr<ParticleSystem> &system, const PointEmissionVolumeModuleTemplate *module_template);
};
}
class __declspec(novtable) Rva003ACC4B : public FXParticleSystem::PointEmissionVolumeModule
{
public:
	Rva003ACC4B(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> &system, const FXParticleSystem::PointEmissionVolumeModuleTemplate *module_template);
};
Rva003ACC4B::Rva003ACC4B(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> &system, const FXParticleSystem::PointEmissionVolumeModuleTemplate *module_template)
	: FXParticleSystem::PointEmissionVolumeModule(system, module_template)
{
	*(void **)this = (void *)g_00C1CB34;
	*(void **)((char *)this + 0x14) = (void *)&s_slot3E4first;
	*(void **)((char *)this + 0x18) = (void *)g_00C1C72C;
	*(void **)((char *)this + 0x1C) = (void *)g_00C1CB24;
}

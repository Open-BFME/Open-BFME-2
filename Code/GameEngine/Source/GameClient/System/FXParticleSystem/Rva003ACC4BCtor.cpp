// cl: /MD
// ??0Rva003ACC4B@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@FXParticleSystem@@PBVPointEmissionVolumeModuleTemplate@2@@Z @0x003ACC4B 49B
// Chain ctor calling rowed PointEmissionVolumeModule base 0x003ABF85 then vtable
// plus three immediates. Evidence: call target rowed; stores match retail order
// vtable s_slot g_00C1C72C g_00C1CB24; caller at 0x003AD283.
// The retail table at RVA 0x0081CB34: 8 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD2AE@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@Rva0055CA8A@@MAEXPAVXfer@@@Z")();
void __identifier("?Rva0055CAEFDraw@@YGXMMM@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ")();
void __identifier("?rva0055CB45@Rva0055CB45@@QAE?AUCoord3D0055CB45@@IIII@Z")();
}
extern const void *const g_00C1CB34[8] = {
	(const void *)&__identifier("??_GRva003AD2AE@@UAEPAXI@Z"), // slot 0 0x003AD42F
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?xfer@Rva0055CA8A@@MAEXPAVXfer@@@Z"), // slot 3 0x0055CA8A
	(const void *)&__identifier("?Rva0055CAEFDraw@@YGXMMM@Z"), // slot 4 0x0055CAEF
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ"), // slot 6 0x003ABEFD
	(const void *)&__identifier("?rva0055CB45@Rva0055CB45@@QAE?AUCoord3D0055CB45@@IIII@Z"), // slot 7 0x0055CB45
};
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BIntermediate3AFC6FC@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BEmissionVolumeInfo4AA@FXParticleSystem@@@")[];
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
	*(void **)((char *)this + 0x14) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003AF47D@@6BIntermediate3AFC6FC@@@");
	*(void **)((char *)this + 0x1C) = (void *)__identifier("??_7Rva003AF47D@@6BEmissionVolumeInfo4AA@FXParticleSystem@@@");
}

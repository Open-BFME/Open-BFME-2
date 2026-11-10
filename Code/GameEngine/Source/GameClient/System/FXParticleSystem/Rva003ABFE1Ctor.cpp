// cl: /DNDEBUG /MD /EHsc
// ??0Rva003ABFE1@@QAE@PAX0@Z @0x003ABFE1 75B
// Unlock lane: ctor calling pinned DefaultParticleModule 0x003ABF54 plus rowed
// LineEmission copy 0x003A653B with branchless arg2+8 select then four
// immediates (vtable g_00C1C750 member vtable g_00C1C770 s_slot at +0x14 and
// g_ data at +0x18). Evidence: neg sbb and select; neighbours /O1.
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7Rva003AF5AC@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF5AC@@6BLineEmissionVolumeInfo@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@")[];
#include "../../../../Include/GameClient/LineEmissionVolumeInfo.h"
namespace FXParticleSystem
{
template <int N> class DefaultParticleModule
{
public:
	DefaultParticleModule(void *a, void *b);
	virtual void baseSlot();
private:
	char m_pad[0x14 - 4];
};
}
class __declspec(novtable) Rva003ABFE1 : public FXParticleSystem::DefaultParticleModule<5>
{
public:
	Rva003ABFE1(void *a, void *b);
private:
	void *m_14;
	void *m_18;
	FXParticleSystem::LineEmissionVolumeInfo m_1C;
};
Rva003ABFE1::Rva003ABFE1(void *a, void *b)
	: FXParticleSystem::DefaultParticleModule<5>(a, b)
	, m_1C(*(FXParticleSystem::LineEmissionVolumeInfo *)(b ? (char *)b + 8 : 0))
{
	*(void **)&m_1C = (void *)__identifier("??_7Rva003AF5AC@@6BLineEmissionVolumeInfo@FXParticleSystem@@@");
	*(void **)this = (void *)__identifier("??_7Rva003AF5AC@@6BDefaultModuleHeadBase@@@");
	m_14 = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	m_18 = (void *)__identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@");
}

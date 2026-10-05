// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva003AC0DA@@QAE@PAX0@Z @0x003AC0DA 75B
// Unlock lane: ctor calling pinned DefaultParticleModule<5> 0x003ABF54 plus rowed
// LineEmission copy 0x003A653B with branchless arg2+8 select then four
// immediates (vtable g_00C1C7EC member vtable g_00C1C80C s_slot at +0x14 and
// g_00C1C7E8 at +0x18). Evidence: neg sbb and select; sibling Rva003ABFE1Ctor.
extern "C" void *s_slot3E4first;
extern const void *const g_00C1C7EC[];
extern const void *const g_00C1C80C[];
extern const void *const g_00C1C7E8[];
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
class LineEmissionVolumeInfo
{
public:
	LineEmissionVolumeInfo(const LineEmissionVolumeInfo &other);
private:
	char m_pad[4];
};
}
class __declspec(novtable) Rva003AC0DA : public FXParticleSystem::DefaultParticleModule<5>
{
public:
	Rva003AC0DA(void *a, void *b);
private:
	void *m_14;
	void *m_18;
	FXParticleSystem::LineEmissionVolumeInfo m_1C;
};
Rva003AC0DA::Rva003AC0DA(void *a, void *b)
	: FXParticleSystem::DefaultParticleModule<5>(a, b)
	, m_1C(*(FXParticleSystem::LineEmissionVolumeInfo *)(b ? (char *)b + 8 : 0))
{
	*(void **)&m_1C = (void *)g_00C1C80C;
	*(void **)this = (void *)g_00C1C7EC;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1C7E8;
}

// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva003ABFE1@@QAE@PAX0@Z @0x003ABFE1 75B
// Unlock lane: ctor calling pinned DefaultParticleModule 0x003ABF54 plus rowed
// LineEmission copy 0x003A653B with branchless arg2+8 select then four
// immediates (vtable g_00C1C750 member vtable g_00C1C770 s_slot at +0x14 and
// g_ data at +0x18). Evidence: neg sbb and select; neighbours /O1.
extern "C" void *s_slot3E4first;
extern const void *const g_00C1C750[];
extern const void *const g_00C1C770[];
extern const void *const g_00C1D788[];
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
	*(void **)&m_1C = (void *)g_00C1C770;
	*(void **)this = (void *)g_00C1C750;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1D788;
}

// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: SphericalEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// SphericalEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc40 (retail .rdata value -83).
extern "C" char SphericalEmissionVelocityModuleTemplate_cvtbl0 = -83;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// SphericalEmissionVelocityModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bc50 (retail .rdata value 125).
extern "C" char SphericalEmissionVelocityModuleTemplate_csub_vtbl = 125;

class SphericalEmissionVelocityModuleTemplate
{
public:
	SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate(
	const SphericalEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	SphericalEmissionVelocityInfo *sub = (SphericalEmissionVelocityInfo *)((char *)this + 8);
	sub->SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo(*(const SphericalEmissionVelocityInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &SphericalEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &SphericalEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _SphericalEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

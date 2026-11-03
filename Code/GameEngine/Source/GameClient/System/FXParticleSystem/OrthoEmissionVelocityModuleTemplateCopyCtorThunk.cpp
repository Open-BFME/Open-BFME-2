// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: OrthoEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/OrthoEmissionVelocityInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// OrthoEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc10 (retail .rdata value -44).
extern "C" char OrthoEmissionVelocityModuleTemplate_cvtbl0 = -44;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// OrthoEmissionVelocityModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bc20 (retail .rdata value -35).
extern "C" char OrthoEmissionVelocityModuleTemplate_csub_vtbl = -35;

class OrthoEmissionVelocityModuleTemplate
{
public:
	OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityModuleTemplate::OrthoEmissionVelocityModuleTemplate(
	const OrthoEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	OrthoEmissionVelocityInfo *sub = (OrthoEmissionVelocityInfo *)((char *)this + 8);
	sub->OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo(*(const OrthoEmissionVelocityInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &OrthoEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &OrthoEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _OrthoEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: BoxEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/BoxEmissionVolumeInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// BoxEmissionVolumeModuleTemplate_cvtbl0: matched references place it at VA 0xc1bb50 (retail .rdata value -99).
extern "C" char BoxEmissionVolumeModuleTemplate_cvtbl0 = -99;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// BoxEmissionVolumeModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bb40 (retail .rdata value -115).
extern "C" char BoxEmissionVolumeModuleTemplate_csub_vtbl = -115;

class BoxEmissionVolumeModuleTemplate
{
public:
	BoxEmissionVolumeModuleTemplate(const BoxEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0BoxEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
BoxEmissionVolumeModuleTemplate::BoxEmissionVolumeModuleTemplate(
	const BoxEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	BoxEmissionVolumeInfo *sub = (BoxEmissionVolumeInfo *)((char *)this + 8);
	sub->BoxEmissionVolumeInfo::BoxEmissionVolumeInfo(*(const BoxEmissionVolumeInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &BoxEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &BoxEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _BoxEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

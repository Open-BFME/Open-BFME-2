// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: PointEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/EmissionVolumeInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// PointEmissionVolumeModuleTemplate_cvtbl0: matched references place it at VA 0xc1baf0 (retail .rdata value -16).
extern "C" char PointEmissionVolumeModuleTemplate_cvtbl0 = -16;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// PointEmissionVolumeModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bae0 (retail .rdata value -91).
extern "C" char PointEmissionVolumeModuleTemplate_csub_vtbl = -91;

class PointEmissionVolumeModuleTemplate
{
public:
	PointEmissionVolumeModuleTemplate(const PointEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
PointEmissionVolumeModuleTemplate::PointEmissionVolumeModuleTemplate(
	const PointEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	EmissionVolumeInfo *sub = (EmissionVolumeInfo *)((char *)this + 8);
	sub->EmissionVolumeInfo::EmissionVolumeInfo(*(const EmissionVolumeInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &PointEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &PointEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _PointEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

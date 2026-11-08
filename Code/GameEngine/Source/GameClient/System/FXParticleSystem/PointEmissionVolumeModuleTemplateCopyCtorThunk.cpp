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


// The tables are retail's exported names, at retail's addresses (reverse/exports.csv).
extern "C" const void *const __identifier("??_7PointEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@")[];
extern "C" char __identifier("?vftable_0112B89C@@3HA");
extern "C" const void *const __identifier("??_7PointEmissionVolumeModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(void **)sub = (void *)__identifier("??_7PointEmissionVolumeModuleTemplate@FXParticleSystem@@6B@");
	m_v0 = (void *)__identifier("??_7PointEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _PointEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

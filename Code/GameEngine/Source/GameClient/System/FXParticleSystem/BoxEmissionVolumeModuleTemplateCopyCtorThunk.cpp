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


// The tables are retail's exported names, at retail's addresses (reverse/exports.csv).
extern "C" const void *const __identifier("??_7BoxEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@")[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7BoxEmissionVolumeModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(void **)sub = (void *)__identifier("??_7BoxEmissionVolumeModuleTemplate@FXParticleSystem@@6B@");
	m_v0 = (void *)__identifier("??_7BoxEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
	m_v4 = &__identifier("??_7Rva003F498ACallback@@6B@");
}
}
// _BoxEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ??_7Rva003F498ACallback@@6B@.

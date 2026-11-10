// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: LineEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

// LineEmissionVolumeModuleTemplate sub vtbl at VA 0x00C1BB10, outer at 0x00C1BB20;
// +4 slot reuses 0x00C1C780 at VA 0x00C1C780.
extern "C" const void *const __identifier("??_7LineEmissionVolumeModuleTemplate@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7LineEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@")[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

#include "../../../../Include/GameClient/LineEmissionVolumeInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


class LineEmissionVolumeModuleTemplate
{
public:
	LineEmissionVolumeModuleTemplate(const LineEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0LineEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LineEmissionVolumeModuleTemplate::LineEmissionVolumeModuleTemplate(
	const LineEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LineEmissionVolumeInfo *sub = (LineEmissionVolumeInfo *)((char *)this + 8);
	sub->LineEmissionVolumeInfo::LineEmissionVolumeInfo(*(const LineEmissionVolumeInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = (void *)__identifier("??_7LineEmissionVolumeModuleTemplate@FXParticleSystem@@6B@");
	m_v0 = (void *)__identifier("??_7LineEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
	m_v4 = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
}
}

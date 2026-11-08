// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: CylinderEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/LineEmissionVolumeInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

// Retail's sub copy is the rowed LineEmissionVolumeInfo copy ctor at 0x003A653B.

// The three vftables (VA 0xc1bb90, 0xc1c780, 0xc1bb10) are the class's own,
// emitted by FXParticleSystem.cpp; __identifier spells those symbols exactly.
extern "C" char __identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
extern "C" char __identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6B?$CategoryModuleInfo@$04@1@@");
extern "C" char __identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6B@");

class CylinderEmissionVolumeModuleTemplate
{
public:
	CylinderEmissionVolumeModuleTemplate(const CylinderEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
CylinderEmissionVolumeModuleTemplate::CylinderEmissionVolumeModuleTemplate(
	const CylinderEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LineEmissionVolumeInfo *sub = (LineEmissionVolumeInfo *)((char *)this + 8);
	sub->LineEmissionVolumeInfo::LineEmissionVolumeInfo(*(const LineEmissionVolumeInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &__identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6B@");
	m_v0 = &__identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
	m_v4 = &__identifier("??_7CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@6B?$CategoryModuleInfo@$04@1@@");
}
}

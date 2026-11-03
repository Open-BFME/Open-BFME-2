// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: TerrainFireEmissionModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/TerrainFireEmissionInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// TerrainFireEmissionModuleTemplate_cvtbl0: matched references place it at VA 0xc1bbe0 (retail .rdata value -123).
extern "C" char TerrainFireEmissionModuleTemplate_cvtbl0 = -123;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// TerrainFireEmissionModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bbf0 (retail .rdata value 77).
extern "C" char TerrainFireEmissionModuleTemplate_csub_vtbl = 77;

class TerrainFireEmissionModuleTemplate
{
public:
	TerrainFireEmissionModuleTemplate(const TerrainFireEmissionModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0TerrainFireEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
TerrainFireEmissionModuleTemplate::TerrainFireEmissionModuleTemplate(
	const TerrainFireEmissionModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	TerrainFireEmissionInfo *sub = (TerrainFireEmissionInfo *)((char *)this + 8);
	sub->TerrainFireEmissionInfo::TerrainFireEmissionInfo(*(const TerrainFireEmissionInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &TerrainFireEmissionModuleTemplate_csub_vtbl;
	m_v0 = &TerrainFireEmissionModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _TerrainFireEmissionModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

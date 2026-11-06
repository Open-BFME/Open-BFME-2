// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: OutwardEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

// Declared call view only: the owned native constructor receives this+8 and a reference.
class OutwardEmissionVelocityInfo
{
public:
	OutwardEmissionVelocityInfo(const OutwardEmissionVelocityInfo &that);
};

// OutwardEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bca0 (retail .rdata value 20).
extern "C" char OutwardEmissionVelocityModuleTemplate_cvtbl0 = 20;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// Retail shares the 6-byte sub vtable at 0x0081BC80 with the cylindrical
// template; CylindricalEmissionVelocityModuleTemplateCopyCtorThunk.cpp defines it.
extern "C" char CylindricalEmissionVelocityModuleTemplate_csub_vtbl;

class OutwardEmissionVelocityModuleTemplate
{
public:
	OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OutwardEmissionVelocityModuleTemplate::OutwardEmissionVelocityModuleTemplate(
	const OutwardEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	OutwardEmissionVelocityInfo *sub =
		(OutwardEmissionVelocityInfo *)((char *)this + 8);
	sub->OutwardEmissionVelocityInfo::OutwardEmissionVelocityInfo(*static_cast<const OutwardEmissionVelocityInfo *>(sub_src));
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &CylindricalEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &OutwardEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _OutwardEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

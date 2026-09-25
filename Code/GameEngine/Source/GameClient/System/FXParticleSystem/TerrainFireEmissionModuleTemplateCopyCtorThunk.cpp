// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: TerrainFireEmissionModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class TerrainFireEmissionModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class TerrainFireEmissionModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char TerrainFireEmissionModuleTemplate_cvtbl0;
extern "C" char TerrainFireEmissionModuleTemplate_cvtbl4;
extern "C" char TerrainFireEmissionModuleTemplate_csub_vtbl;

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
	((TerrainFireEmissionModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	TerrainFireEmissionModuleTemplateSubCopyShim *sub =
		(TerrainFireEmissionModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &TerrainFireEmissionModuleTemplate_csub_vtbl;
	m_v0 = &TerrainFireEmissionModuleTemplate_cvtbl0;
	m_v4 = &TerrainFireEmissionModuleTemplate_cvtbl4;
}
}

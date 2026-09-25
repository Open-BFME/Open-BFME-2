// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: LineEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class LineEmissionVolumeModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class LineEmissionVolumeModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char LineEmissionVolumeModuleTemplate_cvtbl0;
extern "C" char LineEmissionVolumeModuleTemplate_cvtbl4;
extern "C" char LineEmissionVolumeModuleTemplate_csub_vtbl;

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
	((LineEmissionVolumeModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LineEmissionVolumeModuleTemplateSubCopyShim *sub =
		(LineEmissionVolumeModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &LineEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &LineEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &LineEmissionVolumeModuleTemplate_cvtbl4;
}
}

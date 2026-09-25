// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: BoxEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class BoxEmissionVolumeModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class BoxEmissionVolumeModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char BoxEmissionVolumeModuleTemplate_cvtbl0;
extern "C" char BoxEmissionVolumeModuleTemplate_cvtbl4;
extern "C" char BoxEmissionVolumeModuleTemplate_csub_vtbl;

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
	((BoxEmissionVolumeModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	BoxEmissionVolumeModuleTemplateSubCopyShim *sub =
		(BoxEmissionVolumeModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &BoxEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &BoxEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &BoxEmissionVolumeModuleTemplate_cvtbl4;
}
}

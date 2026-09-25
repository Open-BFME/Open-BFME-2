// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: PointEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class PointEmissionVolumeModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class PointEmissionVolumeModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char PointEmissionVolumeModuleTemplate_cvtbl0;
extern "C" char PointEmissionVolumeModuleTemplate_cvtbl4;
extern "C" char PointEmissionVolumeModuleTemplate_csub_vtbl;

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
	((PointEmissionVolumeModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	PointEmissionVolumeModuleTemplateSubCopyShim *sub =
		(PointEmissionVolumeModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &PointEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &PointEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &PointEmissionVolumeModuleTemplate_cvtbl4;
}
}

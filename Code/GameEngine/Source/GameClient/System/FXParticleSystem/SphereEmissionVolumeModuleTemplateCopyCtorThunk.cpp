// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: SphereEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class SphereEmissionVolumeModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class SphereEmissionVolumeModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl0;
extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl4;
extern "C" char SphereEmissionVolumeModuleTemplate_csub_vtbl;

class SphereEmissionVolumeModuleTemplate
{
public:
	SphereEmissionVolumeModuleTemplate(const SphereEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeModuleTemplate::SphereEmissionVolumeModuleTemplate(
	const SphereEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((SphereEmissionVolumeModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	SphereEmissionVolumeModuleTemplateSubCopyShim *sub =
		(SphereEmissionVolumeModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &SphereEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &SphereEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &SphereEmissionVolumeModuleTemplate_cvtbl4;
}
}

// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: CylinderEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class CylinderEmissionVolumeModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class CylinderEmissionVolumeModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char CylinderEmissionVolumeModuleTemplate_cvtbl0;
extern "C" char CylinderEmissionVolumeModuleTemplate_cvtbl4;
extern "C" char CylinderEmissionVolumeModuleTemplate_csub_vtbl;

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
	((CylinderEmissionVolumeModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	CylinderEmissionVolumeModuleTemplateSubCopyShim *sub =
		(CylinderEmissionVolumeModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &CylinderEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &CylinderEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &CylinderEmissionVolumeModuleTemplate_cvtbl4;
}
}

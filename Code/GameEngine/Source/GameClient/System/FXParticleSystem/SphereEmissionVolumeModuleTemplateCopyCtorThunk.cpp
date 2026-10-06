// cl: /DNDEBUG /MD /GX- /Ob2

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

// SphereEmissionVolumeModuleTemplate_cvtbl0: matched references place it at VA 0xc1bb80 (retail .rdata value 13).
extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl0 = 13;
extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl4;
// SphereEmissionVolumeModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bb70 (retail .rdata value 37).
extern "C" char SphereEmissionVolumeModuleTemplate_csub_vtbl = 37;

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
// _SphereEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_SphereEmissionVolumeModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")

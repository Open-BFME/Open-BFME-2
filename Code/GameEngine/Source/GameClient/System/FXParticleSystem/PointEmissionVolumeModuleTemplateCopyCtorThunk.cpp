// cl: /DNDEBUG /MD /GX- /Ob2

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

// PointEmissionVolumeModuleTemplate_cvtbl0: matched references place it at VA 0xc1baf0 (retail .rdata value -16).
extern "C" char PointEmissionVolumeModuleTemplate_cvtbl0 = -16;
extern "C" char PointEmissionVolumeModuleTemplate_cvtbl4;
// PointEmissionVolumeModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bae0 (retail .rdata value -91).
extern "C" char PointEmissionVolumeModuleTemplate_csub_vtbl = -91;

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
// _PointEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_PointEmissionVolumeModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")

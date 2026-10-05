// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: LineEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

// LineEmissionVolumeModuleTemplate sub vtbl at VA 0x00C1BB10, outer at 0x00C1BB20;
// +4 slot reuses s_slot3E4first at VA 0x00C1C780 (?vftable_0112B89C).
extern const void *const g_00C1BB10[];
extern const void *const g_00C1BB20[];
extern "C" char s_slot3E4first;

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
	*(void **)sub = (void *)g_00C1BB10;
	m_v0 = (void *)g_00C1BB20;
	m_v4 = (void *)&s_slot3E4first;
}
}
// _s_slot3E4first: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_s_slot3E4first=?vftable_0112B89C@@3HA")

// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (N=2) copy ctor
// Retail: base copy; null-preserving sub at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class DefaultModuleTemplate01BaseCopyShim
{
public:
	void construct_from(const void *src);
};

class DefaultModuleTemplate01SubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

// DefaultModuleTemplate01_vtbl0: matched references place it at VA 0xc1bcf0 (retail .rdata value 6).
extern "C" char DefaultModuleTemplate01_vtbl0 = 6;
extern "C" char DefaultModuleTemplate01_vtbl4;
// DefaultModuleTemplate01_sub_vtbl: matched references place it at VA 0xc1bd00 (retail .rdata value -75).
extern "C" char DefaultModuleTemplate01_sub_vtbl = -75;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	const void *src = &that;
	((DefaultModuleTemplate01BaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	DefaultModuleTemplate01SubCopyShim *sub =
		(DefaultModuleTemplate01SubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	*(void **)sub = &DefaultModuleTemplate01_sub_vtbl;
	m_v0 = &DefaultModuleTemplate01_vtbl0;
	m_v4 = &DefaultModuleTemplate01_vtbl4;
}

template DefaultModuleTemplate<2>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
// _DefaultModuleTemplate01_vtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_DefaultModuleTemplate01_vtbl4=?vftable_0112B89C@@3HA")

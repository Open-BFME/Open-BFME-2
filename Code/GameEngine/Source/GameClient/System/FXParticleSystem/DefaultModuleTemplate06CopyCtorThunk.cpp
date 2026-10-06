// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $06 / N=7) copy ctor
// Retail: push src; base copy; three vtbl stores at +0/+4/+8.

namespace FXParticleSystem
{

class DefaultModuleTemplate7CopyCtorShim
{
public:
	void construct_from(const void *src);
};

// DefaultModuleTemplate6_vtbl0: matched references place it at VA 0xc1bfa4 (retail .rdata value -44).
extern "C" char DefaultModuleTemplate6_vtbl0 = -44;
extern "C" char DefaultModuleTemplate6_vtbl4;
// DefaultModuleTemplate6_vtbl8: matched references place it at VA 0xc1bf94 (retail .rdata value -107).
extern "C" char DefaultModuleTemplate6_vtbl8 = -107;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	void *m_v8;
};

template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	((DefaultModuleTemplate7CopyCtorShim *)this)->construct_from(&that);
	m_v0 = &DefaultModuleTemplate6_vtbl0;
	m_v4 = &DefaultModuleTemplate6_vtbl4;
	m_v8 = &DefaultModuleTemplate6_vtbl8;
}

template DefaultModuleTemplate<7>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
// _DefaultModuleTemplate6_vtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_DefaultModuleTemplate6_vtbl4=?vftable_0112B89C@@3HA")

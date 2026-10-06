// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005258B2@Rva005258B2@@QAEXPAX@Z, retail 0x005258B2 7B chain via 0x0052557E.
// Forwarder: ecx=[ecx] then tail-jmp to rowed 0x0052557E.
// Evidence: callee rowed ?OnHeroAttacked@Impl@InGameHeroSelectInterface@@QAEXPAX@Z; caller 0x002D3756 guard then jmp; prev 0x0052557E same dir.
#include "ascii_string.h"

class InGameHeroSelectInterface
{
public:
	class Impl;
};

class InGameHeroSelectInterface::Impl
{
public:
	void OnHeroAttacked(void *p);
	void rva005255E2(const AsciiString *a);
};

class Rva005258B2
{
public:
	InGameHeroSelectInterface::Impl *m_ptr;
	void rva005258B2(void *p);
	void rva005258B9(const AsciiString *a);
};

void Rva005258B2::rva005258B2(void *p)
{
	m_ptr->OnHeroAttacked(p);
}

void Rva005258B2::rva005258B9(const AsciiString *a)
{
	m_ptr->rva005255E2(a);
}

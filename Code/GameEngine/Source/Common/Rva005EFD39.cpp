// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva005EFD39@Rva005EFD39@@QAEXXZ @0x005EFD39 26B: clear of StrategicHUD::RegionDetailsArmiesMovieClip::Impl* at +0.
// Evidence: calls rowed dtor 0x005EFB05 plus rowed operator delete 0x0002FD60; caller 0x005EFDE4 tail-jmp after vtable store plus add ecx 4.
#include "RegionDetailsArmiesClipImplView.h"
void __cdecl operator delete(void *);
class Rva005EFD39
{
public:
	void rva005EFD39();
private:
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr;
};
void Rva005EFD39::rva005EFD39()
{
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *tmp = m_ptr;
	m_ptr = 0;
	if (tmp != 0)
		delete tmp;
}
class Rva005EFDDB
{
public:
	virtual ~Rva005EFDDB();
private:
	Rva005EFD39 m_04;
};
Rva005EFDDB::~Rva005EFDDB()
{
	m_04.rva005EFD39();
}

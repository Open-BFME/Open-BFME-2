// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ, retail 0x00560ABA, 39 bytes.
// Vtable slot 5 (offset 0x14) of 0x0081CC28 0x0081D3F4 0x0081CC58 0x0081D440
// 0x0081CC98 0x0081D47C 0x0081CCD8 0x0081D4B8 (classes of copy ctors
// Rva003AE43F Rva003AE465 Rva003AE4E5 Rva003AE50B Rva003AE56F Rva003AE595
// Rva003AE5F9 Rva003AE61F in ParticleModuleInfoCopyCtors.cpp).
// Lazily creates ParticleSystem via rowed Make001FCBD7 0x001FCBD7 when
// [ecx+4] is null, then copies AsciiString at sys+0x10 via rowed
// StringBase copy 0x000365F0 into hidden return pointer. Same 39B shape
// as Rva0056394AGetter with added null-guarded factory call.
#include "ascii_string.h"

class ParticleSystem
{
public:
	void *m_vptr;
	char m_pad04[0xC];
	AsciiString m_name10;
};

ParticleSystem *__cdecl Make001FCBD7();

class Rva00560ABA
{
public:
	AsciiString rva00560ABA();
private:
	void *m_vptr;
	ParticleSystem *m_sys;
};

AsciiString Rva00560ABA::rva00560ABA()
{
	ParticleSystem *sys = m_sys;
	if (!sys)
		sys = Make001FCBD7();
	return sys->m_name10;
}

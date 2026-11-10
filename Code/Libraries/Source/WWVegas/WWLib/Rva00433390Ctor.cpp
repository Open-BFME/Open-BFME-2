// cl: /Ireference/shims/bfme2_ascii /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??0Rva004333C0@@QAE@H@Z @0x00433390 48B: derived ctor installs vtable over base 0x001DA19E plus BitFlags at +0xC4 plus int at +0xC8 plus arg at +0xCC. Evidence: vtable store 0x00C3CB1C plus thiscall base 0x001DA19E plus rowed BitFlags 0x003B31AD plus ret-4 single int arg; sibling 0x00433762 family.
#include "ascii_string.h"

class Rva001DA2D5
{
public:
	virtual ~Rva001DA2D5();
	Rva001DA2D5();
private:
	char m_pad04[0xC4 - 4];
};

#include "../../../../GameEngine/Include/Common/BitFlagsTemplate.h"

class Rva004333C0 : public Rva001DA2D5
{
public:
	virtual ~Rva004333C0();
	Rva004333C0(int val);
private:
	BitFlags<11> m_flagsC4;
	int m_intC8;
	int m_intCC;
};

Rva004333C0::Rva004333C0(int val)
	: Rva001DA2D5()
{
	m_intC8 = 0;
	m_intCC = val;
}

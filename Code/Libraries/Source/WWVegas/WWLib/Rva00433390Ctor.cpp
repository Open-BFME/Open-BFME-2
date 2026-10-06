// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??0Rva00433390@@QAE@H@Z @0x00433390 48B: derived ctor installs vtable over base 0x001DA19E plus BitFlags at +0xC4 plus int at +0xC8 plus arg at +0xCC. Evidence: vtable store 0x00C3CB1C plus thiscall base 0x001DA19E plus rowed BitFlags 0x003B31AD plus ret-4 single int arg; sibling 0x00433762 family.
#include "ascii_string.h"

class Rva001DA19EBase
{
public:
	virtual ~Rva001DA19EBase();
	Rva001DA19EBase();
private:
	char m_pad04[0xC4 - 4];
};

template <int N>
class BitFlags
{
public:
	BitFlags();
private:
	unsigned int m_word;
};

class Rva00433390 : public Rva001DA19EBase
{
public:
	virtual ~Rva00433390();
	Rva00433390(int val);
private:
	BitFlags<11> m_flagsC4;
	int m_intC8;
	int m_intCC;
};

Rva00433390::Rva00433390(int val)
	: Rva001DA19EBase()
{
	m_intC8 = 0;
	m_intCC = val;
}

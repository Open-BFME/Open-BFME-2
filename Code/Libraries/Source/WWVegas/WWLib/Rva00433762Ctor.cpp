// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??0Rva004333C0@@QAE@ABVRva001DA2D5@@@Z @0x00433762 52B: derived ctor installs vtable 0x0083CB1C over base 0x004335BC plus BitFlags at plus 0xC4 plus empty AsciiString at plus 0xC8 plus pointer at plus 0xCC. Evidence: vtable store plus rowed base copy ctor 0x004335BC plus rowed BitFlags 0x003B31AD plus callers 0x0023BA13 0x0027ABDB 0x00433865 0x0043392A.
#include "ascii_string.h"

class Rva001DA2D5
{
public:
	virtual ~Rva001DA2D5();
	Rva001DA2D5(const Rva001DA2D5 &other);
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

class Rva004333C0 : public Rva001DA2D5
{
public:
	virtual ~Rva004333C0();
	Rva004333C0(const Rva001DA2D5 &src, int val);
private:
	BitFlags<11> m_flagsC4;
	AsciiString m_strC8;
	int m_unkCC;
};

Rva004333C0::Rva004333C0(const Rva001DA2D5 &src, int val)
	: Rva001DA2D5(src)
{
	m_unkCC = val;
}

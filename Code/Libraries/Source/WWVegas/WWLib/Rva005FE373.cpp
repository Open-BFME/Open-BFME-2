// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva005FE373@Rva005FE7FA@@UAEXHHHABVUnicodeString@@@Z @0x005FE373 78B via vslot 1 of vtable 0x0087A408 plus base tab update
// Evidence: vslot lane slot 1 of Rva005FE7FA vtable 0x0087A408; base call rowed 0x005FE27A; compare rowed 0x00006A7A set rowed 0x00037150 Rva005FDF83Set rowed 0x005FDF83; neighbours same flags.

#include "ascii_string.h"
#include "unicode_string.h"
struct Rva005FDF1COuter;
class UnicodeString;
namespace StrategicHUD
{
	void __cdecl SetLocalPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text);
}

struct Rva005FDF1COuter;

class Rva005FE750
{
public:
	virtual ~Rva005FE750();
	void rva005FE27A(int idx, int w0, int w1, const UnicodeString &text);
protected:
	int m_04;
	AsciiString m_08;
	char m_pad[0x28];
};

class Rva005FE7FA : public Rva005FE750
{
public:
	virtual ~Rva005FE7FA();
	virtual void rva005FE373(int idx, int w0, int w1, const UnicodeString &text);
private:
	int m_34;
	UnicodeString m_38;
};

void Rva005FE7FA::rva005FE373(int idx, int w0, int w1, const UnicodeString &text)
{
	((Rva005FE750 *)this)->rva005FE27A(idx, w0, w1, text);
	if (idx == 0)
	{
		if (text.compare(m_38) != 0)
		{
			StrategicHUD::SetLocalPlayerNameString(m_04, (Rva005FDF1COuter *)&m_08, text);
			m_38.set(text);
		}
	}
}

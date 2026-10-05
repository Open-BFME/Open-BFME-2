// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00579D96@Rva00579AB7@@QAEXM@Z @0x00579D96 98B slot 5 of 0x0086ED64.
// Float setter with change detection: if arg != m_38, fetch UnicodeString via
// rowed Rva00579995Get 0x00579995, set indexed text via rowed rva00579B17
// 0x00579B17 with index 4, then store arg to m_38. Callees rowed, vtable slot
// evidence, neighbours Rva00579AB7Dtor and Rva00579E47Delegate share /O1.
#include "ascii_string.h"
#include "unicode_string.h"

UnicodeString __cdecl Rva00579995Get(float value);

class Rva00579B17
{
public:
	void rva00579B17(int index, const UnicodeString &text);
};

class Rva00579AB7
{
public:
	void rva00579D96(float value);

private:
	void *m_vptr;
	int m_level;
	char m_name[4];
	char m_pad0C[0x38 - 0x0C];
	float m_38;
};

void Rva00579AB7::rva00579D96(float value)
{
	if (value != m_38)
	{
		((Rva00579B17 *)this)->rva00579B17(4, Rva00579995Get(value));
		m_38 = value;
	}
}

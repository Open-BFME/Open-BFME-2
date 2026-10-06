// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0057F2DE@@UAE@XZ @0x0057F2DE 111B
// Evidence: unlock lane, vtable 0x00C6F584 at [this], member dtor GameSpyLoginPreferences 0x005CAB59 at +0x58 (0x44 bytes), ReleaseTreeHintRef 0x0007DEEF on +0x9C ptr, releaseBuffer D 0x00036410 at +0xAC and G 0x00036E70 at +0xB0, base dtor pin 0x005248D0; callers 0x0043DAE0/11 0x0057F51C/28 0x004421E1/211.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();
private:
	char m_pad[0x58 - 4];
};

class GameSpyLoginPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences();
	AsciiString rva005C9FC4();
private:
	char m_pad[0x44 - 4];
};

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_ref;
};
void __fastcall ReleaseTreeHintRef00217D4C(struct TargetRef00217D4C *p);

struct TreeHintHolder00217D4C
{
	struct TargetRef00217D4C *m_ptr;
	TreeHintHolder00217D4C(TargetRef00217D4C *r)
	{
		m_ptr = r;
		if (r)
			++r->m_ref;
	}
	~TreeHintHolder00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva0057F2DE : public Rva005248D0
{
public:
	Rva0057F2DE(TargetRef00217D4C *ref);
	virtual ~Rva0057F2DE();
private:
	GameSpyLoginPreferences m_gameSpy;
	TreeHintHolder00217D4C m_holder;
	int m_a0;
	int m_a4;
	unsigned char m_a8;
	char m_padA9[3];
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

Rva0057F2DE::Rva0057F2DE(TargetRef00217D4C *ref) : m_holder(ref), m_a0(0), m_a4(0), m_a8(0)
{
	m_ascii.set(m_gameSpy.rva005C9FC4());
}

Rva0057F2DE::~Rva0057F2DE()
{
}

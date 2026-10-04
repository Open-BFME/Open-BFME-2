// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0057F2DE@@UAE@XZ @0x0057F2DE 111B
// Evidence: unlock lane, vtable 0x00C6F584 at [this], member dtor GameSpyLoginPreferences 0x005CAB59 at +0x58 (0x44 bytes), ReleaseTreeHintRef 0x0007DEEF on +0x9C ptr, releaseBuffer D 0x00036410 at +0xAC and G 0x00036E70 at +0xB0, base dtor pin 0x005248D0; callers 0x0043DAE0/11 0x0057F51C/28 0x004421E1/211.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	char m_pad[0x58 - 4];
};

class GameSpyLoginPreferences
{
public:
	virtual ~GameSpyLoginPreferences();
private:
	char m_pad[0x44 - 4];
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(struct TargetRef00217D4C *p);

struct TreeHintHolder00217D4C
{
	struct TargetRef00217D4C *m_ptr;
	~TreeHintHolder00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva0057F2DE : public Rva005248D0
{
public:
	virtual ~Rva0057F2DE();
private:
	GameSpyLoginPreferences m_gameSpy;
	TreeHintHolder00217D4C m_holder;
	char m_gap[12];
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

Rva0057F2DE::~Rva0057F2DE()
{
}

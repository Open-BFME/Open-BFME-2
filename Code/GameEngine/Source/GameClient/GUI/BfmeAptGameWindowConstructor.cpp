// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0_bfme_AptGameWindow@@QAE@PAX@Z @0x0051268C 94B ctor for 0x27C AptGameWindow via rowed base 0x00313847 plus pinned 0x002D2C34 plus vtables C659E8/C659E4 plus 270/274/278 inits evidence factory 0x002D1E55 size 0x27C and dtor 0x005126F5 same vtables
class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase(void *context);
	virtual ~BfmeAptScreenBase();
private:
	char m_pad[0x218 - 4];
};

class Rva002D2C34
{
public:
	void rva002D2C34();
};

extern const void *const g_00C659E8[];
extern const void *const g_00C659E4[];

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow(void *context);
private:
	BfmeAptScreenBase m_primary;
	char m_sec[0x58];
	int m_270;
	int m_274;
	char m_278;
};

_bfme_AptGameWindow::_bfme_AptGameWindow(void *context)
	: m_primary(context)
{
	Rva002D2C34 *sec = (Rva002D2C34 *)m_sec;
	sec->rva002D2C34();
	*(const void **)this = g_00C659E8;
	*(const void **)sec = g_00C659E4;
	m_270 = 0;
	m_274 = -1;
	m_278 = 0;
}

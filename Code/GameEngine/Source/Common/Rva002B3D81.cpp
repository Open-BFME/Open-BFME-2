// cl: /O1 /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?rva002B3D81@@YAHXZ @0x002B3D81 35B. Global int query: gate on
// pinned rva002B2BAA then on ((LANGameInfo *)TheGameInfo) (pinned LANGameInfo*),
// returning 0x7FFFFFFF on either miss, else +0x78 times
// g_Va00DBA4E4 (FramesPerSecond, signed imul).
//
// Target evidence (game.dat, read-only, capstone): frameless global
// (no this); the two misses share one mov-eax-ret tail; pinned names
// supply the callee and the globals. Identities unproven: honest
// address-derived names.
bool rva002B2BAA();
// Bind to the existing data-ledger owner; keep the retail access view local.
extern int g_Va00DBA4E4;

struct LANGameInfo
{
	unsigned char m_pad00[0x78];
	int m_78;
};
// Bind to the existing data-ledger owner; keep the retail access view local.
class GameInfo;
extern GameInfo *TheGameInfo;

// ?rva002B3D81@@YAHXZ
int rva002B3D81()
{
	if (!rva002B2BAA())
		return 0x7FFFFFFF;
	LANGameInfo *p = ((LANGameInfo *)TheGameInfo);
	if (p == 0)
		return 0x7FFFFFFF;
	return p->m_78 * g_Va00DBA4E4;
}

class Rva002B3DB2
{
public:
	int rva002B3DB2();
private:
	unsigned char m_pad00[0x100];
	unsigned int m_100;
	unsigned int m_104;
};

// ?rva002B3DB2@Rva002B3DB2@@QAEHXZ @0x002B3DB2 30B. Saturating
// remainder of the rva002B3D81 limit above over the +0x100/+0x104
// window: returns limit minus the window when the window is below the
// limit, else zero.
int Rva002B3DB2::rva002B3DB2()
{
	unsigned int diff = m_100 - m_104;
	int limit = rva002B3D81();
	if (diff >= (unsigned int)limit)
		return 0;
	return limit - diff;
}

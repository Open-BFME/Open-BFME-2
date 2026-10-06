// cl: /MD /EHsc /DNDEBUG
// ??1TeamFactory@@UAE@XZ, retail 0x003A383A, 95 bytes.
// TeamFactory dtor: stores vtables 0x0081AE2C/0x0081AE1C, calls clear via pin 0x003A2F4C, clears TheTeamFactory, destroys member at +0xB0 via rowed 0x0039FB11, restores Snapshot base BBB554 then base GameEngineDeletingBase dtor via rowed 0x001B4E74.
// Layout: GameEngineDeletingBase at +0 plus Snapshot at +0xC plus member at +0xB0 plus count. Evidence: unlock packet EH prolog plus singleton clear plus unblocks deleting dtor 0x003A398B; next Rva003A4322 dtor shares UAE pattern.
class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

extern const void *const g_00BBB554[];
inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva0039F56E
{
public:
	~Rva0039F56E();
};

class TeamFactory : public GameEngineDeletingBase, public Snapshot
{
public:
	virtual ~TeamFactory();
	void clear();
private:
	char m_pad10[0xB0 - 0x10];
	Rva0039F56E m_b0;
};

extern class TeamFactory *TheTeamFactory;

TeamFactory::~TeamFactory()
{
	clear();
	TheTeamFactory = 0;
}

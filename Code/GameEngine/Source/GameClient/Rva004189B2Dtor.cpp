// cl: /DNDEBUG /MD /EHsc
// ??1Rva004189B2@@UAE@XZ @0x004189B2 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7708 then calls rowed member dtor 0x0022DEA8 at +0xC then rowed base 0x001B4E74; caller 0x0022E026; abuts next 0x004189ED; prev Rva0041811DGet flags.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva0022DD19
{
public:
	~Rva0022DD19();
};

class Rva004189B2 : public GameEngineDeletingBase
{
public:
	virtual ~Rva004189B2();
private:
	Rva0022DD19 m_00C;
};

Rva004189B2::~Rva004189B2() {}

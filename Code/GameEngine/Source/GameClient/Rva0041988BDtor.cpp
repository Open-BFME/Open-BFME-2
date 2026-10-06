// cl: /DNDEBUG /MD /EHsc
// ??1Rva0041988B@@UAE@XZ @0x0041988B 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7778 then calls rowed member dtor 0x0022DF1A at +0xC then rowed base 0x001B4E74; caller 0x0022E0CC; same 59B EH shape as Rva004189B2.
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

class Rva0022DDAB
{
public:
	~Rva0022DDAB();
};

class Rva0041988B : public GameEngineDeletingBase
{
public:
	virtual ~Rva0041988B();
private:
	Rva0022DDAB m_00C;
};

Rva0041988B::~Rva0041988B() {}

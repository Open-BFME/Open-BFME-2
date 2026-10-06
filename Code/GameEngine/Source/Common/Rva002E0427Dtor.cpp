// cl: /DNDEBUG /MD /EHsc
// ??1Rva002E0427@@UAE@XZ @0x002E0427 81B dtor over two hash members and GameEngineDeletingBase
// Vtable 0x00BE7628 slot 0 (deleting dtor 0x0022DA4A calls here); members at +0x10
// (Rva0022CC67 dtor 0x0022CF13) and +0x24 (Rva0022366C dtor 0x0022366C) with base
// 0x001B4E74; global g_00DFF09C cleared. Evidence: chain packet callees all rowed.

extern int g_00DFF09C;

class Rva0022CC67
{
public:
	~Rva0022CC67();
private:
	char m_pad[0x14];
};

class Rva0022366C
{
public:
	~Rva0022366C();
private:
	char m_pad[0x14];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad[8];
};

class Rva002E0427 : public GameEngineDeletingBase
{
public:
	virtual ~Rva002E0427();
private:
	int m_0C;
	Rva0022CC67 m_10;
	Rva0022366C m_24;
};

Rva002E0427::~Rva002E0427()
{
	g_00DFF09C = 0;
}

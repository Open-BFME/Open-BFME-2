// cl: /DNDEBUG /MD /EHsc
// ??1Rva00359290@@UAE@XZ @0x00359290 85B.
// Virtual scalar dtor (vptr 0xC15398): vptr store, three member-dtor calls
// in reverse order through the rowed Rva00358D62/Rva00358E6A bodies, then
// the rowed GameEngineDeletingBase dtor. No new pins; the base is an opaque
// 0xC TU-local stand-in.
class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad[0xC - 4];
};

class Rva00358D62
{
public:
	~Rva00358D62();

private:
	char m_pad[12];
};

class Rva00358E6A
{
public:
	~Rva00358E6A();

private:
	char m_pad[12];
};

class Rva00359290 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00359290();

private:
	Rva00358E6A m_m0C;
	Rva00358E6A m_m18;
	Rva00358D62 m_m24;
};

Rva00359290::~Rva00359290()
{
}

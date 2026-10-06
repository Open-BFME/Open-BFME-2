// cl: /Ob2 /EHsc /MD
//
// ??1Rva00418298@@UAE@XZ @0x00418298 59B.
// Dtor storing vtable g_00BE76D0 then member +0xc and base.
// Evidence: rowed member dtor 0x0022DC62 base dtor 0x001B4E74,
// vtable store at [this], caller 0x0022DFB3.
class Rva0022DB29
{
public:
	~Rva0022DB29();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[0xC - 4];
};

class Rva00418298 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00418298();
private:
	Rva0022DB29 m_0c;
};

Rva00418298::~Rva00418298()
{
}

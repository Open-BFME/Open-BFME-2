// cl: /EHsc /MD
// ??1Rva0022CDDA@@UAE@XZ @0x0022CDDA 63B
// Virtual dtor over GameEngineDeletingBase at +0 (rowed 0x001B4E74) and
// fixed array Rva00226883 m_arr[2] at +0xC with element size 0x10 via
// ??_M (rowed vendor 0x00629110) using the rowed element dtor at
// 0x0022C612 (retail pushes thunk 0x0062CA3B which jmps there).
// Retail emits no vtable store, so derived is __declspec(novtable) like
// PillageModuleDataDtor precedent; EH prolog cookie 0xb6f8b7 matches
// sibling 0x0022C9F6. Evidence: unlock packet calls rowed base and
// rowed ??_M; ??_G caller at 0x0022CDBE proves virtualness; unblocks
// 0x0022CDBE.
class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad[8];
};

class Rva00226883
{
public:
	~Rva00226883();
private:
	void *m_head;
	int m_flag;
	int m_pad08;
	int m_pad0C;
};

class __declspec(novtable) Rva0022CDDA : public GameEngineDeletingBase
{
public:
	virtual ~Rva0022CDDA();
private:
	Rva00226883 m_arr[2];
};

Rva0022CDDA::~Rva0022CDDA()
{
}

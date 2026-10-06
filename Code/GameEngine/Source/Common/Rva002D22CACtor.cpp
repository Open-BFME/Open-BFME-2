// cl: /MD
//
// ??0Rva002D22CA@@QAE@XZ
// RVA 0x002D22AC size 30. Ctor calls GameEngineDeletingBase ctor at 0x1B4E63
// via pin then stores derived vtable 0x00802A20 and zeroes 48B tail at +0x0C
// via 12-int loop lowered to rep stosd with lea before xor. Evidence: vtable
// store names Rva002D22CA per packet; base layout 12B from
// GameEngineDeletingBaseDtor.cpp; unblocks 0x4CA3A; neighbours in
// GameEngineDeletingBaseDerived.cpp share /O1 /MD; loop (not memset) keeps
// retail lea-xor order.

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	Rva002D22CA();
	virtual ~Rva002D22CA();

private:
	char m_tail0C[48];
};

Rva002D22CA::Rva002D22CA() : GameEngineDeletingBase()
{
	for (int i = 0; i < 12; i++)
		((int *)m_tail0C)[i] = 0;
}

// cl: /MD
//
// ?rva002D2457@Rva002D22CA@@UAE_NXZ
// RVA 0x002D2457 size 135. Slot1 init of Rva002D22CA: registers 9 tables at
// +0x0C via rva002D23ED (indices 4,0,1,2,6,7,9,10,11) then tail-jmps to the
// 0x002D22D5 duplicate-unk validator for its bool result. Evidence: vtable
// slot 1 of 0x00802A20 (ctor 0x002D22AC names Rva002D22CA); 9 call targets
// all rowed rva002D23ED; tail jmp to just-landed validator row.

extern char g_009BC998[];
extern char g_009BC9C0[];
extern char g_009BCAC8[];
// g_009FF018: matched references place it at VA 0xdff018; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_009FF018[12];
extern char g_009BC890[];
extern char g_009BCBAC[];
extern char g_009BCBC4[];
extern char g_009BCBDC[];
// g_009FF00C: matched references place it at VA 0xdff00c; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_009FF00C[12];

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
	void rva002D23ED(void *table, int index);
	bool rva002D22D5();
	virtual bool rva002D2457();
};

bool Rva002D22CA::rva002D2457()
{
	rva002D23ED(g_009BC998, 4);
	rva002D23ED(g_009BC9C0, 0);
	rva002D23ED(g_009BCAC8, 1);
	rva002D23ED(g_009FF018, 2);
	rva002D23ED(g_009BC890, 6);
	rva002D23ED(g_009BCBAC, 7);
	rva002D23ED(g_009BCBC4, 9);
	rva002D23ED(g_009BCBDC, 10);
	rva002D23ED(g_009FF00C, 11);
	return rva002D22D5();
}

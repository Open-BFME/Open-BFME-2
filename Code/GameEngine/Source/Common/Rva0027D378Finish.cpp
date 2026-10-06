// ?rva0027D378@Rva0027D378@@QAEHPAXH@Z
// cl: /MD /Oy-
// Countdown on target struct: take = min(amount, target+0x28), subtract,
// if depleted call manager slot31 with target+0xC, reset via rowed
// ?rva0027D098@Rva0027D098@@QAEXXZ, then this+0x1910 = TheGameLogic+0x40.
// Evidence: calls rowed 0x0027D098 with ecx=esi; callees rowed; caller chain.
extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager0027D378
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26();
	virtual void _slot27();
	virtual void _slot28();
	virtual void _slot29();
	virtual void _slot30();
	virtual void _slot31(int a);
};

#define TheRva009FF080Manager0027D378 (*(Rva009FF080Manager0027D378 **)&g_00DFF080)

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class Rva0027D098
{
public:
	void rva0027D098();
};

struct Rva0027D378Target
{
	char m_pad00[0xc];
	int m_field0C;
	char m_pad10[0x18];
	int m_field28;
};

class Rva0027D378
{
public:
	int rva0027D378(void *p, int amount);
private:
	char m_pad00[0x1910];
	int m_1910;
};

int Rva0027D378::rva0027D378(void *p, int amount)
{
	Rva0027D378Target *s = (Rva0027D378Target *)p;
	// volatile forces the read-modify-write of the countdown field to go
	// through memory (retail: sub [esi+0x28],edi + cmp [esi+0x28],0) rather
	// than through a register copy, and puts the old value's spill first.
	volatile int *f = &s->m_field28;
	int b = *f;
	int take = *(amount < b ? &amount : &b);
	*f -= take;
	if (*f > 0)
		return take;
	TheRva009FF080Manager0027D378->_slot31(s->m_field0C);
	((Rva0027D098 *)s)->rva0027D098();
	m_1910 = TheGameLogic->m_40;
	return take;
}
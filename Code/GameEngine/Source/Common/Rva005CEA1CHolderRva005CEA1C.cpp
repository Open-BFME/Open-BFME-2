// cl: /DNDEBUG /MD /EHsc
//
// ?rva005CEA1C@Rva005CEA1CHolder@@QAEXXZ, retail 0x005cea1c, 25 bytes. Banked partial (score 0.8) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// +0x04 through its dtor, then tail-dispatch virtual slot 1 of the object at +0x1C
// when it is set.
// class-gate: allow Coord2D the body only calls the destructor through a held pointer; the banked view is byte-exact
class Coord2D
{
public:
	~Coord2D();
	float m_x;
	float m_y;
};

class Rva005CEA1CTarget
{
public:
	virtual void rva005CEA1CSlot0();
	virtual void rva005CEA1CSlot1();
};

class Rva005CEA1CHolder
{
public:
	void rva005CEA1C();

private:
	char m_pad0[4];
	Coord2D *m_point;
	char m_pad0C[0x1C - 0x08];
	Rva005CEA1CTarget *m_target;
};

void Rva005CEA1CHolder::rva005CEA1C()
{
	m_point->~Coord2D();
	Rva005CEA1CTarget *target = m_target;
	if (target != 0)
		target->rva005CEA1CSlot1();
}

// cl: /DNDEBUG /MD /EHsc
// class-gate: allow Coord2D retail calls the shared empty dtor stub ??1Coord2D at 0x004B3FD0 from this tail; the canonical header declares no user dtor
// ?rva005CEA1C@Rva005CEA1CHolder@@QAEXXZ @0x005CEA1C 25B: release the Coord2D at
// +0x04 through its dtor, then tail-dispatch virtual slot 1 of the object at +0x1C
// when it is set.
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

// ?rva005CEA1C@Rva005CEA1CHolder@@QAEXXZ @0x005CEA1C
void Rva005CEA1CHolder::rva005CEA1C()
{
	m_point->~Coord2D();
	Rva005CEA1CTarget *target = m_target;
	if (target != 0)
		target->rva005CEA1CSlot1();
}
